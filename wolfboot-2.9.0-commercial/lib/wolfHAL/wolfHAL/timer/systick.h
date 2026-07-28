/* systick.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_SYSTICK_H
#define WHAL_SYSTICK_H

#include <stddef.h>
#include <wolfHAL/timer/timer.h>

/*
 * @file systick.h
 * @brief Configuration for the Cortex-M SysTick timer driver.
 */

/*
 * @brief Available SysTick clock sources.
 */
typedef enum {
    WHAL_SYSTICK_CLKSRC_EXT,
    WHAL_SYSTICK_CLKSRC_SYSCLK,
} whal_SysTick_ClkSrc;

/*
 * @brief Enable or disable the SysTick interrupt generation.
 */
typedef enum {
    WHAL_SYSTICK_TICKINT_DISABLED,
    WHAL_SYSTICK_TICKINT_ENABLED,
} whal_SysTick_TickInt;

/*
 * @brief SysTick configuration parameters.
 */
typedef struct {
    size_t cyclesPerTick;
    whal_SysTick_ClkSrc clkSrc;
    whal_SysTick_TickInt tickInt;
} whal_SysTick_Cfg;

/*
 * @brief Platform-owned SysTick device singleton. Defined in the driver TU
 * from the WHAL_CFG_SYSTICK_DEV initializer in board.h.
 */
extern const whal_Timer whal_SysTick_Dev;

#ifndef WHAL_CFG_SYSTICK_TIMER_DIRECT_API_MAPPING
/*
 * @brief Driver instance for the Cortex-M SysTick timer.
 */
extern const whal_TimerDriver whal_SysTick_Driver;

/*
 * @brief Initialize the SysTick timer with the configured clock and reload values.
 *
 * @param timerDev Timer device instance to initialize.
 *
 * @retval WHAL_SUCCESS Initialization completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_SysTick_Init(whal_Timer *timerDev);
/*
 * @brief Deinitialize the SysTick timer.
 *
 * @param timerDev Timer device instance to deinitialize.
 *
 * @retval WHAL_SUCCESS Deinit completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_SysTick_Deinit(whal_Timer *timerDev);
/*
 * @brief Start the SysTick counter.
 *
 * @param timerDev Timer device instance.
 *
 * @retval WHAL_SUCCESS Timer started.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_SysTick_Start(whal_Timer *timerDev);
/*
 * @brief Stop the SysTick counter.
 *
 * @param timerDev Timer device instance.
 *
 * @retval WHAL_SUCCESS Timer stopped.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_SysTick_Stop(whal_Timer *timerDev);
/*
 * @brief Reset the SysTick counter state.
 *
 * @param timerDev Timer device instance.
 *
 * @retval WHAL_SUCCESS Timer reset.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_SysTick_Reset(whal_Timer *timerDev);
#endif /* !WHAL_CFG_SYSTICK_TIMER_DIRECT_API_MAPPING */

#endif /* WHAL_SYSTICK_H */
