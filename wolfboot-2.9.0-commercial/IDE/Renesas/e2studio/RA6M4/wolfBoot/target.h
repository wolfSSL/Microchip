/* target.h
 *
 * User configurable build-time options for bootloader and application offsets
 *
 * This is for Renesas RA6M4 board.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef H_TARGETS_TARGET_
#define H_TARGETS_TARGET_

#include "user_settings.h"

#ifndef WOLFBOOT_NO_PARTITIONS
#    define WOLFBOOT_FIXED_PARTITIONS
#endif

#define WOLFBOOT_FLASH_ADDR                 0x0
#define WOLFBOOT_FLASH_SIZE                 0x100000  /* RA6M4: 1MB code flash */

#ifndef WOLFBOOT_RENESAS_SCEPROTECT

    #define WOLFBOOT_BOOT_SIZE                  0x10000
    #define WOLFBOOT_SECTOR_SIZE                0x10000

    #define WOLFBOOT_PARTITION_SIZE\
            ((WOLFBOOT_FLASH_SIZE - WOLFBOOT_BOOT_SIZE -\
                WOLFBOOT_SECTOR_SIZE) / 2)

    #define WOLFBOOT_PARTITION_BOOT_ADDRESS\
            (WOLFBOOT_FLASH_ADDR + WOLFBOOT_BOOT_SIZE)

    #define WOLFBOOT_PARTITION_UPDATE_ADDRESS\
            (WOLFBOOT_PARTITION_BOOT_ADDRESS + WOLFBOOT_PARTITION_SIZE)

    #define WOLFBOOT_PARTITION_SWAP_ADDRESS\
            (WOLFBOOT_PARTITION_UPDATE_ADDRESS + WOLFBOOT_PARTITION_SIZE)

#else
#    define WOLFBOOT_PARTITION_BOOT_ADDRESS     0x20000
#    define WOLFBOOT_PARTITION_UPDATE_ADDRESS   0x90000
#    define WOLFBOOT_PARTITION_SWAP_ADDRESS     0xf0000
#endif


#endif /* !H_TARGETS_TARGET_ */
