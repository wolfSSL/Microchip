/* cortex_m4_nvic.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "board.h"  /* provides WHAL_CFG_NVIC_DEV initializer */
#include <wolfHAL/irq/cortex_m4_nvic.h>
#include <wolfHAL/error.h>
#include <wolfHAL/reg.h>

const whal_Irq whal_Nvic_Dev = WHAL_CFG_NVIC_DEV;

/*
 * ARM Cortex-M4 NVIC register offsets (relative to 0xE000E100).
 *
 * ISER: Interrupt Set-Enable Registers (0x000-0x01C, 32 IRQs per register)
 * ICER: Interrupt Clear-Enable Registers (0x080-0x09C)
 * IPR:  Interrupt Priority Registers (0x300-0x37F, 4 IRQs per register)
 */
#define NVIC_ISER_REG(irq) (0x000 + (((irq) >> 5) << 2))
#define NVIC_ICER_REG(irq) (0x080 + (((irq) >> 5) << 2))
#define NVIC_IPR_REG(irq)    (0x300 + (((irq) >> 2) << 2))
#define NVIC_IPR_SHIFT(irq)  (((irq) & 0x3) << 3)

#ifdef WHAL_CFG_NVIC_IRQ_DIRECT_API_MAPPING
#define whal_Nvic_Init    whal_Irq_Init
#define whal_Nvic_Deinit  whal_Irq_Deinit
#define whal_Nvic_Enable  whal_Irq_Enable
#define whal_Nvic_Disable whal_Irq_Disable
#endif /* WHAL_CFG_NVIC_IRQ_DIRECT_API_MAPPING */

whal_Error whal_Nvic_Init(whal_Irq *irqDev)
{
    (void)irqDev;
    return WHAL_SUCCESS;
}

whal_Error whal_Nvic_Deinit(whal_Irq *irqDev)
{
    (void)irqDev;
    return WHAL_SUCCESS;
}

whal_Error whal_Nvic_Enable(whal_Irq *irqDev, size_t irq,
                                    const void *irqCfg)
{
    size_t base = whal_Nvic_Dev.base;
    (void)irqDev;

    /* Set priority if config provided */
    if (irqCfg) {
        const whal_Nvic_Cfg *cfg = (const whal_Nvic_Cfg *)irqCfg;
        size_t shift = NVIC_IPR_SHIFT(irq);
        size_t mask = (0xFFUL << shift);
        whal_Reg_Update(base, NVIC_IPR_REG(irq), mask,
                        (size_t)(cfg->priority << 4) << shift);
    }

    /* Enable the interrupt */
    whal_Reg_Write(base, NVIC_ISER_REG(irq), (1UL << (irq & 0x1F)));

    return WHAL_SUCCESS;
}

whal_Error whal_Nvic_Disable(whal_Irq *irqDev, size_t irq)
{
    size_t base = whal_Nvic_Dev.base;
    (void)irqDev;

    whal_Reg_Write(base, NVIC_ICER_REG(irq), (1UL << (irq & 0x1F)));

    return WHAL_SUCCESS;
}

#ifndef WHAL_CFG_NVIC_IRQ_DIRECT_API_MAPPING
const whal_IrqDriver whal_Nvic_Driver = {
    .Init = whal_Nvic_Init,
    .Deinit = whal_Nvic_Deinit,
    .Enable = whal_Nvic_Enable,
    .Disable = whal_Nvic_Disable,
};
#endif /* !WHAL_CFG_NVIC_IRQ_DIRECT_API_MAPPING */
