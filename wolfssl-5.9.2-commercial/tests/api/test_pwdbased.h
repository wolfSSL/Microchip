/* test_pwdbased.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_PWDBASED_H
#define WOLFCRYPT_TEST_PWDBASED_H

#include <tests/api/api_decl.h>

int test_wc_PBKDF1_ex_iterations(void);
int test_wc_PBKDF2_ex_iterations(void);

#define TEST_PWDBASED_DECLS                                                 \
    TEST_DECL_GROUP("pwdbased", test_wc_PBKDF1_ex_iterations),             \
    TEST_DECL_GROUP("pwdbased", test_wc_PBKDF2_ex_iterations)

#endif /* WOLFCRYPT_TEST_PWDBASED_H */
