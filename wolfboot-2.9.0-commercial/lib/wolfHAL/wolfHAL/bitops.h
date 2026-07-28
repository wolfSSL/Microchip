/* bitops.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_BITOPS_H
#define WHAL_BITOPS_H

/*
 * @file bitops.h
 * @brief Bit manipulation helpers for register fields.
 */

#include <stdint.h>

/*
 * @brief Create a bitmask of @p width bits starting at bit 0.
 *
 * Example: WHAL_BITMASK(4) = 0xF
 */
#define WHAL_BITMASK(width) \
    ((1UL << (width)) - 1)

/*
 * @brief Encode a value into a bit field described by @p msk and @p pos.
 */
#define whal_SetBits(msk, pos, val) \
    (((val) << (pos)) & (msk))

/*
 * @brief Extract a bit field value from a register using @p msk and @p pos.
 */
#define whal_GetBits(msk, pos, reg) \
    (((reg) & (msk)) >> (pos))

#endif /* WHAL_BITOPS_H */
