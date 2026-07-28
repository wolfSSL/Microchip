/* stm32h563xx.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32H563XX_H
#define WHAL_STM32H563XX_H

#include <wolfHAL/platform/arm/cortex_m33.h>

#include <wolfHAL/clock/stm32h5_rcc.h>
#include <wolfHAL/gpio/stm32h5_gpio.h>
#include <wolfHAL/uart/stm32h5_uart.h>
#include <wolfHAL/spi/stm32h5_spi.h>
#include <wolfHAL/flash/stm32h5_flash.h>
#include <wolfHAL/rng/stm32h5_rng.h>
#include <wolfHAL/eth/stm32h5_eth.h>
#include <wolfHAL/eth_phy/eth_phy.h>

/*
 * @file stm32h563xx.h
 * @brief Convenience initializers for STM32H563xx device instances.
 *
 * Base addresses from RM0481 Table 2 (memory map).
 * RCC: 0x44020C00
 * GPIO: 0x42020000 (port A), 0x400 spacing per port
 * USART1: 0x40013800
 * USART2: 0x40004400
 * USART3: 0x40004800
 * SysTick: ARM core peripheral (0xE000E010)
 */

/* --- Device macros --- */

#define WHAL_STM32H563_GPIO_BASE 0x42020000
#define WHAL_STM32H563_GPIO_DRIVER &whal_Stm32h5_Gpio_Driver

#define WHAL_STM32H563_USART1_BASE 0x40013800
#define WHAL_STM32H563_USART1_DRIVER &whal_Stm32h5_Uart_Driver

#define WHAL_STM32H563_USART2_BASE 0x40004400
#define WHAL_STM32H563_USART2_DRIVER &whal_Stm32h5_Uart_Driver

#define WHAL_STM32H563_USART3_BASE 0x40004800
#define WHAL_STM32H563_USART3_DRIVER &whal_Stm32h5_Uart_Driver

/* --- Clock gate macros --- */
/* RCC_AHB2ENR (offset 0x08C) */

#define WHAL_STM32H563_GPIOA_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32H563_GPIOB_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 1),       \
    .enablePos = 1

#define WHAL_STM32H563_GPIOC_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 2),       \
    .enablePos = 2

#define WHAL_STM32H563_GPIOD_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 3),       \
    .enablePos = 3

#define WHAL_STM32H563_GPIOE_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 4),       \
    .enablePos = 4

#define WHAL_STM32H563_GPIOF_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 5),       \
    .enablePos = 5

#define WHAL_STM32H563_GPIOG_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 6),       \
    .enablePos = 6

#define WHAL_STM32H563_GPIOH_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 7),       \
    .enablePos = 7

#define WHAL_STM32H563_GPIOI_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 8),       \
    .enablePos = 8

/* RCC_AHB1ENR (offset 0x088) */

#define WHAL_STM32H563_FLASH_CLOCK  \
    .regOffset = 0x088,             \
    .enableMask = (1UL << 8),       \
    .enablePos = 8

/* RCC_APB1LENR (offset 0x09C) */

#define WHAL_STM32H563_USART2_CLOCK \
    .regOffset = 0x09C,             \
    .enableMask = (1UL << 17),      \
    .enablePos = 17

#define WHAL_STM32H563_USART3_CLOCK \
    .regOffset = 0x09C,             \
    .enableMask = (1UL << 18),      \
    .enablePos = 18

/* RCC_APB2ENR (offset 0x0A4) */

#define WHAL_STM32H563_USART1_CLOCK \
    .regOffset = 0x0A4,             \
    .enableMask = (1UL << 14),      \
    .enablePos = 14

#define WHAL_STM32H563_SPI1_CLOCK   \
    .regOffset = 0x0A4,             \
    .enableMask = (1UL << 12),      \
    .enablePos = 12

/* SPI device macros */

#define WHAL_STM32H563_SPI1_BASE 0x40013000
#define WHAL_STM32H563_SPI1_DRIVER &whal_Stm32h5_Spi_Driver

/* RNG device macros */

#define WHAL_STM32H563_RNG_BASE 0x420C0800
#define WHAL_STM32H563_RNG_DRIVER &whal_Stm32h5_Rng_Driver

/* RCC_AHB2ENR (offset 0x08C), bit 18 */
#define WHAL_STM32H563_RNG_CLOCK    \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 18),      \
    .enablePos = 18

/* Flash device macros */

#define WHAL_STM32H563_FLASH_BASE 0x40022000
#define WHAL_STM32H563_FLASH_DRIVER &whal_Stm32h5_Flash_Driver

/* RCC_APB3ENR (offset 0x0A8), bit 1 */
#define WHAL_STM32H563_SBS_CLOCK    \
    .regOffset = 0x0A8,             \
    .enableMask = (1UL << 1),       \
    .enablePos = 1

/* Ethernet device macros */

#define WHAL_STM32H563_ETH_BASE 0x40028000
#define WHAL_STM32H563_ETH_DRIVER &whal_Stm32h5_Eth_Driver

/* RCC_AHB1ENR (offset 0x088), bit 19 */
#define WHAL_STM32H563_ETH_CLOCK    \
    .regOffset = 0x088,             \
    .enableMask = (1UL << 19),      \
    .enablePos = 19

/* RCC_AHB1ENR (offset 0x088), bit 20 — ETH TX clock */
#define WHAL_STM32H563_ETHTX_CLOCK  \
    .regOffset = 0x088,             \
    .enableMask = (1UL << 20),      \
    .enablePos = 20

/* RCC_AHB1ENR (offset 0x088), bit 21 — ETH RX clock */
#define WHAL_STM32H563_ETHRX_CLOCK  \
    .regOffset = 0x088,             \
    .enableMask = (1UL << 21),      \
    .enablePos = 21

#endif /* WHAL_STM32H563XX_H */
