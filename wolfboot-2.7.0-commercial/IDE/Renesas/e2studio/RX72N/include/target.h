/* target.h
 *
 * User configurable build-time options for bootloader and application offsets
 *
 * target.h is automatically generated using the template in target.h.in by running
 * "make config".
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

#ifndef WOLFBOOT_NO_PARTITIONS
#    define WOLFBOOT_FIXED_PARTITIONS
#endif

#define WOLFBOOT_FLASH_ADDR                 0xffc00000
#define WOLFBOOT_FLASH_SIZE                 (0x100000000 - WOLFBOOT_FLASH_ADDR)

#if defined(WOLFBOOT_RENESAS_TSIP)

    #define WOLFBOOT_BOOT_SIZE                  0x70000
    #define WOLFBOOT_RX_EXCVECT                 0x10000
    #define WOLFBOOT_SECTOR_SIZE                0x20000
    
    #define WOLFBOOT_PARTITION_SIZE\
            ((WOLFBOOT_FLASH_SIZE - WOLFBOOT_BOOT_SIZE -\
              WOLFBOOT_RX_EXCVECT - WOLFBOOT_SECTOR_SIZE) / 2)

    #define WOLFBOOT_PARTITION_BOOT_ADDRESS\
            (WOLFBOOT_FLASH_ADDR + WOLFBOOT_BOOT_SIZE)
    #define WOLFBOOT_PARTITION_UPDATE_ADDRESS\
            (WOLFBOOT_PARTITION_BOOT_ADDRESS + WOLFBOOT_PARTITION_SIZE)
    #define WOLFBOOT_PARTITION_SWAP_ADDRESS\
            (WOLFBOOT_PARTITION_UPDATE_ADDRESS + WOLFBOOT_PARTITION_SIZE)

#elif defined(WOLFBOOT_DUALBOOT)

    #define WOLFBOOT_BOOT_SIZE                  0x10000
    #define WOLFBOOT_RX_EXCVECT                 0x10000
    #define WOLFBOOT_SECTOR_SIZE                0x0
    
    #define WOLFBOOT_PARTITION_SIZE     WOLFBOOT_FLASH_SIZE/2 - WOLFBOOT_BOOT_SIZE

    #define WOLFBOOT_PARTITION_BOOT_ADDRESS\
            (WOLFBOOT_FLASH_ADDR + WOLFBOOT_BOOT_SIZE)
    #define WOLFBOOT_PARTITION_UPDATE_ADDRESS\
            (WOLFBOOT_FLASH_ADDR + WOLFBOOT_FLASH_SIZE/2 + WOLFBOOT_BOOT_SIZE)

    #define WOLFBOOT_PARTITION_SWAP_ADDRESS     0x0

#else
    #define WOLFBOOT_BOOT_SIZE                  0x10000
    #define WOLFBOOT_RX_EXCVECT                 0x10000
    #define WOLFBOOT_SECTOR_SIZE                0x10000
    
    #define WOLFBOOT_PARTITION_SIZE\
            ((WOLFBOOT_FLASH_SIZE - WOLFBOOT_BOOT_SIZE -\
              WOLFBOOT_RX_EXCVECT - WOLFBOOT_SECTOR_SIZE) / 2)

    #define WOLFBOOT_PARTITION_BOOT_ADDRESS\
            (WOLFBOOT_FLASH_ADDR + WOLFBOOT_BOOT_SIZE)
    #define WOLFBOOT_PARTITION_UPDATE_ADDRESS\
            (WOLFBOOT_PARTITION_BOOT_ADDRESS + WOLFBOOT_PARTITION_SIZE)
    #define WOLFBOOT_PARTITION_SWAP_ADDRESS\
            (WOLFBOOT_PARTITION_UPDATE_ADDRESS + WOLFBOOT_PARTITION_SIZE)
#endif

#endif /* !H_TARGETS_TARGET_ */
