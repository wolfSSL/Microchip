/* stm32wb_spi.c
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
#ifdef WHAL_CFG_STM32WB_SPI_SINGLE_INSTANCE
#include "board.h"  /* provides whal_Stm32wb_Spi_Dev singleton (possibly via platform alias macro) */
#endif
#include <wolfHAL/spi/stm32wb_spi.h>
#include <wolfHAL/spi/spi.h>
#include <wolfHAL/error.h>
#include <wolfHAL/reg.h>
#include <wolfHAL/bitops.h>

/*
 * STM32WB SPI Register Definitions
 *
 * The SPI peripheral provides full-duplex synchronous serial communication.
 * This driver configures it in master mode with software slave management
 * and 8-bit data frames.
 */

/* Control Register 1 - master config, clock, enable */
#define SPI_CR1_REG  0x00
#define SPI_CR1_CPHA_Pos 0                                              /* Clock phase */
#define SPI_CR1_CPHA_Msk (1UL << SPI_CR1_CPHA_Pos)

#define SPI_CR1_CPOL_Pos 1                                              /* Clock polarity */
#define SPI_CR1_CPOL_Msk (1UL << SPI_CR1_CPOL_Pos)

#define SPI_CR1_MSTR_Pos 2                                              /* Master selection */
#define SPI_CR1_MSTR_Msk (1UL << SPI_CR1_MSTR_Pos)

#define SPI_CR1_BR_Pos   3                                              /* Baud rate prescaler */
#define SPI_CR1_BR_Msk   (WHAL_BITMASK(3) << SPI_CR1_BR_Pos)

#define SPI_CR1_SPE_Pos  6                                              /* SPI enable */
#define SPI_CR1_SPE_Msk  (1UL << SPI_CR1_SPE_Pos)

#define SPI_CR1_SSI_Pos  8                                              /* Internal slave select */
#define SPI_CR1_SSI_Msk  (1UL << SPI_CR1_SSI_Pos)

#define SPI_CR1_SSM_Pos  9                                              /* Software slave management */
#define SPI_CR1_SSM_Msk  (1UL << SPI_CR1_SSM_Pos)

/* Control Register 2 - data size, FIFO threshold */
#define SPI_CR2_REG   0x04
#define SPI_CR2_DS_Pos    8                                             /* Data size (0111 = 8-bit) */
#define SPI_CR2_DS_Msk    (WHAL_BITMASK(4) << SPI_CR2_DS_Pos)

#define SPI_CR2_FRXTH_Pos 12                                           /* FIFO reception threshold */
#define SPI_CR2_FRXTH_Msk (1UL << SPI_CR2_FRXTH_Pos)

/* Status Register */
#define SPI_SR_REG  0x08
#define SPI_SR_RXNE_Pos 0                                               /* Receive buffer not empty */
#define SPI_SR_RXNE_Msk (1UL << SPI_SR_RXNE_Pos)

#define SPI_SR_TXE_Pos  1                                               /* Transmit buffer empty */
#define SPI_SR_TXE_Msk  (1UL << SPI_SR_TXE_Pos)

#define SPI_SR_BSY_Pos  7                                               /* Busy flag */
#define SPI_SR_BSY_Msk  (1UL << SPI_SR_BSY_Pos)

/* Data Register - 8/16-bit access */
#define SPI_DR_REG  0x0C
#define SPI_DR_Pos 0
#define SPI_DR_Msk (WHAL_BITMASK(8) << SPI_DR_Pos)

#ifdef WHAL_CFG_STM32WB_SPI_DIRECT_API_MAPPING
#define whal_Stm32wb_Spi_Init     whal_Spi_Init
#define whal_Stm32wb_Spi_Deinit   whal_Spi_Deinit
#define whal_Stm32wb_Spi_StartCom whal_Spi_StartCom
#define whal_Stm32wb_Spi_EndCom   whal_Spi_EndCom
#define whal_Stm32wb_Spi_SendRecv whal_Spi_SendRecv
#endif /* WHAL_CFG_SPI_API_MAPPING */

#ifdef WHAL_CFG_STM32WB_SPI_SINGLE_INSTANCE
const whal_Spi whal_Stm32wb_Spi_Dev = WHAL_CFG_STM32WB_SPI_DEV;
#endif

/*
 * Calculate the baud rate prescaler index for a target baud rate.
 *
 * SPI baud rate = fPCLK / (2 ^ (BR + 1))
 *   BR=0 -> /2,  BR=1 -> /4,  BR=2 -> /8, ... BR=7 -> /256
 *
 * Returns the smallest prescaler that does not exceed the target baud.
 */
