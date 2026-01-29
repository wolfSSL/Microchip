/* nrf52.c
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
#include "hal/nrf52.h"
#include "printf.h"

static const char extradata[1024 * 16] = "hi!";

static void gpiotoggle(uint32_t pin)
{
    uint32_t reg_val = GPIO_OUT;
    GPIO_OUTCLR = reg_val & (1 << pin);
    GPIO_OUTSET = (~reg_val) & (1 << pin);
}

static const char* START="*";
void main(void)
{
    //uint32_t pin = 19;
    uint32_t pin = 6;
    int i;
    uint32_t version = 0;
    uint8_t *v_array = (uint8_t *)&version;
    (void)extradata;
    GPIO_PIN_CNF[pin] = 1; /* Output */

    version = wolfBoot_current_firmware_version();

    uart_init();
    uart_write(START, 1);
    for (i = 3; i >= 0; i--) {
        uart_write((const char*)&v_array[i], 1);
    }
    while (1) {
        gpiotoggle(pin);
        for (i = 0; i < 800000; i++)  /* Wait a bit. */
              asm volatile ("nop");
    }
}
