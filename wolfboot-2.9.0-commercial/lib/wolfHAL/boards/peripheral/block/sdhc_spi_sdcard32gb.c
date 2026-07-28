/* sdhc_spi_sdcard32gb.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "sdhc_spi_sdcard32gb.h"
#include <wolfHAL/block/sdhc_spi_block.h>
#include "board.h"

static whal_Spi_ComCfg g_sdcardComCfg = {
    .freq = 25000000, /* 25 MHz */
    .mode = WHAL_SPI_MODE_0,
    .wordSz = 8,
    .dataLines = 1,
};

whal_Block g_whalSdhcSpiSdcard32gb = {
    .driver = &whal_SdhcSpi_Driver,
    .cfg = &(whal_SdhcSpi_Cfg) {
        .spiDev = BOARD_SPI_DEV,
        .spiComCfg = &g_sdcardComCfg,
        .gpioDev = BOARD_GPIO_DEV,
        .csPin = SPI_CS_PIN,
        .timeout = &g_whalTimeout,
    },
};
