/* psa_mldsa.c
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

#if defined(WOLFSSL_PSA_ENGINE) && defined(WOLFSSL_HAVE_MLDSA)

#include <psa/crypto.h>
#include "psa_size.h"
#include "psa_pqc_internal.h"
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/wolfcrypt/mem_track.h>
#include <wolfssl/wolfcrypt/wc_mldsa.h>

/* Map PSA security-strength bits to wolfCrypt ML-DSA level constants.
 * Returns WC_ML_DSA_44/65/87 on success, or -1 for unsupported sizes. */
static int mldsa_bits_to_level(size_t bits)
{
    switch (bits) {
        case 128:
            return WC_ML_DSA_44;
        case 192:
            return WC_ML_DSA_65;
        case 256:
            return WC_ML_DSA_87;
        default:
            return -1;
    }
}

/* Map a PSA hash algorithm (extracted via PSA_ALG_GET_HASH) to a wolfCrypt
 * wc_HashType for use with wc_MlDsaKey_SignCtxHash / VerifyCtxHash.
 * Covers the hashes listed in FIPS 204 Table 1 for HashML-DSA. */
static int mldsa_psa_hash_to_wc(psa_algorithm_t hash_alg)
{
    switch (hash_alg) {
        case PSA_ALG_SHA_256:
            return WC_HASH_TYPE_SHA256;
        case PSA_ALG_SHA_384:
            return WC_HASH_TYPE_SHA384;
        case PSA_ALG_SHA_512:
            return WC_HASH_TYPE_SHA512;
        case PSA_ALG_SHA3_256:
            return WC_HASH_TYPE_SHA3_256;
        case PSA_ALG_SHA3_384:
            return WC_HASH_TYPE_SHA3_384;
        case PSA_ALG_SHA3_512:
            return WC_HASH_TYPE_SHA3_512;
        case PSA_ALG_SHAKE128_256:
            return WC_HASH_TYPE_SHAKE128;
        case PSA_ALG_SHAKE256_512:
            return WC_HASH_TYPE_SHAKE256;
        default:
            return WC_HASH_TYPE_NONE;
    }
}

/* Initialise key and set params from bits.  Key must be freed by caller via
 * wc_MlDsaKey_Free() even when this function fails after wc_MlDsaKey_Init. */
static psa_status_t mldsa_key_init(wc_MlDsaKey *key, size_t bits)
{
    int ret;
    int level;

    level = mldsa_bits_to_level(bits);
    if (level < 0) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    ret = wc_MlDsaKey_Init(key, NULL, wolfPSA_GetDefaultDevID());
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    ret = wc_MlDsaKey_SetParams(key, (byte)level);
    if (ret != 0) {
        wc_MlDsaKey_Free(key);
        return wc_error_to_psa_status(ret);
    }

    return PSA_SUCCESS;
}

/* Expand seed into a fully populated key pair.  Caller must have already
 * called mldsa_key_init() on *key. */
static psa_status_t mldsa_expand_seed(wc_MlDsaKey *key, const uint8_t *seed)
{
    int ret;

    ret = wc_MlDsaKey_MakeKeyFromSeed(key, (const byte*)seed);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    return PSA_SUCCESS;
}

/*
 * wolfpsa_mldsa_generate_seed
 *
 * Generate a fresh 32-byte FIPS 204 seed xi for an ML-DSA key pair.
 * Validates that the seed can successfully expand into a key before
 * returning it to the caller.
 */
psa_status_t wolfpsa_mldsa_generate_seed(size_t bits, uint8_t *seed)
{
    psa_status_t status;
    wc_MlDsaKey key;

    /* Validate bits before touching anything. */
    if (mldsa_bits_to_level(bits) < 0) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Fill seed with random bytes via PSA RNG. */
    status = psa_generate_random(seed, WOLFPSA_MLDSA_SEED_SIZE);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* Validate that the seed is well-formed by expanding it. */
    status = mldsa_key_init(&key, bits);
    if (status != PSA_SUCCESS) {
        wc_ForceZero(seed, WOLFPSA_MLDSA_SEED_SIZE);
        return status;
    }

    status = mldsa_expand_seed(&key, seed);
    wc_MlDsaKey_Free(&key);

    if (status != PSA_SUCCESS) {
        wc_ForceZero(seed, WOLFPSA_MLDSA_SEED_SIZE);
        return status;
    }

    return PSA_SUCCESS;
}

