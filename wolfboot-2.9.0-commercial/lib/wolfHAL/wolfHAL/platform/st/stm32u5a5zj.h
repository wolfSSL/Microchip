/* stm32u5a5zj.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32U5A5ZJ_H
#define WHAL_STM32U5A5ZJ_H

#include <wolfHAL/platform/arm/cortex_m33.h>

#include <wolfHAL/clock/stm32u5_rcc.h>
#include <wolfHAL/gpio/stm32u5_gpio.h>
#include <wolfHAL/uart/stm32u5_uart.h>
#include <wolfHAL/spi/stm32u5_spi.h>
#include <wolfHAL/flash/stm32u5_flash.h>
#include <wolfHAL/rng/stm32u5_rng.h>
#include <wolfHAL/i2c/stm32u5_i2c.h>
#include <wolfHAL/watchdog/stm32u5_iwdg.h>
#include <wolfHAL/watchdog/stm32u5_wwdg.h>
#include <wolfHAL/crypto/stm32u5_aes.h>
#include <wolfHAL/crypto/stm32u5_hash.h>
#include <wolfHAL/dma/stm32u5_gpdma.h>

/**
 * @file stm32u5a5zj.h
 * @brief Convenience initializers for STM32U5A5ZJ device instances.
 *
 * Base addresses from RM0456 Table 6 (memory map and peripheral register
 * boundary addresses).
 *
 * GPIO: 0x42020000 (port A), 0x400 spacing per port (A..H)
 * RCC: 0x46020C00
 * PWR: 0x46020800
 * USART1: 0x40013800
 * SPI1: 0x40013000
 * I2C1: 0x40005400
 * Flash interface: 0x40022000
 * RNG: 0x420C0800
 * AES: 0x420C0000
 * HASH: 0x420C0400
 * GPDMA1: 0x40020000
 */

/* --- Regmap and driver macros --- */

#define WHAL_STM32U5A5_GPIO_BASE 0x42020000
#define WHAL_STM32U5A5_GPIO_DRIVER &whal_Stm32u5_Gpio_Driver

#define WHAL_STM32U5A5_USART1_BASE 0x40013800
#define WHAL_STM32U5A5_USART1_DRIVER &whal_Stm32u5_Uart_Driver

#define WHAL_STM32U5A5_USART2_BASE 0x40004400
#define WHAL_STM32U5A5_USART2_DRIVER &whal_Stm32u5_Uart_Driver

#define WHAL_STM32U5A5_USART3_BASE 0x40004800
#define WHAL_STM32U5A5_USART3_DRIVER &whal_Stm32u5_Uart_Driver

#define WHAL_STM32U5A5_LPUART1_BASE 0x46002400
#define WHAL_STM32U5A5_LPUART1_DRIVER &whal_Stm32u5_Uart_Driver

#define WHAL_STM32U5A5_SPI1_BASE 0x40013000
#define WHAL_STM32U5A5_SPI1_DRIVER &whal_Stm32u5_Spi_Driver

#define WHAL_STM32U5A5_SPI2_BASE 0x40003800
#define WHAL_STM32U5A5_SPI2_DRIVER &whal_Stm32u5_Spi_Driver

#define WHAL_STM32U5A5_SPI3_BASE 0x46002000
#define WHAL_STM32U5A5_SPI3_DRIVER &whal_Stm32u5_Spi_Driver

#define WHAL_STM32U5A5_I2C1_BASE 0x40005400
#define WHAL_STM32U5A5_I2C1_DRIVER &whal_Stm32u5_I2c_Driver

#define WHAL_STM32U5A5_I2C2_BASE 0x40005800
#define WHAL_STM32U5A5_I2C2_DRIVER &whal_Stm32u5_I2c_Driver

#define WHAL_STM32U5A5_I2C3_BASE 0x46002800
#define WHAL_STM32U5A5_I2C3_DRIVER &whal_Stm32u5_I2c_Driver

#define WHAL_STM32U5A5_I2C4_BASE 0x40008400
#define WHAL_STM32U5A5_I2C4_DRIVER &whal_Stm32u5_I2c_Driver

#define WHAL_STM32U5A5_FLASH_BASE 0x40022000
#define WHAL_STM32U5A5_FLASH_DRIVER &whal_Stm32u5_Flash_Driver

#define WHAL_STM32U5A5_RNG_BASE 0x420C0800
#define WHAL_STM32U5A5_RNG_DRIVER &whal_Stm32u5_Rng_Driver

