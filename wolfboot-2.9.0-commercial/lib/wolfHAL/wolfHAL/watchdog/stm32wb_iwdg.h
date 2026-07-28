/* stm32wb_iwdg.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB_IWDG_H
#define WHAL_STM32WB_IWDG_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/timeout.h>
#include <wolfHAL/watchdog/watchdog.h>

/*
 * @file stm32wb_iwdg.h
 * @brief STM32WB independent watchdog (IWDG) driver.
 *
 * The IWDG is clocked from the LSI (~32 kHz) and cannot be stopped
 * once started. The timeout is configured via prescaler and reload:
 *
 *   timeout = (reload + 1) * (4 << prescaler) / f_LSI
 *
 * Prescaler index: 0=/4, 1=/8, 2=/16, 3=/32, 4=/64, 5=/128, 6=/256.
 */

/* Prescaler divider indices */
#define WHAL_STM32WB_IWDG_PR_4     0
#define WHAL_STM32WB_IWDG_PR_8     1
#define WHAL_STM32WB_IWDG_PR_16    2
#define WHAL_STM32WB_IWDG_PR_32    3
#define WHAL_STM32WB_IWDG_PR_64    4
#define WHAL_STM32WB_IWDG_PR_128   5
#define WHAL_STM32WB_IWDG_PR_256   6

/*
 * @brief IWDG device configuration.
 */
typedef struct {
    uint8_t prescaler;    /* Prescaler index (WHAL_STM32WB_IWDG_PR_*) */
    uint16_t reload;      /* 12-bit reload value (0-4095) */
    whal_Timeout *timeout;
} whal_Stm32wb_Iwdg_Cfg;

/*
 * @brief Platform-owned IWDG device singleton. Defined in the driver TU
 * from the WHAL_CFG_STM32WB_IWDG_DEV initializer in board.h.
 */
extern const whal_Watchdog whal_Stm32wb_Iwdg_Dev;

#ifndef WHAL_CFG_STM32WB_IWDG_DIRECT_API_MAPPING
/*
 * @brief Driver instance for STM32WB IWDG.
 */
extern const whal_WatchdogDriver whal_Stm32wb_Iwdg_Driver;

/*
 * @brief Configure and start the STM32WB IWDG.
 *
 * Sets the prescaler and reload value, then starts the watchdog.
 * Once started, the IWDG cannot be stopped.
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Watchdog started.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Stm32wb_Iwdg_Init(whal_Watchdog *wdgDev);

/*
 * @brief Deinitialize the STM32WB IWDG.
 *
 * The IWDG cannot be stopped by software. This function has no effect.
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Always.
 */
whal_Error whal_Stm32wb_Iwdg_Deinit(whal_Watchdog *wdgDev);

/*
 * @brief Refresh the IWDG counter to prevent reset.
 *
 * Writes the reload key (0xAAAA) to IWDG_KR, reloading the
 * downcounter with the value from IWDG_RLR.
 *
 * @param wdgDev Watchdog device instance.
 *
 * @retval WHAL_SUCCESS Counter refreshed.
 * @retval WHAL_EINVAL  Null pointer.
 */
whal_Error whal_Stm32wb_Iwdg_Refresh(whal_Watchdog *wdgDev);
#endif /* !WHAL_CFG_STM32WB_IWDG_DIRECT_API_MAPPING */

#endif /* WHAL_STM32WB_IWDG_H */
