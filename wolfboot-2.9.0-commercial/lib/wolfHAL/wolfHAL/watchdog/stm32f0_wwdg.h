/* stm32f0_wwdg.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32F0_WWDG_H
#define WHAL_STM32F0_WWDG_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/watchdog/watchdog.h>

/*
 * @file stm32f0_wwdg.h
 * @brief STM32F0 window watchdog (WWDG) driver.
 *
 * The F0 WWDG has a 2-bit WDGTB prescaler at CFR bits 8:7 (divides by
 * 1/2/4/8), unlike the WB which has a 3-bit WDGTB at bits 13:11.
 */

/*
 * @brief STM32F0 WWDG configuration.
 */
typedef struct {
    uint8_t prescaler; /* WDGTB value (0–3): div 1, 2, 4, or 8 */
    uint8_t window;    /* WWDG window value (0x40–0x7F) */
    uint8_t counter;   /* Initial counter value (0x40–0x7F) */
} whal_Stm32f0_Wwdg_Cfg;

/*
 * @brief Platform-owned WWDG device singleton. Defined in the driver TU
 * from the WHAL_CFG_STM32F0_WWDG_DEV initializer in board.h.
 */
extern const whal_Watchdog whal_Stm32f0_Wwdg_Dev;

#ifndef WHAL_CFG_STM32F0_WWDG_DIRECT_API_MAPPING
/*
 * @brief Driver instance for the STM32F0 window watchdog.
 */
extern const whal_WatchdogDriver whal_Stm32f0_Wwdg_Driver;

/*
 * @brief Initialize and start the WWDG. Programs CFR (window/prescaler)
 *        and CR (enable + initial counter). The watchdog cannot be stopped
 *        once started.
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Watchdog started.
 * @retval WHAL_EINVAL  Null pointer or missing cfg.
 */
whal_Error whal_Stm32f0_Wwdg_Init(whal_Watchdog *wdgDev);

/*
 * @brief Deinitialize the WWDG (driver-side cleanup only — the hardware
 *        cannot be stopped).
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Driver deinitialized.
 * @retval WHAL_EINVAL  Null pointer.
 */
whal_Error whal_Stm32f0_Wwdg_Deinit(whal_Watchdog *wdgDev);

/*
 * @brief Refresh the WWDG counter. Must be called after the window opens
 *        and before the counter underflows, or a reset is generated.
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Counter refreshed.
 * @retval WHAL_EINVAL  Null pointer.
 */
whal_Error whal_Stm32f0_Wwdg_Refresh(whal_Watchdog *wdgDev);
#endif /* !WHAL_CFG_STM32F0_WWDG_DIRECT_API_MAPPING */

#endif /* WHAL_STM32F0_WWDG_H */
