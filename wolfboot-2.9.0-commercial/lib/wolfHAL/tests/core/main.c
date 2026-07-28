/* main.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdio.h>
#include "../test.h"

int g_whalTestPassed;
int g_whalTestFailed;
int g_whalTestSkipped;
int g_whalTestCurFailed;
int g_whalTestCurSkipped;

void whal_Test_Puts(const char *s)
{
    fputs(s, stdout);
}

void whal_Test_Bitops(void);
void whal_Test_Dispatch(void);
void whal_Test_Endian(void);
#ifndef WHAL_CFG_NO_TIMEOUT
void whal_Test_Timeout(void);
#endif

int main(void)
{
    g_whalTestPassed = 0;
    g_whalTestFailed = 0;
    g_whalTestSkipped = 0;

    whal_Test_Bitops();
    whal_Test_Dispatch();
    whal_Test_Endian();
#ifndef WHAL_CFG_NO_TIMEOUT
    whal_Test_Timeout();
#endif

    WHAL_TEST_SUMMARY();

    return g_whalTestFailed ? 1 : 0;
}
