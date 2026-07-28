/* psa_pq.c
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
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/mem_track.h>

/* Check if a key type is a post-quantum key type */
psa_status_t psa_pq_check_key_type_supported(psa_key_type_t type)
{
    /* SLH-DSA is a family of values (key pair 0x7180..0x71ff, public
     * 0x4180..0x41ff) and cannot appear as case labels.  wolfCrypt has no
     * SLH-DSA backend, so reject the whole family here before the switch. */
    if (PSA_KEY_TYPE_IS_SLH_DSA(type)) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    switch (type) {
#if defined(WOLFSSL_HAVE_MLKEM)
        case PSA_KEY_TYPE_ML_KEM_KEY_PAIR:
        case PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY:
            return PSA_SUCCESS;
#endif
#if defined(WOLFSSL_HAVE_MLDSA)
        case PSA_KEY_TYPE_ML_DSA_KEY_PAIR:
        case PSA_KEY_TYPE_ML_DSA_PUBLIC_KEY:
            return PSA_SUCCESS;
#endif
        /* LMS and HSS are public-key-only types in PSA 1.4 */
#if defined(WOLFSSL_HAVE_LMS)
        case PSA_KEY_TYPE_LMS_PUBLIC_KEY:
        case PSA_KEY_TYPE_HSS_PUBLIC_KEY:
            return PSA_SUCCESS;
#endif
        /* XMSS and XMSS^MT are public-key-only types in PSA 1.4 */
#if defined(WOLFSSL_HAVE_XMSS)
        case PSA_KEY_TYPE_XMSS_PUBLIC_KEY:
        case PSA_KEY_TYPE_XMSS_MT_PUBLIC_KEY:
            return PSA_SUCCESS;
#endif
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }
}

/* Check if a key size is valid for the given post-quantum key type */
psa_status_t psa_pq_check_key_size_valid(psa_key_type_t type, size_t bits)
{
    /* Unused when every PQC backend is compiled out. */
    (void)bits;

    /* SLH-DSA is unsupported; reject before the switch (family of values). */
    if (PSA_KEY_TYPE_IS_SLH_DSA(type)) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    switch (type) {
#if defined(WOLFSSL_HAVE_MLKEM)
        case PSA_KEY_TYPE_ML_KEM_KEY_PAIR:
        case PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY:
            /* ML-KEM parameter sets: 512, 768, 1024 */
            if (bits == 512 || bits == 768 || bits == 1024) {
                return PSA_SUCCESS;
            }
            return PSA_ERROR_INVALID_ARGUMENT;
#endif
#if defined(WOLFSSL_HAVE_MLDSA)
        case PSA_KEY_TYPE_ML_DSA_KEY_PAIR:
        case PSA_KEY_TYPE_ML_DSA_PUBLIC_KEY:
            /* ML-DSA security strengths in bits: 128 (ML-DSA-44),
             * 192 (ML-DSA-65), 256 (ML-DSA-87) */
            if (bits == 128 || bits == 192 || bits == 256) {
                return PSA_SUCCESS;
            }
            return PSA_ERROR_INVALID_ARGUMENT;
#endif
        /* LMS and HSS are public-key-only types in PSA 1.4.
         * bits = output length in bits of the parameter set's hash function:
         * 192 (SHA-256/192 or SHAKE-256/192) or 256 (SHA-256 or SHAKE-256). */
#if defined(WOLFSSL_HAVE_LMS)
        case PSA_KEY_TYPE_LMS_PUBLIC_KEY:
        case PSA_KEY_TYPE_HSS_PUBLIC_KEY:
            if (bits == 192 || bits == 256) {
                return PSA_SUCCESS;
            }
            return PSA_ERROR_INVALID_ARGUMENT;
#endif
        /* XMSS and XMSS^MT are public-key-only types in PSA 1.4.
         * bits = output length in bits of the parameter set's hash function:
         * 192 (SHA-256/192 or SHAKE-256/192) or 256 (SHA-256 or SHAKE-256). */
#if defined(WOLFSSL_HAVE_XMSS)
        case PSA_KEY_TYPE_XMSS_PUBLIC_KEY:
        case PSA_KEY_TYPE_XMSS_MT_PUBLIC_KEY:
            if (bits == 192 || bits == 256) {
                return PSA_SUCCESS;
            }
            return PSA_ERROR_INVALID_ARGUMENT;
#endif
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }
}

#endif /* WOLFSSL_PSA_ENGINE */
