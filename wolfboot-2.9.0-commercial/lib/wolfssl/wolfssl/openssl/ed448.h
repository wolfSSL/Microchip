/* ed448.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* ed448.h */

#ifndef WOLFSSL_ED448_H_
#define WOLFSSL_ED448_H_

#include <wolfssl/openssl/compat_types.h>

#ifdef __cplusplus
extern "C" {
#endif

WOLFSSL_API
int wolfSSL_ED448_generate_key(unsigned char *priv, unsigned int *privSz,
                               unsigned char *pub, unsigned int *pubSz);
WOLFSSL_API
int wolfSSL_ED448_sign(const unsigned char *msg, unsigned int msgSz,
                       const unsigned char *priv, unsigned int privSz,
                       unsigned char *sig, unsigned int *sigSz);
WOLFSSL_API
int wolfSSL_ED448_verify(const unsigned char *msg, unsigned int msgSz,
                         const unsigned char *pub, unsigned int pubSz,
                         const unsigned char *sig, unsigned int sigSz);

#if defined(OPENSSL_EXTRA) || defined(WOLFSSL_WPAS_SMALL)
#ifndef WC_ED448KEY_TYPE_DEFINED
    typedef struct ed448_key ed448_key;
    #define WC_ED448KEY_TYPE_DEFINED
#endif
/* Not OpenSSL API's, but these two constructors are leveraged within
 * wolfSSL's compat layer for Ed448 object creation/deletion simplicity */
WOLFSSL_API
ed448_key* wolfSSL_ED448_new(void* heap, int devId);

WOLFSSL_API
void wolfSSL_ED448_free(ed448_key* key);
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* header */
