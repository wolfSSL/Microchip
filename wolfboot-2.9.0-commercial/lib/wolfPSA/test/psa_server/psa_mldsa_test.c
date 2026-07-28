/* psa_mldsa_test.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Coverage tests for the PSA Crypto API 1.4 ML-DSA (FIPS 204) interface.
 *
 * Cases:
 *  1. generate_key / export seed / export_public_key sizes (all three param sets)
 *  2. sign_message + verify_message roundtrip; tamper -> INVALID_SIGNATURE
 *  3. Import public key with bits=0 (inference from length); verify with it
 *  4. Deterministic vs hedged: same message, deterministic produces identical
 *     signatures, hedged produces different ones
 *  5. HashML-DSA(SHA-256): sign_message + verify_message; cross-path
 *     verify_hash (caller-hashes) and sign_hash + verify_message
 *  6. psa_sign_hash with PSA_ALG_ML_DSA -> PSA_ERROR_INVALID_ARGUMENT
 *  7. Import seed with bits=0 -> PSA_ERROR_INVALID_ARGUMENT; with bits=192 ->
 *     success, sign/verify roundtrip works
 *  8. Import seed with wrong length (31 bytes, bits=192) ->
 *     PSA_ERROR_INVALID_ARGUMENT
 */

#include "psa_api_test_user_settings.h"

#ifndef WOLFSSL_USER_SETTINGS
#define WOLFSSL_USER_SETTINGS
#endif

#include <wolfssl/wolfcrypt/settings.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <wolfpsa/psa/crypto.h>

/* -------------------------------------------------------------------------
 * Helpers (mirrors the style of psa_api_test.c)
 * ---------------------------------------------------------------------- */

static int check_status(psa_status_t st, const char *what)
{
    if (st != PSA_SUCCESS) {
        printf("FAIL: %s (status=%d)\n", what, (int)st);
        return 1;
    }
    return 0;
}

static int check_status_eq(psa_status_t st, psa_status_t expected,
                           const char *what)
{
    if (st != expected) {
        printf("FAIL: %s (status=%d expected=%d)\n", what, (int)st,
               (int)expected);
        return 1;
    }
    return 0;
}

static int check_true(int cond, const char *what)
{
    if (!cond) {
        printf("FAIL: %s\n", what);
        return 1;
    }
    return 0;
}

/* -------------------------------------------------------------------------
 * Per-parameter-set constants
 * ---------------------------------------------------------------------- */

/* ML-DSA-44 / ML-DSA-65 / ML-DSA-87 */
static const size_t g_pub_sizes[3]  = { 1312u, 1952u, 2592u };
static const size_t g_sig_sizes[3]  = { 2420u, 3309u, 4627u };
static const size_t g_bits[3]       = {  128u,  192u,  256u };

/* -------------------------------------------------------------------------
 * Reusable volatile-key attribute builder
 * ---------------------------------------------------------------------- */

static void make_mldsa_keypair_attrs(psa_key_attributes_t *attrs,
                                     size_t bits, psa_algorithm_t alg,
                                     psa_key_usage_t usage)
{
    *attrs = psa_key_attributes_init();
    psa_set_key_type(attrs, PSA_KEY_TYPE_ML_DSA_KEY_PAIR);
    psa_set_key_bits(attrs, (psa_key_bits_t)bits);
    psa_set_key_algorithm(attrs, alg);
    psa_set_key_usage_flags(attrs, usage);
    /* No psa_set_key_id / psa_set_key_lifetime -> volatile (default) */
}

/* -------------------------------------------------------------------------
 * Case 1: generate_key sizes
 * For each parameter set: export seed (32 bytes), export public key (1312/1952/2592).
 * ---------------------------------------------------------------------- */

