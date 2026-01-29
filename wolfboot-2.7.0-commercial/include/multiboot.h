/* 
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

uint8_t *mb2_find_header(uint8_t *image, int size);
int mb2_build_boot_info_header(uint8_t *mb2_boot_info,
                               uint8_t *mb2_header,
                               void *stage2_params,
                               unsigned max_size);
void mb2_jump(uintptr_t entry, uint32_t mb2_boot_info);
#endif /* MULTIBOOT_H */
