/* test_chacha.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_CHACHA_H
#define WOLFCRYPT_TEST_CHACHA_H

#include <tests/api/api_decl.h>

int test_wc_Chacha_SetKey(void);
int test_wc_Chacha_Process(void);
int test_wc_Chacha_Process_Chunking(void);
int test_wc_Chacha_MonteCarlo(void);
int test_wc_Chacha_CounterOverflow(void);
int test_wc_Chacha_InPlace(void);
int test_wc_Chacha_UnalignedBuffers(void);

#define TEST_CHACHA_DECLS                                               \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_SetKey),                   \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_Process),                  \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_Process_Chunking),         \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_MonteCarlo),               \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_CounterOverflow),          \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_InPlace),                  \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_UnalignedBuffers)

#endif /* WOLFCRYPT_TEST_CHACHA_H */
