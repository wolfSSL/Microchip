/* psa_crypto_init_test.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "psa_api_test_user_settings.h"

#ifndef WOLFSSL_USER_SETTINGS
#define WOLFSSL_USER_SETTINGS
#endif

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/error-crypt.h>

#include <stdio.h>

#include <wolfpsa/psa/crypto.h>

static int g_wolfcrypt_init_calls;
static int g_wolfcrypt_init_result;

int __wrap_wolfCrypt_Init(void)
{
    g_wolfcrypt_init_calls++;
    return g_wolfcrypt_init_result;
}

static int expect_status(const char* label, psa_status_t status, psa_status_t expected)
{
    if (status != expected) {
        printf("FAIL %s status=%d expected=%d\n", label, (int)status, (int)expected);
        return 1;
    }

    return 0;
}

static int test_hash_requires_psa_crypto_init(void)
{
    static const uint8_t msg[] = "abc";
    static const uint8_t sha256_abc[] = {
        0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea,
        0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
        0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
        0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad
    };
    psa_hash_operation_t op = PSA_HASH_OPERATION_INIT;
    uint8_t hash[PSA_HASH_LENGTH(PSA_ALG_SHA_256)];
    size_t hash_length = 0;
    psa_status_t st;

    st = psa_hash_setup(&op, PSA_ALG_SHA_256);
    if (expect_status("psa_hash_setup before init", st,
                      PSA_ERROR_BAD_STATE) != 0) {
        return 1;
    }

    st = psa_hash_compute(PSA_ALG_SHA_256, msg, sizeof(msg) - 1, hash,
                          sizeof(hash), &hash_length);
    if (expect_status("psa_hash_compute before init", st,
                      PSA_ERROR_BAD_STATE) != 0) {
        return 1;
    }

    st = psa_hash_compare(PSA_ALG_SHA_256, msg, sizeof(msg) - 1, sha256_abc,
                          sizeof(sha256_abc));
    if (expect_status("psa_hash_compare before init", st,
                      PSA_ERROR_BAD_STATE) != 0) {
        return 1;
    }

    return 0;
}

static int test_hash_compare_rejects_null_reference(void)
{
    static const uint8_t msg[] = "abc";
    psa_status_t st;

    /* A NULL reference hash with a length matching the algorithm output size
     * must be rejected, not dereferenced. */
    st = psa_hash_compare(PSA_ALG_SHA_256, msg, sizeof(msg) - 1, NULL,
                          PSA_HASH_LENGTH(PSA_ALG_SHA_256));
    if (expect_status("psa_hash_compare NULL reference", st,
                      PSA_ERROR_INVALID_ARGUMENT) != 0) {
        return 1;
    }

    return 0;
}

static int test_random_requires_psa_crypto_init(void)
{
    uint8_t buf[16];
    psa_status_t st;

    st = psa_generate_random(buf, sizeof(buf));
    if (expect_status("psa_generate_random before init", st,
                      PSA_ERROR_BAD_STATE) != 0) {
        return 1;
    }

    return 0;
}

int main(void)
{
    psa_status_t st;

    if (test_hash_requires_psa_crypto_init() != 0) {
        return 1;
    }

    if (test_random_requires_psa_crypto_init() != 0) {
        return 1;
    }

    g_wolfcrypt_init_calls = 0;
    g_wolfcrypt_init_result = RNG_FAILURE_E;

    st = psa_crypto_init();
    if (expect_status("psa_crypto_init rng failure", st,
                      PSA_ERROR_INSUFFICIENT_ENTROPY) != 0) {
        return 1;
    }
    if (g_wolfcrypt_init_calls != 1) {
        printf("FAIL wolfCrypt_Init calls=%d expected=1\n", g_wolfcrypt_init_calls);
        return 1;
    }

    g_wolfcrypt_init_result = 0;
    st = psa_crypto_init();
    if (expect_status("psa_crypto_init success", st, PSA_SUCCESS) != 0) {
        return 1;
    }
    if (g_wolfcrypt_init_calls != 2) {
        printf("FAIL wolfCrypt_Init calls=%d expected=2\n", g_wolfcrypt_init_calls);
        return 1;
    }

    if (test_hash_compare_rejects_null_reference() != 0) {
        return 1;
    }

    printf("PSA crypto init test: OK\n");
    return 0;
}
