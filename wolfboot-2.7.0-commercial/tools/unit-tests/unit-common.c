/* unit-common.c
 *
 * Unit test common tools 
 *
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
#include <stdio.h>
#include <string.h>
#include <check.h>
#include "target.h"
#define FLASH_SIZE (33 * 1024)

/* Emulation of external flash with a static buffer of 32KB (update) + 1KB (swap) */
uint8_t flash[FLASH_SIZE];

/* Flash lock/unlock counter */
static int elocked = 0;

#ifndef BACKUP_MOCKED

uint8_t image_backup(uint8_t part_id)
{
    printf("Called image_backup\n");
    return 0xFF; /* PART_NONE */
}
#endif

#ifndef EXT_MOCKED

/* Mocks for ext_flash_read, ext_flash_write, and ext_flash_erase functions */
int ext_flash_read(uintptr_t address, uint8_t *data, int len) {
    printf("Called ext_flash_read %p %p %d\n", address, data, len);

    /* Check that the read address and size are within the bounds of the flash memory */
    ck_assert_int_le(address + len, FLASH_SIZE);

    /* Copy the data from the flash memory to the output buffer */
    memcpy(data, &flash[address], len);

    printf("Return value: %d\n", len);
    return len;
}

int ext_flash_write(uintptr_t address, const uint8_t *data, int len) {
    printf("Called ext_flash_write %p %p %d\n", address, data, len);


    /* Check that the write address and size are within the bounds of the flash memory */
    ck_assert_int_le(address + len, FLASH_SIZE);

    /* Copy the data from the input buffer to the flash memory */
    memcpy(&flash[address], data, len);

    return 0;
}

int ext_flash_erase(uintptr_t address, int len) {
    /* Check that the erase address and size are within the bounds of the flash memory */
    ck_assert_int_le(address + len, FLASH_SIZE);

    /* Check that address is aligned to WOLFBOOT_SECTOR_SIZE */
    ck_assert_int_eq(address, address & ~(WOLFBOOT_SECTOR_SIZE - 1));

    /* Check that len is aligned to WOLFBOOT_SECTOR_SIZE */
    ck_assert_int_eq(len, len & ~(WOLFBOOT_SECTOR_SIZE - 1));


    /* Erase the flash memory by setting each byte to 0xFF, WOLFBOOT_SECTOR_SIZE bytes at a time */
    uint32_t i;
    for (i = address; i < address + len; i += WOLFBOOT_SECTOR_SIZE) {
        memset(&flash[i], 0xFF, WOLFBOOT_SECTOR_SIZE);
    }

    return 0;
}

void ext_flash_unlock(void)
{
    ck_assert_msg(elocked, "Double ext unlock detected\n");
    elocked--;
}
void ext_flash_lock(void)
{
    ck_assert_msg(!elocked, "Double ext lock detected\n");
    elocked++;
}

#endif /* EXT_MOCKED */
