/* test_evp_cipher.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_EVP_CIPHER_H
#define WOLFCRYPT_TEST_EVP_CIPHER_H

#include <tests/api/api_decl.h>

int test_wolfSSL_EVP_CIPHER_CTX(void);
int test_wolfSSL_EVP_CIPHER_CTX_iv_length(void);
int test_wolfSSL_EVP_CIPHER_CTX_key_length(void);
int test_wolfSSL_EVP_CIPHER_CTX_set_iv(void);
int test_wolfSSL_EVP_get_cipherbynid(void);
int test_wolfSSL_EVP_CIPHER_block_size(void);
int test_wolfSSL_EVP_CIPHER_iv_length(void);
int test_wolfSSL_EVP_CipherUpdate_Null(void);
int test_wolfSSL_EVP_CIPHER_type_string(void);
int test_wolfSSL_EVP_BytesToKey(void);
int test_wolfSSL_EVP_Cipher_extra(void);
int test_wolfSSL_EVP_X_STATE(void);
int test_wolfSSL_EVP_X_STATE_LEN(void);
int test_wolfSSL_EVP_aes_256_gcm(void);
int test_wolfSSL_EVP_aes_192_gcm(void);
int test_wolfSSL_EVP_aes_128_gcm(void);
int test_evp_cipher_aes_gcm(void);
int test_wolfssl_EVP_aes_gcm(void);
int test_wolfssl_EVP_aes_gcm_AAD_2_parts(void);
int test_wolfssl_EVP_aes_gcm_zeroLen(void);
int test_wolfSSL_EVP_aes_256_ccm(void);
int test_wolfSSL_EVP_aes_192_ccm(void);
int test_wolfSSL_EVP_aes_128_ccm(void);
int test_wolfssl_EVP_aes_ccm(void);
int test_wolfssl_EVP_aes_ccm_zeroLen(void);
int test_wolfssl_EVP_chacha20(void);
int test_wolfssl_EVP_chacha20_poly1305(void);
int test_wolfssl_EVP_aria_gcm(void);
int test_wolfssl_EVP_sm4_ecb(void);
int test_wolfssl_EVP_sm4_cbc(void);
int test_wolfssl_EVP_sm4_ctr(void);
int test_wolfssl_EVP_sm4_gcm_zeroLen(void);
int test_wolfssl_EVP_sm4_gcm(void);
int test_wolfssl_EVP_sm4_ccm_zeroLen(void);
int test_wolfssl_EVP_sm4_ccm(void);
int test_wolfSSL_EVP_rc4(void);
int test_wolfSSL_EVP_enc_null(void);
int test_wolfSSL_EVP_rc2_cbc(void);
int test_wolfSSL_EVP_mdc2(void);
int test_evp_cipher_pkcs7_pad_zero(void);
int test_evp_cipher_aead_aad_overflow(void);

#define TEST_EVP_CIPHER_DECLS                                               \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_CIPHER_CTX),             \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_CIPHER_CTX_iv_length),   \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_CIPHER_CTX_key_length),  \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_CIPHER_CTX_set_iv),      \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_get_cipherbynid),        \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_CIPHER_block_size),      \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_CIPHER_iv_length),       \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_CipherUpdate_Null),      \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_CIPHER_type_string),     \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_BytesToKey),             \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_Cipher_extra),           \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_X_STATE),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_X_STATE_LEN),            \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_aes_256_gcm),            \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_aes_192_gcm),            \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_aes_128_gcm),            \
    TEST_DECL_GROUP("evp_cipher", test_evp_cipher_aes_gcm),                 \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_aes_gcm),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_aes_gcm_AAD_2_parts),    \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_aes_gcm_zeroLen),        \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_aes_256_ccm),            \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_aes_192_ccm),            \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_aes_128_ccm),            \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_aes_ccm),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_aes_ccm_zeroLen),        \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_chacha20),               \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_chacha20_poly1305),      \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_aria_gcm),               \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_sm4_ecb),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_sm4_cbc),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_sm4_ctr),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_sm4_gcm_zeroLen),        \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_sm4_gcm),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_sm4_ccm_zeroLen),        \
    TEST_DECL_GROUP("evp_cipher", test_wolfssl_EVP_sm4_ccm),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_rc4),                    \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_enc_null),               \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_rc2_cbc),                \
    TEST_DECL_GROUP("evp_cipher", test_wolfSSL_EVP_mdc2),                  \
    TEST_DECL_GROUP("evp_cipher", test_evp_cipher_pkcs7_pad_zero),           \
    TEST_DECL_GROUP("evp_cipher", test_evp_cipher_aead_aad_overflow)

#endif /* WOLFCRYPT_TEST_EVP_CIPHER_H */
