/* stm32wb_rcc.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB_RCC_H
#define WHAL_STM32WB_RCC_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/error.h>
#include <wolfHAL/reg.h>
#include <wolfHAL/bitops.h>

/*
 * @file stm32wb_rcc.h
 * @brief STM32WB RCC (Reset and Clock Control) driver.
 *
 * Boards bring up the clock tree imperatively from Board_Init by calling
 * the helpers below in order. The RCC peripheral lives at a fixed address
 * — clock is a board-level driver with no device struct, no generic API,
 * no vtable.
 */

#define WHAL_STM32WB_RCC_BASE            0x58000000

#define WHAL_STM32WB_RCC_CR_REG          0x000
#define WHAL_STM32WB_RCC_CR_MSION_Msk    (1UL <<  0)
#define WHAL_STM32WB_RCC_CR_MSIRDY_Msk   (1UL <<  1)
#define WHAL_STM32WB_RCC_CR_MSIRDY_Pos   1
#define WHAL_STM32WB_RCC_CR_MSIRANGE_Pos 4
#define WHAL_STM32WB_RCC_CR_MSIRANGE_Msk (WHAL_BITMASK(4) << WHAL_STM32WB_RCC_CR_MSIRANGE_Pos)
#define WHAL_STM32WB_RCC_CR_PLLON_Msk    (1UL << 24)
#define WHAL_STM32WB_RCC_CR_PLLRDY_Msk   (1UL << 25)
#define WHAL_STM32WB_RCC_CR_PLLRDY_Pos   25

#define WHAL_STM32WB_RCC_CFGR_REG        0x008
#define WHAL_STM32WB_RCC_CFGR_SW_Pos     0
#define WHAL_STM32WB_RCC_CFGR_SW_Msk     (WHAL_BITMASK(2) << WHAL_STM32WB_RCC_CFGR_SW_Pos)
#define WHAL_STM32WB_RCC_CFGR_SWS_Pos    2
#define WHAL_STM32WB_RCC_CFGR_SWS_Msk    (WHAL_BITMASK(2) << WHAL_STM32WB_RCC_CFGR_SWS_Pos)

#define WHAL_STM32WB_RCC_PLLCFGR_REG         0x00C
#define WHAL_STM32WB_RCC_PLLCFGR_PLLSRC_Pos  0
#define WHAL_STM32WB_RCC_PLLCFGR_PLLSRC_Msk  (WHAL_BITMASK(2) << WHAL_STM32WB_RCC_PLLCFGR_PLLSRC_Pos)
#define WHAL_STM32WB_RCC_PLLCFGR_PLLM_Pos    4
#define WHAL_STM32WB_RCC_PLLCFGR_PLLM_Msk    (WHAL_BITMASK(3) << WHAL_STM32WB_RCC_PLLCFGR_PLLM_Pos)
#define WHAL_STM32WB_RCC_PLLCFGR_PLLN_Pos    8
#define WHAL_STM32WB_RCC_PLLCFGR_PLLN_Msk    (WHAL_BITMASK(7) << WHAL_STM32WB_RCC_PLLCFGR_PLLN_Pos)
#define WHAL_STM32WB_RCC_PLLCFGR_PLLP_Pos    17
#define WHAL_STM32WB_RCC_PLLCFGR_PLLP_Msk    (WHAL_BITMASK(5) << WHAL_STM32WB_RCC_PLLCFGR_PLLP_Pos)
#define WHAL_STM32WB_RCC_PLLCFGR_PLLQ_Pos    25
#define WHAL_STM32WB_RCC_PLLCFGR_PLLQ_Msk    (WHAL_BITMASK(3) << WHAL_STM32WB_RCC_PLLCFGR_PLLQ_Pos)
#define WHAL_STM32WB_RCC_PLLCFGR_PLLREN_Pos  28
#define WHAL_STM32WB_RCC_PLLCFGR_PLLREN_Msk  (1UL << WHAL_STM32WB_RCC_PLLCFGR_PLLREN_Pos)
#define WHAL_STM32WB_RCC_PLLCFGR_PLLR_Pos    29
#define WHAL_STM32WB_RCC_PLLCFGR_PLLR_Msk    (WHAL_BITMASK(3) << WHAL_STM32WB_RCC_PLLCFGR_PLLR_Pos)
#define WHAL_STM32WB_RCC_PLLCFGR_Msk \
        (WHAL_STM32WB_RCC_PLLCFGR_PLLSRC_Msk | WHAL_STM32WB_RCC_PLLCFGR_PLLM_Msk |   \
         WHAL_STM32WB_RCC_PLLCFGR_PLLN_Msk   | WHAL_STM32WB_RCC_PLLCFGR_PLLP_Msk |   \
         WHAL_STM32WB_RCC_PLLCFGR_PLLQ_Msk   | WHAL_STM32WB_RCC_PLLCFGR_PLLREN_Msk | \
         WHAL_STM32WB_RCC_PLLCFGR_PLLR_Msk)