#define WHAL_STM32U5A5_GPDMA1_BASE 0x40020000
#define WHAL_STM32U5A5_GPDMA1_DRIVER &whal_Stm32u5_Gpdma_Driver

#define WHAL_STM32U5A5_AES_BASE 0x420C0000
#define WHAL_STM32U5A5_AES_DRIVER &whal_Stm32u5_Aes_CryptoDriver

#define WHAL_STM32U5A5_HASH_BASE 0x420C0400
#define WHAL_STM32U5A5_HASH_DRIVER &whal_Stm32u5_Hash_CryptoDriver

#define WHAL_STM32U5A5_IWDG_BASE 0x40003000
#define WHAL_STM32U5A5_IWDG_DRIVER &whal_Stm32u5_Iwdg_Driver

#define WHAL_STM32U5A5_WWDG_BASE 0x40002C00
#define WHAL_STM32U5A5_WWDG_DRIVER &whal_Stm32u5_Wwdg_Driver

/* --- Clock gate macros --- */
/* RCC base: 0x46020C00, offsets from base */

/* RCC_AHB1ENR (offset 0x088) */
#define WHAL_STM32U5A5_GPDMA1_CLOCK \
    .regOffset = 0x088,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32U5A5_FLASH_CLOCK \
    .regOffset = 0x088,            \
    .enableMask = (1UL << 8),      \
    .enablePos = 8

/* USART1 TX DMA configuration: memory-to-peripheral, 8-bit, REQSEL=USART1_TX */
#define WHAL_STM32U5A5_USART1_TX_DMA_CFG          \
    .dir = WHAL_STM32U5_GPDMA_DIR_MEM_TO_PERIPH,  \
    .srcWidth = WHAL_STM32U5_GPDMA_WIDTH_8BIT,    \
    .dstWidth = WHAL_STM32U5_GPDMA_WIDTH_8BIT,    \
    .srcInc = WHAL_STM32U5_GPDMA_INC_ENABLE,      \
    .dstInc = WHAL_STM32U5_GPDMA_INC_DISABLE,     \
    .reqSel = 27

/* USART1 RX DMA configuration: peripheral-to-memory, 8-bit, REQSEL=USART1_RX */
#define WHAL_STM32U5A5_USART1_RX_DMA_CFG          \
    .dir = WHAL_STM32U5_GPDMA_DIR_PERIPH_TO_MEM,  \
    .srcWidth = WHAL_STM32U5_GPDMA_WIDTH_8BIT,    \
    .dstWidth = WHAL_STM32U5_GPDMA_WIDTH_8BIT,    \
    .srcInc = WHAL_STM32U5_GPDMA_INC_DISABLE,     \
    .dstInc = WHAL_STM32U5_GPDMA_INC_ENABLE,      \
    .reqSel = 26

/* RCC_AHB2ENR1 (offset 0x08C) */
#define WHAL_STM32U5A5_GPIOA_CLOCK \
    .regOffset = 0x08C,            \
    .enableMask = (1UL << 0),      \
    .enablePos = 0

#define WHAL_STM32U5A5_GPIOB_CLOCK \
    .regOffset = 0x08C,            \
    .enableMask = (1UL << 1),      \
    .enablePos = 1

#define WHAL_STM32U5A5_GPIOC_CLOCK \
    .regOffset = 0x08C,            \
    .enableMask = (1UL << 2),      \
    .enablePos = 2

#define WHAL_STM32U5A5_GPIOD_CLOCK \
    .regOffset = 0x08C,            \
    .enableMask = (1UL << 3),      \
    .enablePos = 3

#define WHAL_STM32U5A5_GPIOE_CLOCK \
    .regOffset = 0x08C,            \
    .enableMask = (1UL << 4),      \
    .enablePos = 4

#define WHAL_STM32U5A5_GPIOF_CLOCK \
    .regOffset = 0x08C,            \
    .enableMask = (1UL << 5),      \
    .enablePos = 5

#define WHAL_STM32U5A5_GPIOG_CLOCK \
    .regOffset = 0x08C,            \
    .enableMask = (1UL << 6),      \
    .enablePos = 6

#define WHAL_STM32U5A5_GPIOH_CLOCK \
    .regOffset = 0x08C,            \
    .enableMask = (1UL << 7),      \
    .enablePos = 7

#define WHAL_STM32U5A5_AES_CLOCK  \
    .regOffset = 0x08C,           \
    .enableMask = (1UL << 16),    \
    .enablePos = 16

#define WHAL_STM32U5A5_HASH_CLOCK \
    .regOffset = 0x08C,           \
    .enableMask = (1UL << 17),    \
    .enablePos = 17

