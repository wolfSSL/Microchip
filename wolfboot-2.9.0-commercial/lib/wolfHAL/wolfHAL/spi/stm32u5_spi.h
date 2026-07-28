/* stm32u5_spi.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32U5_SPI_H
#define WHAL_STM32U5_SPI_H

/**
 * @file stm32u5_spi.h
 * @brief STM32U5 SPI driver (alias for STM32H5 SPI).
 *
 * The STM32U5 SPI peripheral is register-compatible with the STM32H5 SPI
 * (V2 SPI). This header re-exports the STM32H5 SPI driver types and symbols
 * under STM32U5-specific names.
 */

#include <wolfHAL/spi/stm32h5_spi.h>

typedef whal_Stm32h5_Spi_Cfg whal_Stm32u5_Spi_Cfg;

#ifndef WHAL_CFG_STM32U5_SPI_DIRECT_API_MAPPING
#define whal_Stm32u5_Spi_Driver   whal_Stm32h5_Spi_Driver
#define whal_Stm32u5_Spi_Init     whal_Stm32h5_Spi_Init
#define whal_Stm32u5_Spi_Deinit   whal_Stm32h5_Spi_Deinit
#define whal_Stm32u5_Spi_StartCom whal_Stm32h5_Spi_StartCom
#define whal_Stm32u5_Spi_EndCom   whal_Stm32h5_Spi_EndCom
#define whal_Stm32u5_Spi_SendRecv whal_Stm32h5_Spi_SendRecv
#endif /* !WHAL_CFG_STM32U5_SPI_DIRECT_API_MAPPING */

#endif /* WHAL_STM32U5_SPI_H */
