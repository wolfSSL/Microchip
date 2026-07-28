/* wolfhal.c
 *
 * Generic wolfHAL port for wolfBoot. wolfBoot's HAL contract
 * (hal_flash_*, uart_write) is satisfied here by forwarding to the
 * wolfHAL API. The chip drivers behind the wolfHAL API are singletons,
 * instantiated by the driver .c files from initializer macros in
 * board.h; this file passes the BOARD_*_DEV handles defined there.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include "hal.h"
#include "wolfboot/wolfboot.h"
#include "board.h"

void RAMFUNCTION hal_flash_unlock(void)
{
    whal_Flash_Unlock(BOARD_FLASH_DEV, 0, 0);
}

void RAMFUNCTION hal_flash_lock(void)
{
    whal_Flash_Lock(BOARD_FLASH_DEV, 0, 0);
}

int RAMFUNCTION hal_flash_write(uint32_t address, const uint8_t *data, int len)
{
    return whal_Flash_Write(BOARD_FLASH_DEV, (size_t)address, data, (size_t)len);
}

int RAMFUNCTION hal_flash_erase(uint32_t address, int len)
{
    return whal_Flash_Erase(BOARD_FLASH_DEV, (size_t)address, (size_t)len);
}

#ifdef DEBUG_UART
void uart_write(const char *buf, unsigned int len)
{
    whal_Uart_Send(BOARD_UART_DEV, (const uint8_t *)buf, (size_t)len);
}
#endif
