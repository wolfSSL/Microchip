/* psa_sign_context_test.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*
 * Coverage test for PSA 1.4 with-context signature functions:
 *   psa_sign_message_with_context / psa_verify_message_with_context
 *   psa_sign_hash_with_context    / psa_verify_hash_with_context
 *
 * Test cases:
 *  1. ML-DSA-65: sign with context, verify same/different/empty context.
 *  2. ML-DSA-65: plain psa_sign_message is equivalent to empty context.
 *  3. Ed25519 PSA_ALG_EDDSA_CTX: sign/verify with context; mismatch fails.
 *  4. ECDSA secp256r1: non-empty context → INVALID_ARGUMENT; empty → success.
 *  5. Context > 255 bytes → INVALID_ARGUMENT for any algorithm.
 *  6. HashML-DSA: sign_hash_with_context / verify_hash_with_context round-trip.
 */

#include <wolfssl/options.h>
#include "psa_api_test_user_settings.h"

#ifndef WOLFSSL_USER_SETTINGS
#define WOLFSSL_USER_SETTINGS
#endif

#include <wolfssl/wolfcrypt/settings.h>

#include <stdio.h>
#include <string.h>

#include <wolfpsa/psa/crypto.h>

/* ML-DSA-65 signature size: 3309 bytes */
#define MLDSA_65_SIG_SIZE   3309u

static const uint8_t g_msg[] = "psa sign context test message";

static int expect_status(const char *label, psa_status_t status,
                         psa_status_t expected)
{
    if (status != expected) {
        printf("FAIL %s status=%d expected=%d\n", label, (int)status,
               (int)expected);
        return 1;
    }
    return 0;
}

/*
 * Test 1: ML-DSA-65 context sign/verify.
 *   - sign with context "test-ctx"
 *   - verify with same context → PSA_SUCCESS
 *   - verify with different context → PSA_ERROR_INVALID_SIGNATURE
 *   - verify with empty context → PSA_ERROR_INVALID_SIGNATURE
 */
