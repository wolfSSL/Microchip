/* pic32cz.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_PIC32CZ_H
#define WHAL_PIC32CZ_H

#include <wolfHAL/clock/pic32cz_clock.h>
#include <wolfHAL/gpio/pic32cz_gpio.h>
#include <wolfHAL/uart/pic32cz_uart.h>
#include <wolfHAL/flash/pic32cz_flash.h>
#include <wolfHAL/platform/arm/cortex_m7.h>

/*
 * @file pic32cz.h
 * @brief Convenience initializers for PIC32CZ device instances.
 */

#define WHAL_PIC32CZ_FLASH_BASE 0x44002000
#define WHAL_PIC32CZ_FLASH_DRIVER &whal_Pic32cz_Flash_Driver

#define WHAL_PIC32CZ_GPIO_BASE 0x44840000
#define WHAL_PIC32CZ_GPIO_DRIVER &whal_Pic32cz_Gpio_Driver

#define WHAL_PIC32CZ_SERCOM4_UART_BASE 0x46004000
#define WHAL_PIC32CZ_SERCOM4_UART_DRIVER &whal_Pic32cz_Uart_Driver

#define WHAL_PIC32CZ_SUPC_PLL       \
    .enableMask = (1UL << 18),      \
    .enablePos = 18

#endif /* WHAL_PIC32CZ_H */
