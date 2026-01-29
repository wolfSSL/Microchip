/* exceptions.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

int setup_interrupt_gate(int vnum, uintptr_t handler);
int setup_interrupts();
void deinit_interrupts();
void wfi();

#endif /* EXCEPTIONS_H */
