/* app_pic32ck.c
 *
 * Test bare-metal boot-led-on application
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "hal.h"
#include "target.h"
#include "wolfboot/wolfboot.h"
#include <stdint.h>

#if defined(TARGET_pic32ck)

#define PORT_BASE (0x44801000U)

#define PORTB_BASE (PORT_BASE + 0x80 * 1)
#define PORTB_DIRSET (*(volatile uint32_t *)(PORTB_BASE + 0x08))
#define PORTB_DIRSET_OUT(X) (1 << (X))
#define PORTB_OUTSET (*(volatile uint32_t *)(PORTB_BASE + 0x18))
#define PORTB_OUTSET_OUT(X) (1 << (X))
#define PORTB_OUTCLR (*(volatile uint32_t *)(PORTB_BASE + 0x14))
#define PORTB_OUTCLR_OUT(X) (1 << (X))

#define PORTD_BASE (PORT_BASE + 0x80 * 3)
#define PORTD_DIRSET (*(volatile uint32_t *)(PORTD_BASE + 0x08))
#define PORTD_DIRSET_OUT(X) (1 << (X))
#define PORTD_OUTSET (*(volatile uint32_t *)(PORTD_BASE + 0x18))
#define PORTD_OUTSET_OUT(X) (1 << (X))
#define PORTD_OUTCLR (*(volatile uint32_t *)(PORTD_BASE + 0x14))
#define PORTD_OUTCLR_OUT(X) (1 << (X))

#define LED0_PIN (20)
#define LED1_PIN (25)

static void led0_on(void)
{
    PORTD_DIRSET = PORTD_DIRSET_OUT(LED0_PIN);
    PORTD_OUTCLR = PORTD_OUTCLR_OUT(LED0_PIN);
}

static void led1_on(void)
{
    PORTB_DIRSET = PORTB_DIRSET_OUT(LED1_PIN);
    PORTB_OUTCLR = PORTB_OUTCLR_OUT(LED1_PIN);
}

void main(void)
{
    uint32_t boot_version;
    hal_init();
    boot_version = wolfBoot_current_firmware_version();
    if (boot_version == 1) {
        wolfBoot_update_trigger();
        led0_on();
    } else if (boot_version >= 2) {
        wolfBoot_success();
        led1_on();
    }

    /* Wait for reboot */
    while (1) {}
}
#endif /* TARGET_pic32ck */
