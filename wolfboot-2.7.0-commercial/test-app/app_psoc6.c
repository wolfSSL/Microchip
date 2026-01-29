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
#include "wolfboot/wolfboot.h"

#include "cy_gpio.h"

#define BOOT_LED P1_5
#define BOOT_D7 P5_7


void main(void) {
    Cy_PDL_Init(CY_DEVICE_CFG);
    Cy_GPIO_Pin_FastInit(P5_7_PORT, P5_7_NUM, CY_GPIO_DM_PULLUP, 0UL, P5_7_GPIO);
    Cy_GPIO_Pin_FastInit(P1_5_PORT, P1_5_NUM, CY_GPIO_DM_PULLUP, 0UL, P1_5_GPIO);
    while(1)
        ;
}

