/* main.c
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

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "led.h"
#include "wolfboot/wolfboot.h"

#ifdef TARGET_stm32g0

void main(void) {
    boot_led_on();
    /* Wait for reboot */
    while(1)
        ;
}
#endif /* TARGET_stm32g0 */