static int test_mldsa65_context_mismatch(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_id_t key_id = 0;
    psa_status_t st;
    uint8_t sig[MLDSA_65_SIG_SIZE];
    size_t sig_len = 0;
    static const uint8_t ctx_a[] = "test-ctx";
    static const uint8_t ctx_b[] = "wrong-ctx";
    int ret = 0;

    psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_DSA_KEY_PAIR);
    psa_set_key_bits(&attrs, 192);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE);
    psa_set_key_algorithm(&attrs, PSA_ALG_ML_DSA);

    st = psa_generate_key(&attrs, &key_id);
    if (st == PSA_ERROR_NOT_SUPPORTED) {
        printf("SKIP test_mldsa65_context_mismatch (ML-DSA not supported)\n");
        return 0;
    }
    if (expect_status("mldsa65_ctx: generate_key", st, PSA_SUCCESS) != 0)
        return 1;

    /* Sign with context "test-ctx" */
    st = psa_sign_message_with_context(key_id, PSA_ALG_ML_DSA,
                                       g_msg, sizeof(g_msg) - 1,
                                       ctx_a, sizeof(ctx_a) - 1,
                                       sig, sizeof(sig), &sig_len);
    if (expect_status("mldsa65_ctx: sign with ctx_a", st, PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

    /* Verify with the same context → OK */
    st = psa_verify_message_with_context(key_id, PSA_ALG_ML_DSA,
                                         g_msg, sizeof(g_msg) - 1,
                                         ctx_a, sizeof(ctx_a) - 1,
                                         sig, sig_len);
    if (expect_status("mldsa65_ctx: verify same ctx", st, PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

    /* Verify with a different context → INVALID_SIGNATURE */
    st = psa_verify_message_with_context(key_id, PSA_ALG_ML_DSA,
                                         g_msg, sizeof(g_msg) - 1,
                                         ctx_b, sizeof(ctx_b) - 1,
                                         sig, sig_len);
    if (expect_status("mldsa65_ctx: verify diff ctx", st,
                      PSA_ERROR_INVALID_SIGNATURE) != 0) {
        ret = 1;
        goto done;
    }

    /* Verify with empty context → INVALID_SIGNATURE */
    st = psa_verify_message_with_context(key_id, PSA_ALG_ML_DSA,
                                         g_msg, sizeof(g_msg) - 1,
                                         NULL, 0,
                                         sig, sig_len);
    if (expect_status("mldsa65_ctx: verify empty ctx", st,
                      PSA_ERROR_INVALID_SIGNATURE) != 0) {
        ret = 1;
        goto done;
    }

done:
    (void)psa_destroy_key(key_id);
    return ret;
}

/*
 * Test 2: ML-DSA-65 empty-context equivalence.
 *   psa_sign_message (no context) is equivalent to an empty context.
 *   Sign via psa_sign_message, then verify via
 *   psa_verify_message_with_context with empty context → PSA_SUCCESS.
 *
 *   Signatures are hedged/randomized so byte equality cannot be checked;
 *   we use cross-API verify to prove semantic equivalence.
 */
static int test_mldsa65_empty_ctx_equivalence(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_id_t key_id = 0;
    psa_status_t st;
    uint8_t sig[MLDSA_65_SIG_SIZE];
    size_t sig_len = 0;
    int ret = 0;

    psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_DSA_KEY_PAIR);
    psa_set_key_bits(&attrs, 192);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE);
    psa_set_key_algorithm(&attrs, PSA_ALG_ML_DSA);

    st = psa_generate_key(&attrs, &key_id);
    if (st == PSA_ERROR_NOT_SUPPORTED) {
        printf("SKIP test_mldsa65_empty_ctx_equivalence (ML-DSA not supported)\n");
        return 0;
    }
    if (expect_status("mldsa65_equiv: generate_key", st, PSA_SUCCESS) != 0)
        return 1;

    /* Sign via plain psa_sign_message (empty context) */
    st = psa_sign_message(key_id, PSA_ALG_ML_DSA,
                          g_msg, sizeof(g_msg) - 1,
                          sig, sizeof(sig), &sig_len);
    if (expect_status("mldsa65_equiv: plain sign_message", st,
                      PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

    /* Verify via psa_verify_message_with_context with empty context → OK */
    st = psa_verify_message_with_context(key_id, PSA_ALG_ML_DSA,
                                         g_msg, sizeof(g_msg) - 1,
                                         NULL, 0,
                                         sig, sig_len);
    if (expect_status("mldsa65_equiv: verify_with_context(empty)", st,
                      PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

done:
    (void)psa_destroy_key(key_id);
    return ret;
}

/*
 * Test 3: Ed25519 PSA_ALG_EDDSA_CTX context round-trip and mismatch.
 *   - Generate Ed25519 key with PSA_ALG_EDDSA_CTX policy.
 *   - sign_message_with_context("ctx") / verify same → PSA_SUCCESS.
 *   - verify with different context → PSA_ERROR_INVALID_SIGNATURE.
 */
static int test_ed25519_eddsa_ctx(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_id_t key_id = 0;
    psa_status_t st;
    uint8_t sig[64];
    size_t sig_len = 0;
    static const uint8_t ctx[]       = "ctx";
    static const uint8_t ctx_other[] = "other-ctx";
    int ret = 0;

    psa_set_key_type(&attrs,
        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS));
    psa_set_key_bits(&attrs, 255);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE);
    psa_set_key_algorithm(&attrs, PSA_ALG_EDDSA_CTX);

    st = psa_generate_key(&attrs, &key_id);
    if (st == PSA_ERROR_NOT_SUPPORTED) {
        printf("SKIP test_ed25519_eddsa_ctx (Ed25519 not supported)\n");
        return 0;
    }
    if (expect_status("ed25519ctx: generate_key", st, PSA_SUCCESS) != 0)
        return 1;

    /* Sign with context "ctx" */
    st = psa_sign_message_with_context(key_id, PSA_ALG_EDDSA_CTX,
                                       g_msg, sizeof(g_msg) - 1,
                                       ctx, sizeof(ctx) - 1,
                                       sig, sizeof(sig), &sig_len);
    if (expect_status("ed25519ctx: sign with ctx", st, PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }
    if (sig_len != 64u) {
        printf("FAIL ed25519ctx: sig_len=%zu expected=64\n", sig_len);
        ret = 1;
        goto done;
    }

    /* Verify with same context → OK */
    st = psa_verify_message_with_context(key_id, PSA_ALG_EDDSA_CTX,
                                         g_msg, sizeof(g_msg) - 1,
                                         ctx, sizeof(ctx) - 1,
                                         sig, sig_len);
    if (expect_status("ed25519ctx: verify same ctx", st, PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

    /* Verify with different context → INVALID_SIGNATURE */
    st = psa_verify_message_with_context(key_id, PSA_ALG_EDDSA_CTX,
                                         g_msg, sizeof(g_msg) - 1,
                                         ctx_other, sizeof(ctx_other) - 1,
                                         sig, sig_len);
    if (expect_status("ed25519ctx: verify diff ctx", st,
                      PSA_ERROR_INVALID_SIGNATURE) != 0) {
        ret = 1;
        goto done;
    }

done:
    (void)psa_destroy_key(key_id);
    return ret;
}

/*
 * Test 4: ECDSA secp256r1 — non-empty context is rejected.
 *   - Non-empty context → PSA_ERROR_INVALID_ARGUMENT.
 *   - Empty context → PSA_SUCCESS (context is a no-op for ECDSA).
 *   - Plain psa_verify_message accepts the empty-context signature.
 */
static int test_ecdsa_context_rejected(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_id_t key_id = 0;
    psa_status_t st;
    uint8_t sig[128];
    size_t sig_len = 0;
    static const uint8_t ctx4[] = "abcd";
    int ret = 0;

    psa_set_key_type(&attrs,
        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_bits(&attrs, 256);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE);
    psa_set_key_algorithm(&attrs, PSA_ALG_ECDSA(PSA_ALG_SHA_256));

    st = psa_generate_key(&attrs, &key_id);
    if (st == PSA_ERROR_NOT_SUPPORTED) {
        printf("SKIP test_ecdsa_context_rejected (ECDSA not supported)\n");
        return 0;
    }
    if (expect_status("ecdsa_ctx: generate_key", st, PSA_SUCCESS) != 0)
        return 1;

    /* Non-empty context (4 bytes) → INVALID_ARGUMENT */
    st = psa_sign_message_with_context(key_id, PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                                       g_msg, sizeof(g_msg) - 1,
                                       ctx4, sizeof(ctx4) - 1,
                                       sig, sizeof(sig), &sig_len);
    if (expect_status("ecdsa_ctx: sign with nonempty ctx", st,
                      PSA_ERROR_INVALID_ARGUMENT) != 0) {
        ret = 1;
        goto done;
    }

    /* Empty context → success */
    sig_len = 0;
    st = psa_sign_message_with_context(key_id, PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                                       g_msg, sizeof(g_msg) - 1,
                                       NULL, 0,
                                       sig, sizeof(sig), &sig_len);
    if (expect_status("ecdsa_ctx: sign with empty ctx", st,
                      PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

    /* Plain psa_verify_message accepts the empty-context signature */
    st = psa_verify_message(key_id, PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                            g_msg, sizeof(g_msg) - 1,
                            sig, sig_len);
    if (expect_status("ecdsa_ctx: plain verify_message of empty-ctx sig", st,
                      PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

done:
    (void)psa_destroy_key(key_id);
    return ret;
}

/*
 * Test 5: Context longer than 255 bytes → PSA_ERROR_INVALID_ARGUMENT.
 *   Tested with ECDSA (any algorithm applies, as this check is universal).
 */
static int test_overlong_context_rejected(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_id_t key_id = 0;
    psa_status_t st;
    uint8_t sig[128];
    size_t sig_len = 0;
    uint8_t long_ctx[256];
    int ret = 0;

    memset(long_ctx, 0xBB, sizeof(long_ctx));

    psa_set_key_type(&attrs,
        PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_bits(&attrs, 256);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE);
    psa_set_key_algorithm(&attrs, PSA_ALG_ECDSA(PSA_ALG_SHA_256));

    st = psa_generate_key(&attrs, &key_id);
    if (st == PSA_ERROR_NOT_SUPPORTED) {
        printf("SKIP test_overlong_context_rejected (ECDSA not supported)\n");
        return 0;
    }
    if (expect_status("overlong_ctx: generate_key", st, PSA_SUCCESS) != 0)
        return 1;

    /* 256-byte context (> 255 limit) → INVALID_ARGUMENT */
    st = psa_sign_message_with_context(key_id, PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                                       g_msg, sizeof(g_msg) - 1,
                                       long_ctx, sizeof(long_ctx),
                                       sig, sizeof(sig), &sig_len);
    if (expect_status("overlong_ctx: 256-byte ctx rejected", st,
                      PSA_ERROR_INVALID_ARGUMENT) != 0) {
        ret = 1;
        goto done;
    }

done:
    (void)psa_destroy_key(key_id);
    return ret;
}

/*
 * Test 6: HashML-DSA — psa_sign_hash_with_context / psa_verify_hash_with_context.
 *   - Key policy: PSA_ALG_HASH_ML_DSA(PSA_ALG_SHA_256).
 *   - Compute SHA-256 digest, sign_hash_with_context("abc").
 *   - verify_hash_with_context same context → PSA_SUCCESS.
 *   - verify_hash_with_context different context → PSA_ERROR_INVALID_SIGNATURE.
 */
static int test_hash_mldsa65_context(void)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_id_t key_id = 0;
    psa_status_t st;
    uint8_t sig[MLDSA_65_SIG_SIZE];
    size_t sig_len = 0;
    uint8_t hash[PSA_HASH_LENGTH(PSA_ALG_SHA_256)];
    size_t hash_len = 0;
    static const uint8_t ctx[]       = "abc";
    static const uint8_t ctx_other[] = "xyz";
    int ret = 0;

    psa_set_key_type(&attrs, PSA_KEY_TYPE_ML_DSA_KEY_PAIR);
    psa_set_key_bits(&attrs, 192);
    psa_set_key_usage_flags(&attrs,
        PSA_KEY_USAGE_SIGN_HASH   | PSA_KEY_USAGE_VERIFY_HASH |
        PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE);
    psa_set_key_algorithm(&attrs, PSA_ALG_HASH_ML_DSA(PSA_ALG_SHA_256));

    st = psa_generate_key(&attrs, &key_id);
    if (st == PSA_ERROR_NOT_SUPPORTED) {
        printf("SKIP test_hash_mldsa65_context (HashML-DSA not supported)\n");
        return 0;
    }
    if (expect_status("hash_mldsa65: generate_key", st, PSA_SUCCESS) != 0)
        return 1;

    /* Compute SHA-256 digest of the message */
    st = psa_hash_compute(PSA_ALG_SHA_256,
                          g_msg, sizeof(g_msg) - 1,
                          hash, sizeof(hash), &hash_len);
    if (expect_status("hash_mldsa65: psa_hash_compute", st,
                      PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

    /* Sign hash with context "abc" */
    st = psa_sign_hash_with_context(key_id,
                                    PSA_ALG_HASH_ML_DSA(PSA_ALG_SHA_256),
                                    hash, hash_len,
                                    ctx, sizeof(ctx) - 1,
                                    sig, sizeof(sig), &sig_len);
    if (expect_status("hash_mldsa65: sign_hash_with_context(abc)", st,
                      PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

    /* Verify same context → OK */
    st = psa_verify_hash_with_context(key_id,
                                      PSA_ALG_HASH_ML_DSA(PSA_ALG_SHA_256),
                                      hash, hash_len,
                                      ctx, sizeof(ctx) - 1,
                                      sig, sig_len);
    if (expect_status("hash_mldsa65: verify_hash_with_context same ctx", st,
                      PSA_SUCCESS) != 0) {
        ret = 1;
        goto done;
    }

    /* Verify different context → INVALID_SIGNATURE */
    st = psa_verify_hash_with_context(key_id,
                                      PSA_ALG_HASH_ML_DSA(PSA_ALG_SHA_256),
                                      hash, hash_len,
                                      ctx_other, sizeof(ctx_other) - 1,
                                      sig, sig_len);
    if (expect_status("hash_mldsa65: verify_hash_with_context diff ctx", st,
                      PSA_ERROR_INVALID_SIGNATURE) != 0) {
        ret = 1;
        goto done;
    }

done:
    (void)psa_destroy_key(key_id);
    return ret;
}

int main(void)
{
    psa_status_t st;

    st = psa_crypto_init();
    if (st != PSA_SUCCESS) {
        printf("FAIL psa_crypto_init status=%d\n", (int)st);
        return 1;
    }

    if (test_mldsa65_context_mismatch() != 0)
        return 1;

    if (test_mldsa65_empty_ctx_equivalence() != 0)
        return 1;

    if (test_ed25519_eddsa_ctx() != 0)
        return 1;

    if (test_ecdsa_context_rejected() != 0)
        return 1;

    if (test_overlong_context_rejected() != 0)
        return 1;

    if (test_hash_mldsa65_context() != 0)
        return 1;

    printf("PSA sign context test: OK\n");
    return 0;
}
