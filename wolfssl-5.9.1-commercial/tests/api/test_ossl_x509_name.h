/* test_ossl_x509_name.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_NAME_H
#define WOLFCRYPT_TEST_OSSL_X509_NAME_H

#include <tests/api/api_decl.h>

int test_wolfSSL_X509_NAME_get_entry(void);
int test_wolfSSL_X509_NAME(void);
int test_wolfSSL_X509_NAME_hash(void);
int test_wolfSSL_X509_NAME_print_ex(void);
int test_wolfSSL_X509_NAME_ENTRY(void);
int test_wolfSSL_X509_NAME_ENTRY_get_object(void);

#define TEST_OSSL_X509_NAME_DECLS                                              \
    TEST_DECL_GROUP("ossl_x509_name", test_wolfSSL_X509_NAME_get_entry),       \
    TEST_DECL_GROUP("ossl_x509_name", test_wolfSSL_X509_NAME),                 \
    TEST_DECL_GROUP("ossl_x509_name", test_wolfSSL_X509_NAME_hash),            \
    TEST_DECL_GROUP("ossl_x509_name", test_wolfSSL_X509_NAME_print_ex),        \
    TEST_DECL_GROUP("ossl_x509_name", test_wolfSSL_X509_NAME_ENTRY),           \
    TEST_DECL_GROUP("ossl_x509_name", test_wolfSSL_X509_NAME_ENTRY_get_object)

#endif /* WOLFCRYPT_TEST_OSSL_X509_NAME_H */
