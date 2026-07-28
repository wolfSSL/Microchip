/* psa_montgomery.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#if defined(WOLFSSL_PSA_ENGINE) && \
    (defined(HAVE_CURVE25519) || defined(HAVE_CURVE448))

#include <psa/crypto.h>
#include "psa_size.h"
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/random.h>

#ifdef HAVE_CURVE25519
#include <wolfssl/wolfcrypt/curve25519.h>
#endif

#ifdef HAVE_CURVE448
#include <wolfssl/wolfcrypt/curve448.h>
#endif

#if defined(HAVE_CURVE25519) && defined(HAVE_CURVE25519_KEY_IMPORT) && \
    defined(HAVE_CURVE25519_KEY_EXPORT)
psa_status_t psa_asymmetric_generate_key_x25519(psa_key_type_t key_type,
                                                size_t key_bits,
                                                uint8_t *private_key,
                                                size_t private_key_size,
                                                size_t *private_key_length,
                                                uint8_t *public_key,
                                                size_t public_key_size,
                                                size_t *public_key_length)
{
    int ret;
    curve25519_key key;
    WC_RNG rng;
    word32 priv_len;
    word32 pub_len;

    if (key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY) ||
        key_bits != 255) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (private_key == NULL || private_key_length == NULL ||
        public_key == NULL || public_key_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(private_key_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(public_key_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    priv_len = (word32)private_key_size;
    pub_len = (word32)public_key_size;

    ret = wc_curve25519_init(&key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }
    ret = wc_InitRng(&rng);
    if (ret != 0) {
        wc_curve25519_free(&key);
        return wc_error_to_psa_status(ret);
    }

    ret = wc_curve25519_make_key(&rng, CURVE25519_KEYSIZE, &key);
    if (ret == 0) {
        ret = wc_curve25519_export_private_raw_ex(&key, private_key,
                                                  &priv_len,
                                                  EC25519_LITTLE_ENDIAN);
    }
    if (ret == 0) {
        ret = wc_curve25519_export_public_ex(&key, public_key, &pub_len,
                                             EC25519_LITTLE_ENDIAN);
    }

    wc_FreeRng(&rng);
    wc_curve25519_free(&key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *private_key_length = (size_t)priv_len;
    *public_key_length = (size_t)pub_len;
    return PSA_SUCCESS;
}

psa_status_t psa_asymmetric_export_public_key_x25519(psa_key_type_t key_type,
                                                     size_t key_bits,
                                                     const uint8_t *key_buffer,
                                                     size_t key_buffer_size,
                                                     uint8_t *output,
                                                     size_t output_size,
                                                     size_t *output_length)
{
    int ret;
    uint8_t priv[CURVE25519_KEYSIZE];

    if ((key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY) &&
         key_type != PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_MONTGOMERY)) ||
        key_bits != 255) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (key_buffer == NULL || output == NULL || output_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (output_size < CURVE25519_KEYSIZE) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (key_type == PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY)) {
        if (key_buffer_size != CURVE25519_KEYSIZE) {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        XMEMCPY(priv, key_buffer, CURVE25519_KEYSIZE);
        priv[0] &= 248;
        priv[31] &= 127;
        priv[31] |= 64;
        ret = wc_curve25519_make_pub(CURVE25519_KEYSIZE, output,
                                     CURVE25519_KEYSIZE, priv);
        wc_ForceZero(priv, sizeof(priv));
    }
    else {
        if (key_buffer_size != CURVE25519_KEYSIZE) {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        XMEMCPY(output, key_buffer, CURVE25519_KEYSIZE);
        ret = 0;
    }

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *output_length = CURVE25519_KEYSIZE;
    return PSA_SUCCESS;
}
#endif

#if defined(HAVE_CURVE25519) && defined(HAVE_CURVE25519_KEY_IMPORT) && \
    defined(HAVE_CURVE25519_SHARED_SECRET)
psa_status_t psa_asymmetric_key_agreement_x25519(
    const uint8_t *private_key,
    size_t private_key_length,
    const uint8_t *peer_key,
    size_t peer_key_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
{
    int ret;
    curve25519_key priv;
    curve25519_key pub;
    uint8_t peer[CURVE25519_KEYSIZE];
    word32 out_len;
#ifdef WOLFSSL_CURVE25519_BLINDING
    WC_RNG rng;
#endif

    if (private_key == NULL || peer_key == NULL || output == NULL ||
        output_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (private_key_length != CURVE25519_KEYSIZE ||
        peer_key_length != CURVE25519_KEYSIZE) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (output_size < CURVE25519_KEYSIZE) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }
    if (wolfpsa_check_word32_length(output_size) != PSA_SUCCESS) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    out_len = (word32)output_size;

    ret = wc_curve25519_init(&priv);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }
    ret = wc_curve25519_init(&pub);
    if (ret != 0) {
        wc_curve25519_free(&priv);
        return wc_error_to_psa_status(ret);
    }
#ifdef WOLFSSL_CURVE25519_BLINDING
    ret = wc_InitRng(&rng);
    if (ret != 0) {
        wc_curve25519_free(&pub);
        wc_curve25519_free(&priv);
        return wc_error_to_psa_status(ret);
    }
    ret = wc_curve25519_set_rng(&priv, &rng);
    if (ret != 0) {
        wc_FreeRng(&rng);
        wc_curve25519_free(&pub);
        wc_curve25519_free(&priv);
        return wc_error_to_psa_status(ret);
    }
#endif

    XMEMCPY(peer, peer_key, CURVE25519_KEYSIZE);
    peer[CURVE25519_KEYSIZE - 1] &= 127;

    ret = wc_curve25519_import_private_ex(private_key,
                                          (word32)private_key_length, &priv,
                                          EC25519_LITTLE_ENDIAN);
    if (ret == 0) {
        ret = wc_curve25519_import_public_ex(peer, (word32)peer_key_length,
                                             &pub, EC25519_LITTLE_ENDIAN);
    }
    if (ret == 0) {
        ret = wc_curve25519_shared_secret_ex(&priv, &pub, output, &out_len,
                                             EC25519_LITTLE_ENDIAN);
    }

    wc_ForceZero(peer, sizeof(peer));
#ifdef WOLFSSL_CURVE25519_BLINDING
    wc_FreeRng(&rng);
#endif
    wc_curve25519_free(&pub);
    wc_curve25519_free(&priv);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *output_length = (size_t)out_len;
    return PSA_SUCCESS;
}
#endif

#if defined(HAVE_CURVE448) && defined(HAVE_CURVE448_KEY_IMPORT) && \
    defined(HAVE_CURVE448_KEY_EXPORT)
psa_status_t psa_asymmetric_generate_key_x448(psa_key_type_t key_type,
                                              size_t key_bits,
                                              uint8_t *private_key,
                                              size_t private_key_size,
                                              size_t *private_key_length,
                                              uint8_t *public_key,
                                              size_t public_key_size,
                                              size_t *public_key_length)
{
    int ret;
    curve448_key key;
    WC_RNG rng;
    word32 priv_len;
    word32 pub_len;

    if (key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY) ||
        key_bits != 448) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (private_key == NULL || private_key_length == NULL ||
        public_key == NULL || public_key_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(private_key_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(public_key_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    priv_len = (word32)private_key_size;
    pub_len = (word32)public_key_size;

    ret = wc_curve448_init(&key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }
    ret = wc_InitRng(&rng);
    if (ret != 0) {
        wc_curve448_free(&key);
        return wc_error_to_psa_status(ret);
    }

    ret = wc_curve448_make_key(&rng, CURVE448_KEY_SIZE, &key);
    if (ret == 0) {
        ret = wc_curve448_export_private_raw_ex(&key, private_key, &priv_len,
                                                EC448_LITTLE_ENDIAN);
    }
    if (ret == 0) {
        ret = wc_curve448_export_public_ex(&key, public_key, &pub_len,
                                           EC448_LITTLE_ENDIAN);
    }

    wc_FreeRng(&rng);
    wc_curve448_free(&key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *private_key_length = (size_t)priv_len;
    *public_key_length = (size_t)pub_len;
    return PSA_SUCCESS;
}

psa_status_t psa_asymmetric_export_public_key_x448(psa_key_type_t key_type,
                                                   size_t key_bits,
                                                   const uint8_t *key_buffer,
                                                   size_t key_buffer_size,
                                                   uint8_t *output,
                                                   size_t output_size,
                                                   size_t *output_length)
{
    int ret;
    uint8_t priv[CURVE448_KEY_SIZE];

    if ((key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY) &&
         key_type != PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_MONTGOMERY)) ||
        key_bits != 448) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (key_buffer == NULL || output == NULL || output_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (output_size < CURVE448_KEY_SIZE) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (key_type == PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY)) {
        if (key_buffer_size != CURVE448_KEY_SIZE) {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        XMEMCPY(priv, key_buffer, CURVE448_KEY_SIZE);
        priv[0] &= 252;
        priv[55] |= 128;
        ret = wc_curve448_make_pub(CURVE448_KEY_SIZE, output,
                                   CURVE448_KEY_SIZE, priv);
        wc_ForceZero(priv, sizeof(priv));
    }
    else {
        if (key_buffer_size != CURVE448_KEY_SIZE) {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        XMEMCPY(output, key_buffer, CURVE448_KEY_SIZE);
        ret = 0;
    }

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *output_length = CURVE448_KEY_SIZE;
    return PSA_SUCCESS;
}
#endif

#if defined(HAVE_CURVE448) && defined(HAVE_CURVE448_KEY_IMPORT) && \
    defined(HAVE_CURVE448_SHARED_SECRET)
psa_status_t psa_asymmetric_key_agreement_x448(
    const uint8_t *private_key,
    size_t private_key_length,
    const uint8_t *peer_key,
    size_t peer_key_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
{
    int ret;
    curve448_key priv;
    curve448_key pub;
    word32 out_len;

    if (private_key == NULL || peer_key == NULL || output == NULL ||
        output_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (private_key_length != CURVE448_KEY_SIZE ||
        peer_key_length != CURVE448_KEY_SIZE) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (output_size < CURVE448_KEY_SIZE) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }
    if (wolfpsa_check_word32_length(output_size) != PSA_SUCCESS) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    out_len = (word32)output_size;

    ret = wc_curve448_init(&priv);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }
    ret = wc_curve448_init(&pub);
    if (ret != 0) {
        wc_curve448_free(&priv);
        return wc_error_to_psa_status(ret);
    }

    ret = wc_curve448_import_private_ex(private_key,
                                        (word32)private_key_length, &priv,
                                        EC448_LITTLE_ENDIAN);
    if (ret == 0) {
        ret = wc_curve448_import_public_ex(peer_key, (word32)peer_key_length,
                                           &pub, EC448_LITTLE_ENDIAN);
    }
    if (ret == 0) {
        ret = wc_curve448_shared_secret_ex(&priv, &pub, output, &out_len,
                                           EC448_LITTLE_ENDIAN);
    }

    wc_curve448_free(&pub);
    wc_curve448_free(&priv);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *output_length = (size_t)out_len;
    return PSA_SUCCESS;
}
#endif

#endif
