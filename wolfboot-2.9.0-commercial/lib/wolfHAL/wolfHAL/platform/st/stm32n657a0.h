/* stm32n657a0.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32N657A0_H
#define WHAL_STM32N657A0_H

/**
 * @file stm32n657a0.h
 * @brief Convenience initializers for STM32N657A0 device instances.
 *
 * Base addresses from RM0486 Table 3 (peripheral register boundary addresses).
 * RCC: 0x46028000
 * GPIO A: 0x46020000, 0x400 per port (A through Q)
 * USART1: 0x42001000
 * SPI1: 0x42003000
 * I2C1: 0x40005400
 * I2C4: 0x46001C00
 * RNG: 0x44020000
 * HASH: 0x44020400
 * CRYP1: 0x44020800
 * GPDMA1: 0x40021000
 * ETH1: 0x48036000
 * IWDG: 0x46004800
 * WWDG: 0x40002C00
 * SYSCFG: 0x46008000
 * PWR: 0x46024800
 */

#include <wolfHAL/platform/arm/cortex_m55.h>

#include <wolfHAL/clock/stm32n6_rcc.h>
#include <wolfHAL/gpio/stm32n6_gpio.h>
#include <wolfHAL/uart/stm32n6_uart.h>
#include <wolfHAL/spi/stm32n6_spi.h>
#include <wolfHAL/i2c/stm32n6_i2c.h>
#include <wolfHAL/rng/stm32n6_rng.h>
#include <wolfHAL/crypto/stm32n6_cryp.h>
#include <wolfHAL/crypto/stm32n6_hash.h>
#include <wolfHAL/dma/stm32n6_gpdma.h>
#include <wolfHAL/watchdog/stm32n6_iwdg.h>
#include <wolfHAL/watchdog/stm32n6_wwdg.h>
#include <wolfHAL/eth/stm32n6_eth.h>
#include <wolfHAL/eth_phy/eth_phy.h>

/* --- Regmap and driver macros --- */

#define WHAL_STM32N657_GPIO_BASE 0x46020000
#define WHAL_STM32N657_GPIO_DRIVER &whal_Stm32n6_Gpio_Driver

#define WHAL_STM32N657_USART1_BASE 0x42001000
#define WHAL_STM32N657_USART1_DRIVER &whal_Stm32n6_Uart_Driver

#define WHAL_STM32N657_USART2_BASE 0x40004400
#define WHAL_STM32N657_USART2_DRIVER &whal_Stm32n6_Uart_Driver

#define WHAL_STM32N657_USART3_BASE 0x40004800
#define WHAL_STM32N657_USART3_DRIVER &whal_Stm32n6_Uart_Driver

#define WHAL_STM32N657_SPI1_BASE 0x42003000
#define WHAL_STM32N657_SPI1_DRIVER &whal_Stm32n6_Spi_Driver

#define WHAL_STM32N657_I2C1_BASE 0x40005400
#define WHAL_STM32N657_I2C1_DRIVER &whal_Stm32n6_I2c_Driver

#define WHAL_STM32N657_I2C4_BASE 0x46001C00
#define WHAL_STM32N657_I2C4_DRIVER &whal_Stm32n6_I2c_Driver

#define WHAL_STM32N657_RNG_BASE 0x44020000
#define WHAL_STM32N657_RNG_DRIVER &whal_Stm32n6_Rng_Driver

#define WHAL_STM32N657_CRYP_BASE 0x44020800
#define WHAL_STM32N657_CRYP_DRIVER &whal_Stm32n6_Cryp_CryptoDriver

#define WHAL_STM32N657_HASH_BASE 0x44020400
#define WHAL_STM32N657_HASH_DRIVER &whal_Stm32n6_Hash_CryptoDriver

#define WHAL_STM32N657_GPDMA1_BASE 0x40021000
#define WHAL_STM32N657_GPDMA1_DRIVER &whal_Stm32n6_Gpdma_Driver

#define WHAL_STM32N657_IWDG_BASE 0x46004800
#define WHAL_STM32N657_IWDG_DRIVER &whal_Stm32n6_Iwdg_Driver

#define WHAL_STM32N657_WWDG_BASE 0x40002C00
#define WHAL_STM32N657_WWDG_DRIVER &whal_Stm32n6_Wwdg_Driver

#define WHAL_STM32N657_ETH_BASE 0x48036000
#define WHAL_STM32N657_ETH_DRIVER &whal_Stm32n6_Eth_Driver

/* --- Clock gate macros --- */

/* RCC_AHB1ENR (offset 0x250) */

