/* test_bitops.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/bitops.h>
#include "../test.h"

static void Test_Bitops_Bitmask4(void)
{
    WHAL_ASSERT_EQ(WHAL_BITMASK(4), 0xFul);
}

static void Test_Bitops_Bitmask8(void)
{
    WHAL_ASSERT_EQ(WHAL_BITMASK(8), 0xFFul);
}

static void Test_Bitops_Bitmask1(void)
{
    WHAL_ASSERT_EQ(WHAL_BITMASK(1), 1ul);
}

static void Test_Bitops_SetbitsLow(void)
{
    size_t msk = WHAL_BITMASK(4);
    size_t pos = 0;
    WHAL_ASSERT_EQ(whal_SetBits(msk, pos, 0xA), 0xAul);
}

static void Test_Bitops_SetbitsShifted(void)
{
    size_t msk = (WHAL_BITMASK(4) << 4);
    size_t pos = 4;
    WHAL_ASSERT_EQ(whal_SetBits(msk, pos, 0x5), 0x50ul);
}

static void Test_Bitops_GetbitsLow(void)
{
    size_t msk = WHAL_BITMASK(4);
    size_t pos = 0;
    WHAL_ASSERT_EQ(whal_GetBits(msk, pos, 0xABul), 0xBul);
}

static void Test_Bitops_GetbitsShifted(void)
{
    size_t msk = (WHAL_BITMASK(4) << 4);
    size_t pos = 4;
    WHAL_ASSERT_EQ(whal_GetBits(msk, pos, 0xABul), 0xAul);
}

static void Test_Bitops_SetbitsGetbitsRoundtrip(void)
{
    size_t msk = (WHAL_BITMASK(7) << 8);
    size_t pos = 8;
    size_t val = 42;
    size_t encoded = whal_SetBits(msk, pos, val);
    WHAL_ASSERT_EQ(whal_GetBits(msk, pos, encoded), val);
}

static void Test_Bitops_SetbitsSingleBit(void)
{
    size_t msk = (1UL << 24);
    size_t pos = 24;
    WHAL_ASSERT_EQ(whal_SetBits(msk, pos, 1), (1UL << 24));
    WHAL_ASSERT_EQ(whal_SetBits(msk, pos, 0), 0ul);
}

void whal_Test_Bitops(void)
{
    WHAL_TEST_SUITE_START("bitops");
    WHAL_TEST(Test_Bitops_Bitmask4);
    WHAL_TEST(Test_Bitops_Bitmask8);
    WHAL_TEST(Test_Bitops_Bitmask1);
    WHAL_TEST(Test_Bitops_SetbitsLow);
    WHAL_TEST(Test_Bitops_SetbitsShifted);
    WHAL_TEST(Test_Bitops_GetbitsLow);
    WHAL_TEST(Test_Bitops_GetbitsShifted);
    WHAL_TEST(Test_Bitops_SetbitsGetbitsRoundtrip);
    WHAL_TEST(Test_Bitops_SetbitsSingleBit);
    WHAL_TEST_SUITE_END();
}