static int test_generate_key_sizes(void)
{
#if !defined(WOLFSSL_HAVE_MLDSA)
    printf("SKIP: test_generate_key_sizes (WOLFSSL_HAVE_MLDSA not set)\n");
    return 0;
#else
    static const psa_key_usage_t usage =
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE |
        PSA_KEY_USAGE_EXPORT;
    int i;

    for (i = 0; i < 3; i++) {
        psa_key_attributes_t attrs;
        psa_key_id_t key = PSA_KEY_ID_NULL;
        uint8_t seed[64];
        uint8_t pub[2592];
        size_t seed_len = 0, pub_len = 0;
        psa_status_t st;
        char label[64];

        snprintf(label, sizeof(label), "generate_key ML-DSA-%u",
                 (unsigned)g_bits[i]);

        make_mldsa_keypair_attrs(&attrs, g_bits[i], PSA_ALG_ML_DSA, usage);
        st = psa_generate_key(&attrs, &key);
        if (check_status(st, label) != 0)
            return 1;

        snprintf(label, sizeof(label), "export_key seed ML-DSA-%u",
                 (unsigned)g_bits[i]);
        st = psa_export_key(key, seed, sizeof(seed), &seed_len);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(key);
            return 1;
        }
        snprintf(label, sizeof(label), "seed length ML-DSA-%u",
                 (unsigned)g_bits[i]);
        if (check_true(seed_len == 32u, label) != 0) {
            (void)psa_destroy_key(key);
            return 1;
        }

        snprintf(label, sizeof(label), "export_public_key ML-DSA-%u",
                 (unsigned)g_bits[i]);
        st = psa_export_public_key(key, pub, sizeof(pub), &pub_len);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(key);
            return 1;
        }
        snprintf(label, sizeof(label), "public key length ML-DSA-%u",
                 (unsigned)g_bits[i]);
        if (check_true(pub_len == g_pub_sizes[i], label) != 0) {
            (void)psa_destroy_key(key);
            return 1;
        }

        (void)psa_destroy_key(key);
    }

    printf("PASS: test_generate_key_sizes\n");
    return 0;
#endif
}

/* -------------------------------------------------------------------------
 * Case 2: sign_message / verify_message roundtrip + tamper
 * ---------------------------------------------------------------------- */

static int test_sign_verify_message(void)
{
#if !defined(WOLFSSL_HAVE_MLDSA)
    printf("SKIP: test_sign_verify_message (WOLFSSL_HAVE_MLDSA not set)\n");
    return 0;
#else
    static const psa_key_usage_t usage =
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE |
        PSA_KEY_USAGE_EXPORT;
    static const uint8_t msg[] = "PSA ML-DSA test message";
    int i;

    for (i = 0; i < 3; i++) {
        psa_key_attributes_t attrs;
        psa_key_id_t key = PSA_KEY_ID_NULL;
        /* ML-DSA-87 signature is 4627 bytes — allocate for the largest */
        uint8_t sig[4627];
        size_t sig_len = 0;
        psa_status_t st;
        char label[64];

        snprintf(label, sizeof(label), "sign_message ML-DSA-%u",
                 (unsigned)g_bits[i]);

        make_mldsa_keypair_attrs(&attrs, g_bits[i], PSA_ALG_ML_DSA, usage);
        st = psa_generate_key(&attrs, &key);
        if (check_status(st, label) != 0)
            return 1;

        st = psa_sign_message(key, PSA_ALG_ML_DSA, msg, sizeof(msg) - 1,
                              sig, sizeof(sig), &sig_len);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(key);
            return 1;
        }
        snprintf(label, sizeof(label), "signature length ML-DSA-%u",
                 (unsigned)g_bits[i]);
        if (check_true(sig_len == g_sig_sizes[i], label) != 0) {
            (void)psa_destroy_key(key);
            return 1;
        }

        snprintf(label, sizeof(label), "verify_message ML-DSA-%u",
                 (unsigned)g_bits[i]);
        st = psa_verify_message(key, PSA_ALG_ML_DSA, msg, sizeof(msg) - 1,
                                sig, sig_len);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(key);
            return 1;
        }

        /* Tamper: flip a bit in the middle of the signature */
        sig[sig_len / 2] ^= 0x01u;
        snprintf(label, sizeof(label), "verify_message tampered ML-DSA-%u",
                 (unsigned)g_bits[i]);
        st = psa_verify_message(key, PSA_ALG_ML_DSA, msg, sizeof(msg) - 1,
                                sig, sig_len);
        if (check_status_eq(st, PSA_ERROR_INVALID_SIGNATURE, label) != 0) {
            (void)psa_destroy_key(key);
            return 1;
        }

        (void)psa_destroy_key(key);
    }

    printf("PASS: test_sign_verify_message\n");
    return 0;
#endif
}

