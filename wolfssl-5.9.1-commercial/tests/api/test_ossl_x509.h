/* test_ossl_x509.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_OSSL_X509_H
#define WOLFCRYPT_TEST_OSSL_X509_H

#include <tests/api/api_decl.h>

int test_x509_get_key_id(void);
int test_wolfSSL_X509_get_version(void);
int test_wolfSSL_X509_cmp_time(void);
int test_wolfSSL_X509_time_adj(void);
int test_wolfSSL_X509_NID(void);
int test_wolfSSL_i2d_X509_NAME_canon(void);
int test_wolfSSL_X509_subject_name_hash(void);
int test_wolfSSL_X509_issuer_name_hash(void);
int test_wolfSSL_X509_check_host(void);
int test_wolfSSL_X509_check_email(void);
int test_wolfSSL_X509(void);
int test_wolfSSL_X509_get0_tbs_sigalg(void);
int test_wolfSSL_X509_set_name(void);
int test_wolfSSL_X509_set_notAfterBefore(void);
int test_wolfSSL_X509_set_version(void);
int test_wolfSSL_X509_get_serialNumber(void);
int test_wolfSSL_get_tbs(void);
int test_wolfSSL_X509_ext_get_critical_by_NID(void);
int test_wolfSSL_X509_CRL_distribution_points(void);
int test_wolfSSL_X509_check_ip_asc(void);
int test_wolfSSL_X509_bad_altname(void);
int test_wolfSSL_X509_name_match1(void);
int test_wolfSSL_X509_name_match2(void);
int test_wolfSSL_X509_name_match3(void);
int test_wolfSSL_X509_max_altnames(void);
int test_wolfSSL_X509_max_name_constraints(void);
int test_wolfSSL_X509_check_ca(void);
int test_X509_get_signature_nid(void);
int test_wolfSSL_X509_cmp(void);

#define TEST_OSSL_X509_DECLS                                                   \
    TEST_DECL_GROUP("ossl_x509", test_x509_get_key_id),                        \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_get_version),               \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_cmp_time),                  \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_time_adj),                  \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_NID),                       \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_i2d_X509_NAME_canon),            \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_subject_name_hash),         \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_issuer_name_hash),          \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_check_host),                \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_check_email),               \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509),                           \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_get0_tbs_sigalg),           \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_set_name),                  \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_set_notAfterBefore),        \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_set_version),               \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_get_serialNumber),          \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_get_tbs),                        \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_ext_get_critical_by_NID),   \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_CRL_distribution_points),   \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_check_ip_asc),              \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_bad_altname),               \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_name_match1),               \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_name_match2),               \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_name_match3),               \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_max_altnames),              \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_max_name_constraints),      \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_check_ca),                  \
    TEST_DECL_GROUP("ossl_x509", test_X509_get_signature_nid),                 \
    TEST_DECL_GROUP("ossl_x509", test_wolfSSL_X509_cmp)

#endif /* WOLFCRYPT_TEST_OSSL_X509_H */