#define WHAL_STM32U5A5_RNG_CLOCK  \
    .regOffset = 0x08C,           \
    .enableMask = (1UL << 18),    \
    .enablePos = 18

#define WHAL_STM32U5A5_SAES_CLOCK \
    .regOffset = 0x08C,           \
    .enableMask = (1UL << 20),    \
    .enablePos = 20

/* RCC_AHB3ENR (offset 0x094) — PWR, ADC4, LPGPIO1, LPDMA1 live here on U5. */
#define WHAL_STM32U5A5_PWR_CLOCK \
    .regOffset = 0x094,          \
    .enableMask = (1UL << 2),    \
    .enablePos = 2

#define WHAL_STM32U5A5_ADC4_CLOCK \
    .regOffset = 0x094,           \
    .enableMask = (1UL << 5),     \
    .enablePos = 5

/* RCC_APB1ENR1 (offset 0x09C) */
#define WHAL_STM32U5A5_TIM2_CLOCK \
    .regOffset = 0x09C,           \
    .enableMask = (1UL << 0),     \
    .enablePos = 0

#define WHAL_STM32U5A5_TIM3_CLOCK \
    .regOffset = 0x09C,           \
    .enableMask = (1UL << 1),     \
    .enablePos = 1

#define WHAL_STM32U5A5_WWDG_CLOCK \
    .regOffset = 0x09C,           \
    .enableMask = (1UL << 11),    \
    .enablePos = 11

#define WHAL_STM32U5A5_SPI2_CLOCK \
    .regOffset = 0x09C,           \
    .enableMask = (1UL << 14),    \
    .enablePos = 14

#define WHAL_STM32U5A5_USART2_CLOCK \
    .regOffset = 0x09C,             \
    .enableMask = (1UL << 17),      \
    .enablePos = 17

#define WHAL_STM32U5A5_USART3_CLOCK \
    .regOffset = 0x09C,             \
    .enableMask = (1UL << 18),      \
    .enablePos = 18

#define WHAL_STM32U5A5_I2C1_CLOCK \
    .regOffset = 0x09C,           \
    .enableMask = (1UL << 21),    \
    .enablePos = 21

#define WHAL_STM32U5A5_I2C2_CLOCK \
    .regOffset = 0x09C,           \
    .enableMask = (1UL << 22),    \
    .enablePos = 22

/* RCC_APB1ENR2 (offset 0x0A0) */
#define WHAL_STM32U5A5_I2C4_CLOCK \
    .regOffset = 0x0A0,           \
    .enableMask = (1UL << 1),     \
    .enablePos = 1

/* RCC_APB2ENR (offset 0x0A4) */
#define WHAL_STM32U5A5_TIM1_CLOCK \
    .regOffset = 0x0A4,           \
    .enableMask = (1UL << 11),    \
    .enablePos = 11

#define WHAL_STM32U5A5_SPI1_CLOCK \
    .regOffset = 0x0A4,           \
    .enableMask = (1UL << 12),    \
    .enablePos = 12

#define WHAL_STM32U5A5_USART1_CLOCK \
    .regOffset = 0x0A4,             \
    .enableMask = (1UL << 14),      \
    .enablePos = 14

#define WHAL_STM32U5A5_TIM16_CLOCK \
    .regOffset = 0x0A4,            \
    .enableMask = (1UL << 17),     \
    .enablePos = 17

#define WHAL_STM32U5A5_TIM17_CLOCK \
    .regOffset = 0x0A4,            \
    .enableMask = (1UL << 18),     \
    .enablePos = 18

/* RCC_APB3ENR (offset 0x0A8) */
#define WHAL_STM32U5A5_SYSCFG_CLOCK \
    .regOffset = 0x0A8,             \
    .enableMask = (1UL << 1),       \
    .enablePos = 1

#define WHAL_STM32U5A5_SPI3_CLOCK \
    .regOffset = 0x0A8,           \
    .enableMask = (1UL << 5),     \
    .enablePos = 5

#define WHAL_STM32U5A5_LPUART1_CLOCK \
    .regOffset = 0x0A8,              \
    .enableMask = (1UL << 6),        \
    .enablePos = 6

#define WHAL_STM32U5A5_I2C3_CLOCK \
    .regOffset = 0x0A8,           \
    .enableMask = (1UL << 7),     \
    .enablePos = 7

#define WHAL_STM32U5A5_LPTIM1_CLOCK \
    .regOffset = 0x0A8,             \
    .enableMask = (1UL << 11),      \
    .enablePos = 11

#endif /* WHAL_STM32U5A5ZJ_H */