/* -------------------------------------------------------------------------
 * Case 3: Import public key (bits=0, infer from length), verify with it
 * ---------------------------------------------------------------------- */

static int test_import_public_key(void)
{
#if !defined(WOLFSSL_HAVE_MLDSA)
    printf("SKIP: test_import_public_key (WOLFSSL_HAVE_MLDSA not set)\n");
    return 0;
#else
    /* Use the middle parameter set (ML-DSA-65, bits=192) for this test */
    static const size_t idx = 1; /* bits=192, pub=1952, sig=3309 */
    static const psa_key_usage_t usage_kp =
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE |
        PSA_KEY_USAGE_EXPORT;
    static const uint8_t msg[] = "ML-DSA public key import test";

    psa_key_attributes_t kp_attrs;
    psa_key_id_t kp = PSA_KEY_ID_NULL;
    psa_key_id_t pub_key = PSA_KEY_ID_NULL;
    uint8_t pub[2592];
    size_t pub_len = 0;
    uint8_t sig[4627];
    size_t sig_len = 0;
    psa_key_attributes_t pub_attrs;
    psa_key_attributes_t got_attrs;
    psa_status_t st;

    make_mldsa_keypair_attrs(&kp_attrs, g_bits[idx], PSA_ALG_ML_DSA,
                             usage_kp);
    st = psa_generate_key(&kp_attrs, &kp);
    if (check_status(st, "generate key for public import test") != 0)
        return 1;

    st = psa_sign_message(kp, PSA_ALG_ML_DSA, msg, sizeof(msg) - 1,
                          sig, sizeof(sig), &sig_len);
    if (check_status(st, "sign_message for public import test") != 0) {
        (void)psa_destroy_key(kp);
        return 1;
    }

    st = psa_export_public_key(kp, pub, sizeof(pub), &pub_len);
    if (check_status(st, "export_public_key for import test") != 0) {
        (void)psa_destroy_key(kp);
        return 1;
    }
    (void)psa_destroy_key(kp);
    kp = PSA_KEY_ID_NULL;

    /* Import public key with bits=0: library must infer the parameter set
     * from the buffer length (1952 bytes -> ML-DSA-65 -> bits=192). */
    pub_attrs = psa_key_attributes_init();
    psa_set_key_type(&pub_attrs, PSA_KEY_TYPE_ML_DSA_PUBLIC_KEY);
    psa_set_key_bits(&pub_attrs, 0);
    psa_set_key_algorithm(&pub_attrs, PSA_ALG_ML_DSA);
    psa_set_key_usage_flags(&pub_attrs, PSA_KEY_USAGE_VERIFY_MESSAGE);

    st = psa_import_key(&pub_attrs, pub, pub_len, &pub_key);
    if (check_status(st, "import ML_DSA_PUBLIC_KEY bits=0") != 0)
        return 1;

    /* Verify the bits were inferred correctly */
    got_attrs = psa_key_attributes_init();
    st = psa_get_key_attributes(pub_key, &got_attrs);
    if (check_status(st, "get_key_attributes after public import") != 0) {
        (void)psa_destroy_key(pub_key);
        return 1;
    }
    if (check_true(psa_get_key_bits(&got_attrs) == (psa_key_bits_t)g_bits[idx],
                   "inferred bits from public key length") != 0) {
        (void)psa_destroy_key(pub_key);
        return 1;
    }

    /* Verify the signature produced by the key pair */
    st = psa_verify_message(pub_key, PSA_ALG_ML_DSA, msg, sizeof(msg) - 1,
                            sig, sig_len);
    if (check_status(st, "verify_message with imported public key") != 0) {
        (void)psa_destroy_key(pub_key);
        return 1;
    }

    (void)psa_destroy_key(pub_key);
    printf("PASS: test_import_public_key\n");
    return 0;
#endif
}

/* -------------------------------------------------------------------------
 * Case 4: Deterministic produces identical signatures; hedged produces different
 * ---------------------------------------------------------------------- */

