/* test_stm32wb_clock.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/wolfHAL.h>
#include <wolfHAL/platform/st/stm32wb55xx.h>
#include <wolfHAL/clock/stm32wb_rcc.h>
#include <wolfHAL/bitops.h>
#include "board.h"
#include "test.h"

static void Test_Clock_EnableDisable(void)
{
    whal_Stm32wb_Rcc_PeriphClk testClk = { WHAL_STM32WB55_GPIOA_GATE };

    /* Save original state */
    size_t origVal = 0;
    whal_Reg_Get(WHAL_STM32WB_RCC_BASE, 0x4C, (1 << 0), 0, &origVal);

    /* Enable and verify */
    WHAL_ASSERT_EQ(whal_Stm32wb_Rcc_EnablePeriphClk(&testClk), WHAL_SUCCESS);

    size_t val = 0;
    whal_Reg_Get(WHAL_STM32WB_RCC_BASE, 0x4C, (1 << 0), 0, &val);
    WHAL_ASSERT_EQ(val, 1);

    /* Disable and verify */
    WHAL_ASSERT_EQ(whal_Stm32wb_Rcc_DisablePeriphClk(&testClk), WHAL_SUCCESS);

    whal_Reg_Get(WHAL_STM32WB_RCC_BASE, 0x4C, (1 << 0), 0, &val);
    WHAL_ASSERT_EQ(val, 0);

    /* Restore original state */
    if (origVal)
        whal_Stm32wb_Rcc_EnablePeriphClk(&testClk);
}

void whal_Test_Clock_Platform(void)
{
    WHAL_TEST(Test_Clock_EnableDisable);
}
