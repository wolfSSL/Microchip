/* stm32wb_uart_dma.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#ifdef WHAL_CFG_STM32WB_UART_DMA_SINGLE_INSTANCE
#include "board.h"  /* provides whal_Stm32wb_UartDma_Dev singleton */
#endif
#include <wolfHAL/uart/stm32wb_uart_dma.h>
#include <wolfHAL/uart/uart.h>
#include <wolfHAL/error.h>
#include <wolfHAL/reg.h>
#include <wolfHAL/bitops.h>
#include <wolfHAL/timeout.h>

#define UART_CR3_REG 0x08

#define UART_CR3_DMAR_Pos 6
#define UART_CR3_DMAR_Msk (1UL << UART_CR3_DMAR_Pos)

#define UART_CR3_DMAT_Pos 7
#define UART_CR3_DMAT_Msk (1UL << UART_CR3_DMAT_Pos)

#define UART_ISR_REG 0x1C
#define UART_ISR_TC_Pos 6
#define UART_ISR_TC_Msk (1UL << UART_ISR_TC_Pos)

#define UART_RDR_REG 0x24

#define UART_TDR_REG 0x28

#if defined(WHAL_CFG_STM32WB_UART_DIRECT_API_MAPPING) || \
    defined(WHAL_CFG_STM32WB_UART_DMA_DIRECT_API_MAPPING)
#define whal_Stm32wb_Uart_Init   whal_Uart_Init
#define whal_Stm32wb_Uart_Deinit whal_Uart_Deinit
#endif

#ifdef WHAL_CFG_STM32WB_UART_DMA_DIRECT_API_MAPPING
#define whal_Stm32wb_UartDma_Send      whal_Uart_Send
#define whal_Stm32wb_UartDma_Recv      whal_Uart_Recv
#define whal_Stm32wb_UartDma_SendAsync whal_Uart_SendAsync
#define whal_Stm32wb_UartDma_RecvAsync whal_Uart_RecvAsync
#endif /* WHAL_CFG_STM32WB_UART_DMA_DIRECT_API_MAPPING */

#ifdef WHAL_CFG_STM32WB_UART_DMA_SINGLE_INSTANCE
const whal_Uart whal_Stm32wb_UartDma_Dev = WHAL_CFG_STM32WB_UART_DMA_DEV;
#endif

