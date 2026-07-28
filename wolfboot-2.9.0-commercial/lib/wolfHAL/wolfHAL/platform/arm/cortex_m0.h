/* cortex_m0.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_CORTEX_M0_H
#define WHAL_CORTEX_M0_H

#include <wolfHAL/timer/systick.h>

/*
 * @file cortex_m0.h
 * @brief ARM Cortex-M0 core platform constants.
 *
 * Exposes the SysTick base address and driver pointer used by boards built
 * on the Cortex-M0 core. Pulled in by chip-specific platform headers.
 */

#define WHAL_CORTEX_M0_SYSTICK_BASE 0xE000E010
#define WHAL_CORTEX_M0_SYSTICK_DRIVER &whal_SysTick_Driver

#endif /* WHAL_CORTEX_M0_H */
