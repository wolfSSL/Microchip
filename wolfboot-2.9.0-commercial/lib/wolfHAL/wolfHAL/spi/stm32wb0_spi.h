/* stm32wb0_spi.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB0_SPI_H
#define WHAL_STM32WB0_SPI_H

/**
 * @file stm32wb0_spi.h
 * @brief STM32WB0 SPI driver (alias for STM32WB SPI).
 *
 * The STM32WB0 SPI3 peripheral is register-compatible with the STM32WB
 * SPI (V1 SPI: CR1 layout with CPHA=0, CPOL=1, MSTR=2, BR[2:0]=3..5,
 * SPE=6, SSI=8, SSM=9; CR2 with DS=8..11, FRXTH=12; SR with RXNE=0,
 * TXE=1, BSY=7; DR at 0x0C). This header re-exports the STM32WB SPI
 * driver types and symbols under STM32WB0-specific names.
 */

#include <wolfHAL/spi/stm32wb_spi.h>

typedef whal_Stm32wb_Spi_Cfg whal_Stm32wb0_Spi_Cfg;

#define whal_Stm32wb0_Spi_Dev whal_Stm32wb_Spi_Dev

#ifndef WHAL_CFG_STM32WB0_SPI_DIRECT_API_MAPPING
#define whal_Stm32wb0_Spi_Driver   whal_Stm32wb_Spi_Driver
#define whal_Stm32wb0_Spi_Init     whal_Stm32wb_Spi_Init
#define whal_Stm32wb0_Spi_Deinit   whal_Stm32wb_Spi_Deinit
#define whal_Stm32wb0_Spi_StartCom whal_Stm32wb_Spi_StartCom
#define whal_Stm32wb0_Spi_EndCom   whal_Stm32wb_Spi_EndCom
#define whal_Stm32wb0_Spi_SendRecv whal_Stm32wb_Spi_SendRecv
#endif /* !WHAL_CFG_STM32WB0_SPI_DIRECT_API_MAPPING */

/* Config initializer macro alias. The WB0 board.h supplies the body under
 * the WB0-prefixed name; the WB driver source consumes the WB name. */
#define WHAL_CFG_STM32WB_SPI_DEV WHAL_CFG_STM32WB0_SPI_DEV

#endif /* WHAL_STM32WB0_SPI_H */
