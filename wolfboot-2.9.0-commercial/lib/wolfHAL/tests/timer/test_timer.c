/* test_timer.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include <wolfHAL/wolfHAL.h>
#include <wolfHAL/timer/timer.h>
#include "board.h"
#include "test.h"

static void Test_Timer_TicksAdvance(void)
{
    size_t before = g_tick;

    /* Spin for ~100ms worth of ticks. At 1ms/tick this should yield ~100. */
    volatile size_t spin = 0;
    while (g_tick - before < 100) {
        spin++;
    }

    size_t elapsed = g_tick - before;

    /* At least 100 ticks should have passed */
    WHAL_ASSERT_NEQ(elapsed, 0);
    WHAL_ASSERT_EQ(elapsed >= 100, 1);
}

void whal_Test_Timer(void)
{
    WHAL_TEST_SUITE_START("timer");
    WHAL_TEST(Test_Timer_TicksAdvance);
    WHAL_TEST_SUITE_END();
}
