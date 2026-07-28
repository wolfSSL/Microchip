/* psa_mlkem_test.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Coverage test for the PSA Certified Crypto API 1.4 ML-KEM (CRYSTALS-Kyber)
 * key-encapsulation interface implemented in wolfPSA. */

#include "psa_api_test_user_settings.h"

#ifndef WOLFSSL_USER_SETTINGS
#define WOLFSSL_USER_SETTINGS
#endif

#include <wolfssl/wolfcrypt/settings.h>

#include <stdio.h>
#include <string.h>

#include <wolfpsa/psa/crypto.h>

/* --------------------------------------------------------------------------
 * Internal helpers
 * -------------------------------------------------------------------------- */

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
        printf("FAIL: %s status=%d expected=%d\n", what, (int)st, (int)expected);
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

static int check_buf_eq(const char *what,
                        const uint8_t *a, const uint8_t *b, size_t sz)
{
    if (memcmp(a, b, sz) != 0) {
        printf("FAIL: %s (mismatch)\n", what);
        return 1;
    }
    return 0;
}

static int check_buf_ne(const char *what,
                        const uint8_t *a, const uint8_t *b, size_t sz)
{
    if (memcmp(a, b, sz) == 0) {
        printf("FAIL: %s (expected difference, got equal)\n", what);
        return 1;
    }
    return 0;
}

/* Shared-secret output-key attributes: DERIVE / EXPORT / HKDF(SHA-256) / 0b */
static psa_key_attributes_t make_ss_attrs(void)
{
    psa_key_attributes_t a = psa_key_attributes_init();
    psa_set_key_type(&a, PSA_KEY_TYPE_DERIVE);
    psa_set_key_usage_flags(&a, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&a, PSA_ALG_HKDF(PSA_ALG_SHA_256));
    psa_set_key_bits(&a, 0);
    return a;
}

/* Export a key and return the length, -1 on error. */
static int export_key(psa_key_id_t key_id, uint8_t *buf, size_t buf_size,
                      size_t *out_len, const char *label)
{
    psa_status_t st = psa_export_key(key_id, buf, buf_size, out_len);
    if (st != PSA_SUCCESS) {
        printf("FAIL: export_key(%s) status=%d\n", label, (int)st);
        return -1;
    }
    return 0;
}

/* --------------------------------------------------------------------------
 * Case 1: generate key pair, check seed and public-key export sizes.
 * Covers bits in {512, 768, 1024}.
 * -------------------------------------------------------------------------- */
static int test_generate_and_export_sizes(void)
{
    static const struct {
        size_t bits;
        size_t pub_size;
    } cases[] = {
        { 512,   800 },
        { 768,  1184 },
        { 1024, 1568 },
    };
    size_t i;

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        size_t bits    = cases[i].bits;
        size_t pub_exp = cases[i].pub_size;
        char label[64];
        psa_key_attributes_t attrs = psa_key_attributes_init();
        psa_key_id_t kp = PSA_KEY_ID_NULL;
        uint8_t seed_buf[64];
        uint8_t pub_buf[1568];
        size_t seed_len = 0;
        size_t pub_len  = 0;
        psa_status_t st;

        psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
        psa_set_key_bits(&attrs, bits);
        psa_set_key_usage_flags(&attrs,
            PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_EXPORT);
        psa_set_key_algorithm(&attrs, PSA_ALG_ML_KEM);

        snprintf(label, sizeof(label), "generate ML-KEM-%zu", bits);
        st = psa_generate_key(&attrs, &kp);
        if (check_status(st, label) != 0) return 1;

        snprintf(label, sizeof(label), "export_key seed ML-KEM-%zu", bits);
        if (export_key(kp, seed_buf, sizeof(seed_buf), &seed_len, label) != 0) {
            (void)psa_destroy_key(kp);
            return 1;
        }
        snprintf(label, sizeof(label), "seed size ML-KEM-%zu", bits);
        if (check_true(seed_len == 64, label) != 0) {
            (void)psa_destroy_key(kp);
            return 1;
        }

        snprintf(label, sizeof(label), "export_public_key ML-KEM-%zu", bits);
        st = psa_export_public_key(kp, pub_buf, sizeof(pub_buf), &pub_len);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(kp);
            return 1;
        }
        snprintf(label, sizeof(label), "public key size ML-KEM-%zu", bits);
        if (check_true(pub_len == pub_exp, label) != 0) {
            printf("  (got %zu, expected %zu)\n", pub_len, pub_exp);
            (void)psa_destroy_key(kp);
            return 1;
        }

        (void)psa_destroy_key(kp);
    }

    printf("PASS: test_generate_and_export_sizes\n");
    return 0;
}

