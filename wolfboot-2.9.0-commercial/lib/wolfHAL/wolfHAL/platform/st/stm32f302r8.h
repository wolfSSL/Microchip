/* stm32f302r8.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32F302R8_H
#define WHAL_STM32F302R8_H

#include <wolfHAL/platform/arm/cortex_m4.h>

#include <wolfHAL/clock/stm32f3_rcc.h>
#include <wolfHAL/gpio/stm32f3_gpio.h>
#include <wolfHAL/uart/stm32f3_uart.h>
#include <wolfHAL/spi/stm32f3_spi.h>
#include <wolfHAL/flash/stm32f3_flash.h>
#include <wolfHAL/i2c/stm32f3_i2c.h>
#include <wolfHAL/watchdog/stm32f3_iwdg.h>
#include <wolfHAL/watchdog/stm32f3_wwdg.h>

/*
 * @file stm32f302r8.h
 * @brief Convenience initializers for STM32F302R8 device instances.
 *
 * Base addresses from RM0365 Table 4 (STM32F302x6/x8 memory map).
 * RCC: 0x40021000
 * GPIO: 0x48000000 (port A), 0x400 spacing per port
 * USART1: 0x40013800, USART2: 0x40004400, USART3: 0x40004800
 * SPI2: 0x40003800, SPI3: 0x40003C00
 * I2C1: 0x40005400, I2C2: 0x40005800, I2C3: 0x40007800
 * Flash interface: 0x40022000
 * IWDG: 0x40003000, WWDG: 0x40002C00
 * DMA1: 0x40020000
 * PWR: 0x40007000
 */

/* --- Device macros --- */

#define WHAL_STM32F302_GPIO_BASE 0x48000000
#define WHAL_STM32F302_GPIO_DRIVER &whal_Stm32f3_Gpio_Driver

#define WHAL_STM32F302_USART1_BASE 0x40013800
#define WHAL_STM32F302_USART1_DRIVER &whal_Stm32f3_Uart_Driver

#define WHAL_STM32F302_USART2_BASE 0x40004400
#define WHAL_STM32F302_USART2_DRIVER &whal_Stm32f3_Uart_Driver

#define WHAL_STM32F302_USART3_BASE 0x40004800
#define WHAL_STM32F302_USART3_DRIVER &whal_Stm32f3_Uart_Driver

#define WHAL_STM32F302_SPI2_BASE 0x40003800
#define WHAL_STM32F302_SPI2_DRIVER &whal_Stm32f3_Spi_Driver

#define WHAL_STM32F302_SPI3_BASE 0x40003C00
#define WHAL_STM32F302_SPI3_DRIVER &whal_Stm32f3_Spi_Driver

#define WHAL_STM32F302_I2C1_BASE 0x40005400
#define WHAL_STM32F302_I2C1_DRIVER &whal_Stm32f3_I2c_Driver

#define WHAL_STM32F302_I2C2_BASE 0x40005800
#define WHAL_STM32F302_I2C2_DRIVER &whal_Stm32f3_I2c_Driver

#define WHAL_STM32F302_I2C3_BASE 0x40007800
#define WHAL_STM32F302_I2C3_DRIVER &whal_Stm32f3_I2c_Driver

#define WHAL_STM32F302_FLASH_BASE 0x40022000
#define WHAL_STM32F302_FLASH_DRIVER &whal_Stm32f3_Flash_Driver

#define WHAL_STM32F302_IWDG_BASE 0x40003000
#define WHAL_STM32F302_IWDG_DRIVER &whal_Stm32f3_Iwdg_Driver

#define WHAL_STM32F302_WWDG_BASE 0x40002C00
#define WHAL_STM32F302_WWDG_DRIVER &whal_Stm32f3_Wwdg_Driver

/* --- Clock gate macros --- */

/* RCC_AHBENR (offset 0x014) */

#define WHAL_STM32F302_GPIOA_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32F302_GPIOB_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 18),          \
    .enablePos = 18

#define WHAL_STM32F302_GPIOC_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 19),          \
    .enablePos = 19

#define WHAL_STM32F302_GPIOD_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 20),          \
    .enablePos = 20

#define WHAL_STM32F302_GPIOF_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 22),          \
    .enablePos = 22

#define WHAL_STM32F302_FLASH_CLOCK      \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 4),           \
    .enablePos = 4

#define WHAL_STM32F302_DMA1_CLOCK       \
    .regOffset = 0x014,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

/* RCC_APB2ENR (offset 0x018) */

#define WHAL_STM32F302_SYSCFG_CLOCK     \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32F302_USART1_CLOCK     \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 14),          \
    .enablePos = 14

#define WHAL_STM32F302_TIM1_CLOCK       \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 11),          \
    .enablePos = 11

#define WHAL_STM32F302_TIM15_CLOCK      \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 16),          \
    .enablePos = 16

#define WHAL_STM32F302_TIM16_CLOCK      \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32F302_TIM17_CLOCK      \
    .regOffset = 0x018,                 \
    .enableMask = (1UL << 18),          \
    .enablePos = 18

/* RCC_APB1ENR (offset 0x01C) */

#define WHAL_STM32F302_TIM2_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32F302_TIM6_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 4),           \
    .enablePos = 4

#define WHAL_STM32F302_WWDG_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 11),          \
    .enablePos = 11

#define WHAL_STM32F302_SPI2_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 14),          \
    .enablePos = 14

#define WHAL_STM32F302_SPI3_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 15),          \
    .enablePos = 15

#define WHAL_STM32F302_USART2_CLOCK     \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32F302_USART3_CLOCK     \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 18),          \
    .enablePos = 18

#define WHAL_STM32F302_I2C1_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 21),          \
    .enablePos = 21

#define WHAL_STM32F302_I2C2_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 22),          \
    .enablePos = 22

#define WHAL_STM32F302_USB_CLOCK        \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 23),          \
    .enablePos = 23

#define WHAL_STM32F302_CAN_CLOCK        \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 25),          \
    .enablePos = 25

#define WHAL_STM32F302_PWR_CLOCK        \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 28),          \
    .enablePos = 28

#define WHAL_STM32F302_DAC1_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 29),          \
    .enablePos = 29

#define WHAL_STM32F302_I2C3_CLOCK       \
    .regOffset = 0x01C,                 \
    .enableMask = (1UL << 30),          \
    .enablePos = 30

#endif /* WHAL_STM32F302R8_H */
