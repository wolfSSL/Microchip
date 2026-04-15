/* test_ossl_rand.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_RAND_H
#define WOLFCRYPT_TEST_OSSL_RAND_H

#include <tests/api/api_decl.h>

int test_wolfSSL_RAND_set_rand_method(void);
int test_wolfSSL_RAND_bytes(void);
int test_wolfSSL_RAND(void);
int test_wolfSSL_RAND_poll(void);

#define TEST_OSSL_RAND_DECLS                                            \
    TEST_DECL_GROUP("ossl_rand", test_wolfSSL_RAND_set_rand_method),    \
    TEST_DECL_GROUP("ossl_rand", test_wolfSSL_RAND_bytes),              \
    TEST_DECL_GROUP("ossl_rand", test_wolfSSL_RAND),                    \
    TEST_DECL_GROUP("ossl_rand", test_wolfSSL_RAND_poll)

#endif /* WOLFCRYPT_TEST_OSSL_RAND_H */

