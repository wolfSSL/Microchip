/* stm32l152re.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32L152RE_H
#define WHAL_STM32L152RE_H

#include <wolfHAL/platform/arm/cortex_m3.h>

#include <wolfHAL/clock/stm32l1_rcc.h>
#include <wolfHAL/gpio/stm32l1_gpio.h>
#include <wolfHAL/uart/stm32l1_uart.h>
#include <wolfHAL/spi/stm32l1_spi.h>
#include <wolfHAL/flash/stm32l1_flash.h>
#include <wolfHAL/i2c/stm32l1_i2c.h>
#include <wolfHAL/watchdog/stm32l1_iwdg.h>
#include <wolfHAL/watchdog/stm32l1_wwdg.h>

/*
 * @file stm32l152re.h
 * @brief Convenience initializers for STM32L152RE device instances.
 *
 * Base addresses from RM0038 Table 5 (STM32L1xxxx memory map).
 * RCC:    0x40023800
 * GPIO:   0x40020000 (port A), 0x400 spacing per port (A-H)
 * USART1: 0x40013800 (APB2), USART2: 0x40004400 (APB1), USART3: 0x40004800
 * UART4:  0x40004C00, UART5: 0x40005000
 * SPI1:   0x40013000 (APB2), SPI2: 0x40003800, SPI3: 0x40003C00
 * I2C1:   0x40005400, I2C2: 0x40005800
 * Flash:  0x40023C00
 * IWDG:   0x40003000, WWDG: 0x40002C00
 * PWR:    0x40007000
 */

/* --- Device macros --- */

#define WHAL_STM32L152_GPIO_BASE 0x40020000
#define WHAL_STM32L152_GPIO_DRIVER &whal_Stm32l1_Gpio_Driver

#define WHAL_STM32L152_USART1_BASE 0x40013800
#define WHAL_STM32L152_USART1_DRIVER &whal_Stm32l1_Uart_Driver

#define WHAL_STM32L152_USART2_BASE 0x40004400
#define WHAL_STM32L152_USART2_DRIVER &whal_Stm32l1_Uart_Driver

#define WHAL_STM32L152_USART3_BASE 0x40004800
#define WHAL_STM32L152_USART3_DRIVER &whal_Stm32l1_Uart_Driver

#define WHAL_STM32L152_SPI1_BASE 0x40013000
#define WHAL_STM32L152_SPI1_DRIVER &whal_Stm32l1_Spi_Driver

#define WHAL_STM32L152_SPI2_BASE 0x40003800
#define WHAL_STM32L152_SPI2_DRIVER &whal_Stm32l1_Spi_Driver

#define WHAL_STM32L152_SPI3_BASE 0x40003C00
#define WHAL_STM32L152_SPI3_DRIVER &whal_Stm32l1_Spi_Driver

#define WHAL_STM32L152_I2C1_BASE 0x40005400
#define WHAL_STM32L152_I2C1_DRIVER &whal_Stm32l1_I2c_Driver

#define WHAL_STM32L152_I2C2_BASE 0x40005800
#define WHAL_STM32L152_I2C2_DRIVER &whal_Stm32l1_I2c_Driver

#define WHAL_STM32L152_FLASH_BASE 0x40023C00
#define WHAL_STM32L152_FLASH_DRIVER &whal_Stm32l1_Flash_Driver

#define WHAL_STM32L152_IWDG_BASE 0x40003000
#define WHAL_STM32L152_IWDG_DRIVER &whal_Stm32l1_Iwdg_Driver

#define WHAL_STM32L152_WWDG_BASE 0x40002C00
#define WHAL_STM32L152_WWDG_DRIVER &whal_Stm32l1_Wwdg_Driver

/* --- Clock gate macros --- */

/* RCC_AHBENR (offset 0x1C) */

#define WHAL_STM32L152_GPIOA_CLOCK      \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32L152_GPIOB_CLOCK      \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 1),           \
    .enablePos = 1

#define WHAL_STM32L152_GPIOC_CLOCK      \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 2),           \
    .enablePos = 2

#define WHAL_STM32L152_GPIOD_CLOCK      \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 3),           \
    .enablePos = 3

#define WHAL_STM32L152_GPIOE_CLOCK      \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 4),           \
    .enablePos = 4

#define WHAL_STM32L152_GPIOH_CLOCK      \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 5),           \
    .enablePos = 5

#define WHAL_STM32L152_FLITF_CLOCK      \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 15),          \
    .enablePos = 15

#define WHAL_STM32L152_DMA1_CLOCK       \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 24),          \
    .enablePos = 24

#define WHAL_STM32L152_DMA2_CLOCK       \
    .regOffset = 0x1C,                  \
    .enableMask = (1UL << 25),          \
    .enablePos = 25

/* RCC_APB2ENR (offset 0x20) */

#define WHAL_STM32L152_SYSCFG_CLOCK     \
    .regOffset = 0x20,                  \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32L152_TIM9_CLOCK       \
    .regOffset = 0x20,                  \
    .enableMask = (1UL << 2),           \
    .enablePos = 2

#define WHAL_STM32L152_TIM10_CLOCK      \
    .regOffset = 0x20,                  \
    .enableMask = (1UL << 3),           \
    .enablePos = 3

#define WHAL_STM32L152_TIM11_CLOCK      \
    .regOffset = 0x20,                  \
    .enableMask = (1UL << 4),           \
    .enablePos = 4

#define WHAL_STM32L152_ADC1_CLOCK       \
    .regOffset = 0x20,                  \
    .enableMask = (1UL << 9),           \
    .enablePos = 9

#define WHAL_STM32L152_SPI1_CLOCK       \
    .regOffset = 0x20,                  \
    .enableMask = (1UL << 12),          \
    .enablePos = 12

#define WHAL_STM32L152_USART1_CLOCK     \
    .regOffset = 0x20,                  \
    .enableMask = (1UL << 14),          \
    .enablePos = 14

/* RCC_APB1ENR (offset 0x24) */

#define WHAL_STM32L152_TIM2_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 0),           \
    .enablePos = 0

#define WHAL_STM32L152_TIM3_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 1),           \
    .enablePos = 1

#define WHAL_STM32L152_TIM4_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 2),           \
    .enablePos = 2

#define WHAL_STM32L152_TIM5_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 3),           \
    .enablePos = 3

#define WHAL_STM32L152_TIM6_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 4),           \
    .enablePos = 4

#define WHAL_STM32L152_TIM7_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 5),           \
    .enablePos = 5

#define WHAL_STM32L152_WWDG_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 11),          \
    .enablePos = 11

#define WHAL_STM32L152_SPI2_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 14),          \
    .enablePos = 14

#define WHAL_STM32L152_SPI3_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 15),          \
    .enablePos = 15

#define WHAL_STM32L152_USART2_CLOCK     \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 17),          \
    .enablePos = 17

#define WHAL_STM32L152_USART3_CLOCK     \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 18),          \
    .enablePos = 18

#define WHAL_STM32L152_I2C1_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 21),          \
    .enablePos = 21

#define WHAL_STM32L152_I2C2_CLOCK       \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 22),          \
    .enablePos = 22

#define WHAL_STM32L152_USB_CLOCK        \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 23),          \
    .enablePos = 23

#define WHAL_STM32L152_PWR_CLOCK        \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 28),          \
    .enablePos = 28

#define WHAL_STM32L152_DAC_CLOCK        \
    .regOffset = 0x24,                  \
    .enableMask = (1UL << 29),          \
    .enablePos = 29

#endif /* WHAL_STM32L152RE_H */
