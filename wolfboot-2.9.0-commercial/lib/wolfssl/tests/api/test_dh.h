/* test_dh.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_DH_H
#define WOLFCRYPT_TEST_DH_H

#include <tests/api/api_decl.h>

int test_wc_DhPublicKeyDecode(void);
int test_wc_DhAgree_subgroup_check(void);

#define TEST_DH_DECLS                                     \
    TEST_DECL_GROUP("dh", test_wc_DhPublicKeyDecode),     \
    TEST_DECL_GROUP("dh", test_wc_DhAgree_subgroup_check)

#endif /* WOLFCRYPT_TEST_DH_H */
