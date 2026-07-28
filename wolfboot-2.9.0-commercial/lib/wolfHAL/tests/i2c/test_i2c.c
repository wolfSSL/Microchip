/* test_i2c.c
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
#include "board.h"
#include "test.h"

static void Test_I2c_Api(void)
{
    WHAL_ASSERT_EQ(whal_I2c_StartCom(BOARD_I2C_DEV, NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_I2c_Transfer(BOARD_I2C_DEV, NULL, 1), WHAL_EINVAL);
}

void whal_Test_I2c(void)
{
    WHAL_TEST_SUITE_START("i2c");
    WHAL_TEST(Test_I2c_Api);
    WHAL_TEST_SUITE_END();
}
