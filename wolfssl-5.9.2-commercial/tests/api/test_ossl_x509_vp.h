/* test_ossl_x509_vp.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_VP_H
#define WOLFCRYPT_TEST_OSSL_X509_VP_H

#include <tests/api/api_decl.h>

int test_wolfSSL_X509_VERIFY_PARAM(void);
int test_wolfSSL_X509_VERIFY_PARAM_set1_ip(void);
int test_wolfSSL_X509_VERIFY_PARAM_set1_host(void);

#define TEST_OSSL_X509_VFY_PARAMS_DECLS                                        \
    TEST_DECL_GROUP("ossl_x509_vp", test_wolfSSL_X509_VERIFY_PARAM),           \
    TEST_DECL_GROUP("ossl_x509_vp", test_wolfSSL_X509_VERIFY_PARAM_set1_ip),   \
    TEST_DECL_GROUP("ossl_x509_vp", test_wolfSSL_X509_VERIFY_PARAM_set1_host)

#endif /* WOLFCRYPT_TEST_OSSL_X509_VP_H */
