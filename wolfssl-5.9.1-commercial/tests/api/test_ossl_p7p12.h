/* test_ossl_p7p12.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_P7P12_H
#define WOLFCRYPT_TEST_OSSL_P7P12_H

#include <tests/api/api_decl.h>

int test_wolfssl_PKCS7(void);
int test_wolfSSL_PKCS7_certs(void);
int test_wolfSSL_PKCS7_sign(void);
int test_wolfSSL_PKCS7_SIGNED_new(void);
int test_wolfSSL_PEM_write_bio_PKCS7(void);
int test_wolfSSL_PEM_write_bio_encryptedKey(void);
int test_wolfSSL_SMIME_read_PKCS7(void);
int test_wolfSSL_SMIME_write_PKCS7(void);
int test_wolfSSL_PKCS12(void);

#define TEST_OSSL_PKCS7_DECLS                                               \
    TEST_DECL_GROUP("ossl_p7", test_wolfssl_PKCS7),                         \
    TEST_DECL_GROUP("ossl_p7", test_wolfSSL_PKCS7_certs),                   \
    TEST_DECL_GROUP("ossl_p7", test_wolfSSL_PKCS7_sign),                    \
    TEST_DECL_GROUP("ossl_p7", test_wolfSSL_PKCS7_SIGNED_new),              \
    TEST_DECL_GROUP("ossl_p7", test_wolfSSL_PEM_write_bio_PKCS7),           \
    TEST_DECL_GROUP("ossl_p7", test_wolfSSL_PEM_write_bio_encryptedKey),    \
    TEST_DECL_GROUP("ossl_p7", test_wolfSSL_RAND_poll)

#define TEST_OSSL_SMIME_DECLS                                        \
    TEST_DECL_GROUP("ossl_smime", test_wolfSSL_SMIME_read_PKCS7),    \
    TEST_DECL_GROUP("ossl_smime", test_wolfSSL_SMIME_write_PKCS7)

#define TEST_OSSL_PKCS12_DECLS                          \
    TEST_DECL_GROUP("ossl_p12", test_wolfSSL_PKCS12)

#endif /* WOLFCRYPT_TEST_OSSL_P7P12_H */

