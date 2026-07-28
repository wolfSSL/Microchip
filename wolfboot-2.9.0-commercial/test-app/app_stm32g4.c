/* app_stm32g4.c
 *
 * Test bare-metal application for the STM32G4 (NUCLEO-G491RE).
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
#include <stdio.h>
#include "hal.h"
#include "stm32g4.h"
#include "wolfboot/wolfboot.h"
#include "target.h"

#ifdef TARGET_stm32g4

static void led_init(void)
{
    uint32_t reg;
    RCC_AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    reg = RCC_AHB2ENR;
    (void)reg;

    reg = GPIOA_MODER & ~(0x3u << (NUCLEO_G491_LED_LD2_PIN * 2));
    GPIOA_MODER = reg | (0x1u << (NUCLEO_G491_LED_LD2_PIN * 2));
    GPIOA_PUPDR &= ~(0x3u << (NUCLEO_G491_LED_LD2_PIN * 2));
}

static void led_on(void)
{
    GPIOA_BSRR = (1u << NUCLEO_G491_LED_LD2_PIN);
}

static void led_off(void)
{
    GPIOA_BSRR = (1u << (NUCLEO_G491_LED_LD2_PIN + 16));
}

static void busy_delay(uint32_t count)
{
    volatile uint32_t i;
    for (i = 0; i < count; i++)
        __asm__ volatile ("nop");
}

void main(void)
{
    uint32_t version;
    uint32_t on_ticks, off_ticks;

    hal_init();
    led_init();
    uart_init();

    version = wolfBoot_current_firmware_version();
    printf("TEST APP\r\n");
    printf("App version: %lu\r\n", (unsigned long)version);

    /* v1: slow blink. v2+: fast blink + mark update successful. */
    if (version >= 2) {
        wolfBoot_success();
        printf("Update confirmed.\r\n");
        on_ticks  = 200000;
        off_ticks = 200000;
    } else {
        on_ticks  = 600000;
        off_ticks = 600000;
    }

    while (1) {
        led_on();
        busy_delay(on_ticks);
        led_off();
        busy_delay(off_ticks);
    }
}

#endif /* TARGET_stm32g4 */
