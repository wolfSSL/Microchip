/* test_she.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_SHE_H
#define WOLFCRYPT_TEST_SHE_H

#include <tests/api/api_decl.h>

int test_wc_SHE_Init(void);
int test_wc_SHE_Init_Id(void);
int test_wc_SHE_Init_Label(void);
int test_wc_SHE_Free(void);
int test_wc_SHE_ImportM1M2M3(void);
int test_wc_SHE_AesMp16(void);
int test_wc_SHE_GenerateM1M2M3(void);
int test_wc_SHE_GenerateM4M5(void);
#ifdef WOLFSSL_SHE_EXTENDED
int test_wc_SHE_SetKdfConstants(void);
int test_wc_SHE_SetM2M4Header(void);
#endif
#if defined(WOLF_CRYPTO_CB) && defined(WOLFSSL_SHE)
int test_wc_SHE_CryptoCb(void);
#ifndef NO_WC_SHE_LOADKEY
int test_wc_SHE_LoadKey(void);
int test_wc_SHE_LoadKey_Verify(void);
#endif
#endif

#define TEST_SHE_DECLS                                              \
    TEST_DECL_GROUP("she", test_wc_SHE_Init),                       \
    TEST_DECL_GROUP("she", test_wc_SHE_Init_Id),                    \
    TEST_DECL_GROUP("she", test_wc_SHE_Init_Label),                 \
    TEST_DECL_GROUP("she", test_wc_SHE_Free),                       \
    TEST_DECL_GROUP("she", test_wc_SHE_ImportM1M2M3),               \
    TEST_DECL_GROUP("she", test_wc_SHE_AesMp16),                    \
    TEST_DECL_GROUP("she", test_wc_SHE_GenerateM1M2M3),             \
    TEST_DECL_GROUP("she", test_wc_SHE_GenerateM4M5)

#ifdef WOLFSSL_SHE_EXTENDED
#define TEST_SHE_EXT_DECLS                                          \
    TEST_DECL_GROUP("she", test_wc_SHE_SetKdfConstants),            \
    TEST_DECL_GROUP("she", test_wc_SHE_SetM2M4Header)
#else
#define TEST_SHE_EXT_DECLS
#endif

#if defined(WOLF_CRYPTO_CB) && defined(WOLFSSL_SHE)
#if !defined(NO_WC_SHE_LOADKEY)
#define TEST_SHE_CB_DECLS \
    TEST_DECL_GROUP("she", test_wc_SHE_CryptoCb), \
    TEST_DECL_GROUP("she", test_wc_SHE_LoadKey), \
    TEST_DECL_GROUP("she", test_wc_SHE_LoadKey_Verify)
#else
#define TEST_SHE_CB_DECLS \
    TEST_DECL_GROUP("she", test_wc_SHE_CryptoCb)
#endif
#else
#define TEST_SHE_CB_DECLS
#endif

#endif /* WOLFCRYPT_TEST_SHE_H */
