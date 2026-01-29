/* app_stm32l4.c
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


#include "led.h"
#include "hal.h"
#include "wolfboot/wolfboot.h"
#include "target.h"

#ifdef TARGET_stm32l4

void main(void)
{
    uint32_t boot_version;
    hal_init();
    boot_led_on();
    boot_version = wolfBoot_current_firmware_version();
    if (boot_version == 1) {
        /* Turn on Blue LED */
        boot_led_on();
        wolfBoot_update_trigger();
    } else if (boot_version >= 2) {
        /* Turn on Red LED */
        led_on();
        wolfBoot_success();
    }

    /* Wait for reboot */
    while(1) {
    }
}

#endif /* TARGET_stm32l4 */
