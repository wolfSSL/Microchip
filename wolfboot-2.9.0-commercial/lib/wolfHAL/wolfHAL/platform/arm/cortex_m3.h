/* cortex_m3.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_CORTEX_M3_H
#define WHAL_CORTEX_M3_H

#include <wolfHAL/timer/systick.h>
#include <wolfHAL/irq/cortex_m4_nvic.h>

/*
 * @file cortex_m3.h
 * @brief ARM Cortex-M3 core platform constants.
 *
 * Exposes SysTick and NVIC base addresses and driver pointers for boards
 * built on the Cortex-M3 core. Pulled in by chip-specific platform headers.
 */

#define WHAL_CORTEX_M3_SYSTICK_BASE 0xE000E010
#define WHAL_CORTEX_M3_SYSTICK_DRIVER &whal_SysTick_Driver

#define WHAL_CORTEX_M3_NVIC_BASE 0xE000E100
#define WHAL_CORTEX_M3_NVIC_DRIVER &whal_Nvic_Driver

#endif /* WHAL_CORTEX_M3_H */
