/* spi_nor_w25q64.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "spi_nor_w25q64.h"
#include <wolfHAL/flash/spi_nor_flash.h>
#include "board.h"

/*
 * Winbond W25Q64 — 64 Mbit (8 MB) SPI-NOR Flash
 *
 * - Page size:   256 bytes
 * - Sector size: 4 KB (smallest erasable unit)
 * - Capacity:    8,388,608 bytes (8 MB)
 * - SPI modes 0 and 3, up to 104 MHz (standard read up to 50 MHz)
 */

#define W25Q64_PAGE_SZ  256
#define W25Q64_CAPACITY (8 * 1024 * 1024) /* 8 MB */

static whal_Spi_ComCfg g_w25q64ComCfg = {
    .freq = 25000000, /* 25 MHz */
    .mode = WHAL_SPI_MODE_0,
    .wordSz = 8,
    .dataLines = 1,
};

whal_Flash g_whalSpiNorW25q64 = {
    .driver = &whal_SpiNor_Driver,
    .cfg = &(whal_SpiNor_Cfg) {
        .spiDev = BOARD_SPI_DEV,
        .spiComCfg = &g_w25q64ComCfg,
        .gpioDev = BOARD_GPIO_DEV,
        .csPin = SPI_CS_PIN,
        .timeout = &g_whalTimeout,
        .pageSz = W25Q64_PAGE_SZ,
        .capacity = W25Q64_CAPACITY,
    },
};
