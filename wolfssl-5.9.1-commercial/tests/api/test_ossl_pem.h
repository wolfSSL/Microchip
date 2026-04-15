/* test_ossl_pem.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_SSL_PEM_H
#define WOLFCRYPT_TEST_SSL_PEM_H

#include <tests/api/api_decl.h>

int test_wolfSSL_PEM_def_callback(void);
int test_wolfSSL_PEM_read_PrivateKey(void);
int test_wolfSSL_PEM_read_PUBKEY(void);
int test_wolfSSL_PEM_PrivateKey_rsa(void);
int test_wolfSSL_PEM_PrivateKey_ecc(void);
int test_wolfSSL_PEM_PrivateKey_dsa(void);
int test_wolfSSL_PEM_PrivateKey_dh(void);
int test_wolfSSL_PEM_PrivateKey(void);
int test_wolfSSL_PEM_file_RSAKey(void);
int test_wolfSSL_PEM_file_RSAPrivateKey(void);
int test_wolfSSL_PEM_read_RSA_PUBKEY(void);
int test_wolfSSL_PEM_read_bio(void);
int test_wolfSSL_PEM_bio_RSAKey(void);
int test_wolfSSL_PEM_bio_RSAPrivateKey(void);
int test_wolfSSL_PEM_bio_DSAKey(void);
int test_wolfSSL_PEM_bio_ECKey(void);
int test_wolfSSL_PEM_PUBKEY(void);


#define TEST_SSL_PEM_DECLS                                              \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_def_callback),         \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_read_PrivateKey),      \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_read_PUBKEY),          \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_PrivateKey_rsa),       \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_PrivateKey_ecc),       \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_PrivateKey_dsa),       \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_PrivateKey_dh),        \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_PrivateKey),           \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_file_RSAKey),          \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_file_RSAPrivateKey),   \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_read_RSA_PUBKEY),      \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_read_bio),             \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_bio_RSAKey),           \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_bio_RSAPrivateKey),    \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_bio_DSAKey),           \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_bio_ECKey),            \
    TEST_DECL_GROUP("ossl_pem", test_wolfSSL_PEM_PUBKEY)

#endif /* WOLFCRYPT_TEST_SSL_PEM_H */
