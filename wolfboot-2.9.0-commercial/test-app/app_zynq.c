/* app_zynq.c
 *
 * Test bare-metal boot application for AMD ZynqMP ZCU102
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>

#include "wolfboot/wolfboot.h"
#include "printf.h"

#ifdef TARGET_zynq

/* Provide current_el() for hal/zynq.o (normally in boot_aarch64.c) */
__attribute__((weak)) unsigned int current_el(void)
{
    unsigned long el;
    __asm__ volatile("mrs %0, CurrentEL" : "=r" (el) : : "cc");
    return (unsigned int)((el >> 2) & 0x3U);
}

/* Stub for QSPI DMA code in hal/zynq.o (not used with SD card boot) */
void flush_dcache_range(unsigned long start, unsigned long end)
{
    (void)start;
    (void)end;
}

void main(void)
{
#ifdef WOLFBOOT_FIXED_PARTITIONS
    uint32_t boot_version, update_version;
#endif

    wolfBoot_printf("\n\n");
    wolfBoot_printf("===========================================\n");
    wolfBoot_printf(" wolfBoot Test Application - AMD ZynqMP\n");
    wolfBoot_printf("===========================================\n\n");

    wolfBoot_printf("Current EL: %d\n", current_el());

#ifdef WOLFBOOT_FIXED_PARTITIONS
    boot_version = wolfBoot_get_image_version(PART_BOOT);
    update_version = wolfBoot_get_image_version(PART_UPDATE);
    wolfBoot_printf("BOOT: Version: %d (0x%08x)\n", boot_version, boot_version);
    wolfBoot_printf("UPDATE: Version: %d (0x%08x)\n", update_version, update_version);
#else
    wolfBoot_printf("Boot mode: Disk-based (MBR partitions)\n");
#endif

    wolfBoot_printf("Application running successfully!\n");
    wolfBoot_printf("\nEntering idle loop...\n");

    /* Idle loop */
    while (1) {
        __asm__ volatile("wfi");
    }
}
#endif /** TARGET_zynq **/
