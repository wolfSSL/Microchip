/* stm32wb_rng.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB_RNG_H
#define WHAL_STM32WB_RNG_H

#include <stdint.h>
#include <wolfHAL/rng/rng.h>
#include <wolfHAL/timeout.h>

/*
 * @file stm32wb_rng.h
 * @brief STM32WB RNG driver configuration.
 *
 * The STM32WB true random number generator provides 32-bit random values
 * from an analog noise source. The peripheral requires the RNG clock to
 * be enabled and produces one 32-bit word at a time via the DR register.
 */

/*
 * @brief RNG device configuration.
 */
typedef struct whal_Stm32wb_Rng_Cfg {
    whal_Timeout *timeout;
} whal_Stm32wb_Rng_Cfg;

/*
 * @brief Platform-owned RNG device singleton. Defined in the driver TU
 * from the WHAL_CFG_STM32WB_RNG_DEV initializer in board.h.
 */
extern const whal_Rng whal_Stm32wb_Rng_Dev;

#ifndef WHAL_CFG_STM32WB_RNG_DIRECT_API_MAPPING
/*
 * @brief Driver instance for STM32WB RNG peripheral.
 */
extern const whal_RngDriver whal_Stm32wb_Rng_Driver;

/*
 * @brief Initialize the STM32WB RNG peripheral.
 *
 * @param rngDev RNG device instance.
 *
 * @retval WHAL_SUCCESS Initialization completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Stm32wb_Rng_Init(whal_Rng *rngDev);
/*
 * @brief Deinitialize the STM32WB RNG peripheral.
 *
 * @param rngDev RNG device instance.
 *
 * @retval WHAL_SUCCESS Deinit completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Stm32wb_Rng_Deinit(whal_Rng *rngDev);
/*
 * @brief Generate random data.
 *
 * @param rngDev    RNG device instance.
 * @param rngData   Destination buffer.
 * @param rngDataSz Number of random bytes to generate.
 *
 * @retval WHAL_SUCCESS Buffer filled with random data.
 * @retval WHAL_EINVAL  Invalid arguments or seed/clock error detected.
 */
whal_Error whal_Stm32wb_Rng_Generate(whal_Rng *rngDev, void *rngData, size_t rngDataSz);
#endif /* !WHAL_CFG_STM32WB_RNG_DIRECT_API_MAPPING */

#endif /* WHAL_STM32WB_RNG_H */
