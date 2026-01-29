/* renesas-rx64-hw-crypt.h
 *
 * Contributed by Johnson Controls Tyco IP Holdings LLP.
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef __RENESAS_RX64_HW_CRYPT_H__
#define __RENESAS_RX64_HW_CRYPT_H__

#include <renesas/security/sha/r_sha.h>
#include <wolfssl/wolfcrypt/logging.h>

#ifdef __cplusplus
extern "C" {
#endif

int rx64_hw_Open(void);
void rx64_hw_Close(void);
int rx64_hw_lock(void);
void rx64_hw_unlock(void);

#if (!defined(NO_SHA) || defined(WOLFSSL_SHA224) || !defined(NO_SHA256))

typedef enum
{
    RX64_SHA1 = 0,
    RX64_SHA224 = 1,
    RX64_SHA256 = 2,
    NUM_RX64_SHA_TYPES = 3,
} RX64_SHA_TYPE;

typedef struct
{
    byte*  msg;
    void*  heap;
    word32 used;
    word32 len;
    word32 sha_type;
} wolfssl_RX64_HW_Hash;

#if !defined(NO_SHA)
    typedef wolfssl_RX64_HW_Hash wc_Sha;
#endif

#if !defined(NO_SHA256)
    typedef wolfssl_RX64_HW_Hash wc_Sha256;
#endif

#if defined(WOLFSSL_SHA224)
    typedef wolfssl_RX64_HW_Hash wc_Sha224;
    #define WC_SHA224_TYPE_DEFINED
#endif

WOLFSSL_LOCAL int RX64_ShaCalc(byte* data, word32 len, byte* out, word32 sha_type);

#endif /* !NO_SHA || WOLFSSL_SHA224 || !NO_SHA256 */

#ifdef __cplusplus
}
#endif

#endif  /* __RENESAS_RX64_HW_CRYPT_H__ */
