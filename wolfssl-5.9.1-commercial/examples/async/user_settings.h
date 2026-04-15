/* user_settings.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Bare-metal user settings for TLS 1.3 client with WOLFSSL_USER_IO. */
#ifndef WOLFSSL_USER_SETTINGS_H
#define WOLFSSL_USER_SETTINGS_H

#define WOLFSSL_USER_IO
#define SINGLE_THREADED
#define NO_FILESYSTEM
#define WOLFSSL_IGNORE_FILE_WARN

#define HAVE_ECC
#define WC_ECC_NONBLOCK
#define WC_ECC_NONBLOCK_ONLY
#define ECC_USER_CURVES /* P256 only */
#define WOLFSSL_HAVE_SP_ECC
#define WOLFSSL_SP_SMALL
#define WOLFSSL_SP_NONBLOCK
#define WOLFSSL_SP_NO_MALLOC
#define ECC_TIMING_RESISTANT

#define HAVE_ED25519
#define HAVE_CURVE25519
#define CURVE25519_SMALL
#define ED25519_SMALL
#define WC_X25519_NONBLOCK

#define WOLFSSL_ASYNC_CRYPT
#define WC_NO_ASYNC_THREADING
#define HAVE_WOLF_BIGINT

/* Async mode is controlled via Makefile ASYNC_MODE variable:
 * - ASYNC_MODE=sw (default): WOLFSSL_ASYNC_CRYPT_SW for non-blocking ECC
 * - ASYNC_MODE=cryptocb: WOLF_CRYPTO_CB for crypto callback simulation
 * These are mutually exclusive in async.c polling code (#elif).
 * See README.md for build instructions.
 */

#define HAVE_AESGCM

#define WOLFSSL_SHA512
#define WOLFSSL_HASH_FLAGS

#define WOLFSSL_TLS13
#define HAVE_HKDF
#define HAVE_TLS_EXTENSIONS
#define HAVE_SUPPORTED_CURVES
#define HAVE_SERVER_RENEGOTIATION_INFO
#define HAVE_ENCRYPT_THEN_MAC
#define HAVE_SNI

#define HAVE_SESSION_TICKET

extern int posix_getdevrandom(unsigned char *out, unsigned int sz);
#ifndef HAVE_HASHDRBG
    #define CUSTOM_RAND_GENERATE_BLOCK posix_getdevrandom
#else
    #define CUSTOM_RAND_GENERATE_SEED  posix_getdevrandom
#endif

/* Minimal feature set - explicitly disable unwanted algorithms */
#define NO_RSA
#define NO_DH
#define NO_DSA
#define WOLFSSL_NO_SHAKE256
#define WOLFSSL_NO_SHAKE128
#define NO_MD4
#define NO_MD5
#define NO_DES3
#define NO_SHA
#define NO_OLD_TLS

/* Debugging */
#if 0
    #define DEBUG_WOLFSSL
#endif
#define WOLFSSL_DEBUG_NONBLOCK

#endif /* WOLFSSL_USER_SETTINGS_H */
