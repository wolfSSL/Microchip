/* main.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include <wolfHAL/wolfHAL.h>
#include "board.h"

void main(void)
{
    if (Board_Init() != WHAL_SUCCESS)
        goto loop;

    while (1) {
        whal_Gpio_Set(BOARD_GPIO_DEV, BOARD_LED_PIN, 1);
        whal_Uart_Send(BOARD_UART_DEV, "Blink!\r\n", 8);
        Board_WaitMs(1000);
        whal_Gpio_Set(BOARD_GPIO_DEV, BOARD_LED_PIN, 0);
        whal_Uart_Send(BOARD_UART_DEV, "Blink!\r\n", 8);
        Board_WaitMs(1000);
    }

loop:
    while (1);
}