#define WHAL_STM32N657_GPDMA1_CLOCK \
    .regOffset = 0x250,             \
    .enableMask = (1UL << 4),       \
    .enablePos = 4

/* RCC_AHB3ENR (offset 0x258) */

#define WHAL_STM32N657_RNG_CLOCK    \
    .regOffset = 0x258,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32N657_HASH_CLOCK   \
    .regOffset = 0x258,             \
    .enableMask = (1UL << 1),       \
    .enablePos = 1

#define WHAL_STM32N657_CRYP_CLOCK   \
    .regOffset = 0x258,             \
    .enableMask = (1UL << 2),       \
    .enablePos = 2

/* RCC_AHB4ENR (offset 0x25C) */

#define WHAL_STM32N657_GPIOA_CLOCK  \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32N657_GPIOB_CLOCK  \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 1),       \
    .enablePos = 1

#define WHAL_STM32N657_GPIOC_CLOCK  \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 2),       \
    .enablePos = 2

#define WHAL_STM32N657_GPIOD_CLOCK  \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 3),       \
    .enablePos = 3

#define WHAL_STM32N657_GPIOE_CLOCK  \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 4),       \
    .enablePos = 4

#define WHAL_STM32N657_GPIOF_CLOCK  \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 5),       \
    .enablePos = 5

#define WHAL_STM32N657_GPIOG_CLOCK  \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 6),       \
    .enablePos = 6

#define WHAL_STM32N657_GPIOH_CLOCK  \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 7),       \
    .enablePos = 7

#define WHAL_STM32N657_PWR_CLOCK    \
    .regOffset = 0x25C,             \
    .enableMask = (1UL << 18),      \
    .enablePos = 18

/* RCC_AHB5ENR (offset 0x260) */

#define WHAL_STM32N657_ETH1MAC_CLOCK \
    .regOffset = 0x260,              \
    .enableMask = (1UL << 22),       \
    .enablePos = 22

#define WHAL_STM32N657_ETH1TX_CLOCK \
    .regOffset = 0x260,             \
    .enableMask = (1UL << 23),      \
    .enablePos = 23

#define WHAL_STM32N657_ETH1RX_CLOCK \
    .regOffset = 0x260,             \
    .enableMask = (1UL << 24),      \
    .enablePos = 24

#define WHAL_STM32N657_ETH1_CLOCK   \
    .regOffset = 0x260,             \
    .enableMask = (1UL << 25),      \
    .enablePos = 25

/* RCC_APB1LENR (offset 0x264) */

#define WHAL_STM32N657_TIM2_CLOCK   \
    .regOffset = 0x264,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32N657_WWDG_CLOCK   \
    .regOffset = 0x264,             \
    .enableMask = (1UL << 11),      \
    .enablePos = 11

#define WHAL_STM32N657_USART2_CLOCK \
    .regOffset = 0x264,             \
    .enableMask = (1UL << 16),      \
    .enablePos = 16

#define WHAL_STM32N657_USART3_CLOCK \
    .regOffset = 0x264,             \
    .enableMask = (1UL << 17),      \
    .enablePos = 17

#define WHAL_STM32N657_I2C1_CLOCK   \
    .regOffset = 0x264,             \
    .enableMask = (1UL << 21),      \
    .enablePos = 21

#define WHAL_STM32N657_I2C2_CLOCK   \
    .regOffset = 0x264,             \
    .enableMask = (1UL << 22),      \
    .enablePos = 22

#define WHAL_STM32N657_I2C3_CLOCK   \
    .regOffset = 0x264,             \
    .enableMask = (1UL << 23),      \
    .enablePos = 23

/* RCC_APB2ENR (offset 0x26C) */

#define WHAL_STM32N657_TIM1_CLOCK   \
    .regOffset = 0x26C,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#define WHAL_STM32N657_USART1_CLOCK \
    .regOffset = 0x26C,             \
    .enableMask = (1UL << 4),       \
    .enablePos = 4

#define WHAL_STM32N657_SPI1_CLOCK   \
    .regOffset = 0x26C,             \
    .enableMask = (1UL << 12),      \
    .enablePos = 12

/* RCC_APB4LENR (offset 0x274) */

#define WHAL_STM32N657_I2C4_CLOCK   \
    .regOffset = 0x274,             \
    .enableMask = (1UL << 7),       \
    .enablePos = 7

/* RCC_APB4HENR (offset 0x278) */

#define WHAL_STM32N657_SYSCFG_CLOCK \
    .regOffset = 0x278,             \
    .enableMask = (1UL << 0),       \
    .enablePos = 0

#endif /* WHAL_STM32N657A0_H */
