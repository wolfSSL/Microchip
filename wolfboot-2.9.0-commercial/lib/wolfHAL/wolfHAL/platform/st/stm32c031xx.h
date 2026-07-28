/* stm32c031xx.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32C031XX_H
#define WHAL_STM32C031XX_H

#include <wolfHAL/platform/arm/cortex_m0plus.h>

#include <wolfHAL/clock/stm32c0_rcc.h>
#include <wolfHAL/gpio/stm32c0_gpio.h>
#include <wolfHAL/uart/stm32c0_uart.h>
#include <wolfHAL/spi/stm32c0_spi.h>
#include <wolfHAL/flash/stm32c0_flash.h>

/*
 * @file stm32c031xx.h
 * @brief Convenience initializers for STM32C031xx device instances.
 *
 * Base addresses from RM0490 Table 7 (memory map).
 * RCC: 0x40021000
 * GPIO: 0x50000000 (port A), 0x400 spacing per port
 * USART1: 0x40013800
 * USART2: 0x40004400
 * SPI1: 0x40013000
 * FLASH: 0x40022000
 * SysTick: ARM core peripheral (0xE000E010)
 */

/* --- Device macros --- */

#define WHAL_STM32C031_GPIO_BASE 0x50000000
#define WHAL_STM32C031_GPIO_DRIVER &whal_Stm32c0_Gpio_Driver

#define WHAL_STM32C031_USART1_BASE 0x40013800
#define WHAL_STM32C031_USART1_DRIVER &whal_Stm32c0_Uart_Driver

#define WHAL_STM32C031_USART2_BASE 0x40004400
#define WHAL_STM32C031_USART2_DRIVER &whal_Stm32c0_Uart_Driver

#define WHAL_STM32C031_SPI1_BASE 0x40013000
#define WHAL_STM32C031_SPI1_DRIVER &whal_Stm32c0_Spi_Driver

#define WHAL_STM32C031_FLASH_BASE 0x40022000
#define WHAL_STM32C031_FLASH_DRIVER &whal_Stm32c0_Flash_Driver

/* --- Clock gate macros --- */

/* RCC_IOPENR (offset 0x034) - I/O port clock enable */

#define WHAL_STM32C031_GPIOA_CLOCK      \
    .regOffset = 0x034,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32C031_GPIOB_CLOCK      \
    .regOffset = 0x034,                 \
    .enableMask = (1UL << 1),           \
    .enablePos = 1

#define WHAL_STM32C031_GPIOC_CLOCK      \
    .regOffset = 0x034,                 \
    .enableMask = (1UL << 2),           \
    .enablePos = 2

#define WHAL_STM32C031_GPIOD_CLOCK      \
    .regOffset = 0x034,                 \
    .enableMask = (1UL << 3),           \
    .enablePos = 3

#define WHAL_STM32C031_GPIOF_CLOCK      \
    .regOffset = 0x034,                 \
    .enableMask = (1UL << 5),           \
    .enablePos = 5

/* RCC_AHBENR (offset 0x038) - AHB peripheral clock enable */

#define WHAL_STM32C031_FLASH_CLOCK      \
    .regOffset = 0x038,                 \
    .enableMask = (1UL << 8),           \
    .enablePos = 8

/* RCC_APBENR1 (offset 0x03C) - APB peripheral clock enable register 1 */

#define WHAL_STM32C031_USART2_CLOCK     \
    .regOffset = 0x03C,                 \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32C031_SPI2_CLOCK       \
    .regOffset = 0x03C,                 \
    .enableMask = (1UL << 14),          \
    .enablePos = 14

#define WHAL_STM32C031_I2C1_CLOCK       \
    .regOffset = 0x03C,                 \
    .enableMask = (1UL << 21),          \
    .enablePos = 21

#define WHAL_STM32C031_I2C2_CLOCK       \
    .regOffset = 0x03C,                 \
    .enableMask = (1UL << 22),          \
    .enablePos = 22

#define WHAL_STM32C031_TIM2_CLOCK       \
    .regOffset = 0x03C,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32C031_TIM3_CLOCK       \
    .regOffset = 0x03C,                 \
    .enableMask = (1UL << 1),           \
    .enablePos = 1

#define WHAL_STM32C031_PWR_CLOCK        \
    .regOffset = 0x03C,                 \
    .enableMask = (1UL << 28),          \
    .enablePos = 28

/* RCC_APBENR2 (offset 0x040) - APB peripheral clock enable register 2 */

#define WHAL_STM32C031_SYSCFG_CLOCK     \
    .regOffset = 0x040,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32C031_TIM1_CLOCK       \
    .regOffset = 0x040,                 \
    .enableMask = (1UL << 11),          \
    .enablePos = 11

#define WHAL_STM32C031_SPI1_CLOCK       \
    .regOffset = 0x040,                 \
    .enableMask = (1UL << 12),          \
    .enablePos = 12

#define WHAL_STM32C031_USART1_CLOCK     \
    .regOffset = 0x040,                 \
    .enableMask = (1UL << 14),          \
    .enablePos = 14

#define WHAL_STM32C031_TIM14_CLOCK      \
    .regOffset = 0x040,                 \
    .enableMask = (1UL << 15),          \
    .enablePos = 15

#define WHAL_STM32C031_TIM16_CLOCK      \
    .regOffset = 0x040,                 \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32C031_TIM17_CLOCK      \
    .regOffset = 0x040,                 \
    .enableMask = (1UL << 18),          \
    .enablePos = 18

#define WHAL_STM32C031_ADC_CLOCK        \
    .regOffset = 0x040,                 \
    .enableMask = (1UL << 20),          \
    .enablePos = 20

#endif /* WHAL_STM32C031XX_H */
