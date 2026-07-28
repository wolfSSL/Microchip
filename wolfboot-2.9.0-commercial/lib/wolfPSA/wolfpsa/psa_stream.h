/* psa_stream.h
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
 * Platform Security Architecture (PSA) Stream Cipher API header
 *
 * If WOLFSSL_PSA_ENGINE is defined, wolfSSL provides an implementation of the
 * PSA Crypto API for stream cipher operations that calls wolfCrypt APIs.
 *
 */

#ifndef WOLFSSL_PSA_STREAM_H
#define WOLFSSL_PSA_STREAM_H

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#if defined(WOLFSSL_PSA_ENGINE)

#include <psa/crypto.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/visibility.h>

/* Check if a stream cipher algorithm is supported */
WOLFSSL_LOCAL psa_status_t psa_stream_check_alg_supported(psa_algorithm_t alg);

/* Check if a stream cipher key type is supported */
WOLFSSL_LOCAL psa_status_t psa_stream_check_key_type_supported(psa_key_type_t type);

/* Check if a stream cipher key size is valid for the given key type */
WOLFSSL_LOCAL psa_status_t psa_stream_check_key_size_valid(psa_key_type_t type, 
                                                          size_t bits);

/* Encrypt or decrypt a message using a stream cipher */
WOLFSSL_LOCAL psa_status_t psa_stream_cipher(psa_key_type_t key_type,
                                            size_t key_bits,
                                            const uint8_t *key_buffer,
                                            size_t key_buffer_size,
                                            psa_algorithm_t alg,
                                            const uint8_t *nonce,
                                            size_t nonce_length,
                                            const uint8_t *input,
                                            size_t input_length,
                                            uint8_t *output,
                                            size_t output_size,
                                            size_t *output_length);

#endif /* WOLFSSL_PSA_ENGINE */
#endif /* WOLFSSL_PSA_STREAM_H */