static int test_deterministic_vs_hedged(void)
{
#if !defined(WOLFSSL_HAVE_MLDSA)
    printf("SKIP: test_deterministic_vs_hedged (WOLFSSL_HAVE_MLDSA not set)\n");
    return 0;
#else
    static const psa_key_usage_t usage =
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE;
    static const uint8_t msg[] = "determinism test message";

    psa_key_attributes_t attrs;
    psa_key_id_t det_key  = PSA_KEY_ID_NULL;
    psa_key_id_t hed_key  = PSA_KEY_ID_NULL;
    uint8_t sig1[3309], sig2[3309];
    size_t sig1_len = 0, sig2_len = 0;
    psa_status_t st;

    /* Deterministic key (bits=192) */
    make_mldsa_keypair_attrs(&attrs, 192u, PSA_ALG_DETERMINISTIC_ML_DSA,
                             usage);
    st = psa_generate_key(&attrs, &det_key);
    if (check_status(st, "generate deterministic ML-DSA-65 key") != 0)
        return 1;

    st = psa_sign_message(det_key, PSA_ALG_DETERMINISTIC_ML_DSA,
                          msg, sizeof(msg) - 1, sig1, sizeof(sig1), &sig1_len);
    if (check_status(st, "deterministic sign #1") != 0) {
        (void)psa_destroy_key(det_key);
        return 1;
    }

    st = psa_sign_message(det_key, PSA_ALG_DETERMINISTIC_ML_DSA,
                          msg, sizeof(msg) - 1, sig2, sizeof(sig2), &sig2_len);
    if (check_status(st, "deterministic sign #2") != 0) {
        (void)psa_destroy_key(det_key);
        return 1;
    }

    if (check_true(sig1_len == sig2_len, "deterministic sig lengths match") != 0) {
        (void)psa_destroy_key(det_key);
        return 1;
    }
    if (check_true(memcmp(sig1, sig2, sig1_len) == 0,
                   "deterministic signatures are identical") != 0) {
        (void)psa_destroy_key(det_key);
        return 1;
    }
    (void)psa_destroy_key(det_key);
    det_key = PSA_KEY_ID_NULL;

    /* Hedged key (bits=192): two signatures over the same message must DIFFER */
    make_mldsa_keypair_attrs(&attrs, 192u, PSA_ALG_ML_DSA, usage);
    st = psa_generate_key(&attrs, &hed_key);
    if (check_status(st, "generate hedged ML-DSA-65 key") != 0)
        return 1;

    sig1_len = 0;
    st = psa_sign_message(hed_key, PSA_ALG_ML_DSA,
                          msg, sizeof(msg) - 1, sig1, sizeof(sig1), &sig1_len);
    if (check_status(st, "hedged sign #1") != 0) {
        (void)psa_destroy_key(hed_key);
        return 1;
    }

    sig2_len = 0;
    st = psa_sign_message(hed_key, PSA_ALG_ML_DSA,
                          msg, sizeof(msg) - 1, sig2, sizeof(sig2), &sig2_len);
    if (check_status(st, "hedged sign #2") != 0) {
        (void)psa_destroy_key(hed_key);
        return 1;
    }

    if (check_true(sig1_len == sig2_len,
                   "hedged sig lengths match") != 0) {
        (void)psa_destroy_key(hed_key);
        return 1;
    }
    /* Hedged uses randomness: signatures must differ.
     * (If the two happen to collide the PRNG is broken.) */
    if (check_true(memcmp(sig1, sig2, sig1_len) != 0,
                   "hedged signatures differ") != 0) {
        (void)psa_destroy_key(hed_key);
        return 1;
    }
    (void)psa_destroy_key(hed_key);

    printf("PASS: test_deterministic_vs_hedged\n");
    return 0;
#endif
}

/* -------------------------------------------------------------------------
 * Case 5: HashML-DSA(SHA-256): cross-path interop
 *   a) sign_message -> verify_message
 *   b) psa_hash_compute(SHA-256) -> verify_hash with the same sig
 *   c) sign_hash -> verify_message
 * ---------------------------------------------------------------------- */

