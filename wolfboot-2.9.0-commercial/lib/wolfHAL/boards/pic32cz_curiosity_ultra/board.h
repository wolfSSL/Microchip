/* board.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/wolfHAL.h>
#include <wolfHAL/platform/microchip/pic32cz.h>
#include <wolfHAL/power/pic32cz_supc.h>

extern whal_Uart g_whalUart;
extern whal_Timeout g_whalTimeout;

extern volatile uint32_t g_tick;

#define BOARD_LED_PIN         0
#define BOARD_FLASH_TEST_ADDR 0x0C000000
#define BOARD_FLASH_SECTOR_SZ 0x1000

/* BOARD_*_DEV: how this board reaches each peripheral. */
#define BOARD_GPIO_DEV     WHAL_INTERNAL_DEV
#define BOARD_UART_DEV     (&g_whalUart)
#define BOARD_FLASH_DEV    ((whal_Flash *)&whal_Pic32cz_Flash_Dev)

/* Flash dev initializer — singleton defined in pic32cz_flash.c. */
#define WHAL_CFG_PIC32CZ_FLASH_DEV { \
    .driver = WHAL_PIC32CZ_FLASH_DRIVER, \
    .base   = WHAL_PIC32CZ_FLASH_BASE, \
    .cfg    = (void *)&(const whal_Pic32cz_Flash_Cfg){ \
        .startAddr = 0x0C000000, \
        .size      = 0x00800000, /* 8 MB max */ \
        .timeout   = &g_whalTimeout, \
    }, \
}

/* GPIO dev initializer — singleton defined in pic32cz_gpio.c. */
#define WHAL_CFG_PIC32CZ_GPIO_DEV { \
    .base = WHAL_PIC32CZ_GPIO_BASE, \
    .cfg = (void *)&(const whal_Pic32cz_Gpio_Cfg){ \
        .pinCfgCount = 3, \
        .pinCfg = (whal_Pic32cz_Gpio_PinCfg[]) { \
            { /* LED */ \
                .port = 1, \
                .pin = 21, \
                .dir = WHAL_PIC32CZ_DIR_OUTPUT, \
                .out = 0, \
            }, \
            { /* UART TX */ \
                .port = 2, \
                .pin = 21, \
                .pmuxEn = 1, \
                .pmux = WHAL_PIC32CZ_PMUX_SERCOM_ALT, \
            }, \
            { /* UART RX */ \
                .port = 2, \
                .pin = 22, \
                .pmuxEn = 1, \
                .pmux = WHAL_PIC32CZ_PMUX_SERCOM_ALT, \
            }, \
        }, \
    }, \
}

/* SysTick dev initializer — singleton defined in systick.c. */
#define WHAL_CFG_SYSTICK_DEV { \
    .base = WHAL_CORTEX_M7_SYSTICK_BASE, \
    /* .driver: direct API mapping */ \
    .cfg  = (void *)&(const whal_SysTick_Cfg){ \
        .cyclesPerTick = 300000000 / 1000, \
        .clkSrc  = WHAL_SYSTICK_CLKSRC_SYSCLK, \
        .tickInt = WHAL_SYSTICK_TICKINT_ENABLED, \
    }, \
}

whal_Error Board_Init(void);
whal_Error Board_Deinit(void);
void Board_WaitMs(size_t ms);

#endif /* BOARD_H */
