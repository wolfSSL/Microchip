/* stm32f091xx.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32F091XX_H
#define WHAL_STM32F091XX_H

#include <wolfHAL/platform/arm/cortex_m0.h>

#include <wolfHAL/clock/stm32f0_rcc.h>
#include <wolfHAL/gpio/stm32f0_gpio.h>
#include <wolfHAL/uart/stm32f0_uart.h>
#include <wolfHAL/spi/stm32f0_spi.h>
#include <wolfHAL/flash/stm32f0_flash.h>
#include <wolfHAL/i2c/stm32f0_i2c.h>
#include <wolfHAL/watchdog/stm32f0_iwdg.h>
#include <wolfHAL/watchdog/stm32f0_wwdg.h>

/*
 * @file stm32f091xx.h
 * @brief Convenience initializers for STM32F091xx device instances.
 *
 * Base addresses from RM0091 Table 1 (memory map).
 * RCC: 0x40021000
 * GPIO: 0x48000000 (port A), 0x400 spacing per port
 * USART1: 0x40013800, USART2: 0x40004400
 * SPI1: 0x40013000, SPI2: 0x40003800
 * I2C1: 0x40005400, I2C2: 0x40005800
 * Flash: 0x40022000
 * IWDG: 0x40003000, WWDG: 0x40002C00
 */

/* --- Device macros --- */

#define WHAL_STM32F091_GPIO_BASE 0x48000000
#define WHAL_STM32F091_GPIO_DRIVER &whal_Stm32f0_Gpio_Driver

#define WHAL_STM32F091_USART1_BASE 0x40013800
#define WHAL_STM32F091_USART1_DRIVER &whal_Stm32f0_Uart_Driver

#define WHAL_STM32F091_USART2_BASE 0x40004400
#define WHAL_STM32F091_USART2_DRIVER &whal_Stm32f0_Uart_Driver

#define WHAL_STM32F091_USART3_BASE 0x40004800
#define WHAL_STM32F091_USART3_DRIVER &whal_Stm32f0_Uart_Driver

#define WHAL_STM32F091_SPI1_BASE 0x40013000
#define WHAL_STM32F091_SPI1_DRIVER &whal_Stm32f0_Spi_Driver

#define WHAL_STM32F091_SPI2_BASE 0x40003800
#define WHAL_STM32F091_SPI2_DRIVER &whal_Stm32f0_Spi_Driver

#define WHAL_STM32F091_I2C1_BASE 0x40005400
#define WHAL_STM32F091_I2C1_DRIVER &whal_Stm32f0_I2c_Driver

#define WHAL_STM32F091_I2C2_BASE 0x40005800
#define WHAL_STM32F091_I2C2_DRIVER &whal_Stm32f0_I2c_Driver

#define WHAL_STM32F091_FLASH_BASE 0x40022000
#define WHAL_STM32F091_FLASH_DRIVER &whal_Stm32f0_Flash_Driver

#define WHAL_STM32F091_IWDG_BASE 0x40003000
#define WHAL_STM32F091_IWDG_DRIVER &whal_Stm32f0_Iwdg_Driver

#define WHAL_STM32F091_WWDG_BASE 0x40002C00
#define WHAL_STM32F091_WWDG_DRIVER &whal_Stm32f0_Wwdg_Driver

/* --- Clock gate macros --- */

/* RCC_AHBENR (offset 0x014) */

#define WHAL_STM32F091_GPIOA_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32F091_GPIOB_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 18),          \
    .enablePos = 18

#define WHAL_STM32F091_GPIOC_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 19),          \
    .enablePos = 19

#define WHAL_STM32F091_GPIOD_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 20),          \
    .enablePos = 20

#define WHAL_STM32F091_GPIOE_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 21),          \
    .enablePos = 21

#define WHAL_STM32F091_GPIOF_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 22),          \
    .enablePos = 22

#define WHAL_STM32F091_FLASH_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 4),           \
    .enablePos = 4

#define WHAL_STM32F091_DMA1_CLOCK       \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32F091_DMA2_CLOCK       \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 1),           \
    .enablePos = 1

/* RCC_APB2ENR (offset 0x018) */

#define WHAL_STM32F091_SYSCFG_CLOCK     \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32F091_USART6_CLOCK     \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 5),           \
    .enablePos = 5

#define WHAL_STM32F091_USART7_CLOCK     \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 6),           \
    .enablePos = 6

#define WHAL_STM32F091_USART8_CLOCK     \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 7),           \
    .enablePos = 7

#define WHAL_STM32F091_TIM1_CLOCK       \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 11),          \
    .enablePos = 11

#define WHAL_STM32F091_SPI1_CLOCK       \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 12),          \
    .enablePos = 12

#define WHAL_STM32F091_USART1_CLOCK     \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 14),          \
    .enablePos = 14

#define WHAL_STM32F091_TIM15_CLOCK      \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 16),          \
    .enablePos = 16

#define WHAL_STM32F091_TIM16_CLOCK      \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32F091_TIM17_CLOCK      \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 18),          \
    .enablePos = 18

/* RCC_APB1ENR (offset 0x01C) */

#define WHAL_STM32F091_TIM2_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32F091_TIM3_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 1),           \
    .enablePos = 1

#define WHAL_STM32F091_TIM6_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 4),           \
    .enablePos = 4

#define WHAL_STM32F091_TIM7_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 5),           \
    .enablePos = 5

#define WHAL_STM32F091_TIM14_CLOCK      \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 8),           \
    .enablePos = 8

#define WHAL_STM32F091_WWDG_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 11),          \
    .enablePos = 11

#define WHAL_STM32F091_SPI2_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 14),          \
    .enablePos = 14

#define WHAL_STM32F091_USART2_CLOCK     \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32F091_USART3_CLOCK     \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 18),          \
    .enablePos = 18

#define WHAL_STM32F091_USART4_CLOCK     \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 19),          \
    .enablePos = 19

#define WHAL_STM32F091_USART5_CLOCK     \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 20),          \
    .enablePos = 20

#define WHAL_STM32F091_I2C1_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 21),          \
    .enablePos = 21

#define WHAL_STM32F091_I2C2_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 22),          \
    .enablePos = 22

#define WHAL_STM32F091_PWR_CLOCK        \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 28),          \
    .enablePos = 28

#endif /* WHAL_STM32F091XX_H */
