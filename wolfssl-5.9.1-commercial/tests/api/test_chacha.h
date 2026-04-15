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

#define TEST_CHACHA_DECLS                                       \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_SetKey),           \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_Process),          \
    TEST_DECL_GROUP("chacha", test_wc_Chacha_Process_Chunking)

#endif /* WOLFCRYPT_TEST_CHACHA_H */
