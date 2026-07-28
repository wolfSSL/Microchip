/* stm32u5_rng.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32U5_RNG_H
#define WHAL_STM32U5_RNG_H

/**
 * @file stm32u5_rng.h
 * @brief STM32U5 RNG driver (alias for STM32WBA RNG).
 *
 * The STM32U5 RNG peripheral is register-compatible with the STM32WBA RNG
 * (CONDRST/CONFIGLOCK + NIST SP800-90B health check sequence). This header
 * re-exports the STM32WBA RNG driver types and symbols under STM32U5-specific
 * names.
 */

#include <wolfHAL/rng/stm32wba_rng.h>

typedef whal_Stm32wba_Rng_Cfg whal_Stm32u5_Rng_Cfg;

#define whal_Stm32u5_Rng_Dev whal_Stm32wba_Rng_Dev

#ifndef WHAL_CFG_STM32U5_RNG_DIRECT_API_MAPPING
#define whal_Stm32u5_Rng_Driver   whal_Stm32wba_Rng_Driver
#define whal_Stm32u5_Rng_Init     whal_Stm32wba_Rng_Init
#define whal_Stm32u5_Rng_Deinit   whal_Stm32wba_Rng_Deinit
#define whal_Stm32u5_Rng_Generate whal_Stm32wba_Rng_Generate
#endif /* !WHAL_CFG_STM32U5_RNG_DIRECT_API_MAPPING */

/* Config initializer macro alias. The U5 board.h supplies the body under
 * the U5-prefixed name; the WBA driver source consumes the WBA name. */
#define WHAL_CFG_STM32WBA_RNG_DEV WHAL_CFG_STM32U5_RNG_DEV

#endif /* WHAL_STM32U5_RNG_H */