static int test_hash_mldsa_interop(void)
{
#if !defined(WOLFSSL_HAVE_MLDSA)
    printf("SKIP: test_hash_mldsa_interop (WOLFSSL_HAVE_MLDSA not set)\n");
    return 0;
#else
    static const psa_algorithm_t alg =
        PSA_ALG_HASH_ML_DSA(PSA_ALG_SHA_256);
    static const psa_key_usage_t usage =
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE |
        PSA_KEY_USAGE_SIGN_HASH   | PSA_KEY_USAGE_VERIFY_HASH;
    static const uint8_t msg[] = "HashML-DSA interop test message";

    psa_key_attributes_t attrs;
    psa_key_id_t key = PSA_KEY_ID_NULL;
    uint8_t sig_msg[3309];  /* ML-DSA-65 max sig */
    uint8_t sig_hash[3309];
    size_t sig_msg_len = 0, sig_hash_len = 0;
    uint8_t digest[32]; /* SHA-256 */
    size_t digest_len = 0;
    psa_status_t st;

    make_mldsa_keypair_attrs(&attrs, 192u, alg, usage);
    st = psa_generate_key(&attrs, &key);
    if (check_status(st, "generate HashML-DSA-65 key") != 0)
        return 1;

    /* 5a: sign_message -> verify_message */
    st = psa_sign_message(key, alg, msg, sizeof(msg) - 1,
                          sig_msg, sizeof(sig_msg), &sig_msg_len);
    if (check_status(st, "HashML-DSA sign_message") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }
    st = psa_verify_message(key, alg, msg, sizeof(msg) - 1,
                            sig_msg, sig_msg_len);
    if (check_status(st, "HashML-DSA verify_message") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }

    /* 5b: compute digest, then verify_hash (caller-hashes path) */
    st = psa_hash_compute(PSA_ALG_SHA_256, msg, sizeof(msg) - 1,
                          digest, sizeof(digest), &digest_len);
    if (check_status(st, "SHA-256 hash_compute for HashML-DSA") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }
    st = psa_verify_hash(key, alg, digest, digest_len,
                         sig_msg, sig_msg_len);
    if (check_status(st, "HashML-DSA verify_hash (caller-hashed)") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }

    /* 5c: sign_hash -> verify_message */
    st = psa_sign_hash(key, alg, digest, digest_len,
                       sig_hash, sizeof(sig_hash), &sig_hash_len);
    if (check_status(st, "HashML-DSA sign_hash") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }
    st = psa_verify_message(key, alg, msg, sizeof(msg) - 1,
                            sig_hash, sig_hash_len);
    if (check_status(st, "HashML-DSA verify_message after sign_hash") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }

    (void)psa_destroy_key(key);
    printf("PASS: test_hash_mldsa_interop\n");
    return 0;
#endif
}

/* -------------------------------------------------------------------------
 * Case 6: psa_sign_hash with PSA_ALG_ML_DSA must return INVALID_ARGUMENT
 * ---------------------------------------------------------------------- */

static int test_pure_mldsa_sign_hash_rejected(void)
{
#if !defined(WOLFSSL_HAVE_MLDSA)
    printf("SKIP: test_pure_mldsa_sign_hash_rejected (WOLFSSL_HAVE_MLDSA not set)\n");
    return 0;
#else
    static const psa_key_usage_t usage =
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_SIGN_HASH;
    /* A plausible 32-byte digest buffer */
    static const uint8_t digest[32] = { 0 };

    psa_key_attributes_t attrs;
    psa_key_id_t key = PSA_KEY_ID_NULL;
    uint8_t sig[3309];
    size_t sig_len = 0;
    psa_status_t st;

    make_mldsa_keypair_attrs(&attrs, 192u, PSA_ALG_ML_DSA, usage);
    st = psa_generate_key(&attrs, &key);
    if (check_status(st, "generate key for sign_hash rejection test") != 0)
        return 1;

    st = psa_sign_hash(key, PSA_ALG_ML_DSA,
                       digest, sizeof(digest),
                       sig, sizeof(sig), &sig_len);
    if (check_status_eq(st, PSA_ERROR_INVALID_ARGUMENT,
                        "sign_hash with PSA_ALG_ML_DSA") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }

    (void)psa_destroy_key(key);
    printf("PASS: test_pure_mldsa_sign_hash_rejected\n");
    return 0;
#endif
}

/* -------------------------------------------------------------------------
 * Case 7: Import 32-byte seed
 *   7a: bits=0 -> PSA_ERROR_INVALID_ARGUMENT (ambiguous without explicit bits)
 *   7b: bits=192 -> success; sign/verify roundtrip
 * ---------------------------------------------------------------------- */

