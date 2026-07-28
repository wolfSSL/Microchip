/* test_ssl_pk.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef TESTS_API_SSL_PK_H
#define TESTS_API_SSL_PK_H

int test_wolfSSL_CTX_SetMinEccKey_Sz(void);
int test_wolfSSL_SetMinEccKey_Sz(void);
int test_wolfSSL_CTX_SetMinRsaKey_Sz(void);
int test_wolfSSL_SetMinRsaKey_Sz(void);
int test_wolfSSL_SetEnableDhKeyTest(void);
int test_wolfSSL_CTX_SetMinDhKey_Sz(void);
int test_wolfSSL_SetMinDhKey_Sz(void);
int test_wolfSSL_CTX_SetMaxDhKey_Sz(void);
int test_wolfSSL_SetMaxDhKey_Sz(void);
int test_wolfSSL_GetDhKey_Sz(void);
int test_wolfSSL_get_privatekey(void);
int test_wolfSSL_get_signature_nid(void);
int test_wolfSSL_get_signature_type_nid(void);
int test_wolfSSL_get_peer_signature_nid(void);
int test_wolfSSL_get_peer_signature_type_nid(void);
int test_wolfSSL_SSL_CTX_set_tmp_ecdh(void);
int test_wolfSSL_CTX_set_dh_auto(void);

#define TEST_SSL_PK_DECLS                                                      \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_CTX_SetMinEccKey_Sz),           \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_SetMinEccKey_Sz),               \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_CTX_SetMinRsaKey_Sz),           \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_SetMinRsaKey_Sz),               \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_SetEnableDhKeyTest),            \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_CTX_SetMinDhKey_Sz),            \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_SetMinDhKey_Sz),                \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_CTX_SetMaxDhKey_Sz),            \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_SetMaxDhKey_Sz),                \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_GetDhKey_Sz),                   \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_get_privatekey),                \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_get_signature_nid),            \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_get_signature_type_nid),       \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_get_peer_signature_nid),       \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_get_peer_signature_type_nid),  \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_SSL_CTX_set_tmp_ecdh),         \
        TEST_DECL_GROUP("ssl_pk", test_wolfSSL_CTX_set_dh_auto)

#endif /* TESTS_API_SSL_PK_H */
