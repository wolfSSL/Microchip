/* spi_drv_zynq.c
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
#include "spi_drv.h"
#include "spi_drv_zynq.h"

#ifdef TARGET_zynq

#if defined(SPI_FLASH) || defined(WOLFBOOT_TPM)

void spi_cs_off(uint32_t base, int pin)
{
    (void)base;
    (void)pin;
}

void spi_cs_on(uint32_t base, int pin)
{
    (void)base;
    (void)pin;
}

uint8_t spi_read(void)
{
    return 0;
}

void spi_write(const char byte)
{

}


void spi_init(int polarity, int phase)
{
    static int initialized = 0;
    if (!initialized) {
        initialized++;

        (void)polarity;
        (void)phase;
    }
}

void spi_release(void)
{

}

#ifdef WOLFBOOT_TPM
int spi_xfer(int cs, const uint8_t* tx, uint8_t* rx, uint32_t sz, int flags)
{
    uint32_t i;
    spi_cs_on(SPI_CS_TPM_PIO_BASE, cs);
    for (i = 0; i < sz; i++) {
        spi_write((const char)tx[i]);
        rx[i] = spi_read();
    }
    if (!(flags & SPI_XFER_FLAG_CONTINUE)) {
        spi_cs_off(SPI_CS_TPM_PIO_BASE, cs);
    }
    return 0;
}
#endif /* WOLFBOOT_TPM */

#endif /* SPI_FLASH | WOLFBOOT_TPM */
#endif /* TARGET_zynq */