/*
 * wolfpsa_mldsa_export_public
 *
 * Expand the 32-byte seed and export the raw FIPS 204 public key bytes
 * (1312 / 1952 / 2592 bytes for ML-DSA-44/65/87).
 */
psa_status_t wolfpsa_mldsa_export_public(size_t bits, const uint8_t *seed,
        uint8_t *out, size_t out_size, size_t *out_length)
{
    psa_status_t status;
    wc_MlDsaKey key;
    int pub_size;
    word32 pub_len;
    int ret;

    if (wolfpsa_check_word32_length(out_size) != PSA_SUCCESS) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    status = mldsa_key_init(&key, bits);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = mldsa_expand_seed(&key, seed);
    if (status != PSA_SUCCESS) {
        wc_MlDsaKey_Free(&key);
        return status;
    }

    /* Check output buffer size before exporting. */
    pub_size = wc_MlDsaKey_PubSize(&key);
    if (pub_size < 0) {
        wc_MlDsaKey_Free(&key);
        return wc_error_to_psa_status(pub_size);
    }
    if (out_size < (size_t)pub_size) {
        wc_MlDsaKey_Free(&key);
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    pub_len = (word32)out_size;
    ret = wc_MlDsaKey_ExportPubRaw(&key, out, &pub_len);
    wc_MlDsaKey_Free(&key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *out_length = (size_t)pub_len;
    return PSA_SUCCESS;
}

/*
 * wolfpsa_mldsa_sign
 *
 * Sign a message or pre-computed hash with an ML-DSA key pair seed.
 *
 * Algorithm dispatch:
 *  input_is_hash == 0 (raw message):
 *    PSA_ALG_ML_DSA              → wc_MlDsaKey_SignCtx (hedged, uses RNG)
 *    PSA_ALG_DETERMINISTIC_ML_DSA → wc_MlDsaKey_SignCtxWithSeed (zero seed)
 *    HashML-DSA variants         → PSA_ERROR_INVALID_ARGUMENT (front-end
 *                                  pre-hashes before calling this function)
 *  input_is_hash == 1 (pre-computed hash):
 *    PSA_ALG_IS_HASH_ML_DSA      → wc_MlDsaKey_SignCtxHash (hedged)
 *    PSA_ALG_IS_DETERMINISTIC_HASH_ML_DSA → wc_MlDsaKey_SignCtxHashWithSeed
 *    PSA_ALG_ML_DSA / PSA_ALG_DETERMINISTIC_ML_DSA → PSA_ERROR_INVALID_ARGUMENT
 */
psa_status_t wolfpsa_mldsa_sign(size_t bits, const uint8_t *key_data,
        size_t key_data_length, psa_algorithm_t alg,
        const uint8_t *context, size_t context_length,
        const uint8_t *input, size_t input_length, int input_is_hash,
        uint8_t *signature, size_t signature_size, size_t *signature_length)
{
    psa_status_t status;
    wc_MlDsaKey key;
    WC_RNG rng;
    int rng_inited = 0;
    int sig_size;
    word32 sig_len;
    int ret;
    /* FIPS 204 deterministic rnd: 32 zero bytes. */
    static const byte zero32[WOLFPSA_MLDSA_SEED_SIZE] = { 0 };
    /* ctx/ctxLen helpers for the wolfCrypt call. */
    const byte *ctx;
    byte ctx_len;

    /* key_data must be exactly the 32-byte seed. */
    if (key_data_length != WOLFPSA_MLDSA_SEED_SIZE) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    /* context_length is transmitted as a single byte to wolfCrypt. */
    if (context_length > 255u) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(input_length) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(signature_size) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Resolve context pointer: pass NULL to wolfCrypt when empty. */
    if (context_length == 0) {
        ctx     = NULL;
        ctx_len = 0;
    }
    else {
        ctx     = (const byte*)context;
        ctx_len = (byte)context_length;
    }

    status = mldsa_key_init(&key, bits);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = mldsa_expand_seed(&key, key_data);
    if (status != PSA_SUCCESS) {
        wc_MlDsaKey_Free(&key);
        return status;
    }

    /* Verify output buffer size. */
    sig_size = wc_MlDsaKey_SigSize(&key);
    if (sig_size < 0) {
        wc_MlDsaKey_Free(&key);
        return wc_error_to_psa_status(sig_size);
    }
    if (signature_size < (size_t)sig_size) {
        wc_MlDsaKey_Free(&key);
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    sig_len = (word32)signature_size;

    if (input_is_hash == 0) {
        /* Signing over the raw message. */
        if (alg == PSA_ALG_ML_DSA) {
            /* Hedged: requires an RNG. */
            ret = wc_InitRng(&rng);
            if (ret != 0) {
                wc_MlDsaKey_Free(&key);
                return wc_error_to_psa_status(ret);
            }
            rng_inited = 1;
            ret = wc_MlDsaKey_SignCtx(&key, ctx, ctx_len,
                                      signature, &sig_len,
                                      (const byte*)input, (word32)input_length,
                                      &rng);
        }
        else if (alg == PSA_ALG_DETERMINISTIC_ML_DSA) {
            /* Deterministic: rnd is 32 zero bytes per FIPS 204. */
            ret = wc_MlDsaKey_SignCtxWithSeed(&key, ctx, ctx_len,
                                              signature, &sig_len,
                                              (const byte*)input,
                                              (word32)input_length, zero32);
        }
        else if (PSA_ALG_IS_HASH_ML_DSA(alg) ||
                 PSA_ALG_IS_DETERMINISTIC_HASH_ML_DSA(alg)) {
            /* Front-end always pre-hashes before calling here; receiving a
             * raw message for HashML-DSA is a caller contract violation. */
            wc_MlDsaKey_Free(&key);
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        else {
            wc_MlDsaKey_Free(&key);
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else {
        /* input is a pre-computed hash digest. */
        psa_algorithm_t hash_alg;
        int wc_hash;

        if (PSA_ALG_IS_HASH_ML_DSA(alg)) {
            hash_alg = PSA_ALG_GET_HASH(alg);
            wc_hash  = mldsa_psa_hash_to_wc(hash_alg);
            if (wc_hash == WC_HASH_TYPE_NONE) {
                wc_MlDsaKey_Free(&key);
                return PSA_ERROR_NOT_SUPPORTED;
            }
            ret = wc_InitRng(&rng);
            if (ret != 0) {
                wc_MlDsaKey_Free(&key);
                return wc_error_to_psa_status(ret);
            }
            rng_inited = 1;
            ret = wc_MlDsaKey_SignCtxHash(&key, ctx, ctx_len,
                                          signature, &sig_len,
                                          (const byte*)input,
                                          (word32)input_length,
                                          wc_hash, &rng);
        }
        else if (PSA_ALG_IS_DETERMINISTIC_HASH_ML_DSA(alg)) {
            hash_alg = PSA_ALG_GET_HASH(alg);
            wc_hash  = mldsa_psa_hash_to_wc(hash_alg);
            if (wc_hash == WC_HASH_TYPE_NONE) {
                wc_MlDsaKey_Free(&key);
                return PSA_ERROR_NOT_SUPPORTED;
            }
            ret = wc_MlDsaKey_SignCtxHashWithSeed(&key, ctx, ctx_len,
                                                  signature, &sig_len,
                                                  (const byte*)input,
                                                  (word32)input_length,
                                                  wc_hash, zero32);
        }
        else {
            /* Pure ML-DSA with a pre-hashed input is a protocol error. */
            wc_MlDsaKey_Free(&key);
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    if (rng_inited) {
        wc_FreeRng(&rng);
    }
    wc_MlDsaKey_Free(&key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    *signature_length = (size_t)sig_len;
    return PSA_SUCCESS;
}

/*
 * wolfpsa_mldsa_verify
 *
 * Verify an ML-DSA signature.  Accepts both key-pair (seed) and bare public
 * key material.  The algorithm dispatch mirrors wolfpsa_mldsa_sign; hedged
 * and deterministic variants produce identical signatures and verify the
 * same way, so PSA_ALG_ML_DSA and PSA_ALG_DETERMINISTIC_ML_DSA both map to
 * wc_MlDsaKey_VerifyCtx, and the Hash variants both map to
 * wc_MlDsaKey_VerifyCtxHash.
 */
psa_status_t wolfpsa_mldsa_verify(size_t bits, psa_key_type_t key_type,
        const uint8_t *key_data, size_t key_data_length, psa_algorithm_t alg,
        const uint8_t *context, size_t context_length,
        const uint8_t *input, size_t input_length, int input_is_hash,
        const uint8_t *signature, size_t signature_length)
{
    psa_status_t status;
    wc_MlDsaKey key;
    int verify_res = 0;
    int ret;
    const byte *ctx;
    byte ctx_len;

    if (context_length > 255u) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if ((wolfpsa_check_word32_length(key_data_length) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(input_length) != PSA_SUCCESS) ||
        (wolfpsa_check_word32_length(signature_length) != PSA_SUCCESS)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Resolve context pointer: pass NULL when empty. */
    if (context_length == 0) {
        ctx     = NULL;
        ctx_len = 0;
    }
    else {
        ctx     = (const byte*)context;
        ctx_len = (byte)context_length;
    }

    status = mldsa_key_init(&key, bits);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* Load the key depending on whether we have a key pair (seed) or a
     * bare public key. */
    if (key_type == PSA_KEY_TYPE_ML_DSA_KEY_PAIR) {
        /* key_data is the 32-byte seed; expand to obtain the public key. */
        if (key_data_length != WOLFPSA_MLDSA_SEED_SIZE) {
            wc_MlDsaKey_Free(&key);
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        status = mldsa_expand_seed(&key, key_data);
        if (status != PSA_SUCCESS) {
            wc_MlDsaKey_Free(&key);
            return status;
        }
    }
    else if (key_type == PSA_KEY_TYPE_ML_DSA_PUBLIC_KEY) {
        /* key_data is raw pk bytes; import directly. */
        ret = wc_MlDsaKey_ImportPubRaw(&key, (const byte*)key_data,
                                       (word32)key_data_length);
        if (ret != 0) {
            wc_MlDsaKey_Free(&key);
            return wc_error_to_psa_status(ret);
        }
    }
    else {
        wc_MlDsaKey_Free(&key);
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (input_is_hash == 0) {
        /* Verify over the raw message. */
        if (alg == PSA_ALG_ML_DSA || alg == PSA_ALG_DETERMINISTIC_ML_DSA) {
            ret = wc_MlDsaKey_VerifyCtx(&key,
                                        (const byte*)signature,
                                        (word32)signature_length,
                                        ctx, ctx_len,
                                        (const byte*)input,
                                        (word32)input_length,
                                        &verify_res);
        }
        else if (PSA_ALG_IS_HASH_ML_DSA(alg) ||
                 PSA_ALG_IS_DETERMINISTIC_HASH_ML_DSA(alg)) {
            wc_MlDsaKey_Free(&key);
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        else {
            wc_MlDsaKey_Free(&key);
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else {
        /* Verify over a pre-computed hash digest. */
        psa_algorithm_t hash_alg;
        int wc_hash;

        if (PSA_ALG_IS_HASH_ML_DSA(alg) ||
            PSA_ALG_IS_DETERMINISTIC_HASH_ML_DSA(alg)) {
            hash_alg = PSA_ALG_GET_HASH(alg);
            wc_hash  = mldsa_psa_hash_to_wc(hash_alg);
            if (wc_hash == WC_HASH_TYPE_NONE) {
                wc_MlDsaKey_Free(&key);
                return PSA_ERROR_NOT_SUPPORTED;
            }
            ret = wc_MlDsaKey_VerifyCtxHash(&key,
                                            (const byte*)signature,
                                            (word32)signature_length,
                                            ctx, ctx_len,
                                            (const byte*)input,
                                            (word32)input_length,
                                            wc_hash, &verify_res);
        }
        else {
            /* Pure ML-DSA with a pre-hashed input is a protocol error. */
            wc_MlDsaKey_Free(&key);
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }

    wc_MlDsaKey_Free(&key);

    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    if (verify_res != 1) {
        return PSA_ERROR_INVALID_SIGNATURE;
    }

    return PSA_SUCCESS;
}

#endif /* WOLFSSL_PSA_ENGINE && WOLFSSL_HAVE_MLDSA */
