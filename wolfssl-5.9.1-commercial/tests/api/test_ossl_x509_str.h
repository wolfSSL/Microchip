/* test_ossl_x509_str.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_STR_H
#define WOLFCRYPT_TEST_OSSL_X509_STR_H

#include <tests/api/api_decl.h>

int test_wolfSSL_X509_STORE_CTX_set_time(void);
int test_wolfSSL_X509_STORE_check_time(void);
int test_wolfSSL_X509_STORE_CTX_get0_store(void);
int test_wolfSSL_X509_STORE_CTX(void);
int test_wolfSSL_X509_STORE_CTX_ex(void);
int test_X509_STORE_untrusted(void);
int test_X509_STORE_InvalidCa(void);
int test_X509_STORE_InvalidCa_NoCallback(void);
int test_wolfSSL_X509_STORE_CTX_trusted_stack_cleanup(void);
int test_wolfSSL_X509_STORE_CTX_get_issuer(void);
int test_wolfSSL_X509_STORE_set_flags(void);
int test_wolfSSL_X509_STORE(void);
int test_wolfSSL_X509_STORE_load_locations(void);
int test_X509_STORE_get0_objects(void);
int test_wolfSSL_X509_STORE_get1_certs(void);
int test_wolfSSL_X509_STORE_set_get_crl(void);
int test_wolfSSL_X509_CA_num(void);
int test_X509_STORE_No_SSL_CTX(void);

#define TEST_OSSL_X509_STORE_DECLS                                             \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_STORE_CTX_set_time),  \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_STORE_check_time),    \
    TEST_DECL_GROUP("ossl_x509_store",                                         \
                                      test_wolfSSL_X509_STORE_CTX_get0_store), \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_STORE_CTX),           \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_STORE_CTX_ex),        \
    TEST_DECL_GROUP("ossl_x509_store", test_X509_STORE_untrusted),             \
    TEST_DECL_GROUP("ossl_x509_store", test_X509_STORE_InvalidCa),             \
    TEST_DECL_GROUP("ossl_x509_store", test_X509_STORE_InvalidCa_NoCallback),  \
    TEST_DECL_GROUP("ossl_x509_store",                                         \
                           test_wolfSSL_X509_STORE_CTX_trusted_stack_cleanup), \
    TEST_DECL_GROUP("ossl_x509_store",                                         \
                                      test_wolfSSL_X509_STORE_CTX_get_issuer), \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_STORE_set_flags),     \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_STORE),               \
    TEST_DECL_GROUP("ossl_x509_store",                                         \
                                      test_wolfSSL_X509_STORE_load_locations), \
    TEST_DECL_GROUP("ossl_x509_store", test_X509_STORE_get0_objects),          \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_STORE_get1_certs),    \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_STORE_set_get_crl),   \
    TEST_DECL_GROUP("ossl_x509_store", test_wolfSSL_X509_CA_num),              \
    TEST_DECL_GROUP("ossl_x509_store", test_X509_STORE_No_SSL_CTX)

#endif /* WOLFCRYPT_TEST_OSSL_X509_STR_H */
