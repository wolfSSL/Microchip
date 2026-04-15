/* blake2.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*!
    \file wolfssl/wolfcrypt/blake2.h
*/

#ifndef WOLF_CRYPT_BLAKE2_H
#define WOLF_CRYPT_BLAKE2_H

#include <wolfssl/wolfcrypt/settings.h>

#if defined(HAVE_BLAKE2B) || defined(HAVE_BLAKE2S)

#include <wolfssl/wolfcrypt/blake2-int.h>

/* call old functions if using fips for the sake of hmac @wc_fips */
#ifdef HAVE_FIPS
    #ifdef WOLFSSL_API_PREFIX_MAP
        #define InitBlake2b   wc_InitBlake2b
        #define Blake2bUpdate wc_Blake2bUpdate
        #define Blake2bFinal  wc_Blake2bFinal
    #else
        /* Since hmac can call blake functions provide original calls */
        #define wc_InitBlake2b   InitBlake2b
        #define wc_Blake2bUpdate Blake2bUpdate
        #define wc_Blake2bFinal  Blake2bFinal
    #endif
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/* in bytes, variable digest size up to 512 bits (64 bytes) */
#ifdef HAVE_BLAKE2B
    #define BLAKE2B_ID  WC_HASH_TYPE_BLAKE2B
    #define BLAKE2B_256 32  /* 256 bit type, SSL default */
    #define WC_BLAKE2B_DIGEST_SIZE 64
#endif
#ifdef HAVE_BLAKE2S
    #define BLAKE2S_ID WC_HASH_TYPE_BLAKE2S
    #define BLAKE2S_256 32  /* 256 bit type */
    #define WC_BLAKE2S_DIGEST_SIZE 32
#endif


#ifdef HAVE_BLAKE2B
/* BLAKE2b digest */
typedef struct Blake2b {
    blake2b_state S[1];         /* our state */
    word32        digestSz;     /* digest size used on init */
} Blake2b;
#endif

#ifdef HAVE_BLAKE2S
/* BLAKE2s digest */
typedef struct Blake2s {
    blake2s_state S[1];         /* our state */
    word32        digestSz;     /* digest size used on init */
} Blake2s;
#endif


#ifdef HAVE_BLAKE2B
WOLFSSL_API int wc_InitBlake2b(Blake2b* b2b, word32 digestSz);
WOLFSSL_API int wc_InitBlake2b_WithKey(Blake2b* b2b, word32 digestSz,
                                       const byte *key, word32 keylen);
WOLFSSL_API int wc_Blake2bUpdate(Blake2b* b2b, const byte* data, word32 sz);
WOLFSSL_API int wc_Blake2bFinal(Blake2b* b2b, byte* final, word32 requestSz);
WOLFSSL_API int wc_Blake2bHmacInit(Blake2b* b2b,
        const byte* key, size_t key_len);
WOLFSSL_API int wc_Blake2bHmacUpdate(Blake2b* b2b,
        const byte* in, size_t in_len);
WOLFSSL_API int wc_Blake2bHmacFinal(Blake2b* b2b,
        const byte* key, size_t key_len,
        byte* out, size_t out_len);
WOLFSSL_API int wc_Blake2bHmac(const byte* in, size_t in_len,
        const byte* key, size_t key_len,
        byte* out, size_t out_len);
#endif

#ifdef HAVE_BLAKE2S
WOLFSSL_API int wc_InitBlake2s(Blake2s* b2s, word32 digestSz);
WOLFSSL_API int wc_InitBlake2s_WithKey(Blake2s* b2s, word32 digestSz,
                                       const byte *key, word32 keylen);
WOLFSSL_API int wc_Blake2sUpdate(Blake2s* b2s, const byte* data, word32 sz);
WOLFSSL_API int wc_Blake2sFinal(Blake2s* b2s, byte* final, word32 requestSz);
WOLFSSL_API int wc_Blake2sHmacInit(Blake2s* b2s,
        const byte* key, size_t key_len);
WOLFSSL_API int wc_Blake2sHmacUpdate(Blake2s* b2s,
        const byte* in, size_t in_len);
WOLFSSL_API int wc_Blake2sHmacFinal(Blake2s* b2s,
        const byte* key, size_t key_len,
        byte* out, size_t out_len);
WOLFSSL_API int wc_Blake2sHmac(const byte* in, size_t in_len,
        const byte* key, size_t key_len,
        byte* out, size_t out_len);
#endif


#ifdef __cplusplus
    }
#endif

#endif  /* HAVE_BLAKE2B || HAVE_BLAKE2S */
#endif  /* WOLF_CRYPT_BLAKE2_H */

