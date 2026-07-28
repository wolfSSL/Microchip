/* stm32l1_spi.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef WHAL_CFG_STM32L1_SPI_DIRECT_API_MAPPING
#define WHAL_CFG_STM32F4_SPI_DIRECT_API_MAPPING
#endif
#ifdef WHAL_CFG_STM32L1_SPI_SINGLE_INSTANCE
#define WHAL_CFG_STM32F4_SPI_SINGLE_INSTANCE
#endif
#include "stm32f4_spi.c"
