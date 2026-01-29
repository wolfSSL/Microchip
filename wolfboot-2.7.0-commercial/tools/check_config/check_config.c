/* check_config.c
 *
 * Show configuration
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

/* Option to enable sign tool debugging */
/* Must also define DEBUG_WOLFSSL in user_settings.h */
#include <stdio.h>
#include "src/libwolfboot.c"
static int locked = 0;

/* Mocks */
void hal_init(void)
{
}
int hal_flash_write(haladdr_t address, const uint8_t *data, int len)
{
    return 0;
}
int hal_flash_erase(haladdr_t address, int len)
{
    return 0;
}
void hal_flash_unlock(void)
{
    if (!locked)
        printf("Double unlock detected\n");
    locked--;
}
void hal_flash_lock(void)
{
    if (locked)
        printf("Double lock detected\n");
    locked++;
}

void hal_prepare_boot(void)
{
}

int spi_flash_sector_erase(uint32_t address)
{
    return 0;
}
int spi_flash_read(uint32_t address, void *data, int len)
{
    return 0;
}
int spi_flash_write(uint32_t address, const void *data, int len)
{
    return 0;
}
/* End Mocks */

#define Min(A,B) ((A<B)?A:B)

int main(void)
{
    printf("WOLFBOOT_PARTITION_SIZE             : %u\n", WOLFBOOT_PARTITION_SIZE);
    printf("WOLFBOOT_SECTOR_SIZE                : %u\n", WOLFBOOT_SECTOR_SIZE);
    printf("Sectors per partition               : %u\n", (WOLFBOOT_PARTITION_SIZE / WOLFBOOT_SECTOR_SIZE));
    printf("ENCRYPT_TMP_SECRET_OFFSET           : %u\n", ENCRYPT_TMP_SECRET_OFFSET);
    printf("TRAILER_SKIP                        : %u\n", TRAILER_SKIP);
#if defined(EXT_ENCRYPTED)
    printf("TRAILER_OVERHEAD                    : %u\n", TRAILER_OVERHEAD);
#endif
    printf("WOLFBOOT_PARTITION_BOOT_ADDRESS     : %08X\n", WOLFBOOT_PARTITION_BOOT_ADDRESS);
    printf("WOLFBOOT_PARTITION_UPDATE_ADDRESS   : %08X\n", WOLFBOOT_PARTITION_UPDATE_ADDRESS);
    printf("PART_BOOT_ENDFLAGS                  : %08X\n", PART_BOOT_ENDFLAGS);
    printf("PART_UPDATE_ENDFLAGS                : %08X\n", PART_UPDATE_ENDFLAGS);
#if !defined(EXT_FLASH) || defined(FLAGS_HOME)
    printf("Max firmware size                   : %u\n",  (Min(PART_BOOT_ENDFLAGS, PART_UPDATE_ENDFLAGS) - WOLFBOOT_PARTITION_BOOT_ADDRESS)
#if defined(EXT_ENCRYPTED)
           - TRAILER_OVERHEAD
#endif
           );
#else
    printf("Max firmware size                   : %u\n",
           (PART_BOOT_ENDFLAGS - WOLFBOOT_PARTITION_BOOT_ADDRESS)
#if defined(EXT_ENCRYPTED)
           - TRAILER_OVERHEAD
#endif
           );
#endif
    return 0;
}
