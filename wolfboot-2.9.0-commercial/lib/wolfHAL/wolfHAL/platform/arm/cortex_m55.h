/* cortex_m55.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_CORTEX_M55_H
#define WHAL_CORTEX_M55_H

#include <wolfHAL/timer/systick.h>
#include <wolfHAL/irq/cortex_m4_nvic.h>

/*
 * @file cortex_m55.h
 * @brief ARM Cortex-M55 core platform constants.
 *
 * Exposes SysTick and NVIC base addresses and driver pointers for boards
 * built on the Cortex-M55 core. Pulled in by chip-specific platform headers.
 */

#define WHAL_CORTEX_M55_SYSTICK_BASE 0xE000E010
#define WHAL_CORTEX_M55_SYSTICK_DRIVER &whal_SysTick_Driver

#define WHAL_CORTEX_M55_NVIC_BASE 0xE000E100
#define WHAL_CORTEX_M55_NVIC_DRIVER &whal_Nvic_Driver

#endif /* WHAL_CORTEX_M55_H */
