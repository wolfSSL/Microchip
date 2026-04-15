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
int test_GetSetShortInt(void);
int test_wc_IndexSequenceOf(void);
int test_wolfssl_local_MatchBaseName(void);
int test_wc_DecodeRsaPssParams(void);
int test_DecodeAltNames_length_underflow(void);
int test_wc_DecodeObjectId(void);

#define TEST_ASN_DECLS                                              \
    TEST_DECL_GROUP("asn", test_SetAsymKeyDer),                     \
    TEST_DECL_GROUP("asn", test_GetSetShortInt),                    \
    TEST_DECL_GROUP("asn", test_wc_IndexSequenceOf),                \
    TEST_DECL_GROUP("asn", test_wolfssl_local_MatchBaseName),       \
    TEST_DECL_GROUP("asn", test_wc_DecodeRsaPssParams),             \
    TEST_DECL_GROUP("asn", test_DecodeAltNames_length_underflow),    \
    TEST_DECL_GROUP("asn", test_wc_DecodeObjectId)

#endif /* WOLFCRYPT_TEST_ASN_H */
