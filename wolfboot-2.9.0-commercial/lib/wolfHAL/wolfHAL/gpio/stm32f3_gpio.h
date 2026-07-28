/* stm32f3_gpio.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32F3_GPIO_H
#define WHAL_STM32F3_GPIO_H

/*
 * @file stm32f3_gpio.h
 * @brief STM32F3 GPIO driver (alias for STM32WB GPIO).
 *
 * The STM32F3 GPIO peripheral is register-compatible with the STM32WB GPIO
 * (MODER/OTYPER/OSPEEDR/PUPDR/IDR/ODR/BSRR/LCKR/AFRL/AFRH at identical
 * offsets). This header re-exports under STM32F3-specific names.
 */

#include <wolfHAL/gpio/stm32wb_gpio.h>

typedef whal_Stm32wb_Gpio_Cfg    whal_Stm32f3_Gpio_Cfg;
typedef whal_Stm32wb_Gpio_PinCfg whal_Stm32f3_Gpio_PinCfg;

#define whal_Stm32f3_Gpio_Dev whal_Stm32wb_Gpio_Dev

#ifndef WHAL_CFG_STM32F3_GPIO_DIRECT_API_MAPPING
#define whal_Stm32f3_Gpio_Driver whal_Stm32wb_Gpio_Driver
#define whal_Stm32f3_Gpio_Init   whal_Stm32wb_Gpio_Init
#define whal_Stm32f3_Gpio_Deinit whal_Stm32wb_Gpio_Deinit
#define whal_Stm32f3_Gpio_Get    whal_Stm32wb_Gpio_Get
#define whal_Stm32f3_Gpio_Set    whal_Stm32wb_Gpio_Set
#endif /* !WHAL_CFG_STM32F3_GPIO_DIRECT_API_MAPPING */

#define WHAL_STM32F3_GPIO_MODE_IN    WHAL_STM32WB_GPIO_MODE_IN
#define WHAL_STM32F3_GPIO_MODE_OUT   WHAL_STM32WB_GPIO_MODE_OUT
#define WHAL_STM32F3_GPIO_MODE_ALTFN WHAL_STM32WB_GPIO_MODE_ALTFN
#define WHAL_STM32F3_GPIO_MODE_ANALOG WHAL_STM32WB_GPIO_MODE_ANALOG

#define WHAL_STM32F3_GPIO_OUTTYPE_PUSHPULL  WHAL_STM32WB_GPIO_OUTTYPE_PUSHPULL
#define WHAL_STM32F3_GPIO_OUTTYPE_OPENDRAIN WHAL_STM32WB_GPIO_OUTTYPE_OPENDRAIN

#define WHAL_STM32F3_GPIO_SPEED_LOW    WHAL_STM32WB_GPIO_SPEED_LOW
#define WHAL_STM32F3_GPIO_SPEED_MEDIUM WHAL_STM32WB_GPIO_SPEED_MEDIUM
#define WHAL_STM32F3_GPIO_SPEED_FAST   WHAL_STM32WB_GPIO_SPEED_FAST
#define WHAL_STM32F3_GPIO_SPEED_HIGH   WHAL_STM32WB_GPIO_SPEED_HIGH

#define WHAL_STM32F3_GPIO_PULL_NONE WHAL_STM32WB_GPIO_PULL_NONE
#define WHAL_STM32F3_GPIO_PULL_UP   WHAL_STM32WB_GPIO_PULL_UP
#define WHAL_STM32F3_GPIO_PULL_DOWN WHAL_STM32WB_GPIO_PULL_DOWN

#define WHAL_STM32F3_GPIO_PORT_A WHAL_STM32WB_GPIO_PORT_A
#define WHAL_STM32F3_GPIO_PORT_B WHAL_STM32WB_GPIO_PORT_B
#define WHAL_STM32F3_GPIO_PORT_C WHAL_STM32WB_GPIO_PORT_C
#define WHAL_STM32F3_GPIO_PORT_D WHAL_STM32WB_GPIO_PORT_D
#define WHAL_STM32F3_GPIO_PORT_E WHAL_STM32WB_GPIO_PORT_E
#define WHAL_STM32F3_GPIO_PORT_F WHAL_STM32WB_GPIO_PORT_F

#define WHAL_STM32F3_GPIO_PIN WHAL_STM32WB_GPIO_PIN

/* Config initializer macro alias. The F3 board.h supplies the body under
 * the F3-prefixed name; the WB driver source consumes the WB name. */
#define WHAL_CFG_STM32WB_GPIO_DEV WHAL_CFG_STM32F3_GPIO_DEV

#endif /* WHAL_STM32F3_GPIO_H */
