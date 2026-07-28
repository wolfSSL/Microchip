/* pic32cz_supc.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_PIC32CZ_SUPC_H
#define WHAL_PIC32CZ_SUPC_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/error.h>
#include <wolfHAL/reg.h>
#include <wolfHAL/bitops.h>

/*
 * @file pic32cz_supc.h
 * @brief PIC32CZ supply controller (SUPC) driver.
 *
 * Boards toggle SUPC voltage-regulator outputs imperatively from Board_Init
 * by calling the helpers below. Power is a board-level driver — no whal_Power
 * device struct, no generic API, no vtable. The base address is the chip's
 * fixed SUPC location (WHAL_PIC32CZ_SUPC_BASE).
 */

#define WHAL_PIC32CZ_SUPC_BASE                  0x44020000

#define WHAL_PIC32CZ_SUPC_VREGCTRL_REG          0x1C
#define WHAL_PIC32CZ_SUPC_VREGCTRL_AVREGEN_Pos  16
#define WHAL_PIC32CZ_SUPC_VREGCTRL_AVREGEN_Msk  (WHAL_BITMASK(3) << WHAL_PIC32CZ_SUPC_VREGCTRL_AVREGEN_Pos)

/*
 * @brief Descriptor for one SUPC voltage-regulator output (mask + bit position
 *        within VREGCTRL.AVREGEN).
 */
typedef struct whal_Pic32cz_Supc_Supply {
    size_t enableMask;
    size_t enablePos;
} whal_Pic32cz_Supc_Supply;

/*
 * @brief Set a regulator's enable bit in SUPC VREGCTRL.AVREGEN.
 *
 * @param supply Descriptor for the regulator output to enable.
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Pic32cz_Supc_EnableSupply(
    const whal_Pic32cz_Supc_Supply *supply)
{
    whal_Reg_Update(WHAL_PIC32CZ_SUPC_BASE, WHAL_PIC32CZ_SUPC_VREGCTRL_REG,
                    supply->enableMask,
                    whal_SetBits(supply->enableMask, supply->enablePos, 1));
    return WHAL_SUCCESS;
}

/*
 * @brief Clear a regulator's enable bit in SUPC VREGCTRL.AVREGEN.
 *
 * @param supply Descriptor for the regulator output to disable.
 *
 * @retval WHAL_SUCCESS Always.
 */
static inline whal_Error whal_Pic32cz_Supc_DisableSupply(
    const whal_Pic32cz_Supc_Supply *supply)
{
    whal_Reg_Update(WHAL_PIC32CZ_SUPC_BASE, WHAL_PIC32CZ_SUPC_VREGCTRL_REG,
                    supply->enableMask,
                    whal_SetBits(supply->enableMask, supply->enablePos, 0));
    return WHAL_SUCCESS;
}

#endif /* WHAL_PIC32CZ_SUPC_H */
