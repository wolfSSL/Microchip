/* test_ossl_x509_crypto.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_CRYPTO_H
#define WOLFCRYPT_TEST_OSSL_X509_CRYPTO_H

#include <tests/api/api_decl.h>

int test_wolfSSL_X509_check_private_key(void);
int test_wolfSSL_X509_verify(void);
int test_wolfSSL_X509_sign(void);
int test_wolfSSL_X509_sign2(void);
int test_wolfSSL_make_cert(void);

#define TEST_OSSL_X509_CRYPTO_DECLS                                            \
    TEST_DECL_GROUP("ossl_x509_crypto", test_wolfSSL_X509_check_private_key),  \
    TEST_DECL_GROUP("ossl_x509_crypto", test_wolfSSL_X509_verify),             \
    TEST_DECL_GROUP("ossl_x509_crypto", test_wolfSSL_X509_sign),               \
    TEST_DECL_GROUP("ossl_x509_crypto", test_wolfSSL_X509_sign2),              \
    TEST_DECL_GROUP("ossl_x509_crypto", test_wolfSSL_make_cert)

#endif /* WOLFCRYPT_TEST_OSSL_X509_CRYPTO_H */