/*
 * @brief System clock source selection (RCC_CFGR.SW).
 */
typedef enum {
    WHAL_STM32WB_RCC_SYSCLK_SRC_MSI,
    WHAL_STM32WB_RCC_SYSCLK_SRC_HSI16,
    WHAL_STM32WB_RCC_SYSCLK_SRC_HSE,
    WHAL_STM32WB_RCC_SYSCLK_SRC_PLL,
} whal_Stm32wb_Rcc_SysClockSrc;

/*
 * @brief PLL input clock source (RCC_PLLCFGR.PLLSRC).
 */
typedef enum {
    WHAL_STM32WB_RCC_PLLCLK_SRC_NONE,
    WHAL_STM32WB_RCC_PLLCLK_SRC_MSI,
    WHAL_STM32WB_RCC_PLLCLK_SRC_HSI16,
    WHAL_STM32WB_RCC_PLLCLK_SRC_HSE,
} whal_Stm32wb_Rcc_PllClockSrc;

/*
 * @brief MSI oscillator range selection (RCC_CR.MSIRANGE).
 */
typedef enum {
    WHAL_STM32WB_RCC_MSIRANGE_100kHz,
    WHAL_STM32WB_RCC_MSIRANGE_200kHz,
    WHAL_STM32WB_RCC_MSIRANGE_400kHz,
    WHAL_STM32WB_RCC_MSIRANGE_800kHz,
    WHAL_STM32WB_RCC_MSIRANGE_1MHz,
    WHAL_STM32WB_RCC_MSIRANGE_2MHz,
    WHAL_STM32WB_RCC_MSIRANGE_4MHz,
    WHAL_STM32WB_RCC_MSIRANGE_8MHz,
    WHAL_STM32WB_RCC_MSIRANGE_16MHz,
    WHAL_STM32WB_RCC_MSIRANGE_24MHz,
    WHAL_STM32WB_RCC_MSIRANGE_32MHz,
    WHAL_STM32WB_RCC_MSIRANGE_48MHz,
} whal_Stm32wb_Rcc_MsiRange;

/*
 * @brief Peripheral clock descriptor (RCC *ENR enable bit).
 */
typedef struct {
    size_t regOffset;
    size_t enableMask;
    size_t enablePos;
} whal_Stm32wb_Rcc_PeriphClk;

/*
 * @brief Cfg for EnableOsc/DisableOsc — on bit + ready bit.
 */
typedef struct {
    size_t onReg;
    size_t onMsk;
    size_t rdyReg;
    size_t rdyMsk;
    size_t rdyPos;
} whal_Stm32wb_Rcc_OscCfg;

#define WHAL_STM32WB_RCC_HSI_CFG                             \
    .onReg  = 0x000, .onMsk  = (1UL <<  8),                  \
    .rdyReg = 0x000, .rdyMsk = (1UL << 10), .rdyPos = 10
#define WHAL_STM32WB_RCC_HSE_CFG                             \
    .onReg  = 0x000, .onMsk  = (1UL << 16),                  \
    .rdyReg = 0x000, .rdyMsk = (1UL << 17), .rdyPos = 17
