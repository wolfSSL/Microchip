/* app_sama5d3.c
 *
 * Test bare-metal boot application
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
#include <hal/sama5d3.h>

#include "wolfboot/wolfboot.h"

#ifdef TARGET_sama5d3
/* Blue LED is PE23, Red LED is PE24 */

#define BLUE_LED_PIN 23
#define RED_LED_PIN 24

void led_init(uint32_t pin)
{
    uint32_t mask = 1U << pin;
    GPIO_MDDR(GPIOE) |= mask;
    GPIO_PER(GPIOE) |= mask;
    GPIO_IDR(GPIOE) |= mask;
    GPIO_PPUDR(GPIOE) |= mask;
    GPIO_CODR(GPIOE) |= mask;
}

void led_put(uint32_t pin, int val)
{
    uint32_t mask = 1U << pin;
    if (val)
        GPIO_SODR(GPIOE) |= mask;
    else
        GPIO_CODR(GPIOE) |= mask;
}

volatile uint32_t time_elapsed = 0;
void main(void) {

    /* Wait for reboot */
    led_init(RED_LED_PIN);
    led_put(RED_LED_PIN, 1);

    while(1)
        ;
}
#endif /** TARGET_sama5d3 **/
