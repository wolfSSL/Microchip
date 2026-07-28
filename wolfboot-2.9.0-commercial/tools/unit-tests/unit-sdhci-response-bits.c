/* unit-sdhci-response-bits.c
 *
 * Unit tests for sdhci response bit extraction.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#define DISK_SDCARD 1

#include <check.h>
#include <stdint.h>
#include <string.h>

static uint32_t mock_regs[0x260 / sizeof(uint32_t)];

uint64_t hal_get_timer_us(void)
{
    return 0;
}

uint32_t sdhci_reg_read(uint32_t offset)
{
    return mock_regs[offset / sizeof(uint32_t)];
}

void sdhci_reg_write(uint32_t offset, uint32_t val)
{
    mock_regs[offset / sizeof(uint32_t)] = val;
}

void sdhci_platform_init(void)
{
}

void sdhci_platform_irq_init(void)
{
}

void sdhci_platform_set_bus_mode(int is_emmc)
{
    (void)is_emmc;
}

#include "../../src/sdhci.c"

static void set_response(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3)
{
    memset(mock_regs, 0, sizeof(mock_regs));
    mock_regs[SDHCI_SRS04 / sizeof(uint32_t)] = r0;
    mock_regs[SDHCI_SRS05 / sizeof(uint32_t)] = r1;
    mock_regs[SDHCI_SRS06 / sizeof(uint32_t)] = r2;
    mock_regs[SDHCI_SRS07 / sizeof(uint32_t)] = r3;
}

START_TEST(test_csd_struct_does_not_cross_registers)
{
    set_response(0, 0, 0, 2U << 22);

    ck_assert_uint_eq(sdhci_get_response_bits(126, 2), 2);
}
END_TEST

Suite *sdhci_suite(void)
{
    Suite *s = suite_create("sdhci");
    TCase *tc = tcase_create("response_bits");

    tcase_add_test(tc, test_csd_struct_does_not_cross_registers);
    suite_add_tcase(s, tc);

    return s;
}

int main(void)
{
    int fails;
    Suite *s = sdhci_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    fails = srunner_ntests_failed(sr);
    srunner_free(sr);

    return fails;
}
