/* stm32wba55cg.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WBA55CG_H
#define WHAL_STM32WBA55CG_H

#include <wolfHAL/platform/arm/cortex_m33.h>

#include <wolfHAL/clock/stm32wba_rcc.h>
#include <wolfHAL/gpio/stm32wba_gpio.h>
#include <wolfHAL/uart/stm32wba_uart.h>
#include <wolfHAL/uart/stm32wba_uart_dma.h>
#include <wolfHAL/spi/stm32wba_spi.h>
#include <wolfHAL/flash/stm32wba_flash.h>
#include <wolfHAL/rng/stm32wba_rng.h>
#include <wolfHAL/i2c/stm32wba_i2c.h>
#include <wolfHAL/watchdog/stm32wba_iwdg.h>
#include <wolfHAL/watchdog/stm32wba_wwdg.h>
#include <wolfHAL/crypto/stm32wba_aes.h>
#include <wolfHAL/crypto/stm32wba_hash.h>
#include <wolfHAL/dma/stm32wba_gpdma.h>

/*
 * @file stm32wba55cg.h
 * @brief Convenience initializers for STM32WBA55CG device instances.
 *
 * Base addresses from RM0493 Table 5 (memory map).
 * GPIO: 0x42020000 (port A), 0x400 spacing per port (A, B, C, H)
 * RCC: 0x46020C00
 * USART1: 0x40013800
 * SPI1: 0x40013000
 * I2C1: 0x40005400
 * Flash interface: 0x40022000
 * RNG: 0x420C0800
 * AES: 0x420C0000
 */

/* --- Regmap and driver macros --- */

#define WHAL_STM32WBA55_GPIO_BASE 0x42020000
#define WHAL_STM32WBA55_GPIO_DRIVER &whal_Stm32wba_Gpio_Driver

#define WHAL_STM32WBA55_USART1_BASE 0x40013800
#define WHAL_STM32WBA55_USART1_DRIVER &whal_Stm32wba_Uart_Driver

#define WHAL_STM32WBA55_USART2_BASE 0x40004400
#define WHAL_STM32WBA55_USART2_DRIVER &whal_Stm32wba_Uart_Driver

#define WHAL_STM32WBA55_LPUART1_BASE 0x46002400
#define WHAL_STM32WBA55_LPUART1_DRIVER &whal_Stm32wba_Uart_Driver

#define WHAL_STM32WBA55_SPI1_BASE 0x40013000
#define WHAL_STM32WBA55_SPI1_DRIVER &whal_Stm32wba_Spi_Driver

#define WHAL_STM32WBA55_I2C1_BASE 0x40005400
#define WHAL_STM32WBA55_I2C1_DRIVER &whal_Stm32wba_I2c_Driver

#define WHAL_STM32WBA55_I2C3_BASE 0x46002800
#define WHAL_STM32WBA55_I2C3_DRIVER &whal_Stm32wba_I2c_Driver

#define WHAL_STM32WBA55_FLASH_BASE 0x40022000
#define WHAL_STM32WBA55_FLASH_DRIVER &whal_Stm32wba_Flash_Driver

#define WHAL_STM32WBA55_RNG_BASE 0x420C0800
#define WHAL_STM32WBA55_RNG_DRIVER &whal_Stm32wba_Rng_Driver

#define WHAL_STM32WBA55_GPDMA1_BASE 0x40020000
#define WHAL_STM32WBA55_GPDMA1_DRIVER &whal_Stm32wba_Gpdma_Driver

#define WHAL_STM32WBA55_AES_BASE 0x420C0000
#define WHAL_STM32WBA55_AES_DRIVER &whal_Stm32wba_Aes_CryptoDriver

#define WHAL_STM32WBA55_HASH_BASE 0x420C0400
#define WHAL_STM32WBA55_HASH_DRIVER &whal_Stm32wba_Hash_CryptoDriver

#define WHAL_STM32WBA55_IWDG_BASE 0x40003000
#define WHAL_STM32WBA55_IWDG_DRIVER &whal_Stm32wba_Iwdg_Driver

#define WHAL_STM32WBA55_WWDG_BASE 0x40002C00
#define WHAL_STM32WBA55_WWDG_DRIVER &whal_Stm32wba_Wwdg_Driver

/* --- Clock gate macros --- */
/* RCC base: 0x46020C00, offsets from base */

/* RCC_AHB1ENR (offset 0x088) */
#define WHAL_STM32WBA55_FLASH_CLOCK \
    .regOffset = 0x088,             \
    .enableMask = (1UL << 8),       \
    .enablePos = 8

/* USART1 TX DMA configuration: memory-to-peripheral, 8-bit, REQSEL=12 */
#define WHAL_STM32WBA55_USART1_TX_DMA_CFG      \
    .dir = WHAL_STM32WBA_GPDMA_DIR_MEM_TO_PERIPH, \
    .srcWidth = WHAL_STM32WBA_GPDMA_WIDTH_8BIT,   \
    .dstWidth = WHAL_STM32WBA_GPDMA_WIDTH_8BIT,   \
    .srcInc = WHAL_STM32WBA_GPDMA_INC_ENABLE,     \
    .dstInc = WHAL_STM32WBA_GPDMA_INC_DISABLE,    \
    .reqSel = 12