/* --------------------------------------------------------------------------
 * Case 2: full encap/decap round-trip; shared secrets must match.
 * Also validates ciphertext lengths.
 * -------------------------------------------------------------------------- */
static int test_encap_decap_roundtrip(void)
{
    static const struct {
        size_t bits;
        size_t ct_size;
    } cases[] = {
        {  512,  768 },
        {  768, 1088 },
        { 1024, 1568 },
    };
    size_t i;

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        size_t bits   = cases[i].bits;
        size_t ct_exp = cases[i].ct_size;
        char label[80];
        psa_key_attributes_t attrs = psa_key_attributes_init();
        psa_key_attributes_t ss_attrs;
        psa_key_id_t kp = PSA_KEY_ID_NULL;
        psa_key_id_t ss_enc = PSA_KEY_ID_NULL;
        psa_key_id_t ss_dec = PSA_KEY_ID_NULL;
        uint8_t ct[1568];
        size_t ct_len = 0;
        uint8_t ss_enc_buf[32];
        uint8_t ss_dec_buf[32];
        size_t ss_enc_len = 0;
        size_t ss_dec_len = 0;
        psa_status_t st;

        psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
        psa_set_key_bits(&attrs, bits);
        psa_set_key_usage_flags(&attrs,
            PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_EXPORT);
        psa_set_key_algorithm(&attrs, PSA_ALG_ML_KEM);

        st = psa_generate_key(&attrs, &kp);
        snprintf(label, sizeof(label), "roundtrip generate ML-KEM-%zu", bits);
        if (check_status(st, label) != 0) return 1;

        ss_attrs = make_ss_attrs();
        snprintf(label, sizeof(label), "encapsulate ML-KEM-%zu", bits);
        st = psa_encapsulate(kp, PSA_ALG_ML_KEM, &ss_attrs,
                             &ss_enc, ct, sizeof(ct), &ct_len);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(kp);
            return 1;
        }

        snprintf(label, sizeof(label), "ciphertext length ML-KEM-%zu", bits);
        if (check_true(ct_len == ct_exp, label) != 0) {
            printf("  (got %zu, expected %zu)\n", ct_len, ct_exp);
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(kp);
            return 1;
        }

        ss_attrs = make_ss_attrs();
        snprintf(label, sizeof(label), "decapsulate ML-KEM-%zu", bits);
        st = psa_decapsulate(kp, PSA_ALG_ML_KEM, ct, ct_len,
                             &ss_attrs, &ss_dec);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(kp);
            return 1;
        }

        /* Export both secrets and compare. */
        snprintf(label, sizeof(label), "export ss_enc ML-KEM-%zu", bits);
        if (export_key(ss_enc, ss_enc_buf, sizeof(ss_enc_buf),
                       &ss_enc_len, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(ss_dec);
            (void)psa_destroy_key(kp);
            return 1;
        }
        snprintf(label, sizeof(label), "export ss_dec ML-KEM-%zu", bits);
        if (export_key(ss_dec, ss_dec_buf, sizeof(ss_dec_buf),
                       &ss_dec_len, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(ss_dec);
            (void)psa_destroy_key(kp);
            return 1;
        }

        snprintf(label, sizeof(label), "ss length enc ML-KEM-%zu", bits);
        if (check_true(ss_enc_len == 32, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(ss_dec);
            (void)psa_destroy_key(kp);
            return 1;
        }
        snprintf(label, sizeof(label), "ss length dec ML-KEM-%zu", bits);
        if (check_true(ss_dec_len == 32, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(ss_dec);
            (void)psa_destroy_key(kp);
            return 1;
        }

        snprintf(label, sizeof(label), "shared secrets equal ML-KEM-%zu", bits);
        if (check_buf_eq(label, ss_enc_buf, ss_dec_buf, 32) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(ss_dec);
            (void)psa_destroy_key(kp);
            return 1;
        }

        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(ss_dec);
        (void)psa_destroy_key(kp);
    }

    printf("PASS: test_encap_decap_roundtrip\n");
    return 0;
}

/* --------------------------------------------------------------------------
 * Case 3: import public key (bits=0, length inference), encap with it,
 * decap with original key pair — secrets must match.
 * -------------------------------------------------------------------------- */
static int test_import_public_key_and_encap(void)
{
    static const struct {
        size_t bits;
        size_t pub_size;
        size_t ct_size;
    } cases[] = {
        {  512,  800,  768 },
        {  768, 1184, 1088 },
        { 1024, 1568, 1568 },
    };
    size_t i;

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        size_t bits    = cases[i].bits;
        size_t pub_exp = cases[i].pub_size;
        size_t ct_exp  = cases[i].ct_size;
        char label[80];
        psa_key_attributes_t kp_attrs = psa_key_attributes_init();
        psa_key_attributes_t pub_attrs = psa_key_attributes_init();
        psa_key_attributes_t got_attrs = psa_key_attributes_init();
        psa_key_attributes_t ss_attrs;
        psa_key_id_t kp     = PSA_KEY_ID_NULL;
        psa_key_id_t pub_id = PSA_KEY_ID_NULL;
        psa_key_id_t ss_enc = PSA_KEY_ID_NULL;
        psa_key_id_t ss_dec = PSA_KEY_ID_NULL;
        uint8_t pub_buf[1568];
        size_t pub_len = 0;
        uint8_t ct[1568];
        size_t ct_len = 0;
        uint8_t ss_enc_buf[32];
        uint8_t ss_dec_buf[32];
        size_t ss_enc_len = 0;
        size_t ss_dec_len = 0;
        psa_status_t st;

        /* Generate the key pair. */
        psa_set_key_type(&kp_attrs, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
        psa_set_key_bits(&kp_attrs, bits);
        psa_set_key_usage_flags(&kp_attrs,
            PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_EXPORT);
        psa_set_key_algorithm(&kp_attrs, PSA_ALG_ML_KEM);

        snprintf(label, sizeof(label), "pub-import generate ML-KEM-%zu", bits);
        st = psa_generate_key(&kp_attrs, &kp);
        if (check_status(st, label) != 0) return 1;

        /* Export the public key. */
        snprintf(label, sizeof(label), "pub-import export_public ML-KEM-%zu", bits);
        st = psa_export_public_key(kp, pub_buf, sizeof(pub_buf), &pub_len);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(kp);
            return 1;
        }
        snprintf(label, sizeof(label), "pub-import pub_len ML-KEM-%zu", bits);
        if (check_true(pub_len == pub_exp, label) != 0) {
            (void)psa_destroy_key(kp);
            return 1;
        }

        /* Import the public key with bits=0 (length inference). */
        psa_set_key_type(&pub_attrs, PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY);
        psa_set_key_bits(&pub_attrs, 0);
        psa_set_key_usage_flags(&pub_attrs, PSA_KEY_USAGE_ENCRYPT);
        psa_set_key_algorithm(&pub_attrs, PSA_ALG_ML_KEM);

        snprintf(label, sizeof(label), "pub-import import ML-KEM-%zu", bits);
        st = psa_import_key(&pub_attrs, pub_buf, pub_len, &pub_id);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(kp);
            return 1;
        }

        /* Verify inferred bits. */
        snprintf(label, sizeof(label), "pub-import get_attrs ML-KEM-%zu", bits);
        st = psa_get_key_attributes(pub_id, &got_attrs);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(pub_id);
            (void)psa_destroy_key(kp);
            return 1;
        }
        snprintf(label, sizeof(label), "pub-import inferred bits ML-KEM-%zu", bits);
        if (check_true(psa_get_key_bits(&got_attrs) == (psa_key_bits_t)bits,
                       label) != 0) {
            printf("  (got %u, expected %zu)\n",
                   (unsigned)psa_get_key_bits(&got_attrs), bits);
            (void)psa_destroy_key(pub_id);
            (void)psa_destroy_key(kp);
            return 1;
        }

        /* Encapsulate with the imported public key. */
        ss_attrs = make_ss_attrs();
        snprintf(label, sizeof(label), "pub-import encapsulate ML-KEM-%zu", bits);
        st = psa_encapsulate(pub_id, PSA_ALG_ML_KEM, &ss_attrs,
                             &ss_enc, ct, sizeof(ct), &ct_len);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(pub_id);
            (void)psa_destroy_key(kp);
            return 1;
        }
        snprintf(label, sizeof(label), "pub-import ct_len ML-KEM-%zu", bits);
        if (check_true(ct_len == ct_exp, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(pub_id);
            (void)psa_destroy_key(kp);
            return 1;
        }

        /* Decapsulate with the key pair. */
        ss_attrs = make_ss_attrs();
        snprintf(label, sizeof(label), "pub-import decapsulate ML-KEM-%zu", bits);
        st = psa_decapsulate(kp, PSA_ALG_ML_KEM, ct, ct_len,
                             &ss_attrs, &ss_dec);
        if (check_status(st, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(pub_id);
            (void)psa_destroy_key(kp);
            return 1;
        }

        /* Export and compare. */
        snprintf(label, sizeof(label), "pub-import export ss_enc ML-KEM-%zu", bits);
        if (export_key(ss_enc, ss_enc_buf, sizeof(ss_enc_buf),
                       &ss_enc_len, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(ss_dec);
            (void)psa_destroy_key(pub_id);
            (void)psa_destroy_key(kp);
            return 1;
        }
        snprintf(label, sizeof(label), "pub-import export ss_dec ML-KEM-%zu", bits);
        if (export_key(ss_dec, ss_dec_buf, sizeof(ss_dec_buf),
                       &ss_dec_len, label) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(ss_dec);
            (void)psa_destroy_key(pub_id);
            (void)psa_destroy_key(kp);
            return 1;
        }

        snprintf(label, sizeof(label),
                 "pub-import secrets equal ML-KEM-%zu", bits);
        if (check_buf_eq(label, ss_enc_buf, ss_dec_buf, 32) != 0) {
            (void)psa_destroy_key(ss_enc);
            (void)psa_destroy_key(ss_dec);
            (void)psa_destroy_key(pub_id);
            (void)psa_destroy_key(kp);
            return 1;
        }

        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(ss_dec);
        (void)psa_destroy_key(pub_id);
        (void)psa_destroy_key(kp);
    }

    printf("PASS: test_import_public_key_and_encap\n");
    return 0;
}

/* --------------------------------------------------------------------------
 * Case 4: tampered ciphertext — ML-KEM implicit rejection.
 * Decapsulate MUST succeed but secret MUST differ from the genuine one.
 * -------------------------------------------------------------------------- */
static int test_tampered_ciphertext_implicit_rejection(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_attributes_t ss_attrs;
    psa_key_id_t kp     = PSA_KEY_ID_NULL;
    psa_key_id_t ss_enc = PSA_KEY_ID_NULL;
    psa_key_id_t ss_dec = PSA_KEY_ID_NULL;
    uint8_t ct[1088]; /* ML-KEM-768 */
    size_t ct_len = 0;
    uint8_t ss_enc_buf[32];
    uint8_t ss_dec_buf[32];
    size_t ss_enc_len = 0;
    size_t ss_dec_len = 0;
    psa_status_t st;

    psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
    psa_set_key_bits(&attrs, 768);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&attrs, PSA_ALG_ML_KEM);

    st = psa_generate_key(&attrs, &kp);
    if (check_status(st, "tamper generate") != 0) return 1;

    ss_attrs = make_ss_attrs();
    st = psa_encapsulate(kp, PSA_ALG_ML_KEM, &ss_attrs,
                         &ss_enc, ct, sizeof(ct), &ct_len);
    if (check_status(st, "tamper encapsulate") != 0) {
        (void)psa_destroy_key(kp);
        return 1;
    }

    /* Flip a byte in the middle of the ciphertext. */
    ct[ct_len / 2] ^= 0xAA;

    ss_attrs = make_ss_attrs();
    st = psa_decapsulate(kp, PSA_ALG_ML_KEM, ct, ct_len,
                         &ss_attrs, &ss_dec);
    if (check_status(st, "tamper decapsulate (must succeed)") != 0) {
        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(kp);
        return 1;
    }

    if (export_key(ss_enc, ss_enc_buf, sizeof(ss_enc_buf),
                   &ss_enc_len, "tamper export ss_enc") != 0) {
        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(ss_dec);
        (void)psa_destroy_key(kp);
        return 1;
    }
    if (export_key(ss_dec, ss_dec_buf, sizeof(ss_dec_buf),
                   &ss_dec_len, "tamper export ss_dec") != 0) {
        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(ss_dec);
        (void)psa_destroy_key(kp);
        return 1;
    }

    if (check_buf_ne("tamper secrets differ", ss_enc_buf, ss_dec_buf, 32) != 0) {
        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(ss_dec);
        (void)psa_destroy_key(kp);
        return 1;
    }

    (void)psa_destroy_key(ss_enc);
    (void)psa_destroy_key(ss_dec);
    (void)psa_destroy_key(kp);

    printf("PASS: test_tampered_ciphertext_implicit_rejection\n");
    return 0;
}

