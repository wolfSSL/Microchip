/* psa_des3_stack_scrub_test.c
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

int main(void)
{
    static const uint8_t two_key_tdes[16] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
    };
    static const uint8_t three_key_tdes[24] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
        0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67
    };
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_cipher_operation_t op = psa_cipher_operation_init();
    psa_key_id_t key_id = PSA_KEY_ID_NULL;
    psa_status_t st;

    st = psa_crypto_init();
    if (st != PSA_SUCCESS) {
        printf("FAIL psa_crypto_init status=%d\n", (int)st);
        return 1;
    }

    psa_set_key_type(&attrs, PSA_KEY_TYPE_DES);
    psa_set_key_bits(&attrs, 128);
    psa_set_key_usage_flags(&attrs, PSA_KEY_USAGE_ENCRYPT);
    psa_set_key_algorithm(&attrs, PSA_ALG_CBC_NO_PADDING);

    st = psa_import_key(&attrs, two_key_tdes, sizeof(two_key_tdes), &key_id);
    if (st != PSA_ERROR_NOT_SUPPORTED) {
        printf("FAIL psa_import_key accepted 2-key 3DES status=%d\n", (int)st);
        if (st == PSA_SUCCESS) {
            (void)psa_destroy_key(key_id);
        }
        return 1;
    }

    psa_reset_key_attributes(&attrs);
    attrs = psa_key_attributes_init();
    key_id = PSA_KEY_ID_NULL;

    psa_set_key_type(&attrs, PSA_KEY_TYPE_DES);
    psa_set_key_bits(&attrs, 192);
    psa_set_key_usage_flags(&attrs, PSA_KEY_USAGE_ENCRYPT);
    psa_set_key_algorithm(&attrs, PSA_ALG_CBC_NO_PADDING);

    st = psa_import_key(&attrs, three_key_tdes, sizeof(three_key_tdes),
                        &key_id);
    if (st != PSA_SUCCESS) {
        printf("FAIL psa_import_key status=%d\n", (int)st);
        return 1;
    }

    st = psa_cipher_encrypt_setup(&op, key_id, PSA_ALG_CBC_NO_PADDING);
    if (st != PSA_SUCCESS) {
        printf("FAIL psa_cipher_encrypt_setup status=%d\n", (int)st);
        (void)psa_destroy_key(key_id);
        return 1;
    }

    (void)psa_cipher_abort(&op);
    (void)psa_destroy_key(key_id);
    puts("PSA DES3 setup test: OK");
    return 0;
}
