/* test_pic32cz_gpio.c
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
#include <wolfHAL/gpio/pic32cz_gpio.h>
#include <wolfHAL/bitops.h>
#include "board.h"
#include "test.h"

/*
 * PIC32CZ PORT register offsets.
 * Each port group is 0x80 bytes. LED is on port B (index 1), pin 21.
 */
#define PORT_DIR_REG(port) (0x00 + ((port) * 0x80))
#define PORT_OUT_REG(port) (0x10 + ((port) * 0x80))

/* LED pin: port B, pin 21 */
#define LED_PORT 1
#define LED_HW_PIN 21

static void Test_Gpio_DirRegister(void)
{
    /* PB21 should be configured as output (bit 21 set in DIR register) */
    size_t val = 0;
    whal_Reg_Get(whal_Pic32cz_Gpio_Dev.base, PORT_DIR_REG(LED_PORT),
                 (1UL << LED_HW_PIN), LED_HW_PIN, &val);
    WHAL_ASSERT_EQ(val, 1);
}

static void Test_Gpio_SetHighReg(void)
{
    WHAL_ASSERT_EQ(whal_Gpio_Set(BOARD_GPIO_DEV, BOARD_LED_PIN, 1), WHAL_SUCCESS);

    /* Readback OUT register bit 21 */
    size_t val = 0;
    whal_Reg_Get(whal_Pic32cz_Gpio_Dev.base, PORT_OUT_REG(LED_PORT),
                 (1UL << LED_HW_PIN), LED_HW_PIN, &val);
    WHAL_ASSERT_EQ(val, 1);
}

static void Test_Gpio_SetLowReg(void)
{
    WHAL_ASSERT_EQ(whal_Gpio_Set(BOARD_GPIO_DEV, BOARD_LED_PIN, 0), WHAL_SUCCESS);

    size_t val = 0;
    whal_Reg_Get(whal_Pic32cz_Gpio_Dev.base, PORT_OUT_REG(LED_PORT),
                 (1UL << LED_HW_PIN), LED_HW_PIN, &val);
    WHAL_ASSERT_EQ(val, 0);
}

void whal_Test_Gpio_Platform(void)
{
    WHAL_TEST(Test_Gpio_DirRegister);
    WHAL_TEST(Test_Gpio_SetHighReg);
    WHAL_TEST(Test_Gpio_SetLowReg);
}
