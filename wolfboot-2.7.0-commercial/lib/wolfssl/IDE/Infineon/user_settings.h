/* user_settings.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Example build settings for Infineon Modus Toolbox */
/* Enables wolfSSL TLS v1.2-v1.3 and TPM support */
/* SHA-1, SHA-2, AES CBC/GCM, ECDHE, ECDSA, RSA, HMAC, HKDF */

#ifndef WOLF_USER_SETTINGS_TPM_H
#define WOLF_USER_SETTINGS_TPM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Platform / Porting */
#define NO_FILESYSTEM /* File system disable */
#define SINGLE_THREADED /* No threading */
#define WOLFSSL_USER_IO /* user recv/send callbacks for network IO */
#define NO_WRITEV
#define NO_MAIN_DRIVER
#define WOLFSSL_IGNORE_FILE_WARN /* ignore file include warnings */
#define WOLFSSL_SMALL_STACK /* limit stack usage */
#define BENCH_EMBEDDED

/* TLS (allow TLS v1.3 or v1.2) */
#define WOLFSSL_TLS13
//#define WOLFSSL_NO_TLS12
#define NO_OLD_TLS
#define WOLFSSL_EITHER_SIDE /* allow context to be created for either server or client */

#define HAVE_TLS_EXTENSIONS
#define HAVE_SUPPORTED_CURVES
#define HAVE_SERVER_RENEGOTIATION_INFO
#define HAVE_ENCRYPT_THEN_MAC

#ifdef WOLFSSL_TLS13
    #define HAVE_HKDF
    #define WC_RSA_PSS
    #define WOLFSSL_PSS_LONG_SALT
#endif

/* Enable crypto callbacks - for TPM offloading */
#define WOLF_CRYPTO_CB

/* Enable SP math all (sp_int.c) with multi-precision support */
#define WOLFSSL_SP_MATH_ALL

#if 1
    /* Single Precision math for ECC 256 and RSA 2048 */
    #define WOLFSSL_HAVE_SP_RSA
    #define WOLFSSL_HAVE_SP_ECC
    #define WOLFSSL_SP_SMALL
#endif

#if 0
    /* only single precision math */
    #define WOLFSSL_SP_MATH
#endif

/* Enable hardening (timing resistance) */
#define TFM_TIMING_RESISTANT
#define ECC_TIMING_RESISTANT
#define WC_RSA_BLINDING

/* Enable PRNG (SHA2-256) */
#define HAVE_HASHDRBG

/* Asymmetric */
#if 1 /* RSA - needed to encrypt salt */
    #undef  NO_RSA
    #ifdef USE_LOW_RESOURCE
        #define WOLFSSL_RSA_PUBLIC_ONLY
        #define WOLFSSL_RSA_VERIFY_INLINE
        #define NO_CHECK_PRIVATE_KEY
    #endif
#else
    #define NO_RSA
#endif

#if 1 /* ECC - needed for encrypt ECC salt */
    #define HAVE_ECC
    #define ECC_USER_CURVES /* default to only SECP256R1 */
#endif

#if 0 /* DH - TPM doesn't support it */
    #undef  NO_DH
    #define HAVE_FFDHE_2048
    #define HAVE_DH_DEFAULT_PARAMS
#else
    #define NO_DH
#endif

/* Symmetric Hash */
#undef NO_SHA /* allow SHA-1 */
#undef NO_SHA256 /* allow SHA2-256 */
#define WOLFSSL_SHA384
#define WOLFSSL_SHA512

/* Symmetric Cipher */
#define WOLFSSL_AES_CFB
#define HAVE_AES_DECRYPT

#define HAVE_AES_KEYWRAP
#define WOLFSSL_AES_DIRECT
#define HAVE_AESGCM
#define GCM_TABLE_4BIT

/* Features */
#define WOLFSSL_ASN_TEMPLATE

#define WOLFSSL_CERT_GEN
#define WOLFSSL_CERT_REQ
#define WOLFSSL_CERT_EXT

#define HAVE_PKCS7
#define HAVE_X963_KDF
#define WOLFSSL_BASE64_ENCODE

#if 1
    #define HAVE_SESSION_TICKETS
    #define SMALL_SESSION_CACHE
#else
    #define NO_SESSION_CACHE
#endif

/* Disables */
#define NO_PKCS8
#define NO_PKCS12
#define NO_PWDBASED
#define NO_DSA
#define NO_DES3
#define NO_RC4
#define NO_PSK
#define NO_MD4
#define NO_MD5
#define WOLFSSL_NO_SHAKE128
#define WOLFSSL_NO_SHAKE256

/* Logging */
#ifdef ENABLE_SECURE_SOCKETS_LOGS
    #define DEBUG_WOLFSSL
#else
    #define NO_ERROR_STRINGS
#endif

#ifdef __cplusplus
}
#endif

#endif /* WOLF_USER_SETTINGS_TPM_H */
