/* stm32wb0_dma.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB0_DMA_H
#define WHAL_STM32WB0_DMA_H

/**
 * @file stm32wb0_dma.h
 * @brief STM32WB0 DMA driver (alias for STM32WB DMA).
 *
 * The STM32WB0 DMA controller is register-compatible with the STM32WB
 * DMA (DMA_ISR/IFCR at 0x00/0x04, per-channel CCR/CNDTR/CPAR/CMAR at
 * 0x08 + 0x14*(ch-1)), paired with the same DMAMUX layout. The WB0
 * has a single controller with 8 channels (vs WB's DMA1+DMA2 split).
 * Boards configure cfg->numChannels = 8.
 */

#include <wolfHAL/dma/stm32wb_dma.h>

typedef whal_Stm32wb_Dma_Dir   whal_Stm32wb0_Dma_Dir;
typedef whal_Stm32wb_Dma_Width whal_Stm32wb0_Dma_Width;
typedef whal_Stm32wb_Dma_Inc   whal_Stm32wb0_Dma_Inc;
typedef whal_Stm32wb_Dma_ChCfg whal_Stm32wb0_Dma_ChCfg;
typedef whal_Stm32wb_Dma_Cfg   whal_Stm32wb0_Dma_Cfg;
typedef whal_Stm32wb_Dma_Callback whal_Stm32wb0_Dma_Callback;

#define whal_Stm32wb0_Dma_Dev whal_Stm32wb_Dma_Dev

#ifndef WHAL_CFG_STM32WB0_DMA_DIRECT_API_MAPPING
#define whal_Stm32wb0_Dma_Driver     whal_Stm32wb_Dma_Driver
#define whal_Stm32wb0_Dma_Init       whal_Stm32wb_Dma_Init
#define whal_Stm32wb0_Dma_Deinit     whal_Stm32wb_Dma_Deinit
#define whal_Stm32wb0_Dma_Configure  whal_Stm32wb_Dma_Configure
#define whal_Stm32wb0_Dma_Start      whal_Stm32wb_Dma_Start
#define whal_Stm32wb0_Dma_Stop       whal_Stm32wb_Dma_Stop
#endif /* !WHAL_CFG_STM32WB0_DMA_DIRECT_API_MAPPING */

#define whal_Stm32wb0_Dma_IRQHandler whal_Stm32wb_Dma_IRQHandler

/* Enum-value aliases. */
#define WHAL_STM32WB0_DMA_DIR_PERIPH_TO_MEM WHAL_STM32WB_DMA_DIR_PERIPH_TO_MEM
#define WHAL_STM32WB0_DMA_DIR_MEM_TO_PERIPH WHAL_STM32WB_DMA_DIR_MEM_TO_PERIPH
#define WHAL_STM32WB0_DMA_DIR_MEM_TO_MEM    WHAL_STM32WB_DMA_DIR_MEM_TO_MEM
#define WHAL_STM32WB0_DMA_WIDTH_8BIT        WHAL_STM32WB_DMA_WIDTH_8BIT
#define WHAL_STM32WB0_DMA_WIDTH_16BIT       WHAL_STM32WB_DMA_WIDTH_16BIT
#define WHAL_STM32WB0_DMA_WIDTH_32BIT       WHAL_STM32WB_DMA_WIDTH_32BIT
#define WHAL_STM32WB0_DMA_INC_DISABLE       WHAL_STM32WB_DMA_INC_DISABLE
#define WHAL_STM32WB0_DMA_INC_ENABLE        WHAL_STM32WB_DMA_INC_ENABLE

/* Config initializer macro alias. The WB0 board.h supplies the body under
 * the WB0-prefixed name; the WB driver source consumes the WB name. */
#define WHAL_CFG_STM32WB_DMA_DEV WHAL_CFG_STM32WB0_DMA_DEV

#endif /* WHAL_STM32WB0_DMA_H */
