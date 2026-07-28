/* test_asn.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_ASN_H
#define WOLFCRYPT_TEST_ASN_H

#include <tests/api/api_decl.h>

int test_SetAsymKeyDer(void);
int test_DecodeAsymKey_lenient_versions(void);
int test_DecodeAsymKey_negative(void);
int test_GetSetShortInt(void);
int test_wc_IndexSequenceOf(void);
int test_wolfssl_local_MatchBaseName(void);
int test_wolfssl_local_MatchDnsConstraintWildcard(void);
int test_wolfssl_local_MatchUriNameConstraint(void);
int test_wc_DecodeRsaPssParams(void);
int test_SerialNumber0_RootCA(void);
int test_DecodeAltNames_length_underflow(void);
int test_DecodeCertExtensions_dup_certpol(void);
int test_ParseCert_SM3wSM2_short_pubkey(void);
int test_wc_DecodeObjectId(void);
int test_ToTraditional_ex_handcrafted(void);
int test_ToTraditional_ex_roundtrip(void);
int test_ToTraditional_ex_negative(void);
int test_ToTraditional_ex_mldsa_bad_params(void);

#define TEST_ASN_DECLS                                              \
    TEST_DECL_GROUP("asn", test_SetAsymKeyDer),                     \
    TEST_DECL_GROUP("asn", test_DecodeAsymKey_lenient_versions),    \
    TEST_DECL_GROUP("asn", test_DecodeAsymKey_negative),            \
    TEST_DECL_GROUP("asn", test_GetSetShortInt),                    \
    TEST_DECL_GROUP("asn", test_wc_IndexSequenceOf),                \
    TEST_DECL_GROUP("asn", test_wolfssl_local_MatchBaseName),       \
    TEST_DECL_GROUP("asn", test_wolfssl_local_MatchDnsConstraintWildcard), \
    TEST_DECL_GROUP("asn", test_wolfssl_local_MatchUriNameConstraint), \
    TEST_DECL_GROUP("asn", test_wc_DecodeRsaPssParams),             \
    TEST_DECL_GROUP("asn", test_SerialNumber0_RootCA),              \
    TEST_DECL_GROUP("asn", test_DecodeAltNames_length_underflow),   \
    TEST_DECL_GROUP("asn", test_DecodeCertExtensions_dup_certpol),  \
    TEST_DECL_GROUP("asn", test_ParseCert_SM3wSM2_short_pubkey),    \
    TEST_DECL_GROUP("asn", test_wc_DecodeObjectId),                 \
    TEST_DECL_GROUP("asn", test_ToTraditional_ex_handcrafted),      \
    TEST_DECL_GROUP("asn", test_ToTraditional_ex_roundtrip),        \
    TEST_DECL_GROUP("asn", test_ToTraditional_ex_negative),         \
    TEST_DECL_GROUP("asn", test_ToTraditional_ex_mldsa_bad_params)

#endif /* WOLFCRYPT_TEST_ASN_H */
