/* user_settings.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFSSL_USER_SETTINGS_H
#define WOLFSSL_USER_SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#define NO_WOLFSSL_SERVER
#define NO_OLD_TLS


#define HAVE_TLS_EXTENSIONS
#define HAVE_SUPPORTED_CURVES
#define HAVE_EXTENDED_MASTER
#define HAVE_ENCRYPT_THEN_MAC

#define HAVE_HASHDRBG
#define HAVE_GETRANDOM

#define HAVE_ECC
#define HAVE_ECC_KEY_EXPORT
#define HAVE_ECC_KEY_IMPORT
#define ECC_USER_CURVES
#define ECC_TIMING_RESISTANT
#define WC_RSA_BLINDING

#define WOLFSSL_ECDSA_DETERMINISTIC_K

#define HAVE_AESGCM
#define GCM_SMALL

#define NO_DH
#define NO_DSA
#define NO_PSK
#define NO_RC4
#define NO_MD4
#define NO_MD5
#define NO_DES3
#define NO_PWDBASED
#define NO_SHA

#define WOLFSSL_SHA256
#define WOLFSSL_SHA384
#define WOLFSSL_SHA512

#define HAVE_HKDF
#define WOLFSSL_HAVE_PRF

#ifdef __cplusplus
}
#endif

#endif /* WOLFSSL_USER_SETTINGS_H */