static int test_import_seed(void)
{
#if !defined(WOLFSSL_HAVE_MLDSA)
    printf("SKIP: test_import_seed (WOLFSSL_HAVE_MLDSA not set)\n");
    return 0;
#else
    static const psa_key_usage_t usage =
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE |
        PSA_KEY_USAGE_EXPORT;
    static const uint8_t msg[] = "import seed test";
    /* A fixed 32-byte seed for reproducibility */
    static const uint8_t seed[32] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20
    };

    psa_key_attributes_t attrs;
    psa_key_id_t key = PSA_KEY_ID_NULL;
    psa_status_t st;
    uint8_t sig[3309];
    size_t sig_len = 0;

    /* 7a: bits=0 must fail */
    attrs = psa_key_attributes_init();
    psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_DSA_KEY_PAIR);
    psa_set_key_bits(&attrs, 0);
    psa_set_key_algorithm(&attrs, PSA_ALG_ML_DSA);
    psa_set_key_usage_flags(&attrs, usage);

    st = psa_import_key(&attrs, seed, sizeof(seed), &key);
    if (check_status_eq(st, PSA_ERROR_INVALID_ARGUMENT,
                        "import seed bits=0") != 0) {
        if (key != PSA_KEY_ID_NULL) (void)psa_destroy_key(key);
        return 1;
    }

    /* 7b: bits=192 must succeed */
    make_mldsa_keypair_attrs(&attrs, 192u, PSA_ALG_ML_DSA, usage);
    key = PSA_KEY_ID_NULL;

    st = psa_import_key(&attrs, seed, sizeof(seed), &key);
    if (check_status(st, "import seed bits=192") != 0)
        return 1;

    st = psa_sign_message(key, PSA_ALG_ML_DSA, msg, sizeof(msg) - 1,
                          sig, sizeof(sig), &sig_len);
    if (check_status(st, "sign after import seed") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }
    st = psa_verify_message(key, PSA_ALG_ML_DSA, msg, sizeof(msg) - 1,
                            sig, sig_len);
    if (check_status(st, "verify after import seed") != 0) {
        (void)psa_destroy_key(key);
        return 1;
    }

    (void)psa_destroy_key(key);
    printf("PASS: test_import_seed\n");
    return 0;
#endif
}

/* -------------------------------------------------------------------------
 * Case 8: Import wrong-length seed (31 bytes, bits=192) -> INVALID_ARGUMENT
 * ---------------------------------------------------------------------- */

static int test_import_wrong_seed_length(void)
{
#if !defined(WOLFSSL_HAVE_MLDSA)
    printf("SKIP: test_import_wrong_seed_length (WOLFSSL_HAVE_MLDSA not set)\n");
    return 0;
#else
    static const psa_key_usage_t usage =
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE;
    static const uint8_t short_seed[31] = { 0 }; /* 31 bytes, not 32 */

    psa_key_attributes_t attrs;
    psa_key_id_t key = PSA_KEY_ID_NULL;
    psa_status_t st;

    make_mldsa_keypair_attrs(&attrs, 192u, PSA_ALG_ML_DSA, usage);

    st = psa_import_key(&attrs, short_seed, sizeof(short_seed), &key);
    if (check_status_eq(st, PSA_ERROR_INVALID_ARGUMENT,
                        "import 31-byte seed bits=192") != 0) {
        if (key != PSA_KEY_ID_NULL) (void)psa_destroy_key(key);
        return 1;
    }

    printf("PASS: test_import_wrong_seed_length\n");
    return 0;
#endif
}

/* -------------------------------------------------------------------------
 * main
 * ---------------------------------------------------------------------- */

int main(void)
{
    psa_status_t st;

    st = psa_crypto_init();
    if (st != PSA_SUCCESS) {
        printf("FAIL: psa_crypto_init (status=%d)\n", (int)st);
        return 1;
    }

    if (test_generate_key_sizes() != 0)             return 1;
    if (test_sign_verify_message() != 0)            return 1;
    if (test_import_public_key() != 0)              return 1;
    if (test_deterministic_vs_hedged() != 0)        return 1;
    if (test_hash_mldsa_interop() != 0)             return 1;
    if (test_pure_mldsa_sign_hash_rejected() != 0)  return 1;
    if (test_import_seed() != 0)                    return 1;
    if (test_import_wrong_seed_length() != 0)       return 1;

    printf("PSA ML-DSA test: OK\n");
    return 0;
}
