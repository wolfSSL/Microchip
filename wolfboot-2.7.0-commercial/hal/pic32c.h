/* pic32c.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef PIC32C_H
#define PIC32C_H

#include <stdint.h>

#if defined(TEST_FLASH)
void pic32_flash_test(void);
#endif

#if defined(DUALBANK_SWAP)
void pic32_flash_dualbank_swap(void);
#endif

void pic32_fcw_grab(void);
void pic32_fcw_release(void);
int pic32_flash_erase(uint32_t addr, int len);
int pic32_flash_write(uint32_t address, const uint8_t *data, int len);
void pic32_clock_pll0_init(int refdiv, int fbdiv, int bw, int postdiv);
void pic32_clock_fracdiv0_set(int intdiv, int remdiv);
void pic32_clock_gclk_gen0(int mclk_div1, int cpudiv);
void pic32_clock_reset(void);
#if defined(TEST_CLOCK)
void pic32_clock_test(unsigned long cpu_freq);
#endif /* TEST_CLOCK */
#endif /* PIC32C_H */
