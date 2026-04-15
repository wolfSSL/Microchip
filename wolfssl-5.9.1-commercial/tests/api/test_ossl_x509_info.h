/* test_ossl_x509_info.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_INFO_H
#define WOLFCRYPT_TEST_OSSL_X509_INFO_H

#include <tests/api/api_decl.h>

int test_wolfSSL_X509_INFO_multiple_info(void);
int test_wolfSSL_X509_INFO(void);
int test_wolfSSL_PEM_X509_INFO_read_bio(void);
int test_wolfSSL_PEM_X509_INFO_read(void);

#define TEST_OSSL_X509_INFO_DECLS                                              \
    TEST_DECL_GROUP("ossl_x509_info", test_wolfSSL_X509_INFO_multiple_info),   \
    TEST_DECL_GROUP("ossl_x509_info", test_wolfSSL_X509_INFO),                 \
    TEST_DECL_GROUP("ossl_x509_info", test_wolfSSL_PEM_X509_INFO_read_bio),    \
    TEST_DECL_GROUP("ossl_x509_info", test_wolfSSL_PEM_X509_INFO_read)

#endif /* WOLFCRYPT_TEST_OSSL_X509_INFO_H */
