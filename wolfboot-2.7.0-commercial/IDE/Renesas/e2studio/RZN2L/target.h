/* target.h
 *
 * User configurable build-time options for bootloader and application offsets
 *
 * This is for Renesas RZN2L board.
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
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
#include "bsp_api.h"

#ifndef WOLFBOOT_NO_PARTITIONS
#    define WOLFBOOT_FIXED_PARTITIONS
#endif

#define WOLFBOOT_FLASH_ADDR                 0x60100000
#define WOLFBOOT_FLASH_SIZE                 0x100000

#define WOLFBOOT_SECTOR_SIZE                0x10000
#define WOLFBOOT_PARTITION_SIZE             0x60000

#define WOLFBOOT_PARTITION_BOOT_ADDRESS     WOLFBOOT_FLASH_ADDR
#define WOLFBOOT_PARTITION_UPDATE_ADDRESS   (WOLFBOOT_FLASH_ADDR + 0x80000)
#define WOLFBOOT_PARTITION_SWAP_ADDRESS     (WOLFBOOT_FLASH_ADDR + 0xf0000)

#define WOLFBOOT_LOAD_ADDRESS               0x10010000

#endif /* !H_TARGETS_TARGET_ */
