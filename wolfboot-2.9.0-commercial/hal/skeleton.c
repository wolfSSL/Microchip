/* skeleton.c
 *
 * Stubs for custom HAL implementation. Defines the 
 * functions used by wolfboot for a specific target.
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
#include <target.h>
#include "image.h"


#ifdef __WOLFBOOT
void hal_init(void)
{
}

void hal_prepare_boot(void)
{
    /* wolfBoot calls hal_flash_protect() before this hook.
     * Override int hal_flash_protect(haladdr_t address, int len) to lock
     * the bootloader region on targets that support runtime write
     * protection. Return 0 on success or a negative value on failure, and
     * use this hook only for any remaining platform-specific handoff work.
     */
}

#endif

int RAMFUNCTION hal_flash_write(uint32_t address, const uint8_t *data, int len)
{
    return 0; /* on success. */
}

void RAMFUNCTION hal_flash_unlock(void)
{
}

void RAMFUNCTION hal_flash_lock(void)
{
}

int RAMFUNCTION hal_flash_erase(uint32_t address, int len)
{
    return 0; /* on success. */
}