#define WHAL_STM32WB_RCC_HSI48_CFG                           \
    .onReg  = 0x098, .onMsk  = (1UL <<  0),                  \
    .rdyReg = 0x098, .rdyMsk = (1UL <<  1), .rdyPos =  1
#define WHAL_STM32WB_RCC_LSI_CFG                             \
    .onReg  = 0x094, .onMsk  = (1UL <<  0),                  \
    .rdyReg = 0x094, .rdyMsk = (1UL <<  1), .rdyPos =  1
#define WHAL_STM32WB_RCC_LSE_CFG                             \
    .onReg  = 0x090, .onMsk  = (1UL <<  0),                  \
    .rdyReg = 0x090, .rdyMsk = (1UL <<  1), .rdyPos =  1

/*
 * @brief PLL configuration parameters.
 *   VCO = (input / m) * n
 *   PLLR = VCO / r (SYSCLK domain)
 */
typedef struct {
    whal_Stm32wb_Rcc_PllClockSrc clkSrc;
    uint8_t r;
    uint8_t q;
    uint8_t p;
    uint8_t n;
    uint8_t m;
} whal_Stm32wb_Rcc_PllCfg;

/*
 * @brief Turn on an oscillator and wait for its ready bit.
 *
 * @param cfg    Oscillator on/ready bit descriptor (e.g. WHAL_STM32WB_RCC_HSE_CFG).
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Stm32wb_Rcc_EnableOsc(
    const whal_Stm32wb_Rcc_OscCfg *cfg)
{
    size_t rdy;

    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, cfg->onReg, cfg->onMsk, cfg->onMsk);
    do {
        whal_Reg_Get(WHAL_STM32WB_RCC_BASE, cfg->rdyReg, cfg->rdyMsk,
                     cfg->rdyPos, &rdy);
    } while (!rdy);
    return WHAL_SUCCESS;
}

/*
 * @brief Turn off an oscillator.
 *
 * @param cfg    Oscillator on/ready bit descriptor.
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Stm32wb_Rcc_DisableOsc(
    const whal_Stm32wb_Rcc_OscCfg *cfg)
{
    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, cfg->onReg, cfg->onMsk, 0);
    return WHAL_SUCCESS;
}

/*
 * @brief Enable the MSI oscillator, wait for ready, and select its range.
 *
 * Sets MSION, polls MSIRDY, then writes MSIRANGE.
 *
 * @param range  MSI range selection.
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Stm32wb_Rcc_EnableMsi(
    whal_Stm32wb_Rcc_MsiRange range)
{
    size_t rdy;

    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_CR_REG,
                    WHAL_STM32WB_RCC_CR_MSION_Msk,
                    WHAL_STM32WB_RCC_CR_MSION_Msk);
    do {
        whal_Reg_Get(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_CR_REG,
                     WHAL_STM32WB_RCC_CR_MSIRDY_Msk,
                     WHAL_STM32WB_RCC_CR_MSIRDY_Pos, &rdy);
    } while (!rdy);
    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_CR_REG,
                    WHAL_STM32WB_RCC_CR_MSIRANGE_Msk,
                    whal_SetBits(WHAL_STM32WB_RCC_CR_MSIRANGE_Msk,
                                 WHAL_STM32WB_RCC_CR_MSIRANGE_Pos, range));
    return WHAL_SUCCESS;
}

/*
 * @brief Configure and enable the PLL, waiting for lock.
 *
 * Programs PLLCFGR (source/M/N/P/Q/R + REN), sets PLLON, polls PLLRDY.
 *
 * @param cfg    PLL configuration.
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Stm32wb_Rcc_EnablePll(
    const whal_Stm32wb_Rcc_PllCfg *cfg)
{
    size_t rdy;

    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_PLLCFGR_REG,
                    WHAL_STM32WB_RCC_PLLCFGR_Msk,
                    whal_SetBits(WHAL_STM32WB_RCC_PLLCFGR_PLLSRC_Msk,
                                 WHAL_STM32WB_RCC_PLLCFGR_PLLSRC_Pos, cfg->clkSrc) |
                    whal_SetBits(WHAL_STM32WB_RCC_PLLCFGR_PLLM_Msk,
                                 WHAL_STM32WB_RCC_PLLCFGR_PLLM_Pos,   cfg->m) |
                    whal_SetBits(WHAL_STM32WB_RCC_PLLCFGR_PLLN_Msk,
                                 WHAL_STM32WB_RCC_PLLCFGR_PLLN_Pos,   cfg->n) |
                    whal_SetBits(WHAL_STM32WB_RCC_PLLCFGR_PLLP_Msk,
                                 WHAL_STM32WB_RCC_PLLCFGR_PLLP_Pos,   cfg->p) |
                    whal_SetBits(WHAL_STM32WB_RCC_PLLCFGR_PLLQ_Msk,
                                 WHAL_STM32WB_RCC_PLLCFGR_PLLQ_Pos,   cfg->q) |
                    whal_SetBits(WHAL_STM32WB_RCC_PLLCFGR_PLLREN_Msk,
                                 WHAL_STM32WB_RCC_PLLCFGR_PLLREN_Pos, 1) |
                    whal_SetBits(WHAL_STM32WB_RCC_PLLCFGR_PLLR_Msk,
                                 WHAL_STM32WB_RCC_PLLCFGR_PLLR_Pos,   cfg->r));
    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_CR_REG,
                    WHAL_STM32WB_RCC_CR_PLLON_Msk,
                    WHAL_STM32WB_RCC_CR_PLLON_Msk);
    do {
        whal_Reg_Get(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_CR_REG,
                     WHAL_STM32WB_RCC_CR_PLLRDY_Msk,
                     WHAL_STM32WB_RCC_CR_PLLRDY_Pos, &rdy);
    } while (!rdy);
    return WHAL_SUCCESS;
}

/*
 * @brief Turn the PLL off (clears RCC_CR.PLLON).
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Stm32wb_Rcc_DisablePll(void)
{
    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_CR_REG,
                    WHAL_STM32WB_RCC_CR_PLLON_Msk, 0);
    return WHAL_SUCCESS;
}

/*
 * @brief Switch SYSCLK to the requested source and wait for the switch.
 *
 * @param src    System clock source.
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Stm32wb_Rcc_SetSysClock(
    whal_Stm32wb_Rcc_SysClockSrc src)
{
    size_t sws;

    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_CFGR_REG,
                    WHAL_STM32WB_RCC_CFGR_SW_Msk,
                    whal_SetBits(WHAL_STM32WB_RCC_CFGR_SW_Msk,
                                 WHAL_STM32WB_RCC_CFGR_SW_Pos, src));
    do {
        whal_Reg_Get(WHAL_STM32WB_RCC_BASE, WHAL_STM32WB_RCC_CFGR_REG,
                     WHAL_STM32WB_RCC_CFGR_SWS_Msk,
                     WHAL_STM32WB_RCC_CFGR_SWS_Pos, &sws);
    } while (sws != (size_t)src);
    return WHAL_SUCCESS;
}

/*
 * @brief Set the enable bit for a peripheral clock gate.
 *
 * @param clk    Peripheral clock descriptor (RCC *ENR register + bit).
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Stm32wb_Rcc_EnablePeriphClk(
    const whal_Stm32wb_Rcc_PeriphClk *clk)
{
    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, clk->regOffset, clk->enableMask,
                    whal_SetBits(clk->enableMask, clk->enablePos, 1));
    return WHAL_SUCCESS;
}

/*
 * @brief Clear the enable bit for a peripheral clock gate.
 *
 * @param clk    Peripheral clock descriptor (RCC *ENR register + bit).
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Stm32wb_Rcc_DisablePeriphClk(
    const whal_Stm32wb_Rcc_PeriphClk *clk)
{
    whal_Reg_Update(WHAL_STM32WB_RCC_BASE, clk->regOffset, clk->enableMask,
                    whal_SetBits(clk->enableMask, clk->enablePos, 0));
    return WHAL_SUCCESS;
}

#endif /* WHAL_STM32WB_RCC_H */
