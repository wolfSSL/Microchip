/* stm32wb_wwdg.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB_WWDG_H
#define WHAL_STM32WB_WWDG_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/watchdog/watchdog.h>

/*
 * @file stm32wb_wwdg.h
 * @brief STM32WB window watchdog (WWDG) driver.
 *
 * The WWDG is clocked from PCLK1 and must be refreshed within a
 * configurable window. Refreshing too early or too late triggers
 * a system reset. An early wakeup interrupt can be enabled to
 * allow state saving before reset.
 *
 * Timeout = (4096 * 2^WDGTB * (counter - 0x3F)) / f_PCLK1
 */

/* Timebase prescaler values */
#define WHAL_STM32WB_WWDG_TB_1      0
#define WHAL_STM32WB_WWDG_TB_2      1
#define WHAL_STM32WB_WWDG_TB_4      2
#define WHAL_STM32WB_WWDG_TB_8      3
#define WHAL_STM32WB_WWDG_TB_16     4
#define WHAL_STM32WB_WWDG_TB_32     5
#define WHAL_STM32WB_WWDG_TB_64     6
#define WHAL_STM32WB_WWDG_TB_128    7

/*
 * @brief WWDG device configuration.
 */
typedef struct {
    uint8_t prescaler;    /* Timebase prescaler (WHAL_STM32WB_WWDG_TB_*) */
    uint8_t window;       /* 7-bit window value (must be > 0x3F) */
    uint8_t counter;      /* 7-bit counter value (must be > 0x3F) */
} whal_Stm32wb_Wwdg_Cfg;

/*
 * @brief Platform-owned WWDG device singleton. Defined in the driver TU
 * from the WHAL_CFG_STM32WB_WWDG_DEV initializer in board.h.
 */
extern const whal_Watchdog whal_Stm32wb_Wwdg_Dev;

#ifndef WHAL_CFG_STM32WB_WWDG_DIRECT_API_MAPPING
/*
 * @brief Driver instance for STM32WB WWDG.
 */
extern const whal_WatchdogDriver whal_Stm32wb_Wwdg_Driver;

/*
 * @brief Configure and start the STM32WB WWDG.
 *
 * Sets the window, prescaler, and counter values, then enables
 * the watchdog.
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Watchdog started.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Stm32wb_Wwdg_Init(whal_Watchdog *wdgDev);

/*
 * @brief Deinitialize the STM32WB WWDG.
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Always (no-op, WWDG can only be stopped by reset).
 */
whal_Error whal_Stm32wb_Wwdg_Deinit(whal_Watchdog *wdgDev);

/*
 * @brief Refresh the WWDG counter within the window.
 *
 * Must be called after the counter has counted down past the
 * window value but before it reaches 0x3F. Refreshing outside
 * this window triggers a reset.
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Counter refreshed.
 * @retval WHAL_EINVAL  Null pointer.
 */
whal_Error whal_Stm32wb_Wwdg_Refresh(whal_Watchdog *wdgDev);
#endif /* !WHAL_CFG_STM32WB_WWDG_DIRECT_API_MAPPING */

#endif /* WHAL_STM32WB_WWDG_H */