/* --------------------------------------------------------------------------
 * Case 5: wrong ciphertext length must return PSA_ERROR_INVALID_ARGUMENT.
 * -------------------------------------------------------------------------- */
static int test_wrong_ciphertext_length(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_attributes_t ss_attrs;
    psa_key_id_t kp     = PSA_KEY_ID_NULL;
    psa_key_id_t ss_enc = PSA_KEY_ID_NULL;
    psa_key_id_t ss_dec = PSA_KEY_ID_NULL;
    uint8_t ct[1088]; /* ML-KEM-768 */
    size_t ct_len = 0;
    psa_status_t st;

    psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
    psa_set_key_bits(&attrs, 768);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&attrs, PSA_ALG_ML_KEM);

    st = psa_generate_key(&attrs, &kp);
    if (check_status(st, "wrong-len generate") != 0) return 1;

    ss_attrs = make_ss_attrs();
    st = psa_encapsulate(kp, PSA_ALG_ML_KEM, &ss_attrs,
                         &ss_enc, ct, sizeof(ct), &ct_len);
    if (check_status(st, "wrong-len encapsulate") != 0) {
        (void)psa_destroy_key(kp);
        return 1;
    }
    (void)psa_destroy_key(ss_enc);
    ss_enc = PSA_KEY_ID_NULL;

    /* Pass ct_len - 1: must fail. */
    ss_attrs = make_ss_attrs();
    st = psa_decapsulate(kp, PSA_ALG_ML_KEM, ct, ct_len - 1,
                         &ss_attrs, &ss_dec);
    if (check_status_eq(st, PSA_ERROR_INVALID_ARGUMENT,
                        "wrong-len decapsulate") != 0) {
        if (ss_dec != PSA_KEY_ID_NULL)
            (void)psa_destroy_key(ss_dec);
        (void)psa_destroy_key(kp);
        return 1;
    }

    (void)psa_destroy_key(kp);

    printf("PASS: test_wrong_ciphertext_length\n");
    return 0;
}

