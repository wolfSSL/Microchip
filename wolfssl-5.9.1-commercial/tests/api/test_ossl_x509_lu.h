/* test_ossl_x509_lu.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_LU_H
#define WOLFCRYPT_TEST_OSSL_X509_LU_H

#include <tests/api/api_decl.h>

int test_wolfSSL_X509_LOOKUP_load_file(void);
int test_wolfSSL_X509_LOOKUP_ctrl_file(void);
int test_wolfSSL_X509_LOOKUP_ctrl_hash_dir(void);
int test_wolfSSL_X509_load_crl_file(void);
int test_X509_LOOKUP_add_dir(void);

#define TEST_OSSL_X509_LOOKUP_DECLS                                            \
    TEST_DECL_GROUP("ossl_x509_lu", test_wolfSSL_X509_LOOKUP_load_file),       \
    TEST_DECL_GROUP("ossl_x509_lu", test_wolfSSL_X509_LOOKUP_ctrl_file),       \
    TEST_DECL_GROUP("ossl_x509_lu", test_wolfSSL_X509_LOOKUP_ctrl_hash_dir),   \
    TEST_DECL_GROUP("ossl_x509_lu", test_wolfSSL_X509_LOOKUP_ctrl_hash_dir),   \
    TEST_DECL_GROUP("ossl_x509_lu", test_X509_LOOKUP_add_dir)

#endif /* WOLFCRYPT_TEST_OSSL_X509_LU_H */
