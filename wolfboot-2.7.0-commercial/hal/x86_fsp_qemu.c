/* x86_fsp_qemu.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfboot/wolfboot.h>
#include <stdint.h>
#include <string.h>
#include <uart_drv.h>

#ifdef __WOLFBOOT
#include <printf.h>
#include <x86/ata.h>
#include <x86/gdt.h>
#include <x86/common.h>
#include <x86/fsp.h>
#include <pci.h>

void hal_init(void)
{
    gdt_setup_table();
    gdt_update_segments();
    fsp_init_silicon();
}

void hal_prepare_boot(void)
{
}
#endif

int hal_flash_write(uintptr_t address, const uint8_t *data, int len)
{
    return 0;
}

void hal_flash_unlock(void)
{
}

void hal_flash_lock(void)
{
}

int hal_flash_erase(uintptr_t address, int len)
{
    return 0;
}

int wolfBoot_fallback_is_possible(void)
{
    return 0;

}

int wolfBoot_dualboot_candidate(void)
{
    return PART_BOOT;
}

void* hal_get_primary_address(void)
{
    return (void*)0;
}

void* hal_get_update_address(void)
{
  return (void*)0;
}

void *hal_get_dts_address(void)
{
    return 0;
}

void *hal_get_dts_update_address(void)
{
    return 0;
}
