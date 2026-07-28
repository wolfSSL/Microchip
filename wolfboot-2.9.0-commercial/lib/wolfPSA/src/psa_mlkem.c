/* psa_mlkem.c
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

#if defined(WOLFSSL_PSA_ENGINE) && defined(WOLFSSL_HAVE_MLKEM)

#include <psa/crypto.h>
#include "psa_size.h"
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/mem_track.h>
#include <wolfssl/wolfcrypt/wc_mlkem.h>
#include "psa_pqc_internal.h"

/* Map PSA security-strength bits to wolfCrypt ML-KEM type constant. */
static int mlkem_bits_to_type(size_t bits)
{
    switch (bits) {
        case 512:
            return WC_ML_KEM_512;
        case 768:
            return WC_ML_KEM_768;
        case 1024:
            return WC_ML_KEM_1024;
        default:
            return -1;
    }
}

/*
 * wolfpsa_mlkem_generate_seed
 *
 * Generate a fresh 64-byte d||z seed (FIPS 203 ML-KEM.KeyGen_internal) for
 * an ML-KEM key pair of the requested strength.  The seed is validated by
 * attempting a full key expansion before returning it to the caller.
 */
psa_status_t wolfpsa_mlkem_generate_seed(size_t bits, uint8_t *seed)
{
    psa_status_t psa_ret;
    MlKemKey key;
    int type;
    int ret;

    type = mlkem_bits_to_type(bits);
    if (type < 0) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Generate 64 bytes of randomness: d (32 bytes) || z (32 bytes). */
    psa_ret = psa_generate_random(seed, WOLFPSA_MLKEM_SEED_SIZE);
    if (psa_ret != PSA_SUCCESS) {
        return psa_ret;
    }

    /* Validate the seed by expanding it into a full key pair. */
    ret = wc_MlKemKey_Init(&key, type, NULL, wolfPSA_GetDefaultDevID());
    if (ret != 0) {
        wc_ForceZero(seed, WOLFPSA_MLKEM_SEED_SIZE);
        return wc_error_to_psa_status(ret);
    }

    /* MakeKeyWithRandom expects the 64-byte d||z buffer directly. */
    ret = wc_MlKemKey_MakeKeyWithRandom(&key, seed, WOLFPSA_MLKEM_SEED_SIZE);
    wc_MlKemKey_Free(&key);
    if (ret != 0) {
        wc_ForceZero(seed, WOLFPSA_MLKEM_SEED_SIZE);
        return wc_error_to_psa_status(ret);
    }

    return PSA_SUCCESS;
}

/*
 * wolfpsa_mlkem_export_public
 *
 * Expand a 64-byte seed into a key pair and encode the public key (ek) into
 * the caller-supplied buffer.
 */
