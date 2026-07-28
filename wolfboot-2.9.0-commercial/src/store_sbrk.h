/* store_sbrk.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_STORE_SBRK_H
#define WOLFBOOT_STORE_SBRK_H

#include <stdint.h>

void *wolfboot_store_sbrk(unsigned int incr, uint8_t **heap,
    uint8_t *heap_base, uint32_t heap_size);

#endif
