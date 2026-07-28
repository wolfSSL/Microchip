/* psa_aead_internal.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFPSA_PSA_AEAD_INTERNAL_H
#define WOLFPSA_PSA_AEAD_INTERNAL_H

#include <stdint.h>

#include <wolfpsa/psa/crypto.h>

typedef struct wolfpsa_aead_ctx {
    psa_algorithm_t alg;
    psa_key_type_t key_type;
    size_t key_bits;
    int direction;
    uint8_t *key;
    size_t key_length;
    uint8_t nonce[PSA_AEAD_NONCE_MAX_SIZE];
    size_t nonce_length;
    uint8_t *aad;
    size_t aad_length;
    uint8_t *input;
    size_t input_length;
    size_t ad_expected;
    size_t plaintext_expected;
    size_t tag_length;
    int lengths_set;
} wolfpsa_aead_ctx_t;

static inline wolfpsa_aead_ctx_t*
wolfpsa_aead_get_ctx_ptr(psa_aead_operation_t *operation)
{
    if (operation == NULL) {
        return NULL;
    }

    return (wolfpsa_aead_ctx_t *)(uintptr_t)operation->opaque;
}

#endif /* WOLFPSA_PSA_AEAD_INTERNAL_H */
