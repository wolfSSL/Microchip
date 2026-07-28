/* stm32u5_gpdma.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32U5_GPDMA_H
#define WHAL_STM32U5_GPDMA_H

/**
 * @file stm32u5_gpdma.h
 * @brief STM32U5 GPDMA driver (alias for STM32WBA GPDMA).
 *
 * The STM32U5 GPDMA controller is register-compatible with the STM32WBA
 * GPDMA. This header re-exports the STM32WBA GPDMA driver types and symbols
 * under STM32U5-specific names.
 */

#include <wolfHAL/dma/stm32wba_gpdma.h>

typedef whal_Stm32wba_Gpdma_Dir   whal_Stm32u5_Gpdma_Dir;
typedef whal_Stm32wba_Gpdma_Width whal_Stm32u5_Gpdma_Width;
typedef whal_Stm32wba_Gpdma_Inc   whal_Stm32u5_Gpdma_Inc;
typedef whal_Stm32wba_Gpdma_ChCfg whal_Stm32u5_Gpdma_ChCfg;
typedef whal_Stm32wba_Gpdma_Cfg   whal_Stm32u5_Gpdma_Cfg;
typedef whal_Stm32wba_Gpdma_Callback whal_Stm32u5_Gpdma_Callback;

#define whal_Stm32u5_Gpdma_Dev whal_Stm32wba_Gpdma_Dev

#ifndef WHAL_CFG_STM32U5_GPDMA_DIRECT_API_MAPPING
#define whal_Stm32u5_Gpdma_Driver     whal_Stm32wba_Gpdma_Driver
#define whal_Stm32u5_Gpdma_IRQHandler whal_Stm32wba_Gpdma_IRQHandler
#endif /* !WHAL_CFG_STM32U5_GPDMA_DIRECT_API_MAPPING */

/**
 * @brief Transfer direction (re-exported from STM32WBA).
 */
#define WHAL_STM32U5_GPDMA_DIR_PERIPH_TO_MEM WHAL_STM32WBA_GPDMA_DIR_PERIPH_TO_MEM
#define WHAL_STM32U5_GPDMA_DIR_MEM_TO_PERIPH WHAL_STM32WBA_GPDMA_DIR_MEM_TO_PERIPH
#define WHAL_STM32U5_GPDMA_DIR_MEM_TO_MEM    WHAL_STM32WBA_GPDMA_DIR_MEM_TO_MEM

/**
 * @brief Data width (re-exported from STM32WBA).
 */
#define WHAL_STM32U5_GPDMA_WIDTH_8BIT  WHAL_STM32WBA_GPDMA_WIDTH_8BIT
#define WHAL_STM32U5_GPDMA_WIDTH_16BIT WHAL_STM32WBA_GPDMA_WIDTH_16BIT
#define WHAL_STM32U5_GPDMA_WIDTH_32BIT WHAL_STM32WBA_GPDMA_WIDTH_32BIT

/**
 * @brief Address increment (re-exported from STM32WBA).
 */
#define WHAL_STM32U5_GPDMA_INC_DISABLE WHAL_STM32WBA_GPDMA_INC_DISABLE
#define WHAL_STM32U5_GPDMA_INC_ENABLE  WHAL_STM32WBA_GPDMA_INC_ENABLE

#endif /* WHAL_STM32U5_GPDMA_H */