whal_Error whal_Stm32wb_UartDma_SendAsync(whal_Uart *uartDev, const void *data,
                                         size_t dataSz)
{
    whal_Error err;
#ifdef WHAL_CFG_STM32WB_UART_DMA_SINGLE_INSTANCE
    whal_Stm32wb_UartDma_Cfg *cfg =
        (whal_Stm32wb_UartDma_Cfg *)whal_Stm32wb_UartDma_Dev.cfg;
    size_t base = whal_Stm32wb_UartDma_Dev.base;
    (void)uartDev;

    if (!data || dataSz > UINT16_MAX)
        return WHAL_EINVAL;
#else
    whal_Stm32wb_UartDma_Cfg *cfg;
    size_t base;

    if (!uartDev || !uartDev->cfg || !data || dataSz > UINT16_MAX)
        return WHAL_EINVAL;

    cfg = (whal_Stm32wb_UartDma_Cfg *)uartDev->cfg;
    base = uartDev->base;
#endif

    if (dataSz == 0)
        return WHAL_SUCCESS;

    if (cfg->txResult == WHAL_ENOTREADY)
        return WHAL_ENOTREADY;

    cfg->txChCfg->srcAddr = (uint32_t)(uintptr_t)data;
    cfg->txChCfg->dstAddr = (uint32_t)(base + UART_TDR_REG);
    cfg->txChCfg->length = dataSz;

    cfg->txResult = WHAL_ENOTREADY;

    err = whal_Dma_Configure(cfg->dma, cfg->txCh, cfg->txChCfg);
    if (err) {
        cfg->txResult = err;
        return err;
    }

    whal_Reg_Update(base, UART_CR3_REG, UART_CR3_DMAT_Msk,
                    UART_CR3_DMAT_Msk);

    err = whal_Dma_Start(cfg->dma, cfg->txCh);
    if (err) {
        whal_Reg_Update(base, UART_CR3_REG, UART_CR3_DMAT_Msk, 0);
        cfg->txResult = err;
        return err;
    }

    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb_UartDma_RecvAsync(whal_Uart *uartDev, void *data,
                                         size_t dataSz)
{
    whal_Error err;
#ifdef WHAL_CFG_STM32WB_UART_DMA_SINGLE_INSTANCE
    whal_Stm32wb_UartDma_Cfg *cfg =
        (whal_Stm32wb_UartDma_Cfg *)whal_Stm32wb_UartDma_Dev.cfg;
    size_t base = whal_Stm32wb_UartDma_Dev.base;
    (void)uartDev;

    if (!data || dataSz > UINT16_MAX)
        return WHAL_EINVAL;
#else
    whal_Stm32wb_UartDma_Cfg *cfg;
    size_t base;

    if (!uartDev || !uartDev->cfg || !data || dataSz > UINT16_MAX)
        return WHAL_EINVAL;

    cfg = (whal_Stm32wb_UartDma_Cfg *)uartDev->cfg;
    base = uartDev->base;
#endif

    if (dataSz == 0)
        return WHAL_SUCCESS;

    if (cfg->rxResult == WHAL_ENOTREADY)
        return WHAL_ENOTREADY;

    cfg->rxChCfg->srcAddr = (uint32_t)(base + UART_RDR_REG);
    cfg->rxChCfg->dstAddr = (uint32_t)(uintptr_t)data;
    cfg->rxChCfg->length = dataSz;

    cfg->rxResult = WHAL_ENOTREADY;

    err = whal_Dma_Configure(cfg->dma, cfg->rxCh, cfg->rxChCfg);
    if (err) {
        cfg->rxResult = err;
        return err;
    }

    whal_Reg_Update(base, UART_CR3_REG, UART_CR3_DMAR_Msk,
                    UART_CR3_DMAR_Msk);

    err = whal_Dma_Start(cfg->dma, cfg->rxCh);
    if (err) {
        whal_Reg_Update(base, UART_CR3_REG, UART_CR3_DMAR_Msk, 0);
        cfg->rxResult = err;
        return err;
    }

    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb_UartDma_Send(whal_Uart *uartDev, const void *data,
                                    size_t dataSz)
{
    whal_Stm32wb_UartDma_Cfg *cfg;
    size_t base;
    whal_Error err;

    err = whal_Stm32wb_UartDma_SendAsync(uartDev, data, dataSz);
    if (err)
        return err;

#ifdef WHAL_CFG_STM32WB_UART_DMA_SINGLE_INSTANCE
    cfg = (whal_Stm32wb_UartDma_Cfg *)whal_Stm32wb_UartDma_Dev.cfg;
    base = whal_Stm32wb_UartDma_Dev.base;
#else
    cfg = (whal_Stm32wb_UartDma_Cfg *)uartDev->cfg;
    base = uartDev->base;
#endif

    WHAL_TIMEOUT_START(cfg->base.timeout);
    while (cfg->txResult == WHAL_ENOTREADY) {
        if (WHAL_TIMEOUT_EXPIRED(cfg->base.timeout)) {
            err = WHAL_ETIMEOUT;
            goto cleanup;
        }
    }

    if (cfg->txResult != WHAL_SUCCESS) {
        err = cfg->txResult;
        goto cleanup;
    }

    err = whal_Reg_ReadPoll(base, UART_ISR_REG,
                            UART_ISR_TC_Msk, UART_ISR_TC_Msk, cfg->base.timeout);

cleanup:
    whal_Dma_Stop(cfg->dma, cfg->txCh);
    whal_Reg_Update(base, UART_CR3_REG, UART_CR3_DMAT_Msk, 0);
    cfg->txResult = err;

    return err;
}

whal_Error whal_Stm32wb_UartDma_Recv(whal_Uart *uartDev, void *data,
                                     size_t dataSz)
{
    whal_Stm32wb_UartDma_Cfg *cfg;
    size_t base;
    whal_Error err;

    err = whal_Stm32wb_UartDma_RecvAsync(uartDev, data, dataSz);
    if (err)
        return err;

#ifdef WHAL_CFG_STM32WB_UART_DMA_SINGLE_INSTANCE
    cfg = (whal_Stm32wb_UartDma_Cfg *)whal_Stm32wb_UartDma_Dev.cfg;
    base = whal_Stm32wb_UartDma_Dev.base;
#else
    cfg = (whal_Stm32wb_UartDma_Cfg *)uartDev->cfg;
    base = uartDev->base;
#endif

    WHAL_TIMEOUT_START(cfg->base.timeout);
    while (cfg->rxResult == WHAL_ENOTREADY) {
        if (WHAL_TIMEOUT_EXPIRED(cfg->base.timeout)) {
            err = WHAL_ETIMEOUT;
            goto cleanup;
        }
    }

    err = cfg->rxResult;

cleanup:
    whal_Dma_Stop(cfg->dma, cfg->rxCh);
    whal_Reg_Update(base, UART_CR3_REG, UART_CR3_DMAR_Msk, 0);
    cfg->rxResult = err;

    return err;
}

void whal_Stm32wb_UartDma_TxCallback(void *ctx, whal_Error err)
{
    whal_Stm32wb_UartDma_Cfg *cfg = (whal_Stm32wb_UartDma_Cfg *)ctx;
    cfg->txResult = err;
}

void whal_Stm32wb_UartDma_RxCallback(void *ctx, whal_Error err)
{
    whal_Stm32wb_UartDma_Cfg *cfg = (whal_Stm32wb_UartDma_Cfg *)ctx;
    cfg->rxResult = err;
}

#ifndef WHAL_CFG_STM32WB_UART_DMA_DIRECT_API_MAPPING
const whal_UartDriver whal_Stm32wb_UartDma_Driver = {
    .Init = whal_Stm32wb_Uart_Init,
    .Deinit = whal_Stm32wb_Uart_Deinit,
    .Send = whal_Stm32wb_UartDma_Send,
    .Recv = whal_Stm32wb_UartDma_Recv,
    .SendAsync = whal_Stm32wb_UartDma_SendAsync,
    .RecvAsync = whal_Stm32wb_UartDma_RecvAsync,
};
#endif /* !WHAL_CFG_STM32WB_UART_DMA_DIRECT_API_MAPPING */
