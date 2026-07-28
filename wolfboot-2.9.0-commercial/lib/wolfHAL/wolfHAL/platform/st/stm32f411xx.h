/* stm32f411xx.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32F411XX_H
#define WHAL_STM32F411XX_H

#include <wolfHAL/platform/arm/cortex_m4.h>

#include <wolfHAL/clock/stm32f4_rcc.h>
#include <wolfHAL/gpio/stm32f4_gpio.h>
#include <wolfHAL/uart/stm32f4_uart.h>
#include <wolfHAL/spi/stm32f4_spi.h>
#include <wolfHAL/flash/stm32f4_flash.h>

/*
 * @file stm32f411xx.h
 * @brief Convenience initializers for STM32F411xx device instances.
 *
 * Base addresses from RM0383 Table 1 (memory map).
 * RCC: 0x40023800
 * GPIO: 0x40020000 (port A), 0x400 spacing per port
 * USART1: 0x40011000
 * USART2: 0x40004400
 * USART6: 0x40011400
 * SPI1: 0x40013000
 * SPI2: 0x40003800
 * SPI3: 0x40003C00
 * Flash interface: 0x40023C00
 * SysTick: ARM core peripheral (0xE000E010)
 */

/* --- Device macros --- */

#define WHAL_STM32F411_GPIO_BASE 0x40020000
#define WHAL_STM32F411_GPIO_DRIVER &whal_Stm32f4_Gpio_Driver

#define WHAL_STM32F411_USART1_BASE 0x40011000
#define WHAL_STM32F411_USART1_DRIVER &whal_Stm32f4_Uart_Driver

#define WHAL_STM32F411_USART2_BASE 0x40004400
#define WHAL_STM32F411_USART2_DRIVER &whal_Stm32f4_Uart_Driver

#define WHAL_STM32F411_USART6_BASE 0x40011400
#define WHAL_STM32F411_USART6_DRIVER &whal_Stm32f4_Uart_Driver

/* --- Clock gate macros --- */
/* RCC_AHB1ENR (offset 0x030) */

#define WHAL_STM32F411_GPIOA_CLOCK  \
    .regOffset = 0x030,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32F411_GPIOB_CLOCK  \
    .regOffset = 0x030,             \
    .enableMask = (1UL << 1),       \
    .enablePos = 1

#define WHAL_STM32F411_GPIOC_CLOCK  \
    .regOffset = 0x030,             \
    .enableMask = (1UL << 2),       \
    .enablePos = 2

#define WHAL_STM32F411_GPIOD_CLOCK  \
    .regOffset = 0x030,             \
    .enableMask = (1UL << 3),       \
    .enablePos = 3

#define WHAL_STM32F411_GPIOE_CLOCK  \
    .regOffset = 0x030,             \
    .enableMask = (1UL << 4),       \
    .enablePos = 4

#define WHAL_STM32F411_GPIOH_CLOCK  \
    .regOffset = 0x030,             \
    .enableMask = (1UL << 7),       \
    .enablePos = 7

/* RCC_APB1ENR (offset 0x040) */

#define WHAL_STM32F411_USART2_CLOCK \
    .regOffset = 0x040,             \
    .enableMask = (1UL << 17),      \
    .enablePos = 17

/* RCC_APB2ENR (offset 0x044) */

#define WHAL_STM32F411_USART1_CLOCK \
    .regOffset = 0x044,             \
    .enableMask = (1UL << 4),       \
    .enablePos = 4

#define WHAL_STM32F411_USART6_CLOCK \
    .regOffset = 0x044,             \
    .enableMask = (1UL << 5),       \
    .enablePos = 5

#define WHAL_STM32F411_SPI1_CLOCK   \
    .regOffset = 0x044,             \
    .enableMask = (1UL << 12),      \
    .enablePos = 12

/* RCC_APB1ENR (offset 0x040) */

#define WHAL_STM32F411_SPI2_CLOCK   \
    .regOffset = 0x040,             \
    .enableMask = (1UL << 14),      \
    .enablePos = 14

#define WHAL_STM32F411_SPI3_CLOCK   \
    .regOffset = 0x040,             \
    .enableMask = (1UL << 15),      \
    .enablePos = 15

/* SPI device macros */

#define WHAL_STM32F411_SPI1_BASE 0x40013000
#define WHAL_STM32F411_SPI1_DRIVER &whal_Stm32f4_Spi_Driver

#define WHAL_STM32F411_SPI2_BASE 0x40003800
#define WHAL_STM32F411_SPI2_DRIVER &whal_Stm32f4_Spi_Driver

/* Flash device macros */

#define WHAL_STM32F411_FLASH_BASE 0x40023C00
#define WHAL_STM32F411_FLASH_DRIVER &whal_Stm32f4_Flash_Driver

#endif /* WHAL_STM32F411XX_H */
