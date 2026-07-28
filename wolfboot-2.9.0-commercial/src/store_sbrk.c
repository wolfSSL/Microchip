/* store_sbrk.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stddef.h>
#include <limits.h>

#include "store_sbrk.h"

void *wolfboot_store_sbrk(unsigned int incr, uint8_t **heap,
    uint8_t *heap_base, uint32_t heap_size)
{
    uint8_t *heap_limit = heap_base + heap_size;
    void *old_heap = *heap;

    if ((incr & 3U) != 0U) {
        if (incr > (UINT_MAX - 3U))
            return (void *)-1;
        incr = (incr + 3U) & ~3U;
    }

    if (*heap == NULL) {
        *heap = heap_base;
        old_heap = *heap;
    }

    if ((uint32_t)(heap_limit - *heap) < incr)
        return (void *)-1;

    *heap += incr;

    return old_heap;
}
