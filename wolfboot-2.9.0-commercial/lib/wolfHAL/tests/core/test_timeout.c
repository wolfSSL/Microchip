/* test_timeout.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/timeout.h>
#include "../test.h"

#ifndef WHAL_CFG_NO_TIMEOUT

static uint32_t g_fakeTick;

static uint32_t FakeTick(void)
{
    return g_fakeTick;
}

static whal_Timeout g_timeout = {
    .timeoutTicks = 10,
    .GetTick = FakeTick,
};

/* Helper: get a pointer to g_timeout (avoids -Waddress on &global) */
static whal_Timeout *timeout(void)
{
    return &g_timeout;
}

/* WHAL_TIMEOUT_EXPIRED returns 0 when NULL */
static void Test_Timeout_NullNotExpired(void)
{
    whal_Timeout *t = NULL;
    int expired = WHAL_TIMEOUT_EXPIRED(t);
    WHAL_ASSERT_EQ(expired, 0);
}

/* START snapshots current tick */
static void Test_Timeout_StartSnapshotsTick(void)
{
    g_fakeTick = 42;
    WHAL_TIMEOUT_START(timeout());
    WHAL_ASSERT_EQ(g_timeout.startTick, 42);
}

/* Not expired immediately after start */
static void Test_Timeout_NotExpiredImmediately(void)
{
    g_fakeTick = 0;
    WHAL_TIMEOUT_START(timeout());
    int expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_EQ(expired, 0);
}

/* Not expired one tick before deadline */
static void Test_Timeout_NotExpiredBeforeDeadline(void)
{
    g_fakeTick = 0;
    WHAL_TIMEOUT_START(timeout());
    g_fakeTick = 9;
    int expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_EQ(expired, 0);
}

/* Expired exactly at deadline */
static void Test_Timeout_ExpiredAtDeadline(void)
{
    g_fakeTick = 0;
    WHAL_TIMEOUT_START(timeout());
    g_fakeTick = 10;
    int expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_NEQ(expired, 0);
}

/* Expired well past deadline */
static void Test_Timeout_ExpiredPastDeadline(void)
{
    g_fakeTick = 0;
    WHAL_TIMEOUT_START(timeout());
    g_fakeTick = 100;
    int expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_NEQ(expired, 0);
}

/* START resets the window */
static void Test_Timeout_StartResetsWindow(void)
{
    int expired;

    g_fakeTick = 0;
    WHAL_TIMEOUT_START(timeout());
    g_fakeTick = 10;
    expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_NEQ(expired, 0);

    /* Restart — should no longer be expired */
    WHAL_TIMEOUT_START(timeout());
    expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_EQ(expired, 0);
}

/* Non-zero start tick works correctly */
static void Test_Timeout_NonZeroStart(void)
{
    int expired;

    g_fakeTick = 1000;
    WHAL_TIMEOUT_START(timeout());
    g_fakeTick = 1005;
    expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_EQ(expired, 0);
    g_fakeTick = 1010;
    expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_NEQ(expired, 0);
}

/* Tick counter wrapping (unsigned subtraction handles this) */
static void Test_Timeout_TickWrap(void)
{
    int expired;

    g_fakeTick = UINT32_MAX - 3;
    WHAL_TIMEOUT_START(timeout());
    g_fakeTick = UINT32_MAX;
    expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_EQ(expired, 0);
    g_fakeTick = UINT32_MAX - 3 + 10;
    expired = WHAL_TIMEOUT_EXPIRED(timeout());
    WHAL_ASSERT_NEQ(expired, 0);
}

void whal_Test_Timeout(void)
{
    WHAL_TEST_SUITE_START("timeout");
    WHAL_TEST(Test_Timeout_NullNotExpired);
    WHAL_TEST(Test_Timeout_StartSnapshotsTick);
    WHAL_TEST(Test_Timeout_NotExpiredImmediately);
    WHAL_TEST(Test_Timeout_NotExpiredBeforeDeadline);
    WHAL_TEST(Test_Timeout_ExpiredAtDeadline);
    WHAL_TEST(Test_Timeout_ExpiredPastDeadline);
    WHAL_TEST(Test_Timeout_StartResetsWindow);
    WHAL_TEST(Test_Timeout_NonZeroStart);
    WHAL_TEST(Test_Timeout_TickWrap);
    WHAL_TEST_SUITE_END();
}

#endif /* !WHAL_CFG_NO_TIMEOUT */
