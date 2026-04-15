/* test_ossl_x509_io.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_IO_H
#define WOLFCRYPT_TEST_OSSL_X509_IO_H

#include <tests/api/api_decl.h>

int test_wolfSSL_i2d_X509(void);
int test_wolfSSL_PEM_read_X509(void);
int test_wolfSSL_PEM_write_bio_X509(void);

#define TEST_OSSL_X509_IO_DECLS                                         \
    TEST_DECL_GROUP("ossl_x509_io", test_wolfSSL_i2d_X509),             \
    TEST_DECL_GROUP("ossl_x509_io", test_wolfSSL_PEM_read_X509),        \
    TEST_DECL_GROUP("ossl_x509_io", test_wolfSSL_PEM_write_bio_X509)

#endif /* WOLFCRYPT_TEST_OSSL_X509_IO_H */
