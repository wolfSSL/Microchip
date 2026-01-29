/* app_nxp_t2080.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include "../hal/nxp_ppc.h"
#include "printf.h"

static const char* hex_lut = "0123456789abcdef";

void main(void)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char snum[8];

    uart_init();

    uart_write("Test App\n", 9);

    /* Wait for reboot */
    while(1) {
        for (j=0; j<1000000; j++)
            ;
        i++;

        uart_write("\r\n0x", 4);
        for (k=0; k<8; k++) {
            snum[7 - k] = hex_lut[(i >> 4*k) & 0xf];
        }
        uart_write(snum, 8);
    }
}
