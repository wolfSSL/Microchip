/* emu_app.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef EMU_APP_H
#define EMU_APP_H

#include <stdint.h>

void emu_uart_init(void);
int emu_uart_read(uint8_t *c);
void emu_uart_write(uint8_t c);

#endif /* EMU_APP_H */
