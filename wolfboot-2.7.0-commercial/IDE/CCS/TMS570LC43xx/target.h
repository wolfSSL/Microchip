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

#define WOLFBOOT_SECTOR_SIZE                 0x040000
#define WOLFBOOT_PARTITION_BOOT_ADDRESS      0x040000
#define WOLFBOOT_PARTITION_SIZE              0x100000
#define WOLFBOOT_PARTITION_UPDATE_ADDRESS    0x200000
#define WOLFBOOT_PARTITION_SWAP_ADDRESS      0x3c0000

/* Load address in RAM for staged OS (update_ram only) */
#define WOLFBOOT_DTS_BOOT_ADDRESS            
#define WOLFBOOT_DTS_UPDATE_ADDRESS          
#define WOLFBOOT_LOAD_ADDRESS                
#define WOLFBOOT_LOAD_DTS_ADDRESS            

#endif /* !H_TARGETS_TARGET_ */
