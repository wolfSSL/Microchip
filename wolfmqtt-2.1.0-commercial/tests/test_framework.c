/* test_framework.c
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Pass-path smoke tests for every assertion macro defined by unit_test.h.
 * The fail paths call return after setting ut_current_test_failed, so they
 * cannot be exercised without the framework reporting the test as failed.
 * These tests ensure each macro at least compiles and evaluates its
 * non-failing branch correctly. */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "tests/unit_test.h"

void run_framework_tests(void);

TEST(assert_true_pass)
{
    ASSERT_TRUE(1);
    ASSERT_TRUE(1 == 1);
}

TEST(assert_false_pass)
{
    ASSERT_FALSE(0);
    ASSERT_FALSE(1 == 2);
}

TEST(assert_eq_pass)
{
    ASSERT_EQ(0, 0);
    ASSERT_EQ(42, 42);
}

TEST(assert_ne_pass)
{
    ASSERT_NE(0, 1);
    ASSERT_NE(42, -1);
}

TEST(assert_null_pass)
{
    void* p = NULL;
    ASSERT_NULL(p);
}

TEST(assert_not_null_pass)
{
    int x;
    ASSERT_NOT_NULL(&x);
}

TEST(assert_str_eq_pass)
{
    ASSERT_STR_EQ("hello", "hello");
}

TEST(assert_mem_eq_pass)
{
    const unsigned char a[] = {0x01, 0x02, 0x03, 0x04};
    const unsigned char b[] = {0x01, 0x02, 0x03, 0x04};
    ASSERT_MEM_EQ(a, b, sizeof(a));
}

/* FAIL has no pass path; guard with a never-true condition so the macro
 * body is compiled but never executed. */
TEST(fail_compiles)
{
    if (0) {
        FAIL("unreachable");
    }
    ASSERT_TRUE(1);
}

void run_framework_tests(void)
{
    TEST_SUITE_BEGIN("framework", NULL, NULL);

    RUN_TEST(assert_true_pass);
    RUN_TEST(assert_false_pass);
    RUN_TEST(assert_eq_pass);
    RUN_TEST(assert_ne_pass);
    RUN_TEST(assert_null_pass);
    RUN_TEST(assert_not_null_pass);
    RUN_TEST(assert_str_eq_pass);
    RUN_TEST(assert_mem_eq_pass);
    RUN_TEST(fail_compiles);

    TEST_SUITE_END();
}
