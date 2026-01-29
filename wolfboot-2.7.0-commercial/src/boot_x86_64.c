/* boot_x86_64.c
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

#include "image.h"
#include "loader.h"
#include "wolfboot/wolfboot.h"

#ifdef TARGET_X86_64_EFI

#include <efi/efi.h>
#include <efi/efilib.h>

extern unsigned int __bss_start__;
extern unsigned int __bss_end__;
static volatile unsigned int cpu_id;
extern unsigned int *END_STACK;

extern void RAMFUNCTION x86_64_efi_do_boot(uint8_t *kernel);

#ifdef MMU
void RAMFUNCTION do_boot(const uint32_t *app_offset, const uint32_t* dts_offset)
#else
void RAMFUNCTION do_boot(const uint32_t *app_offset)
#endif
{
    x86_64_efi_do_boot((uint8_t *)app_offset);
}

#endif /* TARGET_X86_64_EFI */
