/* test_slhdsa.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_SLHDSA_H
#define WOLFCRYPT_TEST_SLHDSA_H

#include <tests/api/api_decl.h>

int test_wc_slhdsa(void);
int test_wc_slhdsa_sizes(void);
int test_wc_slhdsa_make_key(void);
int test_wc_slhdsa_sign(void);
int test_wc_slhdsa_verify(void);
int test_wc_slhdsa_sign_vfy(void);
int test_wc_slhdsa_sign_hash(void);
int test_wc_slhdsa_export_import(void);
int test_wc_slhdsa_check_key(void);

#define TEST_SLHDSA_DECLS                                                      \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa),                                 \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa_sizes),                           \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa_make_key),                        \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa_sign),                            \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa_verify),                          \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa_sign_vfy),                        \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa_sign_hash),                       \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa_export_import),                   \
    TEST_DECL_GROUP("slhdsa", test_wc_slhdsa_check_key)

#endif /* WOLFCRYPT_TEST_SLHDSA_H */
