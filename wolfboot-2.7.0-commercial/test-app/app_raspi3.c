/* app_raspi3.c
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

#include "wolfboot/wolfboot.h"

#ifdef TARGET_raspi3

volatile uint32_t time_elapsed = 0;
void __attribute__((section(".boot"))) main(void) {

    /* Wait for reboot */
    while(1)
        ;
}
#endif /** TARGET_raspi3 **/
