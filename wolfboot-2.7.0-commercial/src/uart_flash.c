/* uart_flash.c
 *
 * Generic implementation of the read/write/erase
 * functionalities, on top of the spi_drv_*.c API.
 *
 * This interface creates the communication to access an emulated
 * non-volatile memory, hosted on a remote machine, through the UART 
 * interface.
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

#ifdef UART_FLASH

#include "wolfboot/wolfboot.h"
#include "hal.h"
#include <stdint.h>
#include <string.h>

#define CMD_HDR_WOLF  'W'
#define CMD_HDR_WRITE 0x01
#define CMD_HDR_READ  0x02
#define CMD_HDR_ERASE 0x03
#define CMD_ACK       0x06

#define WAIT_CYCLES 500000
#define ERASE_TIMEOUT 5
#define READ_TIMEOUT 1

int uart_tx(const uint8_t c);
int uart_rx(uint8_t *c);

static int wait_ack(void)
{
    volatile int count = 0;
    while(++count < WAIT_CYCLES) {
        uint8_t c;
        if ((uart_rx(&c) == 1) && (c == CMD_ACK))
            return 0;
    }
    return -1;
}

static int uart_rx_timeout(uint8_t *c)
{
    volatile int count = 0;
    while(++count < (WAIT_CYCLES * READ_TIMEOUT)) {
        if (uart_rx(c) == 1) /* Success */
           return 0;
    }
    *c = 0x00;
    return -1;
}


int  ext_flash_write(uintptr_t address, const uint8_t *data, int len)
{
    int i;
    uint8_t cmd[10];
    cmd[0] = CMD_HDR_WOLF;
    cmd[1] = CMD_HDR_WRITE;
    cmd[2] = address & 0xFF;
    cmd[3] = (address >> 8) & 0xFF;
    cmd[4] = (address >> 16) & 0xFF;
    cmd[5] = (address >> 24) & 0xFF;
    cmd[6] = len & 0xFF;
    cmd[7] = (len >> 8) & 0xFF;
    cmd[8] = (len >> 16) & 0xFF;
    cmd[9] = (len >> 24) & 0xFF;
    for (i = 0; i < 10; i++) {
        uart_tx(cmd[i]);
        if (wait_ack() != 0)
            return -1;
    }
    for (i = 0; i < len; i++) {
        uart_tx(data[i]);
        if (wait_ack() != 0)
            return -1;
    }
    return len;
}

int  ext_flash_read(uintptr_t address, uint8_t *data, int len)
{
    int i;
    uint8_t cmd[10];
    cmd[0] = CMD_HDR_WOLF;
    cmd[1] = CMD_HDR_READ;
    cmd[2] = address & 0xFF;
    cmd[3] = (address >> 8) & 0xFF;
    cmd[4] = (address >> 16) & 0xFF;
    cmd[5] = (address >> 24) & 0xFF;
    cmd[6] = len & 0xFF;
    cmd[7] = (len >> 8) & 0xFF;
    cmd[8] = (len >> 16) & 0xFF;
    cmd[9] = (len >> 24) & 0xFF;
    for (i = 0; i < 10; i++) {
        uart_tx(cmd[i]);
        if (wait_ack() != 0)
            return -1;
    }
    for (i = 0; i < len; i++) {
        if (uart_rx_timeout(&data[i]) != 0)
            return 0;
        uart_tx(CMD_ACK);
    }
    return i;
}

int  ext_flash_erase(uintptr_t address, int len)
{
    int i;
    uint8_t cmd[10];
    cmd[0] = CMD_HDR_WOLF;
    cmd[1] = CMD_HDR_ERASE;
    cmd[2] = address & 0xFF;
    cmd[3] = (address >> 8) & 0xFF;
    cmd[4] = (address >> 16) & 0xFF;
    cmd[5] = (address >> 24) & 0xFF;
    cmd[6] = len & 0xFF;
    cmd[7] = (len >> 8) & 0xFF;
    cmd[8] = (len >> 16) & 0xFF;
    cmd[9] = (len >> 24) & 0xFF;
    for (i = 0; i < 10; i++) {
        uart_tx(cmd[i]);
        if (wait_ack() != 0)
            return -1;
    }
    /* Wait for extra ack at the end of Erase */
    if (wait_ack() == 0)
        return 0;
    return -1;
}

void ext_flash_lock(void)
{
    wait_ack();
}

void ext_flash_unlock(void)
{
    wait_ack();
}

void uart_send_current_version(void)
{
    uint32_t version = wolfBoot_current_firmware_version();
    uart_tx('V');
    if (wait_ack() != 0)
        return;
    uart_tx(version & 0x000000FF);
    if (wait_ack() != 0)
        return;
    uart_tx((version >> 8) & 0x000000FF);
    if (wait_ack() != 0)
        return;
    uart_tx((version >> 16) & 0x000000FF);
    if (wait_ack() != 0)
        return;
    uart_tx((version >> 24) & 0x000000FF);
    if (wait_ack() != 0)
        return;
}

#endif /* UART_FLASH */
