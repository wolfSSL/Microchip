/* test_ossl_x509_pk.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_PK_H
#define WOLFCRYPT_TEST_OSSL_X509_PK_H

#include <tests/api/api_decl.h>

int test_wolfSSL_X509_get_X509_PUBKEY(void);
int test_wolfSSL_X509_PUBKEY_RSA(void);
int test_wolfSSL_X509_PUBKEY_EC(void);
int test_wolfSSL_X509_PUBKEY_DSA(void);
int test_wolfSSL_X509_PUBKEY_get(void);
int test_wolfSSL_X509_set_pubkey(void);

#define TEST_OSSL_X509_PK_DECLS                                                \
    TEST_DECL_GROUP("ossl_x509_pk", test_wolfSSL_X509_get_X509_PUBKEY),        \
    TEST_DECL_GROUP("ossl_x509_pk", test_wolfSSL_X509_PUBKEY_RSA),             \
    TEST_DECL_GROUP("ossl_x509_pk", test_wolfSSL_X509_PUBKEY_EC),              \
    TEST_DECL_GROUP("ossl_x509_pk", test_wolfSSL_X509_PUBKEY_DSA),             \
    TEST_DECL_GROUP("ossl_x509_pk", test_wolfSSL_X509_PUBKEY_get),             \
    TEST_DECL_GROUP("ossl_x509_pk", test_wolfSSL_X509_set_pubkey)

#endif /* WOLFCRYPT_TEST_OSSL_X509_PK_H */
