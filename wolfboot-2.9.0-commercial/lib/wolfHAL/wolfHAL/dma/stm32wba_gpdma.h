/* stm32wba_gpdma.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WBA_GPDMA_H
#define WHAL_STM32WBA_GPDMA_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/dma/dma.h>
#include <wolfHAL/timeout.h>

/*
 * @file stm32wba_gpdma.h
 * @brief STM32WBA GPDMA controller driver configuration types.
 *
 * The GPDMA (General Purpose DMA) controller provides 8 independent
 * channels supporting memory-to-memory, memory-to-peripheral, and
 * peripheral-to-memory transfers.
 *
 * This driver supports direct-programming mode for run-to-completion
 * transfers. Linked-list mode is not supported.
 *
 * Each channel occupies 0x80 bytes starting at offset 0x50 from the
 * GPDMA base address.
 */

/*
 * @brief Transfer direction.
 */
typedef enum {
    WHAL_STM32WBA_GPDMA_DIR_PERIPH_TO_MEM, /* Peripheral to memory */
    WHAL_STM32WBA_GPDMA_DIR_MEM_TO_PERIPH, /* Memory to peripheral */
    WHAL_STM32WBA_GPDMA_DIR_MEM_TO_MEM,    /* Software request memory-to-memory */
} whal_Stm32wba_Gpdma_Dir;

/*
 * @brief Data width for transfers.
 */
typedef enum {
    WHAL_STM32WBA_GPDMA_WIDTH_8BIT  = 0,
    WHAL_STM32WBA_GPDMA_WIDTH_16BIT = 1,
    WHAL_STM32WBA_GPDMA_WIDTH_32BIT = 2,
} whal_Stm32wba_Gpdma_Width;

/*
 * @brief Address increment mode.
 */
typedef enum {
    WHAL_STM32WBA_GPDMA_INC_DISABLE = 0, /* Fixed address */
    WHAL_STM32WBA_GPDMA_INC_ENABLE  = 1, /* Incremented address */
} whal_Stm32wba_Gpdma_Inc;

/*
 * @brief Per-channel transfer configuration.
 *
 * For hardware-paced transfers, reqSel selects the peripheral request line
 * (REQSEL[5:0] from TRM Table 208 - e.g. 11=USART1_RX, 12=USART1_TX).
 */
typedef struct {
    whal_Stm32wba_Gpdma_Dir dir;
    size_t srcAddr;
    size_t dstAddr;
    size_t nbytes;                   /* Byte count (max 65535) */
    whal_Stm32wba_Gpdma_Width srcWidth;
    whal_Stm32wba_Gpdma_Width dstWidth;
    whal_Stm32wba_Gpdma_Inc srcInc;
    whal_Stm32wba_Gpdma_Inc dstInc;
    uint8_t reqSel;                  /* REQSEL[5:0] (ignored for MEM_TO_MEM) */
} whal_Stm32wba_Gpdma_ChCfg;

/*
 * @brief Controller-level configuration.
 */
typedef struct {
    uint8_t numChannels;     /* 8 for the STM32WBA GPDMA1 controller */
    whal_Timeout *timeout;   /* Timeout for channel reset/suspend polling */
} whal_Stm32wba_Gpdma_Cfg;

/*
 * @brief Single-instance device struct. Defined in the driver TU
 * from the WHAL_CFG_STM32WBA_GPDMA_DEV initializer in board.h.
 */
#if defined(WHAL_CFG_STM32WBA_GPDMA_SINGLE_INSTANCE) || \
    defined(WHAL_CFG_STM32N6_GPDMA_SINGLE_INSTANCE)
extern const whal_Dma whal_Stm32wba_Gpdma_Dev;
#endif

extern const whal_DmaDriver whal_Stm32wba_Gpdma_Driver;

/*
 * @brief DMA completion callback invoked from the channel IRQ handler.
 */
typedef void (*whal_Stm32wba_Gpdma_Callback)(void *ctx, whal_Error err);

/*
 * @brief Handle a GPDMA channel interrupt.
 *
 * Clears TCF/error flags and invokes the callback with the completion status.
 */
void whal_Stm32wba_Gpdma_IRQHandler(whal_Dma *dmaDev, size_t ch,
                                    whal_Stm32wba_Gpdma_Callback cb, void *ctx);

#endif /* WHAL_STM32WBA_GPDMA_H */
