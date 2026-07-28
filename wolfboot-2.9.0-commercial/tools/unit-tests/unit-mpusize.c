/* unit-mpusize.c
 *
 * Unit tests for the Cortex-M MPU region-size lookup in src/boot_arm.c.
 *
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <check.h>
#include <stdint.h>
#include <stdio.h>

/* Compile only the host-portable MPU helpers from boot_arm.c. The rest of the
 * file is ARM reset/boot code built around inline assembly. */
#define WOLFBOOT_UNIT_TEST_MPU

/* Linker symbols referenced by mpu_init(); never dereferenced by the tests. */
unsigned int _start_text;
unsigned int _stored_data;
unsigned int _start_data;
unsigned int _end_data;
unsigned int _start_bss;
unsigned int _end_bss;
uint32_t *END_STACK;

#include "../../src/boot_arm.c"

/* The MPU SIZE field encodes region size as 2^(field+1); mpusize() rounds the
 * requested size up to the next supported power of two and shifts the field
 * left by one to land in the RASR layout. */
static uint32_t expected_rasr(uint32_t field)
{
    return field << 1;
}

START_TEST(test_mpusize_small_sizes)
{
    ck_assert_uint_eq(mpusize(1), MPUSIZE_8K);
    ck_assert_uint_eq(mpusize(8 * 1024), MPUSIZE_8K);
    ck_assert_uint_eq(mpusize(8 * 1024 + 1), MPUSIZE_16K);
    ck_assert_uint_eq(mpusize(32 * 1024), MPUSIZE_32K);
    ck_assert_uint_eq(mpusize(64 * 1024), MPUSIZE_64K);
}
END_TEST

/* Regression for F-5132: builds whose .text+.rodata exceed 64 KB (TrustZone,
 * PQC, delta-update, multi-algorithm) must still map to a valid MPU region size
 * rather than MPUSIZE_ERR, which would make mpu_init() bail before mpu_on() and
 * silently disable the MPU. */
START_TEST(test_mpusize_above_64k_is_not_err)
{
    ck_assert_uint_ne(mpusize(64 * 1024 + 1), MPUSIZE_ERR);
    ck_assert_uint_ne(mpusize(80 * 1024), MPUSIZE_ERR);
    ck_assert_uint_ne(mpusize(128 * 1024), MPUSIZE_ERR);
    ck_assert_uint_ne(mpusize(256 * 1024), MPUSIZE_ERR);
    ck_assert_uint_ne(mpusize(512 * 1024), MPUSIZE_ERR);
    ck_assert_uint_ne(mpusize(1024 * 1024), MPUSIZE_ERR);
}
END_TEST

START_TEST(test_mpusize_large_sizes_round_up)
{
    ck_assert_uint_eq(mpusize(64 * 1024 + 1), MPUSIZE_128K);
    ck_assert_uint_eq(mpusize(128 * 1024), MPUSIZE_128K);
    ck_assert_uint_eq(mpusize(128 * 1024 + 1), MPUSIZE_256K);
    ck_assert_uint_eq(mpusize(512 * 1024), MPUSIZE_512K);
    ck_assert_uint_eq(mpusize(1024 * 1024), MPUSIZE_1M);
    ck_assert_uint_eq(mpusize(128 * 1024 * 1024), MPUSIZE_128M);
}
END_TEST

/* Every returned value must carry the SIZE field in the RASR bit layout
 * (field << 1), and decode back to a power-of-two region >= the request. */
START_TEST(test_mpusize_encoding)
{
    ck_assert_uint_eq(mpusize(128 * 1024), expected_rasr(0x10));
    ck_assert_uint_eq(mpusize(128 * 1024 * 1024), expected_rasr(0x1a));
}
END_TEST

Suite *mpusize_suite(void)
{
    Suite *s = suite_create("mpusize");
    TCase *tc = tcase_create("mpusize");

    tcase_add_test(tc, test_mpusize_small_sizes);
    tcase_add_test(tc, test_mpusize_above_64k_is_not_err);
    tcase_add_test(tc, test_mpusize_large_sizes_round_up);
    tcase_add_test(tc, test_mpusize_encoding);

    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    int fails;
    Suite *s = mpusize_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    fails = srunner_ntests_failed(sr);
    srunner_free(sr);

    return fails;
}
