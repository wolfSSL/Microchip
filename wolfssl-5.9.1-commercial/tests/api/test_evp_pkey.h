/* test_evp_pkey.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_EVP_PKEY_H
#define WOLFCRYPT_TEST_EVP_PKEY_H

#include <tests/api/api_decl.h>

int test_wolfSSL_EVP_PKEY_CTX_new_id(void);
int test_wolfSSL_EVP_PKEY_CTX_set_rsa_keygen_bits(void);
int test_wolfSSL_QT_EVP_PKEY_CTX_free(void);
int test_wolfSSL_EVP_PKEY_up_ref(void);
int test_wolfSSL_EVP_PKEY_base_id(void);
int test_wolfSSL_EVP_PKEY_id(void);
int test_wolfSSL_EVP_MD_pkey_type(void);
int test_wolfSSL_EVP_MD_hmac_signing(void);
int test_wolfSSL_EVP_PKEY_new_mac_key(void);
int test_wolfSSL_EVP_PKEY_hkdf(void);
int test_wolfSSL_EVP_PBE_scrypt(void);
int test_EVP_PKEY_cmp(void);
int test_wolfSSL_EVP_PKEY_set1_get1_DSA(void);
int test_wolfSSL_EVP_PKEY_set1_get1_EC_KEY (void);
int test_wolfSSL_EVP_PKEY_get0_EC_KEY(void);
int test_wolfSSL_EVP_PKEY_set1_get1_DH (void);
int test_wolfSSL_EVP_PKEY_assign(void);
int test_wolfSSL_EVP_PKEY_assign_DH(void);
int test_EVP_PKEY_rsa(void);
int test_EVP_PKEY_ec(void);
int test_wolfSSL_EVP_PKEY_missing_parameters(void);
int test_wolfSSL_EVP_PKEY_copy_parameters(void);
int test_wolfSSL_EVP_PKEY_paramgen(void);
int test_wolfSSL_EVP_PKEY_param_check(void);
int test_wolfSSL_EVP_PKEY_keygen_init(void);
int test_wolfSSL_EVP_PKEY_keygen(void);
int test_wolfSSL_EVP_SignInit_ex(void);
int test_wolfSSL_EVP_PKEY_sign_verify_rsa(void);
int test_wolfSSL_EVP_PKEY_sign_verify_dsa(void);
int test_wolfSSL_EVP_PKEY_sign_verify_ec(void);
int test_wolfSSL_EVP_MD_rsa_signing(void);
int test_wc_RsaPSS_DigitalSignVerify(void);
int test_wolfSSL_EVP_MD_ecc_signing(void);
int test_wolfSSL_EVP_PKEY_encrypt(void);
int test_wolfSSL_EVP_PKEY_derive(void);
int test_wolfSSL_EVP_PKEY_print_public(void);

#define TEST_EVP_PKEY_DECLS                                                    \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_CTX_new_id),             \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_CTX_set_rsa_keygen_bits),\
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_QT_EVP_PKEY_CTX_free),            \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_up_ref),                 \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_base_id),                \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_id),                     \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_MD_pkey_type),                \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_MD_hmac_signing),             \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_new_mac_key),            \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_hkdf),                   \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PBE_scrypt),                  \
    TEST_DECL_GROUP("evp_pkey", test_EVP_PKEY_cmp),                            \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_set1_get1_DSA),          \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_set1_get1_EC_KEY),       \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_get0_EC_KEY),            \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_set1_get1_DH),           \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_assign),                 \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_assign_DH),              \
    TEST_DECL_GROUP("evp_pkey", test_EVP_PKEY_rsa),                            \
    TEST_DECL_GROUP("evp_pkey", test_EVP_PKEY_ec),                             \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_missing_parameters),     \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_copy_parameters),        \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_paramgen),               \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_param_check),            \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_keygen_init),            \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_keygen),                 \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_SignInit_ex),                 \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_sign_verify_rsa),        \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_sign_verify_dsa),        \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_sign_verify_ec),         \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_MD_rsa_signing),              \
    TEST_DECL_GROUP("evp_pkey", test_wc_RsaPSS_DigitalSignVerify),             \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_MD_ecc_signing),              \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_encrypt),                \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_derive),                 \
    TEST_DECL_GROUP("evp_pkey", test_wolfSSL_EVP_PKEY_print_public)

#endif /* WOLFCRYPT_TEST_EVP_PKEY_H */
