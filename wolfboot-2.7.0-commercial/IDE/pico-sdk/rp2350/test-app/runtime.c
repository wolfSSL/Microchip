/* runtime.c
 *
 * Custom pre-init for non-secure application, staged by wolfBoot.
 * Wolfboot test application for raspberry-pi pico2 (rp2350)
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#include <stdint.h>
typedef void (*preinit_fn_t)(void);

void runtime_init_cpasr(void)
{
    volatile uint32_t *cpasr_ns = (volatile uint32_t*) 0xE000ED88;
    *cpasr_ns |= 0xFF;
}

preinit_fn_t __attribute__((section(".nonsecure_preinit_array"))) nonsecure_preinit[] = 
             { &runtime_init_cpasr };
