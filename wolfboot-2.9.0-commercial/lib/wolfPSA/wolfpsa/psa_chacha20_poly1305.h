/* psa_chacha20_poly1305.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/**
 * Platform Security Architecture (PSA) ChaCha20-Poly1305 API header
 *
 * If WOLFSSL_PSA_ENGINE is defined, wolfSSL provides an implementation of the
 * PSA Crypto API for ChaCha20-Poly1305 operations that calls wolfCrypt APIs.
 *
 */

#ifndef WOLFSSL_PSA_CHACHA20_POLY1305_H
#define WOLFSSL_PSA_CHACHA20_POLY1305_H

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#if defined(WOLFSSL_PSA_ENGINE) && defined(HAVE_CHACHA) && defined(HAVE_POLY1305)

#include <psa/crypto.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/visibility.h>

/* Encrypt using ChaCha20-Poly1305 */
WOLFSSL_LOCAL psa_status_t psa_chacha20_poly1305_encrypt(
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *plaintext, size_t plaintext_length,
    uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length);

/* Decrypt using ChaCha20-Poly1305 */
WOLFSSL_LOCAL psa_status_t psa_chacha20_poly1305_decrypt(
    const uint8_t *key, size_t key_length,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    uint8_t *plaintext, size_t plaintext_size, size_t *plaintext_length);

#endif /* WOLFSSL_PSA_ENGINE && HAVE_CHACHA && HAVE_POLY1305 */
#endif /* WOLFSSL_PSA_CHACHA20_POLY1305_H */
