/* test_ossl_x509_acert.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_ACERT_H
#define WOLFCRYPT_TEST_OSSL_X509_ACERT_H

#include <tests/api/api_decl.h>

int test_wolfSSL_X509_ACERT_verify(void);
int test_wolfSSL_X509_ACERT_misc_api(void);
int test_wolfSSL_X509_ACERT_buffer(void);
int test_wolfSSL_X509_ACERT_new_and_sign(void);
int test_wolfSSL_X509_ACERT_asn(void);

#define TEST_OSSL_X509_ACERT_DECLS                                             \
    TEST_DECL_GROUP("ossl_x509_acert", test_wolfSSL_X509_ACERT_verify),        \
    TEST_DECL_GROUP("ossl_x509_acert", test_wolfSSL_X509_ACERT_misc_api),      \
    TEST_DECL_GROUP("ossl_x509_acert", test_wolfSSL_X509_ACERT_buffer),        \
    TEST_DECL_GROUP("ossl_x509_acert", test_wolfSSL_X509_ACERT_new_and_sign),  \
    TEST_DECL_GROUP("ossl_x509_acert", test_wolfSSL_X509_ACERT_new_and_sign)

#endif /* WOLFCRYPT_TEST_OSSL_X509_ACERT_H */
