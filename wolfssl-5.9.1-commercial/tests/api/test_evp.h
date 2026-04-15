/* test_evp.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFSSL_TEST_EVP_H
#define WOLFSSL_TEST_EVP_H

#include <tests/api/api_decl.h>

int test_wolfSSL_EVP_ENCODE_CTX_new(void);
int test_wolfSSL_EVP_ENCODE_CTX_free(void);
int test_wolfSSL_EVP_EncodeInit(void);
int test_wolfSSL_EVP_EncodeUpdate(void);
int test_wolfSSL_EVP_EncodeFinal(void);
int test_wolfSSL_EVP_DecodeInit(void);
int test_wolfSSL_EVP_DecodeUpdate(void);
int test_wolfSSL_EVP_DecodeFinal(void);

#define TEST_EVP_ENC_DECLS                                          \
    TEST_DECL_GROUP("evp_enc", test_wolfSSL_EVP_ENCODE_CTX_new),    \
    TEST_DECL_GROUP("evp_enc", test_wolfSSL_EVP_ENCODE_CTX_free),   \
    TEST_DECL_GROUP("evp_enc", test_wolfSSL_EVP_EncodeInit),        \
    TEST_DECL_GROUP("evp_enc", test_wolfSSL_EVP_EncodeUpdate),      \
    TEST_DECL_GROUP("evp_enc", test_wolfSSL_EVP_EncodeFinal),       \
    TEST_DECL_GROUP("evp_enc", test_wolfSSL_EVP_DecodeInit),        \
    TEST_DECL_GROUP("evp_enc", test_wolfSSL_EVP_DecodeUpdate),      \
    TEST_DECL_GROUP("evp_enc", test_wolfSSL_EVP_DecodeFinal)

#endif /* WOLFSSL_TEST_EVP_H */
