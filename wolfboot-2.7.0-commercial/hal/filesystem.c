/* filesystem.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#include "hal.h"
#include "wolfboot/wolfboot.h"
#include "printf.h"

#ifndef WOLFBOOT_PARTITION_FILENAME
#error "WOLFBOOT_PARTITION_FILENAME needs to be defined for filesystem HAL"
#endif

#ifndef MIN
   #define MIN(x,y) ((x)<(y)?(x):(y))
#endif

/* HAL Stubs */
void hal_init(void)
{
    return;
}

int hal_flash_write(haladdr_t address, const uint8_t *data, int len)
{
    (void)address;
    (void)data;
    (void)len;
    return -1;
}
int hal_flash_erase(haladdr_t address, int len)
{
    (void)address;
    (void)len;
    return -1;
}
void hal_flash_unlock(void)
{
    return;
}
void hal_flash_lock(void)
{
    return;
}
void hal_prepare_boot(void)
{
    return;
}

#ifdef MMU
void do_boot(const uint32_t *app_offset, const uint32_t* dts_offset)
#else
void do_boot(const uint32_t *app_offset)
#endif
{
    (void)app_offset;
}

/* filesystem access */
static XFILE fp = XBADFILE;
static byte fp_write = 0;
static long fp_size = 0;

static int setup_file(byte read_only)
{
    if (fp != XBADFILE) {
        if (!read_only && !fp_write) {
            /* Need to reopen to allow writing */
            XFCLOSE(fp);
            fp = XBADFILE;
        }
    }
    if (fp == XBADFILE) {
        fp = XFOPEN(WOLFBOOT_PARTITION_FILENAME, read_only ? "rb" : "r+b");
        if (fp != XBADFILE) {
            fp_write = !read_only;
            if (XFSEEK(fp, 0, XSEEK_END) < 0 || (fp_size = XFTELL(fp)) < 0 ||
                    XFSEEK(fp, 0, XSEEK_SET) < 0) {
                /* Failed to get the file size */
                XFCLOSE(fp);
                fp = XBADFILE;
            }
        }
        else {
            wolfBoot_printf("Failed to open file %s\n",
                WOLFBOOT_PARTITION_FILENAME);
        }
    }
    return fp != XBADFILE ? 0 : -1;
}

int ext_flash_write(uintptr_t address, const uint8_t *data, int len)
{
#ifdef DEBUG_EXT_FLASH
    wolfBoot_printf("ext_flash_write: addr %p data %p len %d\n",
        (void*)address, data, len);
#endif
    if (setup_file(0) != 0)
        return -1;
    if (address + len > (uintptr_t)fp_size)
        return -1; /* Don't allow writing past the file size */
    if (XFSEEK(fp, address, XSEEK_SET) < 0)
        return -1;
    if ((int)XFWRITE(data, 1, len, fp) != len)
        return -1;
    if (XFFLUSH(fp) != 0)
        return -1;
    return 0;
}

int ext_flash_read(uintptr_t address, uint8_t *data, int len)
{
#ifdef DEBUG_EXT_FLASH
    wolfBoot_printf("ext_flash_read: addr %p data %p len %d\n",
        (void*)address, data, len);
#endif
    if (setup_file(1) != 0)
        return -1;
    if (XFSEEK(fp, address, XSEEK_SET) < 0)
        return -1;
    return (int)XFREAD(data, 1, len, fp);
}

int ext_flash_erase(uintptr_t address, int len)
{
    byte erase_data[256];
#ifdef DEBUG_EXT_FLASH
    wolfBoot_printf("ext_flash_erase: addr %p len %d\n",
        (void*)address, len);
#endif
    XMEMSET(erase_data, 0xFF, sizeof(erase_data));
    while (len > 0) {
        int erase_len = (int)MIN((int)sizeof(erase_data), len);
        if (ext_flash_write(address, erase_data, erase_len) != 0) {
            return -1;
        }
        len -= erase_len;
        address += erase_len;
    }
    return 0;
}
void ext_flash_lock(void)
{
    return;
}
void ext_flash_unlock(void)
{
    return;
}