psa_status_t wolfpsa_mlkem_export_public(size_t bits, const uint8_t *seed,
        uint8_t *out, size_t out_size, size_t *out_length)
{
    MlKemKey key;
    int type;
    int ret;
    word32 pubSz;

    type = mlkem_bits_to_type(bits);
    if (type < 0) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    ret = wc_MlKemKey_Init(&key, type, NULL, wolfPSA_GetDefaultDevID());
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    ret = wc_MlKemKey_MakeKeyWithRandom(&key, seed, WOLFPSA_MLKEM_SEED_SIZE);
    if (ret != 0) {
        wc_MlKemKey_Free(&key);
        return wc_error_to_psa_status(ret);
    }

    ret = wc_MlKemKey_PublicKeySize(&key, &pubSz);
    if (ret != 0) {
        wc_MlKemKey_Free(&key);
        return wc_error_to_psa_status(ret);
    }

    if (out_size < (size_t)pubSz) {
        wc_MlKemKey_Free(&key);
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    ret = wc_MlKemKey_EncodePublicKey(&key, out, pubSz);
    wc_MlKemKey_Free(&key);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *out_length = (size_t)pubSz;
    return PSA_SUCCESS;
}

/*
 * wolfpsa_mlkem_encapsulate
 *
 * Perform ML-KEM encapsulation.  The caller supplies either a raw public key
 * (PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY) or a 64-byte seed representing a key pair
 * (PSA_KEY_TYPE_ML_KEM_KEY_PAIR).  The output ciphertext and shared secret
 * buffers must be pre-allocated; the shared secret is exactly 32 bytes.
 */
psa_status_t wolfpsa_mlkem_encapsulate(size_t bits, psa_key_type_t key_type,
        const uint8_t *key_data, size_t key_data_length,
        uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length,
        uint8_t *shared_secret)
{
    MlKemKey key;
    WC_RNG rng;
    int type;
    int ret;
    word32 ctSz;
    word32 pubSz;
    int rng_init = 0;

    type = mlkem_bits_to_type(bits);
    if (type < 0) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    ret = wc_MlKemKey_Init(&key, type, NULL, wolfPSA_GetDefaultDevID());
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    if (key_type == PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY) {
        /* Validate the provided length against the expected public-key size. */
        ret = wc_MlKemKey_PublicKeySize(&key, &pubSz);
        if (ret != 0) {
            wc_MlKemKey_Free(&key);
            return wc_error_to_psa_status(ret);
        }
        if (key_data_length != (size_t)pubSz) {
            wc_MlKemKey_Free(&key);
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        if (wolfpsa_check_word32_length(key_data_length) != PSA_SUCCESS) {
            wc_MlKemKey_Free(&key);
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        ret = wc_MlKemKey_DecodePublicKey(&key, key_data,
                                          (word32)key_data_length);
        if (ret != 0) {
            wc_MlKemKey_Free(&key);
            return wc_error_to_psa_status(ret);
        }
    }
    else if (key_type == PSA_KEY_TYPE_ML_KEM_KEY_PAIR) {
        /* Key pair is stored as a 64-byte seed; expand it. */
        if (key_data_length != WOLFPSA_MLKEM_SEED_SIZE) {
            wc_MlKemKey_Free(&key);
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        ret = wc_MlKemKey_MakeKeyWithRandom(&key, key_data,
                                            WOLFPSA_MLKEM_SEED_SIZE);
        if (ret != 0) {
            wc_MlKemKey_Free(&key);
            return wc_error_to_psa_status(ret);
        }
    }
    else {
        wc_MlKemKey_Free(&key);
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ret = wc_MlKemKey_CipherTextSize(&key, &ctSz);
    if (ret != 0) {
        wc_MlKemKey_Free(&key);
        return wc_error_to_psa_status(ret);
    }

    if (ciphertext_size < (size_t)ctSz) {
        wc_MlKemKey_Free(&key);
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    ret = wc_InitRng(&rng);
    if (ret != 0) {
        wc_MlKemKey_Free(&key);
        return wc_error_to_psa_status(ret);
    }
    rng_init = 1;

    /* wc_MlKemKey_Encapsulate(key, ct, ss, rng) */
    ret = wc_MlKemKey_Encapsulate(&key, ciphertext, shared_secret, &rng);

    if (rng_init) {
        wc_FreeRng(&rng);
    }
    wc_MlKemKey_Free(&key);

    if (ret != 0) {
        wc_ForceZero(shared_secret, WOLFPSA_MLKEM_SS_SIZE);
        return wc_error_to_psa_status(ret);
    }

    *ciphertext_length = (size_t)ctSz;
    return PSA_SUCCESS;
}

/*
 * wolfpsa_mlkem_decapsulate
 *
 * Expand a 64-byte seed into a full key pair and decapsulate the ciphertext,
 * producing a 32-byte shared secret.  Per FIPS 203 implicit rejection: an
 * invalid (but correctly sized) ciphertext will still produce a deterministic
 * pseudorandom output rather than an error.
 */
psa_status_t wolfpsa_mlkem_decapsulate(size_t bits, const uint8_t *seed,
        const uint8_t *ciphertext, size_t ciphertext_length,
        uint8_t *shared_secret)
{
    MlKemKey key;
    int type;
    int ret;
    word32 ctSz;

    type = mlkem_bits_to_type(bits);
    if (type < 0) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (wolfpsa_check_word32_length(ciphertext_length) != PSA_SUCCESS) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ret = wc_MlKemKey_Init(&key, type, NULL, wolfPSA_GetDefaultDevID());
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    ret = wc_MlKemKey_MakeKeyWithRandom(&key, seed, WOLFPSA_MLKEM_SEED_SIZE);
    if (ret != 0) {
        wc_MlKemKey_Free(&key);
        return wc_error_to_psa_status(ret);
    }

    ret = wc_MlKemKey_CipherTextSize(&key, &ctSz);
    if (ret != 0) {
        wc_MlKemKey_Free(&key);
        return wc_error_to_psa_status(ret);
    }

    if ((word32)ciphertext_length != ctSz) {
        wc_MlKemKey_Free(&key);
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* wc_MlKemKey_Decapsulate(key, ss, ct, len) */
    ret = wc_MlKemKey_Decapsulate(&key, shared_secret, ciphertext,
                                  (word32)ciphertext_length);
    wc_MlKemKey_Free(&key);
    if (ret != 0) {
        wc_ForceZero(shared_secret, WOLFPSA_MLKEM_SS_SIZE);
        return wc_error_to_psa_status(ret);
    }

    return PSA_SUCCESS;
}

#endif /* WOLFSSL_PSA_ENGINE && WOLFSSL_HAVE_MLKEM */
