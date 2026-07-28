/* test_certman.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_CERTMAN_H
#define WOLFCRYPT_TEST_CERTMAN_H

#include <tests/api/api_decl.h>

int test_wolfSSL_CertManagerAPI(void);
int test_wolfSSL_CertManagerLoadCABuffer(void);
int test_wolfSSL_CertManagerLoadCABuffer_ex(void);
int test_wolfSSL_CertManagerLoadCABufferType(void);
int test_wolfSSL_CertManagerGetCerts(void);
int test_wolfSSL_CertManagerSetVerify(void);
int test_wolfSSL_CertManagerNameConstraint(void);
int test_wolfSSL_CertManagerNameConstraint2(void);
int test_wolfSSL_CertManagerNameConstraint3(void);
int test_wolfSSL_CertManagerNameConstraint4(void);
int test_wolfSSL_CertManagerNameConstraint5(void);
int test_wolfSSL_CertManagerNameConstraint_DNS_CN(void);
int test_wolfSSL_CertManagerNameConstraint_IP_SAN(void);
int test_wolfSSL_CertManagerNameConstraint_RID_SAN(void);
int test_wolfSSL_X509_get_ext_d2i_RID_SAN(void);
int test_wolfSSL_X509_check_host_IP_only_SAN_CN_fallback(void);
int test_wolfSSL_X509_check_host_URI_SAN_not_DNS_match(void);
int test_wolfSSL_CertManagerCRL(void);
int test_wolfSSL_CRL_reason_extensions_cleanup(void);
int test_wolfSSL_CRL_static_revoked_list(void);
int test_wolfSSL_CRL_duplicate_extensions(void);
int test_wolfSSL_CRL_critical_idp(void);
int test_wolfSSL_CRL_unknown_critical_ext(void);
int test_wolfSSL_CRL_unknown_critical_entry_ext(void);
int test_wolfSSL_CertManagerCheckOCSPResponse(void);
int test_various_pathlen_chains(void);
int test_wolfSSL_CertManagerRejectMD5Cert(void);
int test_wolfSSL_X509_V_ERR_strings(void);

#define TEST_CERTMAN_DECLS                                                  \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerAPI),                \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerLoadCABuffer),       \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerLoadCABuffer_ex),    \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerLoadCABufferType),   \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerGetCerts),           \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerSetVerify),          \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerNameConstraint),     \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerNameConstraint2),    \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerNameConstraint3),    \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerNameConstraint4),    \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerNameConstraint5),    \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerNameConstraint_DNS_CN), \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerNameConstraint_IP_SAN), \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerNameConstraint_RID_SAN), \
    TEST_DECL_GROUP("certman", test_wolfSSL_X509_get_ext_d2i_RID_SAN),       \
    TEST_DECL_GROUP("certman",                                              \
        test_wolfSSL_X509_check_host_IP_only_SAN_CN_fallback),              \
    TEST_DECL_GROUP("certman",                                              \
        test_wolfSSL_X509_check_host_URI_SAN_not_DNS_match),                \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerCRL),                \
    TEST_DECL_GROUP("certman", test_wolfSSL_CRL_reason_extensions_cleanup), \
    TEST_DECL_GROUP("certman", test_wolfSSL_CRL_static_revoked_list),      \
    TEST_DECL_GROUP("certman", test_wolfSSL_CRL_duplicate_extensions),      \
    TEST_DECL_GROUP("certman", test_wolfSSL_CRL_critical_idp),             \
    TEST_DECL_GROUP("certman", test_wolfSSL_CRL_unknown_critical_ext),     \
    TEST_DECL_GROUP("certman", test_wolfSSL_CRL_unknown_critical_entry_ext), \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerCheckOCSPResponse),  \
    TEST_DECL_GROUP("certman", test_various_pathlen_chains),                \
    TEST_DECL_GROUP("certman", test_wolfSSL_CertManagerRejectMD5Cert),      \
    TEST_DECL_GROUP("certman", test_wolfSSL_X509_V_ERR_strings)

#endif /* WOLFCRYPT_TEST_CERTMAN_H */

