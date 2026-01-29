/* uart_flash.h
 *
 * Generic implementation of the read/write/erase
 * functionalities, on top of the uart_drv_*.h HAL.
 *
 * Compile with UART_FLASH=1
 *
 * Use tools/ufserver on the host to provide a remote
 * emulated non-volatile image via UART.
 *
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef UART_FLASH_DRI_H
#define UART_FLASH_DRI_H
#include <stdint.h>
#include "uart_drv.h"

#ifdef UART_FLASH
    #ifndef UART_FLASH_BITRATE
      #define UART_FLASH_BITRATE 115200
    #endif
    void uart_send_current_version(void);
#else
    #define uart_send_current_version() do{}while(0)
#endif /* UART_FLASH */

#endif /* !UART_FLASH_DRI_H */
