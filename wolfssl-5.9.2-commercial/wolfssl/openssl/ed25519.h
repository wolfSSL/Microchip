/* ed25519.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* ed25519.h */

#ifndef WOLFSSL_ED25519_H_
#define WOLFSSL_ED25519_H_

#include <wolfssl/openssl/compat_types.h>

#ifdef __cplusplus
extern "C" {
#endif

WOLFSSL_API
int wolfSSL_ED25519_generate_key(unsigned char *priv, unsigned int *privSz,
                                 unsigned char *pub, unsigned int *pubSz);
WOLFSSL_API
int wolfSSL_ED25519_sign(const unsigned char *msg, unsigned int msgSz,
                         const unsigned char *priv, unsigned int privSz,
                         unsigned char *sig, unsigned int *sigSz);
WOLFSSL_API
int wolfSSL_ED25519_verify(const unsigned char *msg, unsigned int msgSz,
                           const unsigned char *pub, unsigned int pubSz,
                           const unsigned char *sig, unsigned int sigSz);

#if defined(OPENSSL_EXTRA) || defined(WOLFSSL_WPAS_SMALL)
#ifndef WC_ED25519KEY_TYPE_DEFINED
    typedef struct ed25519_key ed25519_key;
    #define WC_ED25519KEY_TYPE_DEFINED
#endif
/* Not OpenSSL API's, but these two constructors are leveraged within
 * wolfSSL's compat layer for Ed25519 object creation/deletion simplicity */
WOLFSSL_API
ed25519_key* wolfSSL_ED25519_new(void* heap, int devId);

WOLFSSL_API
void wolfSSL_ED25519_free(ed25519_key* key);
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* header */