/* --------------------------------------------------------------------------
 * Case 6: missing usage flags.
 *   - Key pair without ENCRYPT: psa_encapsulate -> PSA_ERROR_NOT_PERMITTED.
 *   - Public key used for decapsulate -> PSA_ERROR_INVALID_ARGUMENT
 *     (wrong key type — decapsulate requires a key pair).
 * -------------------------------------------------------------------------- */
static int test_missing_usage(void)
{
    psa_key_attributes_t kp_attrs  = psa_key_attributes_init();
    psa_key_attributes_t pub_attrs = psa_key_attributes_init();
    psa_key_attributes_t ss_attrs;
    psa_key_id_t kp_no_enc  = PSA_KEY_ID_NULL;
    psa_key_id_t pub_id     = PSA_KEY_ID_NULL;
    psa_key_id_t ss_out     = PSA_KEY_ID_NULL;
    uint8_t pub_buf[800];   /* ML-KEM-512 public key */
    size_t pub_len = 0;
    uint8_t ct[768];
    size_t ct_len = 0;
    psa_status_t st;

    /* Generate a key pair WITHOUT PSA_KEY_USAGE_ENCRYPT. */
    psa_set_key_type(&kp_attrs, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
    psa_set_key_bits(&kp_attrs, 512);
    psa_set_key_usage_flags(&kp_attrs,
        PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&kp_attrs, PSA_ALG_ML_KEM);

    st = psa_generate_key(&kp_attrs, &kp_no_enc);
    if (check_status(st, "missing-usage generate kp") != 0) return 1;

    ss_attrs = make_ss_attrs();
    st = psa_encapsulate(kp_no_enc, PSA_ALG_ML_KEM, &ss_attrs,
                         &ss_out, ct, sizeof(ct), &ct_len);
    if (check_status_eq(st, PSA_ERROR_NOT_PERMITTED,
                        "encapsulate without ENCRYPT") != 0) {
        if (ss_out != PSA_KEY_ID_NULL)
            (void)psa_destroy_key(ss_out);
        (void)psa_destroy_key(kp_no_enc);
        return 1;
    }

    /* Export the public key and import it as ML_KEM_PUBLIC_KEY, then try
     * decapsulate with it (must fail: wrong type). */
    st = psa_export_public_key(kp_no_enc, pub_buf, sizeof(pub_buf), &pub_len);
    if (check_status(st, "missing-usage export_public") != 0) {
        (void)psa_destroy_key(kp_no_enc);
        return 1;
    }

    psa_set_key_type(&pub_attrs, PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY);
    psa_set_key_bits(&pub_attrs, 0);
    psa_set_key_usage_flags(&pub_attrs, PSA_KEY_USAGE_ENCRYPT);
    psa_set_key_algorithm(&pub_attrs, PSA_ALG_ML_KEM);

    st = psa_import_key(&pub_attrs, pub_buf, pub_len, &pub_id);
    if (check_status(st, "missing-usage import public key") != 0) {
        (void)psa_destroy_key(kp_no_enc);
        return 1;
    }

    /* Fabricate a dummy ciphertext (768 bytes of zeros). */
    memset(ct, 0, sizeof(ct));
    ct_len = 768;

    ss_attrs = make_ss_attrs();
    ss_out = PSA_KEY_ID_NULL;
    st = psa_decapsulate(pub_id, PSA_ALG_ML_KEM, ct, ct_len,
                         &ss_attrs, &ss_out);
    if (check_status_eq(st, PSA_ERROR_INVALID_ARGUMENT,
                        "decapsulate with public key") != 0) {
        if (ss_out != PSA_KEY_ID_NULL)
            (void)psa_destroy_key(ss_out);
        (void)psa_destroy_key(pub_id);
        (void)psa_destroy_key(kp_no_enc);
        return 1;
    }

    (void)psa_destroy_key(pub_id);
    (void)psa_destroy_key(kp_no_enc);

    printf("PASS: test_missing_usage\n");
    return 0;
}

/* --------------------------------------------------------------------------
 * Case 7: import a 64-byte seed as ML_KEM_KEY_PAIR.
 *   - bits=0 -> PSA_ERROR_INVALID_ARGUMENT (ambiguous).
 *   - bits=768 -> success; full encap/decap round-trip works.
 * -------------------------------------------------------------------------- */
static int test_import_seed(void)
{
    psa_key_attributes_t gen_attrs   = psa_key_attributes_init();
    psa_key_attributes_t imp_attrs0  = psa_key_attributes_init();
    psa_key_attributes_t imp_attrs768 = psa_key_attributes_init();
    psa_key_attributes_t ss_attrs;
    psa_key_id_t kp_gen   = PSA_KEY_ID_NULL;
    psa_key_id_t kp_imp0  = PSA_KEY_ID_NULL;
    psa_key_id_t kp_imp   = PSA_KEY_ID_NULL;
    psa_key_id_t ss_enc   = PSA_KEY_ID_NULL;
    psa_key_id_t ss_dec   = PSA_KEY_ID_NULL;
    uint8_t seed[64];
    size_t seed_len = 0;
    uint8_t ct[1088];
    size_t ct_len = 0;
    uint8_t ss_enc_buf[32];
    uint8_t ss_dec_buf[32];
    size_t ss_enc_len = 0;
    size_t ss_dec_len = 0;
    psa_status_t st;

    /* Generate ML-KEM-768 key pair and export seed. */
    psa_set_key_type(&gen_attrs, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
    psa_set_key_bits(&gen_attrs, 768);
    psa_set_key_usage_flags(&gen_attrs,
        PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&gen_attrs, PSA_ALG_ML_KEM);

    st = psa_generate_key(&gen_attrs, &kp_gen);
    if (check_status(st, "import-seed generate") != 0) return 1;

    if (export_key(kp_gen, seed, sizeof(seed), &seed_len,
                   "import-seed export seed") != 0) {
        (void)psa_destroy_key(kp_gen);
        return 1;
    }
    if (check_true(seed_len == 64, "import-seed seed_len") != 0) {
        (void)psa_destroy_key(kp_gen);
        return 1;
    }

    /* Import with bits=0 must fail (ambiguous). */
    psa_set_key_type(&imp_attrs0, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
    psa_set_key_bits(&imp_attrs0, 0);
    psa_set_key_usage_flags(&imp_attrs0,
        PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&imp_attrs0, PSA_ALG_ML_KEM);

    st = psa_import_key(&imp_attrs0, seed, seed_len, &kp_imp0);
    if (check_status_eq(st, PSA_ERROR_INVALID_ARGUMENT,
                        "import seed bits=0") != 0) {
        if (kp_imp0 != PSA_KEY_ID_NULL)
            (void)psa_destroy_key(kp_imp0);
        (void)psa_destroy_key(kp_gen);
        return 1;
    }

    /* Import with bits=768 must succeed. */
    psa_set_key_type(&imp_attrs768, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
    psa_set_key_bits(&imp_attrs768, 768);
    psa_set_key_usage_flags(&imp_attrs768,
        PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&imp_attrs768, PSA_ALG_ML_KEM);

    st = psa_import_key(&imp_attrs768, seed, seed_len, &kp_imp);
    if (check_status(st, "import seed bits=768") != 0) {
        (void)psa_destroy_key(kp_gen);
        return 1;
    }

    /* Full round-trip with the imported seed key. */
    ss_attrs = make_ss_attrs();
    st = psa_encapsulate(kp_imp, PSA_ALG_ML_KEM, &ss_attrs,
                         &ss_enc, ct, sizeof(ct), &ct_len);
    if (check_status(st, "import-seed encapsulate") != 0) {
        (void)psa_destroy_key(kp_imp);
        (void)psa_destroy_key(kp_gen);
        return 1;
    }

    ss_attrs = make_ss_attrs();
    st = psa_decapsulate(kp_imp, PSA_ALG_ML_KEM, ct, ct_len,
                         &ss_attrs, &ss_dec);
    if (check_status(st, "import-seed decapsulate") != 0) {
        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(kp_imp);
        (void)psa_destroy_key(kp_gen);
        return 1;
    }

    if (export_key(ss_enc, ss_enc_buf, sizeof(ss_enc_buf),
                   &ss_enc_len, "import-seed export ss_enc") != 0 ||
        export_key(ss_dec, ss_dec_buf, sizeof(ss_dec_buf),
                   &ss_dec_len, "import-seed export ss_dec") != 0) {
        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(ss_dec);
        (void)psa_destroy_key(kp_imp);
        (void)psa_destroy_key(kp_gen);
        return 1;
    }

    if (check_buf_eq("import-seed secrets equal",
                     ss_enc_buf, ss_dec_buf, 32) != 0) {
        (void)psa_destroy_key(ss_enc);
        (void)psa_destroy_key(ss_dec);
        (void)psa_destroy_key(kp_imp);
        (void)psa_destroy_key(kp_gen);
        return 1;
    }

    (void)psa_destroy_key(ss_enc);
    (void)psa_destroy_key(ss_dec);
    (void)psa_destroy_key(kp_imp);
    (void)psa_destroy_key(kp_gen);

    printf("PASS: test_import_seed\n");
    return 0;
}

/* --------------------------------------------------------------------------
 * Case 8: buffer too small for ciphertext -> PSA_ERROR_BUFFER_TOO_SMALL.
 * -------------------------------------------------------------------------- */
static int test_buffer_too_small(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_attributes_t ss_attrs;
    psa_key_id_t kp     = PSA_KEY_ID_NULL;
    psa_key_id_t ss_out = PSA_KEY_ID_NULL;
    /* ML-KEM-768 needs 1088 bytes; give 1087. */
    uint8_t small_ct[1087];
    size_t ct_len = 0;
    psa_status_t st;

    psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_KEM_KEY_PAIR);
    psa_set_key_bits(&attrs, 768);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&attrs, PSA_ALG_ML_KEM);

    st = psa_generate_key(&attrs, &kp);
    if (check_status(st, "buf-small generate") != 0) return 1;

    ss_attrs = make_ss_attrs();
    st = psa_encapsulate(kp, PSA_ALG_ML_KEM, &ss_attrs,
                         &ss_out, small_ct, sizeof(small_ct), &ct_len);
    if (check_status_eq(st, PSA_ERROR_BUFFER_TOO_SMALL,
                        "encapsulate buf too small") != 0) {
        if (ss_out != PSA_KEY_ID_NULL)
            (void)psa_destroy_key(ss_out);
        (void)psa_destroy_key(kp);
        return 1;
    }

    (void)psa_destroy_key(kp);

    printf("PASS: test_buffer_too_small\n");
    return 0;
}

/* --------------------------------------------------------------------------
 * main
 * -------------------------------------------------------------------------- */
int main(void)
{
    psa_status_t st;

    st = psa_crypto_init();
    if (st != PSA_SUCCESS) {
        printf("FAIL: psa_crypto_init status=%d\n", (int)st);
        return 1;
    }

    if (test_generate_and_export_sizes() != 0)           return 1;
    if (test_encap_decap_roundtrip() != 0)               return 1;
    if (test_import_public_key_and_encap() != 0)         return 1;
    if (test_tampered_ciphertext_implicit_rejection() != 0) return 1;
    if (test_wrong_ciphertext_length() != 0)             return 1;
    if (test_missing_usage() != 0)                       return 1;
    if (test_import_seed() != 0)                         return 1;
    if (test_buffer_too_small() != 0)                    return 1;

    printf("PSA ML-KEM test: OK\n");
    return 0;
}
