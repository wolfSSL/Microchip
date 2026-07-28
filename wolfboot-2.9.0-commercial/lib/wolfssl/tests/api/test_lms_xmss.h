/* test_lms_xmss.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_LMS_XMSS_H
#define WOLFCRYPT_TEST_LMS_XMSS_H

#include <tests/api/api_decl.h>

int test_wc_LmsKey_sign_verify(void);
int test_wc_LmsKey_reload_cache(void);
int test_rfc9802_lms_x509_verify(void);
int test_rfc9802_xmss_x509_verify(void);
int test_rfc9802_lms_x509_gen(void);
int test_rfc9802_xmss_x509_gen(void);

/* LMS, and RFC 9802 (HSS/LMS and XMSS/XMSS^MT in X.509). */
#define TEST_LMS_XMSS_DECLS                                                  \
    TEST_DECL_GROUP("lms", test_wc_LmsKey_sign_verify),                 \
    TEST_DECL_GROUP("lms", test_wc_LmsKey_reload_cache),                \
    TEST_DECL_GROUP("lms", test_rfc9802_lms_x509_verify),               \
    TEST_DECL_GROUP("xmss", test_rfc9802_xmss_x509_verify),             \
    TEST_DECL_GROUP("lms", test_rfc9802_lms_x509_gen),                  \
    TEST_DECL_GROUP("xmss", test_rfc9802_xmss_x509_gen)

#endif /* WOLFCRYPT_TEST_LMS_XMSS_H */
