/* psa_random.h
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
 * Platform Security Architecture (PSA) Random Number Generator API header
 *
 * If WOLFSSL_PSA_ENGINE is defined, wolfSSL provides an implementation of the
 * PSA Crypto API for random number generation that calls wolfCrypt APIs.
 *
 */

#ifndef WOLFSSL_PSA_RANDOM_H
#define WOLFSSL_PSA_RANDOM_H

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#if defined(WOLFSSL_PSA_ENGINE)

#include <psa/crypto.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/visibility.h>

/* Generate random bytes */
WOLFSSL_LOCAL psa_status_t psa_generate_random(uint8_t *output,
                                              size_t output_size);

#endif /* WOLFSSL_PSA_ENGINE */
#endif /* WOLFSSL_PSA_RANDOM_H */
