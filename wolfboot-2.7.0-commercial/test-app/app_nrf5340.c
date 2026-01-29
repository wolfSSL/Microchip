/* nrf5340.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
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
#include "target.h"
#include "wolfboot/wolfboot.h"
#include "hal/nrf5340.h"
#include "printf.h"

void gpiotoggle(uint32_t port, uint32_t pin)
{
    uint32_t reg_val = GPIO_OUT(port);
    GPIO_OUTCLR(port) = reg_val & (1 << pin);
    GPIO_OUTSET(port) = (~reg_val) & (1 << pin);
}

void main(void)
{
    int i;
    /* nRF5340-DK LEDs:
     *  LED1 P0.28
     *  LED2 P0.29
     *  LED3 P0.30
     *  LED4 P0.31 */
    uint32_t port = 0;
    uint32_t pin = 28;
    uint32_t app_version;

    GPIO_PIN_CNF(port, pin) = GPIO_CNF_OUT;
#ifndef TZEN
    /* Allow network core access to P0.29 GPIO */
    GPIO_PIN_CNF(0, 29) = (GPIO_CNF_OUT | GPIO_CNF_MCUSEL(1));
#endif

    app_version = wolfBoot_current_firmware_version();

    uart_init();

    wolfBoot_printf("========================\n");
    wolfBoot_printf("nRF5340 wolfBoot (app core)\n");
    wolfBoot_printf("Copyright 2025 wolfSSL Inc\n");
    wolfBoot_printf("GPL v3\n");
    wolfBoot_printf("Version : 0x%lx\n", app_version);
    wolfBoot_printf("Compiled: " __DATE__ ":" __TIME__ "\n");
#ifdef TZEN
    wolfBoot_printf("TrustZone enabled: yes\n");
#else
    wolfBoot_printf("TrustZone enabled: no\n");
#endif
    wolfBoot_printf("========================\n");

    /* mark boot successful */
    wolfBoot_success();

    /* Toggle LED loop */
    while (1) {
        gpiotoggle(port, pin);

        sleep_us(500 * 1000);
    }
}
