/* systick.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "board.h"  /* provides WHAL_CFG_SYSTICK_DEV initializer */
#include <wolfHAL/error.h>
#include <wolfHAL/reg.h>
#include <wolfHAL/bitops.h>
#include <wolfHAL/timer/timer.h>
#include <wolfHAL/timer/systick.h>

const whal_Timer whal_SysTick_Dev = WHAL_CFG_SYSTICK_DEV;

#define SYSTICK_CSR_REG 0x00
#define SYSTICK_CSR_ENABLE_Pos 0
#define SYSTICK_CSR_ENABLE_Msk (1UL << SYSTICK_CSR_ENABLE_Pos)

#define SYSTICK_CSR_TICKINT_Pos 1
#define SYSTICK_CSR_TICKINT_Msk (1UL << SYSTICK_CSR_TICKINT_Pos)

#define SYSTICK_CSR_CLKSOURCE_Pos 2
#define SYSTICK_CSR_CLKSOURCE_Msk (1UL << SYSTICK_CSR_CLKSOURCE_Pos)

#define SYSTICK_CSR_COUNTFLAG_Pos 16
#define SYSTICK_CSR_COUNTFLAG_Msk (1UL << SYSTICK_CSR_COUNTFLAG_Pos)

#define SYSTICK_RVR_REG 0x04
#define SYSTICK_RVR_RELOAD_Pos 0
#define SYSTICK_RVR_RELOAD_Msk (WHAL_BITMASK(24) << SYSTICK_RVR_RELOAD_Pos)

#ifdef WHAL_CFG_SYSTICK_TIMER_DIRECT_API_MAPPING
#define whal_SysTick_Init   whal_Timer_Init
#define whal_SysTick_Deinit whal_Timer_Deinit
#define whal_SysTick_Start  whal_Timer_Start
#define whal_SysTick_Stop   whal_Timer_Stop
#define whal_SysTick_Reset  whal_Timer_Reset
#endif /* WHAL_CFG_SYSTICK_TIMER_DIRECT_API_MAPPING */

whal_Error whal_SysTick_Init(whal_Timer *timerDev)
{
    const whal_SysTick_Cfg *cfg =
        (const whal_SysTick_Cfg *)whal_SysTick_Dev.cfg;
    size_t base = whal_SysTick_Dev.base;
    (void)timerDev;

    whal_Reg_Update(base, SYSTICK_CSR_REG,
                          SYSTICK_CSR_CLKSOURCE_Msk | SYSTICK_CSR_TICKINT_Msk,
                          whal_SetBits(SYSTICK_CSR_CLKSOURCE_Msk, SYSTICK_CSR_CLKSOURCE_Pos, cfg->clkSrc) |
                          whal_SetBits(SYSTICK_CSR_TICKINT_Msk, SYSTICK_CSR_TICKINT_Pos, cfg->tickInt));

    whal_Reg_Update(base, SYSTICK_RVR_REG,
                    SYSTICK_RVR_RELOAD_Msk,
                    whal_SetBits(SYSTICK_RVR_RELOAD_Msk, SYSTICK_RVR_RELOAD_Pos, cfg->cyclesPerTick));

    return WHAL_SUCCESS;
}

whal_Error whal_SysTick_Deinit(whal_Timer *timerDev)
{
    (void)timerDev;
    return WHAL_SUCCESS;
}

whal_Error whal_SysTick_Start(whal_Timer *timerDev)
{
    size_t base = whal_SysTick_Dev.base;
    (void)timerDev;

    whal_Reg_Update(base, SYSTICK_CSR_REG, SYSTICK_CSR_ENABLE_Msk,
                    whal_SetBits(SYSTICK_CSR_ENABLE_Msk, SYSTICK_CSR_ENABLE_Pos, 1));

    return WHAL_SUCCESS;
}

whal_Error whal_SysTick_Stop(whal_Timer *timerDev)
{
    size_t base = whal_SysTick_Dev.base;
    (void)timerDev;

    whal_Reg_Update(base, SYSTICK_CSR_REG, SYSTICK_CSR_ENABLE_Msk,
                    whal_SetBits(SYSTICK_CSR_ENABLE_Msk, SYSTICK_CSR_ENABLE_Pos, 0));

    return WHAL_SUCCESS;
}

whal_Error whal_SysTick_Reset(whal_Timer *timerDev)
{
    (void)timerDev;
    return WHAL_SUCCESS;
}

#ifndef WHAL_CFG_SYSTICK_TIMER_DIRECT_API_MAPPING
const whal_TimerDriver whal_SysTick_Driver = {
    .Init = whal_SysTick_Init,
    .Deinit = whal_SysTick_Deinit,
    .Start = whal_SysTick_Start,
    .Stop = whal_SysTick_Stop,
    .Reset = whal_SysTick_Reset,
};
#endif /* !WHAL_CFG_SYSTICK_TIMER_DIRECT_API_MAPPING */
