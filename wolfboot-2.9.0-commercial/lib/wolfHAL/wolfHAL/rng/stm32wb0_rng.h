/* stm32wb0_rng.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB0_RNG_H
#define WHAL_STM32WB0_RNG_H

#include <stdint.h>
#include <wolfHAL/rng/rng.h>
#include <wolfHAL/timeout.h>

/**
 * @file stm32wb0_rng.h
 * @brief STM32WB0 RNG driver configuration.
 *
 * The STM32WB0 RNG is a Bluetooth-LE-oriented true random number generator
 * that differs from the standard STM32 RNG IP:
 *   - RNG_VAL is a 16-bit register (not 32-bit DR), delivered every 20
 *     RNGCLK cycles. Reads stall the AHB bus until a value is available.
 *   - Only 32-bit accesses are allowed on the RNG registers; an 8-bit or
 *     16-bit access generates an AHB fault.
 *   - RNG_CR has RNG_DIS at bit 2 (active-low disable; cleared at reset)
 *     and TST_CLK at bit 3.
 *   - RNG_SR exposes RNGRDY (bit 0), REVCLK (bit 1), and FAULT (bit 2).
 *   - No CONDRST, no CED, no clock source selection — RNGCLK is a fixed
 *     16 MHz internal feed enabled through RCC_AHBENR.RNGEN.
 */

/**
 * @brief RNG device configuration.
 */
typedef struct whal_Stm32wb0_Rng_Cfg {
    whal_Timeout *timeout;
} whal_Stm32wb0_Rng_Cfg;

/**
 * @brief Platform-owned RNG device singleton. Defined in the driver TU
 * from the WHAL_CFG_STM32WB0_RNG_DEV initializer in board.h.
 */
extern const whal_Rng whal_Stm32wb0_Rng_Dev;

#ifndef WHAL_CFG_STM32WB0_RNG_DIRECT_API_MAPPING
/**
 * @brief Driver instance for STM32WB0 RNG peripheral.
 */
extern const whal_RngDriver whal_Stm32wb0_Rng_Driver;

/**
 * @brief Initialize the STM32WB0 RNG peripheral.
 *
 * Enables the RNG analog block (clears RNG_DIS).
 *
 * @param rngDev RNG device instance.
 *
 * @retval WHAL_SUCCESS Initialization completed.
 */
whal_Error whal_Stm32wb0_Rng_Init(whal_Rng *rngDev);
/**
 * @brief Deinitialize the STM32WB0 RNG peripheral.
 *
 * Disables the RNG by setting RNG_DIS to put the internal free-running
 * oscillators into power-down.
 *
 * @param rngDev RNG device instance.
 *
 * @retval WHAL_SUCCESS Deinit completed.
 */
whal_Error whal_Stm32wb0_Rng_Deinit(whal_Rng *rngDev);
/**
 * @brief Generate random data.
 *
 * Reads 16-bit RNG_VAL values until rngDataSz bytes have been delivered.
 *
 * @param rngDev    RNG device instance.
 * @param rngData   Destination buffer.
 * @param rngDataSz Number of random bytes to generate.
 *
 * @retval WHAL_SUCCESS  Buffer filled with random data.
 * @retval WHAL_EINVAL   Null destination buffer.
 */
whal_Error whal_Stm32wb0_Rng_Generate(whal_Rng *rngDev, void *rngData,
                                      size_t rngDataSz);
#endif /* !WHAL_CFG_STM32WB0_RNG_DIRECT_API_MAPPING */

#endif /* WHAL_STM32WB0_RNG_H */
