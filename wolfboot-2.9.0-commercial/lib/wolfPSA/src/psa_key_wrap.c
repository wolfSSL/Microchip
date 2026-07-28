/* psa_key_wrap.c
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

#if defined(WOLFSSL_PSA_ENGINE)

#include <psa/crypto.h>
#include "psa_trace.h"
#include <wolfpsa/psa_engine.h>
#include <wolfpsa/psa_key_storage.h>
#include <wolfssl/wolfcrypt/aes.h>
#include <wolfssl/wolfcrypt/mem_track.h>

/*
 * psa_wrap_key: RFC 3394 AES Key Wrap (PSA_ALG_KW).
 *
 * Exports the target key's raw material via psa_export_key() (which itself
 * enforces PSA_KEY_USAGE_EXPORT on the target key), then encrypts it with
 * the wrapping key using wc_AesKeyWrap().
 */
psa_status_t psa_wrap_key(psa_key_id_t wrapping_key,
                           psa_algorithm_t alg,
                           psa_key_id_t key,
                           uint8_t *data,
                           size_t data_size,
                           size_t *data_length)
{
#ifdef HAVE_AES_KEYWRAP
    psa_status_t status;
    psa_key_attributes_t wrap_attr;
    psa_key_attributes_t target_attr;
    psa_key_type_t wrap_type;
    psa_key_usage_t wrap_usage;
    psa_algorithm_t wrap_alg;
    uint8_t *kek = NULL;
    size_t kek_len = 0;
    uint8_t *plaintext = NULL;
    size_t plain_max;
    size_t exported_len = 0;
    int wret;
#endif

    wolfpsa_trace("psa_wrap_key(wrapping_key=%u alg=0x%08x key=%u)",
                  (unsigned)wrapping_key, (unsigned)alg, (unsigned)key);

    /* Validate output pointers */
    if (data == NULL || data_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Only key-wrap category algorithms are accepted */
    if (!PSA_ALG_IS_KEY_WRAP(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* KWP is not implemented by wolfCrypt */
    if (alg == PSA_ALG_KWP) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Only PSA_ALG_KW remains valid at this point */
    if (alg != PSA_ALG_KW) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

#ifdef HAVE_AES_KEYWRAP
    /* Load and validate the wrapping key */
    status = wolfpsa_get_key_data(wrapping_key, &wrap_attr, &kek, &kek_len);
    if (status != PSA_SUCCESS) {
        return status;
    }

    wrap_type = psa_get_key_type(&wrap_attr);
    if (wrap_type != PSA_KEY_TYPE_AES) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    wrap_usage = psa_get_key_usage_flags(&wrap_attr);
    if ((wrap_usage & PSA_KEY_USAGE_WRAP) == 0) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_NOT_PERMITTED;
    }

    wrap_alg = psa_get_key_algorithm(&wrap_attr);
    if (wrap_alg == PSA_ALG_NONE || wrap_alg != alg) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_NOT_PERMITTED;
    }

    /* Obtain the target key's attributes to size the export buffer */
    status = psa_get_key_attributes(key, &target_attr);
    if (status != PSA_SUCCESS) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return status;
    }

    plain_max = PSA_EXPORT_KEY_OUTPUT_SIZE(psa_get_key_type(&target_attr),
                                           psa_get_key_bits(&target_attr));
    if (plain_max == 0) {
        /* Unknown key type — fall back to a reasonable maximum */
        plain_max = PSA_EXPORT_KEY_PAIR_OR_PUBLIC_MAX_SIZE;
    }

    plaintext = (uint8_t *)XMALLOC(plain_max, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    if (plaintext == NULL) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    /*
     * psa_export_key enforces PSA_KEY_USAGE_EXPORT on the target key
     * (verified in src/psa_key_storage.c at lines 1331-1334 for volatile
     * keys and lines 1355-1357 for persistent keys).
     */
    status = psa_export_key(key, plaintext, plain_max, &exported_len);
    if (status != PSA_SUCCESS) {
        wc_ForceZero(plaintext, plain_max);
        XFREE(plaintext, NULL, DYNAMIC_TYPE_TMP_BUFFER);
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return status;
    }

    /* RFC 3394 requires the plaintext to be a multiple of 8 and >= 16 */
    if (exported_len < 16 || (exported_len % 8) != 0) {
        wc_ForceZero(plaintext, plain_max);
        XFREE(plaintext, NULL, DYNAMIC_TYPE_TMP_BUFFER);
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check that the caller's output buffer is large enough */
    if (data_size < exported_len + 8) {
        wc_ForceZero(plaintext, plain_max);
        XFREE(plaintext, NULL, DYNAMIC_TYPE_TMP_BUFFER);
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Perform RFC 3394 key wrap; pass iv=NULL to use the default IV */
    wret = wc_AesKeyWrap(kek, (word32)kek_len,
                         plaintext, (word32)exported_len,
                         data, (word32)data_size,
                         NULL);

    wc_ForceZero(plaintext, plain_max);
    XFREE(plaintext, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    wolfpsa_forcezero_free_key_data(kek, kek_len);

    if (wret < 0) {
        return wc_error_to_psa_status(wret);
    }

    *data_length = (size_t)wret;
    return PSA_SUCCESS;

#else /* HAVE_AES_KEYWRAP */
    (void)wrapping_key;
    (void)alg;
    (void)key;
    (void)data;
    (void)data_size;
    (void)data_length;
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* HAVE_AES_KEYWRAP */
}

/*
 * psa_unwrap_key: RFC 3394 AES Key Unwrap (PSA_ALG_KW).
 *
 * Decrypts the wrapped blob with wc_AesKeyUnWrap() and imports the recovered
 * plaintext as a new key via psa_import_key().
 */
psa_status_t psa_unwrap_key(const psa_key_attributes_t *attributes,
                             psa_key_id_t wrapping_key,
                             psa_algorithm_t alg,
                             const uint8_t *data,
                             size_t data_length,
                             psa_key_id_t *key)
{
#ifdef HAVE_AES_KEYWRAP
    psa_status_t status;
    psa_key_attributes_t wrap_attr;
    psa_key_type_t wrap_type;
    psa_key_usage_t wrap_usage;
    psa_algorithm_t wrap_alg;
    uint8_t *kek = NULL;
    size_t kek_len = 0;
    uint8_t *plaintext = NULL;
    size_t plain_len;
    int wret;
#endif

    wolfpsa_trace("psa_unwrap_key(wrapping_key=%u alg=0x%08x data_len=%zu)",
                  (unsigned)wrapping_key, (unsigned)alg, data_length);

    /* Validate pointers */
    if (attributes == NULL || data == NULL || key == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    *key = PSA_KEY_ID_NULL;

    /* Only key-wrap category algorithms are accepted */
    if (!PSA_ALG_IS_KEY_WRAP(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* KWP is not implemented by wolfCrypt */
    if (alg == PSA_ALG_KWP) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Only PSA_ALG_KW remains valid at this point */
    if (alg != PSA_ALG_KW) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /*
     * RFC 3394 ciphertext must be >= 24 bytes (16 plaintext + 8 ICV)
     * and a multiple of 8.
     */
    if (data_length < 24 || (data_length % 8) != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

#ifdef HAVE_AES_KEYWRAP
    /* Load and validate the wrapping key */
    status = wolfpsa_get_key_data(wrapping_key, &wrap_attr, &kek, &kek_len);
    if (status != PSA_SUCCESS) {
        return status;
    }

    wrap_type = psa_get_key_type(&wrap_attr);
    if (wrap_type != PSA_KEY_TYPE_AES) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    wrap_usage = psa_get_key_usage_flags(&wrap_attr);
    if ((wrap_usage & PSA_KEY_USAGE_UNWRAP) == 0) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_NOT_PERMITTED;
    }

    wrap_alg = psa_get_key_algorithm(&wrap_attr);
    if (wrap_alg == PSA_ALG_NONE || wrap_alg != alg) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_NOT_PERMITTED;
    }

    plain_len = data_length - 8;
    plaintext = (uint8_t *)XMALLOC(plain_len, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    if (plaintext == NULL) {
        wolfpsa_forcezero_free_key_data(kek, kek_len);
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    /* Perform RFC 3394 key unwrap; pass iv=NULL for the default IV */
    wret = wc_AesKeyUnWrap(kek, (word32)kek_len,
                            data, (word32)data_length,
                            plaintext, (word32)plain_len,
                            NULL);

    wolfpsa_forcezero_free_key_data(kek, kek_len);

    if (wret < 0) {
        wc_ForceZero(plaintext, plain_len);
        XFREE(plaintext, NULL, DYNAMIC_TYPE_TMP_BUFFER);
        /*
         * BAD_KEYWRAP_IV_E (-240): the decrypted integrity check value did
         * not match the expected default IV — the wrapped data is corrupt or
         * was encrypted with a different key.
         */
        if (wret == BAD_KEYWRAP_IV_E) {
            return PSA_ERROR_INVALID_SIGNATURE;
        }
        return wc_error_to_psa_status(wret);
    }

    /* Import the recovered plaintext as a new key */
    status = psa_import_key(attributes, plaintext, (size_t)wret, key);

    wc_ForceZero(plaintext, plain_len);
    XFREE(plaintext, NULL, DYNAMIC_TYPE_TMP_BUFFER);

    if (status != PSA_SUCCESS) {
        *key = PSA_KEY_ID_NULL;
    }

    return status;

#else /* HAVE_AES_KEYWRAP */
    (void)attributes;
    (void)wrapping_key;
    (void)alg;
    (void)data;
    (void)data_length;
    (void)key;
    return PSA_ERROR_NOT_SUPPORTED;
#endif /* HAVE_AES_KEYWRAP */
}

#endif /* WOLFSSL_PSA_ENGINE */
