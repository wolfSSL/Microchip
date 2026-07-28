/* test_chacha20_poly1305.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_CHACHA20_POLY1305_H
#define WOLFCRYPT_TEST_CHACHA20_POLY1305_H

#include <tests/api/api_decl.h>

int test_wc_ChaCha20Poly1305_aead(void);
int test_wc_XChaCha20Poly1305_aead(void);
int test_wc_XChaCha20Poly1305_BadAuthTag(void);
int test_wc_ChaCha20Poly1305_MonteCarlo(void);
int test_wc_ChaCha20Poly1305_Stream(void);
int test_wc_ChaCha20Poly1305_AeadEdgeCases(void);
int test_wc_ChaCha20Poly1305_MidStreamState(void);
int test_wc_ChaCha20Poly1305_ReinitAfterFinal(void);
int test_wc_ChaCha20Poly1305_InPlace(void);
int test_wc_ChaCha20Poly1305_UnalignedBuffers(void);
int test_wc_ChaCha20Poly1305_CrossCipher(void);

#define TEST_CHACHA20_POLY1305_DECLS                                                        \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_aead),                   \
    TEST_DECL_GROUP("xchacha20-poly1305", test_wc_XChaCha20Poly1305_aead),                 \
    TEST_DECL_GROUP("xchacha20-poly1305", test_wc_XChaCha20Poly1305_BadAuthTag),           \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_MonteCarlo),             \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_Stream),                 \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_AeadEdgeCases),          \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_MidStreamState),         \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_ReinitAfterFinal),       \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_InPlace),               \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_UnalignedBuffers),      \
    TEST_DECL_GROUP("chacha20-poly1305", test_wc_ChaCha20Poly1305_CrossCipher)

#endif /* WOLFCRYPT_TEST_CHACHA20_POLY1305_H */
