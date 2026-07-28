/* app_versal.c
 *
 * Test application for AMD Versal VMK180
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

#include "hal.h"
#include "hal/versal.h"
#include "wolfboot/wolfboot.h"
#include "printf.h"

void main(void)
{
#ifdef WOLFBOOT_FIXED_PARTITIONS
    uint32_t boot_version, update_version;
#endif

    hal_init();

    wolfBoot_printf("\n\n");
    wolfBoot_printf("===========================================\n");
    wolfBoot_printf(" wolfBoot Test Application - AMD Versal\n");
    wolfBoot_printf("===========================================\n\n");

    wolfBoot_printf("Current EL: %d\n", current_el());

#ifdef WOLFBOOT_FIXED_PARTITIONS
    /* Get versions from both partitions (only available with fixed partitions) */
    boot_version = wolfBoot_get_image_version(PART_BOOT);
    update_version = wolfBoot_get_image_version(PART_UPDATE);

    /* Print firmware versions */
    wolfBoot_printf("BOOT: Version: %d (0x%08x)\n", boot_version, boot_version);
    wolfBoot_printf("UPDATE: Version: %d (0x%08x)\n", update_version, update_version);
#else
    wolfBoot_printf("Boot mode: Disk-based (GPT/MBR partitions)\n");
#endif

    wolfBoot_printf("Application running successfully!\n");
    wolfBoot_printf("\nEntering idle loop...\n");

    /* Idle loop */
    while (1) {
        __asm__ volatile("wfi");
    }
}
