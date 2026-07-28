/* user_settings_curve25519nonblock.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Example wolfSSL user_settings.h file for Curve25519 (X25519) non-blocking.
 * See doc/dox_comments/header_files/curve25519.h wc_curve25519_set_nonblock.
 */

/* Settings based on this configure:
./configure --enable-curve25519=nonblock --enable-ecc=nonblock \
    --enable-sp=yes,nonblock \
    CFLAGS="-DWOLFSSL_PUBLIC_MP -DWOLFSSL_DEBUG_NONBLOCK"
*/

/* Tested using:
cp ./examples/configs/user_settings_curve25519nonblock.h user_settings.h
./configure --enable-usersettings --enable-debug --disable-examples
make
./wolfcrypt/test/testwolfcrypt
*/

/* Example test results:
CURVE25519 non-block key gen: 1273 times
CURVE25519 non-block shared secret: 1275 times
CURVE25519 test passed!
*/

#ifndef WOLFSSL_USER_SETTINGS_H
#define WOLFSSL_USER_SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Features */
#define WOLFCRYPT_ONLY
#define WOLFSSL_ASN_TEMPLATE
#define WOLFSSL_PUBLIC_MP /* expose mp_ math API's */
#define HAVE_HASHDRBG

/* Curve25519 (X25519) */
#define HAVE_CURVE25519
#define CURVE25519_SMALL
#define WC_X25519_NONBLOCK

/* Debugging */
#if 1
    #undef  DEBUG_WOLFSSL
    #define DEBUG_WOLFSSL
    #define WOLFSSL_DEBUG_NONBLOCK
#endif

/* Disabled algorithms */
#define NO_OLD_TLS
#define NO_RSA
#define NO_DH
#define NO_PSK
#define NO_MD4
#define NO_MD5
#define NO_SHA
#define NO_DSA
#define NO_DES3
#define NO_RC4
#define WOLFSSL_NO_SHAKE128
#define WOLFSSL_NO_SHAKE256

#ifdef __cplusplus
}
#endif

#endif /* WOLFSSL_USER_SETTINGS_H */
