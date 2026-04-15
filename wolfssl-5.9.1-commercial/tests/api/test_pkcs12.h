/* test_pkcs12.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_PKCS12_H
#define WOLFCRYPT_TEST_PKCS12_H

#include <tests/api/api_decl.h>

int test_wc_i2d_PKCS12(void);
int test_wc_PKCS12_create(void);
int test_wc_d2i_PKCS12_bad_mac_salt(void);
int test_wc_d2i_PKCS12_oid_underflow(void);
int test_wc_PKCS12_PBKDF(void);
int test_wc_PKCS12_PBKDF_ex(void);
int test_wc_PKCS12_PBKDF_ex_sha1(void);
int test_wc_PKCS12_PBKDF_ex_sha512(void);
int test_wc_PKCS12_PBKDF_ex_sha224(void);
int test_wc_PKCS12_PBKDF_ex_sha384(void);
int test_wc_PKCS12_PBKDF_ex_sha512_224(void);
int test_wc_PKCS12_PBKDF_ex_sha512_256(void);

#define TEST_PKCS12_DECLS                                               \
    TEST_DECL_GROUP("pkcs12", test_wc_i2d_PKCS12),                     \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_create),                  \
    TEST_DECL_GROUP("pkcs12", test_wc_d2i_PKCS12_bad_mac_salt),        \
    TEST_DECL_GROUP("pkcs12", test_wc_d2i_PKCS12_oid_underflow),       \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_PBKDF),                   \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_PBKDF_ex),                \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_PBKDF_ex_sha1),           \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_PBKDF_ex_sha512),         \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_PBKDF_ex_sha224),         \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_PBKDF_ex_sha384),         \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_PBKDF_ex_sha512_224),     \
    TEST_DECL_GROUP("pkcs12", test_wc_PKCS12_PBKDF_ex_sha512_256)

#endif /* WOLFCRYPT_TEST_PKCS12_H */
