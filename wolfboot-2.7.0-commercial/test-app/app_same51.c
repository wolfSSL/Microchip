/* same51.c
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
#include "hal.h"
#include "wolfboot/wolfboot.h"

#define PORT_BASE      0x41008000 
#define GPIOA_BASE      PORT_BASE
#define GPIOA_DIR      *((volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_OUT      *((volatile uint32_t *)(GPIOA_BASE + 0x10))
#define GPIOA_WRCONFIG *((volatile uint32_t *)(GPIOA_BASE + 0x28))

#define WRCONFIG_INEN (1 << 1)
#define WRCONFIG_PULLEN (1 << 2)

void main(void) {
    GPIOA_WRCONFIG &= ~(WRCONFIG_PULLEN | WRCONFIG_INEN);
    GPIOA_DIR |= (1 << 2);
    GPIOA_OUT |= (1 << 2);
    asm volatile ("cpsie i");
    while(1)
        asm volatile("WFI");
}
