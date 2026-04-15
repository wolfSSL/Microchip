/* user_settings_wolfboot_keytools.h
 *
 * wolfCrypt build settings for wolfBoot keygen and signing tool
 * Enabled via WOLFSSL_USER_SETTINGS.
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* wolfBoot key generation and signing tool.
 * Derived from wolfBoot tools/keytools/user_settings.h
 *
 * Build and test:
 * cp ./examples/configs/user_settings_wolfboot_keytools.h user_settings.h
 * ./configure --enable-usersettings --disable-examples
 * make
 * ./wolfcrypt/test/testwolfcrypt
 */

#ifndef WOLFSSL_USER_SETTINGS_H
#define WOLFSSL_USER_SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------- */
/* Platform */
/* ------------------------------------------------- */
#define SINGLE_THREADED
#define WOLFCRYPT_ONLY

/* ------------------------------------------------- */
/* Math */
/* ------------------------------------------------- */
#if 0 /* Fast Math */
    #define USE_FAST_MATH
    #define FP_MAX_BITS (4096 * 2)
#else /* SP Math (recommended) */
    #define WOLFSSL_SP_MATH
    #define WOLFSSL_HAVE_SP_ECC
    #define WOLFSSL_SP_384
    #define WOLFSSL_SP_521
    #define WOLFSSL_HAVE_SP_RSA
    #define WOLFSSL_SP_4096
#endif
#define TFM_TIMING_RESISTANT

/* ------------------------------------------------- */
/* ECC */
/* ------------------------------------------------- */
#if 1 /* ECC support */
    #define HAVE_ECC
    #define ECC_TIMING_RESISTANT
    #define ECC_USER_CURVES
    #undef  NO_ECC256
    #if 1 /* ECC P-384 */
        #define HAVE_ECC384
    #endif
    #if 1 /* ECC P-521 */
        #define HAVE_ECC521
    #endif
#endif

/* ------------------------------------------------- */
/* ED25519 / Curve25519 */
/* ------------------------------------------------- */
#if 1 /* ED25519 signing support */
    #define HAVE_ED25519
#endif

/* ------------------------------------------------- */
/* ED448 / Curve448 */
/* ------------------------------------------------- */
#if 1 /* ED448 signing support */
    #define HAVE_ED448
    #define WOLFSSL_SHAKE256
#endif

/* ------------------------------------------------- */
/* RSA */
/* ------------------------------------------------- */
#if 1 /* RSA signing support */
    #define HAVE_RSA
    #define WC_RSA_BLINDING
    #define WOLFSSL_KEY_GEN
#else
    #define NO_RSA
#endif

/* ------------------------------------------------- */
/* Hashing */
/* ------------------------------------------------- */
#define WOLFSSL_SHA512 /* Required for ED25519/ED448 */
#define WOLFSSL_SHA384
#define WOLFSSL_SHA3

/* ------------------------------------------------- */
/* Post-Quantum Algorithms */
/* ------------------------------------------------- */
#define WOLFSSL_EXPERIMENTAL_SETTINGS

#if 1 /* ML-DSA / Dilithium */
    #define HAVE_DILITHIUM
    #define WOLFSSL_WC_DILITHIUM
    /* Builds to FIPS 204 final standard by default.
     * Set to 1 for draft version. */
    #if 0 /* FIPS 204 Draft */
        #define WOLFSSL_DILITHIUM_FIPS204_DRAFT
    #endif
    #ifndef ML_DSA_LEVEL
        #define ML_DSA_LEVEL 2
    #endif
    #define WOLFSSL_SHAKE128 /* Required for Dilithium */
#endif

#if 1 /* LMS */
    #define WOLFSSL_HAVE_LMS
    #define WOLFSSL_WC_LMS
    #ifndef LMS_LEVELS
        #define LMS_LEVELS 1
    #endif
    #ifndef LMS_HEIGHT
        #define LMS_HEIGHT 10
    #endif
    #ifndef LMS_WINTERNITZ
        #define LMS_WINTERNITZ 8
    #endif
#endif

#if 1 /* XMSS */
    #define WOLFSSL_HAVE_XMSS
    #define WOLFSSL_WC_XMSS
    #ifndef WOLFSSL_XMSS_MAX_HEIGHT
        #define WOLFSSL_XMSS_MAX_HEIGHT 32
    #endif
#endif

/* ------------------------------------------------- */
/* Symmetric Ciphers */
/* ------------------------------------------------- */
#if 1 /* ChaCha20 stream cipher */
    #define HAVE_CHACHA
#endif
#if 1 /* AES-CTR / AES direct */
    #define WOLFSSL_AES_COUNTER
    #define WOLFSSL_AES_DIRECT
#endif

/* ------------------------------------------------- */
/* ASN */
/* ------------------------------------------------- */
#define WOLFSSL_ASN_TEMPLATE

/* ------------------------------------------------- */
/* Disabled Algorithms */
/* ------------------------------------------------- */
#define NO_CMAC
#define NO_HMAC
#define NO_RC4
#define NO_SHA
#define NO_DH
#define NO_DSA
#define NO_MD4
#define NO_MD5
#define NO_DES3
#define NO_PWDBASED
#define NO_OLD_RNGNAME
#define NO_RABBIT
#define NO_HC128

/* ------------------------------------------------- */
/* Disabled Features */
/* ------------------------------------------------- */
#define NO_SIG_WRAPPER
#define NO_CERTS
#define NO_SESSION_CACHE
#define NO_WRITEV
#define NO_WOLFSSL_DIR
#define WOLFSSL_NO_SOCK
#define WOLFSSL_IGNORE_FILE_WARN
#define BENCH_EMBEDDED

#if 1 /* Disable error strings to save flash */
    #define NO_ERROR_STRINGS
#endif

#ifdef __cplusplus
}
#endif

#endif /* WOLFSSL_USER_SETTINGS_H */
