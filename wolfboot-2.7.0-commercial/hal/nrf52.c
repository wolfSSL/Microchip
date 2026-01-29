/* nrf52.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef TARGET_nrf52

#include <stdint.h>
#include "image.h"
#include "nrf52.h"

#ifdef DEBUG_UART
void uart_init(void)
{
    UART0_BAUDRATE = BAUD_115200;
    UART0_ENABLE = 1;
}

static void uart_write_char(char c)
{
    UART0_EVENT_ENDTX = 0;

    UART0_TXD_PTR = (uint32_t)(&c);
    UART0_TXD_MAXCOUNT = 1;
    UART0_TASK_STARTTX = 1;
    while(UART0_EVENT_ENDTX == 0)
        ;
}

void uart_write(const char* buf, unsigned int sz)
{
    uint32_t pos = 0;
    while (sz-- > 0) {
        char c = buf[pos++];
        if (c == '\n') { /* handle CRLF */
            uart_write_char('\r');
        }
        uart_write_char(c);
    }
}
#endif /* DEBUG_UART */

static void RAMFUNCTION flash_wait_complete(void)
{
    while (NVMC_READY == 0)
        ;
}

int RAMFUNCTION hal_flash_write(uint32_t address, const uint8_t *data, int len)
{
    int i = 0;
    uint32_t *src, *dst;

    while (i < len) {
        if ((len - i > 3) && ((((address + i) & 0x03) == 0)  && ((((uint32_t)data) + i) & 0x03) == 0)) {
            src = (uint32_t *)data;
            dst = (uint32_t *)address;
            NVMC_CONFIG = NVMC_CONFIG_WEN;
            flash_wait_complete();
            dst[i >> 2] = src[i >> 2];
            flash_wait_complete();
            i+=4;
        } else {
            uint32_t val;
            uint8_t *vbytes = (uint8_t *)(&val);
            int off = (address + i) - (((address + i) >> 2) << 2);
            dst = (uint32_t *)(address - off);
            val = dst[i >> 2];
            vbytes[off] = data[i];
            NVMC_CONFIG = NVMC_CONFIG_WEN;
            flash_wait_complete();
            dst[i >> 2] = val;
            flash_wait_complete();
            i++;
        }
    }
    return 0;
}

void RAMFUNCTION hal_flash_unlock(void)
{
}

void RAMFUNCTION hal_flash_lock(void)
{
}


int RAMFUNCTION hal_flash_erase(uint32_t address, int len)
{
    uint32_t end = address + len - 1;
    uint32_t p;
    for (p = address; p <= end; p += FLASH_PAGE_SIZE) {
        NVMC_CONFIG = NVMC_CONFIG_EEN;
        flash_wait_complete();
        NVMC_ERASEPAGE = p;
        flash_wait_complete();
    }
    return 0;
}

void hal_init(void)
{
    TASKS_HFCLKSTART = 1;
    while(TASKS_HFCLKSTARTED == 0)
        ;
}

void hal_prepare_boot(void)
{
#ifdef WOLFBOOT_RESTORE_CLOCK
    TASKS_HFCLKSTOP = 1;
#endif
}

#endif /* TARGET_nrf52 */
