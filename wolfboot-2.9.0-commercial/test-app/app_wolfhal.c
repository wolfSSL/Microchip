/* app_wolfhal.c
 *
 * Generic test bare-metal application using wolfHAL
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hal.h"
#include "wolfboot/wolfboot.h"
#include "target.h"

#include "board.h"

/* Chip drivers behind the wolfHAL API are singletons (configured via
 * board.h). Use the BOARD_*_DEV handles defined there. */

/* Matches all keys:
 *    - chacha (32 + 12)
 *    - aes128 (16 + 16)
 *    - aes256 (32 + 16)
 */
char enc_key[] = "0123456789abcdef0123456789abcdef"
                 "0123456789abcdef";

volatile uint32_t time_elapsed = 0;

void main(void)
{
    uint32_t version;
    uint32_t updv;
    uint8_t ver_buf[5];

    hal_init();

    /* LED on */
    whal_Gpio_Set(BOARD_GPIO_DEV, BOARD_LED_PIN, 1);

    version = wolfBoot_current_firmware_version();
    updv = wolfBoot_update_firmware_version();

    ver_buf[0] = '*';
    ver_buf[1] = (version >> 24) & 0xFF;
    ver_buf[2] = (version >> 16) & 0xFF;
    ver_buf[3] = (version >> 8) & 0xFF;
    ver_buf[4] = version & 0xFF;
    whal_Uart_Send(BOARD_UART_DEV, ver_buf, sizeof(ver_buf));

    if ((version == 1) && (updv != 8)) {
        /* LED off */
        whal_Gpio_Set(BOARD_GPIO_DEV, BOARD_LED_PIN, 0);
#if EXT_ENCRYPTED
        wolfBoot_set_encrypt_key((uint8_t *)enc_key,
                                 (uint8_t *)(enc_key + 32));
#endif
        wolfBoot_update_trigger();
        /* LED on */
        whal_Gpio_Set(BOARD_GPIO_DEV, BOARD_LED_PIN, 1);
    } else {
        if (version != 7)
            wolfBoot_success();
    }

    /* Wait for reboot */
    while (1)
        __asm__ volatile("wfi");
}
