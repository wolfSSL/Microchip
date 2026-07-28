/* endian.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_ENDIAN_H
#define WHAL_ENDIAN_H

/*
 * @file endian.h
 * @brief Byte-order conversion helpers.
 */

#include <stdint.h>
#include <stddef.h>

/*
 * @brief Load a 32-bit value from a big-endian byte array.
 */
static inline uint32_t whal_LoadBe32(const uint8_t *p)
{
    return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
           ((uint32_t)p[2] << 8)  | p[3];
}

/*
 * @brief Store a 32-bit value into a big-endian byte array.
 */
static inline void whal_StoreBe32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)(v >> 24);
    p[1] = (uint8_t)(v >> 16);
    p[2] = (uint8_t)(v >> 8);
    p[3] = (uint8_t)v;
}

/*
 * @brief Load n bytes from a byte array into a 32-bit big-endian value.
 *
 * The first byte becomes the MSB and the remaining (4-n) bytes are zero.
 * Equivalent to whal_LoadBe32 when n == 4.
 *
 * @param p Source byte array.
 * @param n Number of bytes to load (must be 0..4).
 */
static inline uint32_t whal_LoadBe32Partial(const uint8_t *p, size_t n)
{
    uint32_t v = 0;
    size_t i;
    for (i = 0; i < n; i++)
        v |= (uint32_t)p[i] << (24 - i * 8);
    return v;
}

/*
 * @brief Load n bytes from a byte array into a 32-bit little-endian value.
 *
 * The first byte becomes the LSB and the remaining (4-n) bytes are zero.
 *
 * @param p Source byte array.
 * @param n Number of bytes to load (must be 0..4).
 */
static inline uint32_t whal_LoadLe32Partial(const uint8_t *p, size_t n)
{
    uint32_t v = 0;
    size_t i;
    for (i = 0; i < n; i++)
        v |= (uint32_t)p[i] << (i * 8);
    return v;
}

#endif /* WHAL_ENDIAN_H */
