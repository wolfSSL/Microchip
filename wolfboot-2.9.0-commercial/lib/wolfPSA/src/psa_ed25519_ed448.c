/* psa_ed25519_ed448.c
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

#if defined(WOLFSSL_PSA_ENGINE) && (defined(HAVE_ED25519) || defined(HAVE_ED448))

#include <psa/crypto.h>
#include "psa_size.h"
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/mem_track.h>

#ifdef HAVE_ED25519
#include <wolfssl/wolfcrypt/ed25519.h>
#endif

#ifdef HAVE_ED448
#include <wolfssl/wolfcrypt/ed448.h>
#endif

#ifdef HAVE_ED25519
/* Sign a hash or short message with an ED25519 private key */
psa_status_t psa_asymmetric_sign_ed25519(psa_key_type_t key_type,
                                        size_t key_bits,
                                        const uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        psa_algorithm_t alg,
                                        const uint8_t *hash,
                                        size_t hash_length,
                                        uint8_t *signature,
                                        size_t signature_size,
                                        size_t *signature_length,
                                        const uint8_t *context,
                                        size_t context_length)
{
    int ret;
    ed25519_key ed_key;
    word32 sig_len32;
    const byte *ctx_ptr;
    byte ctx_len;

    if (alg != PSA_ALG_PURE_EDDSA &&
        alg != PSA_ALG_EDDSA_CTX  &&
        alg != PSA_ALG_ED25519PH) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* PSA_ALG_PURE_EDDSA forbids any context */
    if (alg == PSA_ALG_PURE_EDDSA && context_length != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* context must fit in a byte for all Ed25519 variants */
    if (context_length > 255u) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check if key type is ED25519 key pair */
    if (key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS) ||
        key_bits != 255) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(key_buffer_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(hash_length) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(signature_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* HashEdDSA (Ed25519ph) signs the SHA-512 prehash, which is exactly
     * PSA_HASH_LENGTH(PSA_ALG_SHA_512) (64) bytes. */
    if (alg == PSA_ALG_ED25519PH &&
        hash_length != PSA_HASH_LENGTH(PSA_ALG_SHA_512)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ctx_ptr = (context_length > 0u) ? (const byte *)context : NULL;
    ctx_len = (byte)context_length;

    /* Initialize ED25519 key */
    ret = wc_ed25519_init(&ed_key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Import the stored private seed and derive the public component. */
    ret = wc_ed25519_import_private_only(key_buffer, (word32)key_buffer_size,
                                         &ed_key);
    if (ret == 0) {
        ret = wc_ed25519_make_public(&ed_key, ed_key.p, ED25519_PUB_KEY_SIZE);
    }
    if (ret != 0) {
        wc_ed25519_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    sig_len32 = (word32)signature_size;

    if (alg == PSA_ALG_ED25519PH) {
        /* HashEdDSA: sign the prehash with optional context */
        ret = wc_ed25519ph_sign_hash(hash, (word32)hash_length, signature,
                                     &sig_len32, &ed_key, ctx_ptr, ctx_len);
    }
    else {
        /* PURE_EDDSA (Ed25519, no context) or EDDSA_CTX (Ed25519ctx, with
         * optional context): use the _ex variant selecting the right type. */
        byte wc_type = (alg == PSA_ALG_EDDSA_CTX) ? Ed25519ctx : Ed25519;
        ret = wc_ed25519_sign_msg_ex(hash, (word32)hash_length, signature,
                                     &sig_len32, &ed_key, wc_type,
                                     ctx_ptr, ctx_len);
    }

    wc_ed25519_free(&ed_key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *signature_length = (size_t)sig_len32;

    return PSA_SUCCESS;
}

/* Verify a signature of a hash or short message with an ED25519 public key */
psa_status_t psa_asymmetric_verify_ed25519(psa_key_type_t key_type,
                                          size_t key_bits,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg,
                                          const uint8_t *hash,
                                          size_t hash_length,
                                          const uint8_t *signature,
                                          size_t signature_length,
                                          const uint8_t *context,
                                          size_t context_length)
{
    int ret;
    ed25519_key ed_key;
    int verify_res = 0;
    const byte *ctx_ptr;
    byte ctx_len;

    if (alg != PSA_ALG_PURE_EDDSA &&
        alg != PSA_ALG_EDDSA_CTX  &&
        alg != PSA_ALG_ED25519PH) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* PSA_ALG_PURE_EDDSA forbids any context */
    if (alg == PSA_ALG_PURE_EDDSA && context_length != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* context must fit in a byte for all Ed25519 variants */
    if (context_length > 255u) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check if key type is ED25519 */
    if ((key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS) &&
         key_type != PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS)) ||
        key_bits != 255) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(key_buffer_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(hash_length) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(signature_length) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* HashEdDSA (Ed25519ph) verifies over the SHA-512 prehash, which is
     * exactly PSA_HASH_LENGTH(PSA_ALG_SHA_512) (64) bytes. */
    if (alg == PSA_ALG_ED25519PH &&
        hash_length != PSA_HASH_LENGTH(PSA_ALG_SHA_512)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ctx_ptr = (context_length > 0u) ? (const byte *)context : NULL;
    ctx_len = (byte)context_length;

    /* Initialize ED25519 key */
    ret = wc_ed25519_init(&ed_key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Import the key material needed for verification. */
    if (key_type == PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS)) {
        ret = wc_ed25519_import_private_only(key_buffer, (word32)key_buffer_size,
                                             &ed_key);
        if (ret == 0) {
            ret = wc_ed25519_make_public(&ed_key, ed_key.p,
                                         ED25519_PUB_KEY_SIZE);
        }
    }
    else {
        ret = wc_ed25519_import_public(key_buffer, (word32)key_buffer_size, &ed_key);
    }
    if (ret != 0) {
        wc_ed25519_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    if (alg == PSA_ALG_ED25519PH) {
        /* HashEdDSA: verify the prehash with optional context */
        ret = wc_ed25519ph_verify_hash(signature, (word32)signature_length,
                                       hash, (word32)hash_length,
                                       &verify_res, &ed_key, ctx_ptr, ctx_len);
    }
    else {
        /* PURE_EDDSA (Ed25519, no context) or EDDSA_CTX (Ed25519ctx, with
         * optional context): use the _ex variant selecting the right type. */
        byte wc_type = (alg == PSA_ALG_EDDSA_CTX) ? Ed25519ctx : Ed25519;
        ret = wc_ed25519_verify_msg_ex(signature, (word32)signature_length,
                                       hash, (word32)hash_length,
                                       &verify_res, &ed_key, wc_type,
                                       ctx_ptr, ctx_len);
    }

    wc_ed25519_free(&ed_key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    if (verify_res != 1) {
        return PSA_ERROR_INVALID_SIGNATURE;
    }

    return PSA_SUCCESS;
}

/* Generate an ED25519 key pair */
psa_status_t psa_asymmetric_generate_key_ed25519(psa_key_type_t key_type,
                                                size_t key_bits,
                                                uint8_t *private_key,
                                                size_t private_key_size,
                                                size_t *private_key_length,
                                                uint8_t *public_key,
                                                size_t public_key_size,
                                                size_t *public_key_length)
{
    int ret;
    ed25519_key ed_key;
    WC_RNG rng;
    word32 priv_len32;
    word32 pub_len32;

    /* Check if key type is ED25519 key pair */
    if (key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS) ||
        key_bits != 255) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(private_key_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(public_key_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Initialize ED25519 key */
    ret = wc_ed25519_init(&ed_key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Initialize RNG */
    ret = wc_InitRng(&rng);
    if (ret != 0) {
        wc_ed25519_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    /* Generate key pair */
    ret = wc_ed25519_make_key(&rng, ED25519_KEY_SIZE, &ed_key);
    if (ret != 0) {
        wc_FreeRng(&rng);
        wc_ed25519_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    /* Export private key */
    priv_len32 = (word32)private_key_size;
    ret = wc_ed25519_export_private_only(&ed_key, private_key, &priv_len32);
    if (ret != 0) {
        wc_FreeRng(&rng);
        wc_ed25519_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    /* Export public key */
    pub_len32 = (word32)public_key_size;
    ret = wc_ed25519_export_public(&ed_key, public_key, &pub_len32);
    if (ret != 0) {
        wc_FreeRng(&rng);
        wc_ed25519_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    wc_FreeRng(&rng);
    wc_ed25519_free(&ed_key);

    *private_key_length = (size_t)priv_len32;
    *public_key_length = (size_t)pub_len32;

    return PSA_SUCCESS;
}

/* Export an ED25519 public key or the public part of an ED25519 key pair */
psa_status_t psa_asymmetric_export_public_key_ed25519(psa_key_type_t key_type,
                                                     size_t key_bits,
                                                     const uint8_t *key_buffer,
                                                     size_t key_buffer_size,
                                                     uint8_t *output,
                                                     size_t output_size,
                                                     size_t *output_length)
{
    int ret;
    ed25519_key ed_key;
    word32 out_len32;

    /* Check if key type is ED25519 */
    if ((key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS) &&
         key_type != PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS)) ||
        key_bits != 255) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(key_buffer_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(output_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Initialize ED25519 key */
    ret = wc_ed25519_init(&ed_key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Import key */
    if (key_type == PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS)) {
        ret = wc_ed25519_import_private_only(key_buffer, (word32)key_buffer_size,
                                             &ed_key);
        if (ret == 0) {
            ret = wc_ed25519_make_public(&ed_key, ed_key.p,
                                         ED25519_PUB_KEY_SIZE);
        }
    }
    else {
        ret = wc_ed25519_import_public(key_buffer, (word32)key_buffer_size, &ed_key);
    }

    if (ret != 0) {
        wc_ed25519_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    /* Export public key */
    out_len32 = (word32)output_size;
    ret = wc_ed25519_export_public(&ed_key, output, &out_len32);

    wc_ed25519_free(&ed_key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *output_length = (size_t)out_len32;

    return PSA_SUCCESS;
}
#endif /* HAVE_ED25519 */

#ifdef HAVE_ED448
/* Sign a hash or short message with an ED448 private key */
psa_status_t psa_asymmetric_sign_ed448(psa_key_type_t key_type,
                                      size_t key_bits,
                                      const uint8_t *key_buffer,
                                      size_t key_buffer_size,
                                      psa_algorithm_t alg,
                                      const uint8_t *hash,
                                      size_t hash_length,
                                      uint8_t *signature,
                                      size_t signature_size,
                                      size_t *signature_length,
                                      const uint8_t *context,
                                      size_t context_length)
{
    int ret;
    ed448_key ed_key;
    word32 sig_len32;
    const byte *ctx_ptr;
    byte ctx_len;

    if (alg != PSA_ALG_PURE_EDDSA &&
        alg != PSA_ALG_EDDSA_CTX  &&
        alg != PSA_ALG_ED448PH) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* context must fit in a byte for all Ed448 variants */
    if (context_length > 255u) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check if key type is ED448 key pair */
    if (key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS) ||
        key_bits != 448) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(key_buffer_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(hash_length) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(signature_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* HashEdDSA (Ed448ph) signs the 64-byte SHAKE256 prehash
     * (PSA_HASH_LENGTH(PSA_ALG_SHAKE256_512)). */
    if (alg == PSA_ALG_ED448PH && hash_length != 64u) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ctx_ptr = (context_length > 0u) ? (const byte *)context : NULL;
    ctx_len = (byte)context_length;

    /* Initialize ED448 key */
    ret = wc_ed448_init(&ed_key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Import the stored private seed and derive the public component. */
    ret = wc_ed448_import_private_only(key_buffer, (word32)key_buffer_size,
                                       &ed_key);
    if (ret == 0) {
        ret = wc_ed448_make_public(&ed_key, ed_key.p, ED448_PUB_KEY_SIZE);
    }
    if (ret != 0) {
        wc_ed448_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    sig_len32 = (word32)signature_size;

    if (alg == PSA_ALG_ED448PH) {
        /* HashEdDSA: sign the prehash with optional context */
        ret = wc_ed448ph_sign_hash(hash, (word32)hash_length, signature,
                                   &sig_len32, &ed_key, ctx_ptr, ctx_len);
    }
    else {
        /* PURE_EDDSA and EDDSA_CTX both map to Ed448 PureEdDSA with context
         * (RFC 8032: Ed448 has no separate ctx variant, context is always
         * part of the domain separation string). */
        ret = wc_ed448_sign_msg(hash, (word32)hash_length, signature,
                                &sig_len32, &ed_key, ctx_ptr, ctx_len);
    }

    wc_ed448_free(&ed_key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *signature_length = (size_t)sig_len32;

    return PSA_SUCCESS;
}

/* Verify a signature of a hash or short message with an ED448 public key */
psa_status_t psa_asymmetric_verify_ed448(psa_key_type_t key_type,
                                        size_t key_bits,
                                        const uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        psa_algorithm_t alg,
                                        const uint8_t *hash,
                                        size_t hash_length,
                                        const uint8_t *signature,
                                        size_t signature_length,
                                        const uint8_t *context,
                                        size_t context_length)
{
    int ret;
    ed448_key ed_key;
    int verify_res = 0;
    const byte *ctx_ptr;
    byte ctx_len;

    if (alg != PSA_ALG_PURE_EDDSA &&
        alg != PSA_ALG_EDDSA_CTX  &&
        alg != PSA_ALG_ED448PH) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* context must fit in a byte for all Ed448 variants */
    if (context_length > 255u) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check if key type is ED448 */
    if ((key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS) &&
         key_type != PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS)) ||
        key_bits != 448) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(key_buffer_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(hash_length) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(signature_length) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* HashEdDSA (Ed448ph) verifies over the 64-byte SHAKE256 prehash
     * (PSA_HASH_LENGTH(PSA_ALG_SHAKE256_512)). */
    if (alg == PSA_ALG_ED448PH && hash_length != 64u) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ctx_ptr = (context_length > 0u) ? (const byte *)context : NULL;
    ctx_len = (byte)context_length;

    /* Initialize ED448 key */
    ret = wc_ed448_init(&ed_key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Import the key material needed for verification. */
    if (key_type == PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS)) {
        ret = wc_ed448_import_private_only(key_buffer, (word32)key_buffer_size,
                                           &ed_key);
        if (ret == 0) {
            ret = wc_ed448_make_public(&ed_key, ed_key.p, ED448_PUB_KEY_SIZE);
        }
    }
    else {
        ret = wc_ed448_import_public(key_buffer, (word32)key_buffer_size, &ed_key);
    }
    if (ret != 0) {
        wc_ed448_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    if (alg == PSA_ALG_ED448PH) {
        /* HashEdDSA: verify the prehash with optional context */
        ret = wc_ed448ph_verify_hash(signature, (word32)signature_length,
                                     hash, (word32)hash_length,
                                     &verify_res, &ed_key, ctx_ptr, ctx_len);
    }
    else {
        /* PURE_EDDSA and EDDSA_CTX both map to Ed448 PureEdDSA with context. */
        ret = wc_ed448_verify_msg(signature, (word32)signature_length,
                                  hash, (word32)hash_length,
                                  &verify_res, &ed_key, ctx_ptr, ctx_len);
    }

    wc_ed448_free(&ed_key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    if (verify_res != 1) {
        return PSA_ERROR_INVALID_SIGNATURE;
    }

    return PSA_SUCCESS;
}

/* Generate an ED448 key pair */
psa_status_t psa_asymmetric_generate_key_ed448(psa_key_type_t key_type,
                                              size_t key_bits,
                                              uint8_t *private_key,
                                              size_t private_key_size,
                                              size_t *private_key_length,
                                              uint8_t *public_key,
                                              size_t public_key_size,
                                              size_t *public_key_length)
{
    int ret;
    ed448_key ed_key;
    WC_RNG rng;
    word32 priv_len32;
    word32 pub_len32;

    /* Check if key type is ED448 key pair */
    if (key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS) ||
        key_bits != 448) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(private_key_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(public_key_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Initialize ED448 key */
    ret = wc_ed448_init(&ed_key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Initialize RNG */
    ret = wc_InitRng(&rng);
    if (ret != 0) {
        wc_ed448_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    /* Generate key pair */
    ret = wc_ed448_make_key(&rng, ED448_KEY_SIZE, &ed_key);
    if (ret != 0) {
        wc_FreeRng(&rng);
        wc_ed448_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    /* Export private key */
    priv_len32 = (word32)private_key_size;
    ret = wc_ed448_export_private_only(&ed_key, private_key, &priv_len32);
    if (ret != 0) {
        wc_FreeRng(&rng);
        wc_ed448_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    /* Export public key */
    pub_len32 = (word32)public_key_size;
    ret = wc_ed448_export_public(&ed_key, public_key, &pub_len32);
    if (ret != 0) {
        wc_FreeRng(&rng);
        wc_ed448_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    wc_FreeRng(&rng);
    wc_ed448_free(&ed_key);

    *private_key_length = (size_t)priv_len32;
    *public_key_length = (size_t)pub_len32;

    return PSA_SUCCESS;
}

/* Export an ED448 public key or the public part of an ED448 key pair */
psa_status_t psa_asymmetric_export_public_key_ed448(psa_key_type_t key_type,
                                                   size_t key_bits,
                                                   const uint8_t *key_buffer,
                                                   size_t key_buffer_size,
                                                   uint8_t *output,
                                                   size_t output_size,
                                                   size_t *output_length)
{
    int ret;
    ed448_key ed_key;
    word32 out_len32;

    /* Check if key type is ED448 */
    if ((key_type != PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS) &&
         key_type != PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS)) ||
        key_bits != 448) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(key_buffer_size) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(output_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Initialize ED448 key */
    ret = wc_ed448_init(&ed_key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Import key */
    if (key_type == PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS)) {
        ret = wc_ed448_import_private_only(key_buffer, (word32)key_buffer_size,
                                           &ed_key);
        if (ret == 0) {
            ret = wc_ed448_make_public(&ed_key, ed_key.p, ED448_PUB_KEY_SIZE);
        }
    }
    else {
        ret = wc_ed448_import_public(key_buffer, (word32)key_buffer_size, &ed_key);
    }

    if (ret != 0) {
        wc_ed448_free(&ed_key);
        return wc_error_to_psa_status(ret);
    }

    /* Export public key */
    out_len32 = (word32)output_size;
    ret = wc_ed448_export_public(&ed_key, output, &out_len32);

    wc_ed448_free(&ed_key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *output_length = (size_t)out_len32;

    return PSA_SUCCESS;
}
#endif /* HAVE_ED448 */

#endif /* WOLFSSL_PSA_ENGINE && (HAVE_ED25519 || HAVE_ED448) */
