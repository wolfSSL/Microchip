/* stm32f3_wwdg.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32F3_WWDG_H
#define WHAL_STM32F3_WWDG_H

/*
 * @file stm32f3_wwdg.h
 * @brief STM32F3 WWDG driver (alias for STM32F0 WWDG).
 *
 * The STM32F3 WWDG peripheral uses the same register layout as the STM32F0
 * (2-bit WDGTB prescaler at CFR bits 8:7).
 */

#include <wolfHAL/watchdog/stm32f0_wwdg.h>

typedef whal_Stm32f0_Wwdg_Cfg whal_Stm32f3_Wwdg_Cfg;

#define whal_Stm32f3_Wwdg_Dev whal_Stm32f0_Wwdg_Dev

#ifndef WHAL_CFG_STM32F3_WWDG_DIRECT_API_MAPPING
#define whal_Stm32f3_Wwdg_Driver  whal_Stm32f0_Wwdg_Driver
#define whal_Stm32f3_Wwdg_Init    whal_Stm32f0_Wwdg_Init
#define whal_Stm32f3_Wwdg_Deinit  whal_Stm32f0_Wwdg_Deinit
#define whal_Stm32f3_Wwdg_Refresh whal_Stm32f0_Wwdg_Refresh
#endif /* !WHAL_CFG_STM32F3_WWDG_DIRECT_API_MAPPING */

/* Config initializer macro alias. The F3 board.h supplies the body under
 * the F3-prefixed name; the F0 driver source consumes the F0 name. */
#define WHAL_CFG_STM32F0_WWDG_DEV WHAL_CFG_STM32F3_WWDG_DEV

#endif /* WHAL_STM32F3_WWDG_H */