/* USART1 RX DMA configuration: peripheral-to-memory, 8-bit, REQSEL=11 */
#define WHAL_STM32WBA55_USART1_RX_DMA_CFG      \
    .dir = WHAL_STM32WBA_GPDMA_DIR_PERIPH_TO_MEM, \
    .srcWidth = WHAL_STM32WBA_GPDMA_WIDTH_8BIT,   \
    .dstWidth = WHAL_STM32WBA_GPDMA_WIDTH_8BIT,   \
    .srcInc = WHAL_STM32WBA_GPDMA_INC_DISABLE,    \
    .dstInc = WHAL_STM32WBA_GPDMA_INC_ENABLE,     \
    .reqSel = 11

#define WHAL_STM32WBA55_GPDMA1_CLOCK \
    .regOffset = 0x088,              \
    .enableMask = (1UL << 0),        \
    .enablePos = 0

/* RCC_AHB2ENR (offset 0x08C) */
#define WHAL_STM32WBA55_GPIOA_CLOCK \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32WBA55_GPIOB_CLOCK \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 1),       \
    .enablePos = 1

#define WHAL_STM32WBA55_GPIOC_CLOCK \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 2),       \
    .enablePos = 2

#define WHAL_STM32WBA55_GPIOH_CLOCK \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 7),       \
    .enablePos = 7

#define WHAL_STM32WBA55_AES_CLOCK   \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 16),      \
    .enablePos = 16

#define WHAL_STM32WBA55_HASH_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 17),      \
    .enablePos = 17

#define WHAL_STM32WBA55_RNG_CLOCK   \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 18),      \
    .enablePos = 18

#define WHAL_STM32WBA55_SAES_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 19),      \
    .enablePos = 19

#define WHAL_STM32WBA55_HSEM_CLOCK  \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 20),      \
    .enablePos = 20

#define WHAL_STM32WBA55_PKA_CLOCK   \
    .regOffset = 0x08C,             \
    .enableMask = (1UL << 21),      \
    .enablePos = 21

/* RCC_AHB4ENR (offset 0x094) */
#define WHAL_STM32WBA55_PWR_CLOCK   \
    .regOffset = 0x094,             \
    .enableMask = (1UL << 2),       \
    .enablePos = 2

#define WHAL_STM32WBA55_ADC4_CLOCK  \
    .regOffset = 0x094,             \
    .enableMask = (1UL << 5),       \
    .enablePos = 5

/* RCC_AHB5ENR (offset 0x098) */
#define WHAL_STM32WBA55_RADIO_CLOCK \
    .regOffset = 0x098,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

/* RCC_APB1ENR1 (offset 0x09C) */
#define WHAL_STM32WBA55_TIM2_CLOCK  \
    .regOffset = 0x09C,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32WBA55_TIM3_CLOCK  \
    .regOffset = 0x09C,             \
    .enableMask = (1UL << 1),       \
    .enablePos = 1

#define WHAL_STM32WBA55_WWDG_CLOCK  \
    .regOffset = 0x09C,             \
    .enableMask = (1UL << 11),      \
    .enablePos = 11

#define WHAL_STM32WBA55_USART2_CLOCK \
    .regOffset = 0x09C,              \
    .enableMask = (1UL << 17),       \
    .enablePos = 17

#define WHAL_STM32WBA55_I2C1_CLOCK  \
    .regOffset = 0x09C,             \
    .enableMask = (1UL << 21),      \
    .enablePos = 21

/* RCC_APB2ENR (offset 0x0A4) */
#define WHAL_STM32WBA55_TIM1_CLOCK  \
    .regOffset = 0x0A4,             \
    .enableMask = (1UL << 11),      \
    .enablePos = 11

#define WHAL_STM32WBA55_SPI1_CLOCK  \
    .regOffset = 0x0A4,             \
    .enableMask = (1UL << 12),      \
    .enablePos = 12

#define WHAL_STM32WBA55_USART1_CLOCK \
    .regOffset = 0x0A4,              \
    .enableMask = (1UL << 14),       \
    .enablePos = 14

#define WHAL_STM32WBA55_TIM16_CLOCK \
    .regOffset = 0x0A4,             \
    .enableMask = (1UL << 17),      \
    .enablePos = 17

#define WHAL_STM32WBA55_TIM17_CLOCK \
    .regOffset = 0x0A4,             \
    .enableMask = (1UL << 18),      \
    .enablePos = 18

/* RCC_APB7ENR (offset 0x0A8) */
#define WHAL_STM32WBA55_SYSCFG_CLOCK \
    .regOffset = 0x0A8,              \
    .enableMask = (1UL << 1),        \
    .enablePos = 1

#define WHAL_STM32WBA55_SPI3_CLOCK  \
    .regOffset = 0x0A8,             \
    .enableMask = (1UL << 5),       \
    .enablePos = 5

#define WHAL_STM32WBA55_LPUART1_CLOCK \
    .regOffset = 0x0A8,               \
    .enableMask = (1UL << 6),         \
    .enablePos = 6

#define WHAL_STM32WBA55_I2C3_CLOCK  \
    .regOffset = 0x0A8,             \
    .enableMask = (1UL << 7),       \
    .enablePos = 7

#define WHAL_STM32WBA55_LPTIM1_CLOCK \
    .regOffset = 0x0A8,              \
    .enableMask = (1UL << 11),       \
    .enablePos = 11

#endif /* WHAL_STM32WBA55CG_H */
