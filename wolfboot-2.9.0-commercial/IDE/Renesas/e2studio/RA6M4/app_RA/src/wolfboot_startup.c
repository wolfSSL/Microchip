/* wolfboot_startup.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
 /*
 wolfBoot-specific early startup code for RA6M4 application.
 *
 * When this application is booted by wolfBoot, wolfBoot's own RAM functions
 * occupy 0x20000000-0x20001188 with a DIFFERENT layout than this application
 * expects.  The C runtime startup (SystemRuntimeInit) tries to call memcpy()
 * at the address this application was linked to, but that address contains
 * wolfBoot's code, not the application's memcpy, causing an immediate crash.
 *
 * wolfboot_pre_init() must be called from R_BSP_WarmStart(BSP_WARM_START_RESET)
 * BEFORE SystemRuntimeInit runs.  It copies the __ram_from_flash$$ section
 * using a plain word loop (no library memcpy) so that the application's RAM
 * functions are placed at their correct VMA addresses.  SystemRuntimeInit will
 * then redundantly copy the same data, but by that point memcpy is valid.
 */
#include <stdint.h>

/**
 * Copy __ram_from_flash$$ section to its VMA before SystemRuntimeInit runs.
 *
 * Call this from R_BSP_WarmStart(BSP_WARM_START_RESET), which fires inside
 * SystemInit() BEFORE SystemRuntimeInit() is called.
 */
void wolfboot_pre_init(void)
{
    extern uint32_t __ram_from_flash$$Base;
    extern uint32_t __ram_from_flash$$Limit;
    extern uint32_t __ram_from_flash$$Load;

    volatile uint32_t       *dst = &__ram_from_flash$$Base;
    volatile const uint32_t *src = (const uint32_t *)(&__ram_from_flash$$Load);
    volatile const uint32_t *end = &__ram_from_flash$$Limit;

    while (dst < end)
    {
        *dst++ = *src++;
    }
}
