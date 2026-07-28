/* psa_ecc_bit_inference_test.c
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

#include <stdio.h>
#include <string.h>

#include <wolfpsa/psa/crypto.h>

static int check_inferred_bits(psa_key_type_t key_type, const uint8_t* key_data,
                               size_t key_data_len, psa_key_bits_t expected_bits,
                               const char* label)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_attributes_t got = psa_key_attributes_init();
    psa_key_id_t key_id = PSA_KEY_ID_NULL;
    psa_status_t st;

    psa_set_key_type(&attrs, key_type);
    psa_set_key_usage_flags(&attrs, PSA_KEY_USAGE_EXPORT);

    st = psa_import_key(&attrs, key_data, key_data_len, &key_id);
    if (st != PSA_SUCCESS) {
        printf("FAIL %s import status=%d\n", label, (int)st);
        return 1;
    }

    st = psa_get_key_attributes(key_id, &got);
    if (st != PSA_SUCCESS) {
        printf("FAIL %s attrs status=%d\n", label, (int)st);
        (void)psa_destroy_key(key_id);
        return 1;
    }

    if (psa_get_key_bits(&got) != expected_bits) {
        printf("FAIL %s bits=%u expected=%u\n", label,
               (unsigned)psa_get_key_bits(&got), (unsigned)expected_bits);
        (void)psa_destroy_key(key_id);
        return 1;
    }

    (void)psa_destroy_key(key_id);
    return 0;
}

static int test_public_key_bits(void)
{
    uint8_t pub[133];

    memset(pub, 0, sizeof(pub));
    pub[0] = 0x04;

    return check_inferred_bits(
        PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1),
        pub, sizeof(pub), 521, "secp521r1 public");
}

static int test_private_key_bits(void)
{
    uint8_t priv[66];
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_key_attributes_t got = psa_key_attributes_init();
    psa_key_id_t key_id = PSA_KEY_ID_NULL;
    psa_status_t st;

    memset(priv, 0, sizeof(priv));
    priv[sizeof(priv) - 1] = 1;

    psa_set_key_type(&attrs, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
    psa_set_key_usage_flags(&attrs, PSA_KEY_USAGE_EXPORT);

    st = psa_import_key(&attrs, priv, sizeof(priv), &key_id);
    if (st != PSA_SUCCESS) {
        printf("FAIL private import status=%d\n", (int)st);
        return 1;
    }

    st = psa_get_key_attributes(key_id, &got);
    if (st != PSA_SUCCESS) {
        printf("FAIL private attrs status=%d\n", (int)st);
        (void)psa_destroy_key(key_id);
        return 1;
    }

    if (psa_get_key_bits(&got) != 521) {
        printf("FAIL private bits=%u expected=521\n",
               (unsigned)psa_get_key_bits(&got));
        (void)psa_destroy_key(key_id);
        return 1;
    }

    (void)psa_destroy_key(key_id);
    return 0;
}

static int test_raw_public_key_bits(void)
{
    uint8_t x25519_pub[32];
    uint8_t ed25519_pub[32];
    uint8_t ed448_pub[57];

    memset(x25519_pub, 0xA5, sizeof(x25519_pub));
    memset(ed25519_pub, 0x5A, sizeof(ed25519_pub));
    memset(ed448_pub, 0x3C, sizeof(ed448_pub));

    if (check_inferred_bits(
            PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_MONTGOMERY),
            x25519_pub, sizeof(x25519_pub), 255, "x25519 public") != 0) {
        return 1;
    }

    if (check_inferred_bits(
            PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS),
            ed25519_pub, sizeof(ed25519_pub), 255, "ed25519 public") != 0) {
        return 1;
    }

    return check_inferred_bits(
        PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS),
        ed448_pub, sizeof(ed448_pub), 448, "ed448 public");
}

int main(void)
{
    psa_status_t st = psa_crypto_init();
    if (st != PSA_SUCCESS) {
        printf("FAIL psa_crypto_init status=%d\n", (int)st);
        return 1;
    }

    if (test_public_key_bits() != 0) {
        return 1;
    }
    if (test_private_key_bits() != 0) {
        return 1;
    }
    if (test_raw_public_key_bits() != 0) {
        return 1;
    }

    printf("PSA ECC bit inference test: OK\n");
    return 0;
}