static uint32_t whal_Stm32wb_Spi_CalcBr(size_t pclk, uint32_t targetBaud)
{
    uint32_t br;

    for (br = 0; br < 7; br++) {
        if ((pclk / (2u << br)) <= targetBaud) {
            return br;
        }
    }

    return 7;
}

whal_Error whal_Stm32wb_Spi_Init(whal_Spi *spiDev)
{
#ifdef WHAL_CFG_STM32WB_SPI_SINGLE_INSTANCE
    size_t base = whal_Stm32wb_Spi_Dev.base;
    (void)spiDev;
#else
    size_t base;

    if (!spiDev || !spiDev->cfg) {
        return WHAL_EINVAL;
    }

    base = spiDev->base;
#endif

    /* Master mode with software slave management */
    whal_Reg_Update(base, SPI_CR1_REG,
                    SPI_CR1_MSTR_Msk | SPI_CR1_SSM_Msk | SPI_CR1_SSI_Msk,
                    whal_SetBits(SPI_CR1_MSTR_Msk, SPI_CR1_MSTR_Pos, 1) |
                    whal_SetBits(SPI_CR1_SSM_Msk, SPI_CR1_SSM_Pos, 1) |
                    whal_SetBits(SPI_CR1_SSI_Msk, SPI_CR1_SSI_Pos, 1));

    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb_Spi_Deinit(whal_Spi *spiDev)
{
#ifdef WHAL_CFG_STM32WB_SPI_SINGLE_INSTANCE
    size_t base = whal_Stm32wb_Spi_Dev.base;
    (void)spiDev;
#else
    size_t base;

    if (!spiDev || !spiDev->cfg) {
        return WHAL_EINVAL;
    }

    base = spiDev->base;
#endif

    /* Disable SPI */
    whal_Reg_Update(base, SPI_CR1_REG, SPI_CR1_SPE_Msk,
                    whal_SetBits(SPI_CR1_SPE_Msk, SPI_CR1_SPE_Pos, 0));

    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb_Spi_StartCom(whal_Spi *spiDev, whal_Spi_ComCfg *comCfg)
{
    uint32_t cpol, cpha, br, ds, frxth;
#ifdef WHAL_CFG_STM32WB_SPI_SINGLE_INSTANCE
    whal_Stm32wb_Spi_Cfg *cfg =
        (whal_Stm32wb_Spi_Cfg *)whal_Stm32wb_Spi_Dev.cfg;
    size_t base = whal_Stm32wb_Spi_Dev.base;
    (void)spiDev;

    if (!comCfg) {
        return WHAL_EINVAL;
    }
#else
    size_t base;
    whal_Stm32wb_Spi_Cfg *cfg;

    if (!spiDev || !spiDev->cfg || !comCfg) {
        return WHAL_EINVAL;
    }
#endif

    /* DS field encodes word size as (bits - 1); valid range 4-16 */
    if (comCfg->wordSz < 4 || comCfg->wordSz > 16) {
        return WHAL_EINVAL;
    }

    if (comCfg->mode > 3 || comCfg->dataLines != 1 || comCfg->freq == 0) {
        return WHAL_EINVAL;
    }

#ifndef WHAL_CFG_STM32WB_SPI_SINGLE_INSTANCE
    base = spiDev->base;
    cfg = (whal_Stm32wb_Spi_Cfg *)spiDev->cfg;
#endif

    br = whal_Stm32wb_Spi_CalcBr(cfg->pclk, comCfg->freq);

    cpol = (comCfg->mode >> 1) & 1;
    cpha = comCfg->mode & 1;
    ds = comCfg->wordSz - 1;
    frxth = (comCfg->wordSz <= 8) ? 1 : 0;

    /* Disable SPE before reconfiguring */
    whal_Reg_Update(base, SPI_CR1_REG, SPI_CR1_SPE_Msk,
                    whal_SetBits(SPI_CR1_SPE_Msk, SPI_CR1_SPE_Pos, 0));

    /* Set mode and baud rate */
    whal_Reg_Update(base, SPI_CR1_REG,
                    SPI_CR1_CPOL_Msk | SPI_CR1_CPHA_Msk | SPI_CR1_BR_Msk,
                    whal_SetBits(SPI_CR1_CPOL_Msk, SPI_CR1_CPOL_Pos, cpol) |
                    whal_SetBits(SPI_CR1_CPHA_Msk, SPI_CR1_CPHA_Pos, cpha) |
                    whal_SetBits(SPI_CR1_BR_Msk, SPI_CR1_BR_Pos, br));

    /* Set data size and FIFO receive threshold */
    whal_Reg_Update(base, SPI_CR2_REG,
                    SPI_CR2_DS_Msk | SPI_CR2_FRXTH_Msk,
                    whal_SetBits(SPI_CR2_DS_Msk, SPI_CR2_DS_Pos, ds) |
                    whal_SetBits(SPI_CR2_FRXTH_Msk, SPI_CR2_FRXTH_Pos, frxth));

    /* Enable SPE */
    whal_Reg_Update(base, SPI_CR1_REG, SPI_CR1_SPE_Msk,
                    whal_SetBits(SPI_CR1_SPE_Msk, SPI_CR1_SPE_Pos, 1));

    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb_Spi_EndCom(whal_Spi *spiDev)
{
#ifdef WHAL_CFG_STM32WB_SPI_SINGLE_INSTANCE
    size_t base = whal_Stm32wb_Spi_Dev.base;
    (void)spiDev;
#else
    size_t base;

    if (!spiDev || !spiDev->cfg) {
        return WHAL_EINVAL;
    }

    base = spiDev->base;
#endif

    /* Disable SPE */
    whal_Reg_Update(base, SPI_CR1_REG, SPI_CR1_SPE_Msk,
                    whal_SetBits(SPI_CR1_SPE_Msk, SPI_CR1_SPE_Pos, 0));

    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb_Spi_SendRecv(whal_Spi *spiDev,
                                    const void *tx, size_t txLen,
                                    void *rx, size_t rxLen)
{
    const uint8_t *txBuf = (const uint8_t *)tx;
    uint8_t *rxBuf = (uint8_t *)rx;
    size_t totalLen;
    whal_Error err;
    uint8_t txByte;
#ifdef WHAL_CFG_STM32WB_SPI_SINGLE_INSTANCE
    whal_Stm32wb_Spi_Cfg *cfg =
        (whal_Stm32wb_Spi_Cfg *)whal_Stm32wb_Spi_Dev.cfg;
    size_t base = whal_Stm32wb_Spi_Dev.base;
    (void)spiDev;

    if ((!tx && txLen) || (!rx && rxLen)) {
        return WHAL_EINVAL;
    }
#else
    size_t base;
    whal_Stm32wb_Spi_Cfg *cfg;

    if (!spiDev || !spiDev->cfg || (!tx && txLen) || (!rx && rxLen)) {
        return WHAL_EINVAL;
    }

    base = spiDev->base;
    cfg = (whal_Stm32wb_Spi_Cfg *)spiDev->cfg;
#endif
    totalLen = txLen > rxLen ? txLen : rxLen;

    for (size_t i = 0; i < totalLen; i++) {
        /* Wait for TX buffer empty */
        err = whal_Reg_ReadPoll(base, SPI_SR_REG,
                                SPI_SR_TXE_Msk, SPI_SR_TXE_Msk,
                                cfg->timeout);
        if (err)
            return err;

        /* Write TX data, pad with 0xFF when tx is exhausted or NULL */
        txByte = (txBuf && i < txLen) ? txBuf[i] : 0xFF;
        *(volatile uint8_t *)(base + SPI_DR_REG) = txByte;

        /* Wait for RX byte */
        err = whal_Reg_ReadPoll(base, SPI_SR_REG,
                                SPI_SR_RXNE_Msk, SPI_SR_RXNE_Msk,
                                cfg->timeout);
        if (err)
            return err;

        /* Store or discard received byte */
        if (rxBuf && i < rxLen)
            rxBuf[i] = *(volatile uint8_t *)(base + SPI_DR_REG);
        else
            (void)*(volatile uint8_t *)(base + SPI_DR_REG);
    }

    /* Wait for not busy */
    return whal_Reg_ReadPoll(base, SPI_SR_REG, SPI_SR_BSY_Msk, 0,
                             cfg->timeout);
}

#ifndef WHAL_CFG_STM32WB_SPI_DIRECT_API_MAPPING
const whal_SpiDriver whal_Stm32wb_Spi_Driver = {
    .Init = whal_Stm32wb_Spi_Init,
    .Deinit = whal_Stm32wb_Spi_Deinit,
    .StartCom = whal_Stm32wb_Spi_StartCom,
    .EndCom = whal_Stm32wb_Spi_EndCom,
    .SendRecv = whal_Stm32wb_Spi_SendRecv,
};
#endif /* !WHAL_CFG_SPI_API_MAPPING */
