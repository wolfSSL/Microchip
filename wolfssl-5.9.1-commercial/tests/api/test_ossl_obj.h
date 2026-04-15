/* test_ossl_obj.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_OBJ_H
#define WOLFCRYPT_TEST_OSSL_OBJ_H

#include <tests/api/api_decl.h>

int test_OBJ_NAME_do_all(void);
int test_wolfSSL_OBJ(void);
int test_wolfSSL_OBJ_cmp(void);
int test_wolfSSL_OBJ_txt2nid(void);
int test_wolfSSL_OBJ_txt2obj(void);
int test_wolfSSL_OBJ_ln(void);
int test_wolfSSL_OBJ_sn(void);

#define TEST_OSSL_OBJ_DECLS                                 \
    TEST_DECL_GROUP("ossl_obj", test_OBJ_NAME_do_all),      \
    TEST_DECL_GROUP("ossl_obj", test_wolfSSL_OBJ),          \
    TEST_DECL_GROUP("ossl_obj", test_wolfSSL_OBJ_cmp),      \
    TEST_DECL_GROUP("ossl_obj", test_wolfSSL_OBJ_txt2nid),  \
    TEST_DECL_GROUP("ossl_obj", test_wolfSSL_OBJ_txt2obj),  \
    TEST_DECL_GROUP("ossl_obj", test_wolfSSL_OBJ_ln),       \
    TEST_DECL_GROUP("ossl_obj", test_wolfSSL_OBJ_sn)

#endif /* WOLFCRYPT_TEST_OSSL_OBJ_H */

