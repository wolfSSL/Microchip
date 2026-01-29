/* uart_drv.h
 *
 * The HAL API definitions for UART driver extension.
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef H_HAL_UART_
#define H_HAL_UART_

#include <stdint.h>
int uart_tx(const uint8_t c);
int uart_rx(uint8_t *c);
int uart_init(uint32_t bitrate, uint8_t data, char parity, uint8_t stop);

#ifdef DEBUG_UART
void uart_write(const char *buf, unsigned int len);
#endif

#endif /* H_HAL_UART_ */
