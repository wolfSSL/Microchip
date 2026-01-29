/* spi_flash.h
 *
 * Generic implementation of the read/write/erase
 * functionalities, on top of the spi_drv.h HAL.
 *
 * Compile with SPI_FLASH=1
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

#ifndef SPI_FLASH_DRI_H
#define SPI_FLASH_DRI_H

/* SPI Configuration */
#ifndef SPI_FLASH_SECTOR_SIZE
#define SPI_FLASH_SECTOR_SIZE (4096)
#endif

#ifndef SPI_FLASH_PAGE_SIZE
#define SPI_FLASH_PAGE_SIZE   (256)
#endif

#if defined(SPI_FLASH) || defined(QSPI_FLASH) || defined(OCTOSPI_FLASH)

#include <stdint.h>

/* returns (manuf << 8 | product) */
uint16_t spi_flash_probe(void);
void spi_flash_release(void);

int spi_flash_sector_erase(uint32_t address);
int spi_flash_chip_erase(void);
int spi_flash_read(uint32_t address, void *data, int len);
int spi_flash_write(uint32_t address, const void *data, int len);

#else

#define spi_flash_probe() do{}while(0)
#define spi_flash_release() do{}while(0)

#endif /* SPI_FLASH || QSPI_FLASH || OCTOSPI_FLASH */

#endif /* !SPI_FLASH_DRI_H */
