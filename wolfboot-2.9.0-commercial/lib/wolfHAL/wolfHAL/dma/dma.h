/* dma.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_DMA_H
#define WHAL_DMA_H

#include <wolfHAL/error.h>
#include <stddef.h>

/*
 * @file dma.h
 * @brief Generic DMA abstraction and driver interface.
 *
 * A DMA device represents one DMA controller. Individual channels are
 * identified by index. Channel configuration is platform-specific and
 * passed as an opaque pointer to Configure.
 *
 * Typical usage from a peripheral driver:
 *   1. whal_Dma_Init()       — enable the DMA controller
 *   2. whal_Dma_Configure()  — set up a channel (direction, width, src/dst,
 *                              buffer, length, callback, etc.)
 *   3. whal_Dma_Start()      — kick off the transfer
 *   4. whal_Dma_Stop()       — abort or clean up after completion
 *
 * The completion callback (provided in the platform-specific channel config)
 * runs in ISR context.
 */

typedef struct whal_Dma whal_Dma;

/*
 * @brief Driver vtable for DMA controllers.
 */
typedef struct {
    /* Initialize the DMA controller. */
    whal_Error (*Init)(whal_Dma *dmaDev);
    /* Deinitialize the DMA controller. */
    whal_Error (*Deinit)(whal_Dma *dmaDev);
    /* Configure a DMA channel. chCfg is platform-specific. */
    whal_Error (*Configure)(whal_Dma *dmaDev, size_t ch, const void *chCfg);
    /* Start a previously configured DMA channel. */
    whal_Error (*Start)(whal_Dma *dmaDev, size_t ch);
    /* Stop a DMA channel. */
    whal_Error (*Stop)(whal_Dma *dmaDev, size_t ch);
} whal_DmaDriver;

/*
 * @brief DMA device instance containing driver and configuration data.
 */
struct whal_Dma {
    const size_t base;
    const whal_DmaDriver *driver;
    const void *cfg;
};

/*
 * @brief Initialize a DMA controller.
 *
 * @param dmaDev DMA instance to initialize.
 *
 * @retval WHAL_SUCCESS Init completed.
 * @retval WHAL_EINVAL  Null pointer or missing driver function.
 */
whal_Error whal_Dma_Init(whal_Dma *dmaDev);
/*
 * @brief Deinitialize a DMA controller.
 *
 * @param dmaDev DMA instance to deinitialize.
 *
 * @retval WHAL_SUCCESS Deinit completed.
 * @retval WHAL_EINVAL  Null pointer or missing driver function.
 */
whal_Error whal_Dma_Deinit(whal_Dma *dmaDev);
/*
 * @brief Configure a DMA channel.
 *
 * @param dmaDev DMA controller instance.
 * @param ch     Channel index.
 * @param chCfg  Platform-specific channel configuration.
 *
 * @retval WHAL_SUCCESS Channel configured.
 * @retval WHAL_EINVAL  Null pointer, missing driver function, or bad config.
 */
whal_Error whal_Dma_Configure(whal_Dma *dmaDev, size_t ch, const void *chCfg);
/*
 * @brief Start a previously configured DMA channel.
 *
 * @param dmaDev DMA controller instance.
 * @param ch     Channel index.
 *
 * @retval WHAL_SUCCESS Transfer started.
 * @retval WHAL_EINVAL  Null pointer or missing driver function.
 */
whal_Error whal_Dma_Start(whal_Dma *dmaDev, size_t ch);
/*
 * @brief Stop a DMA channel.
 *
 * @param dmaDev DMA controller instance.
 * @param ch     Channel index.
 *
 * @retval WHAL_SUCCESS Channel stopped.
 * @retval WHAL_EINVAL  Null pointer or missing driver function.
 */
whal_Error whal_Dma_Stop(whal_Dma *dmaDev, size_t ch);

#endif /* WHAL_DMA_H */
