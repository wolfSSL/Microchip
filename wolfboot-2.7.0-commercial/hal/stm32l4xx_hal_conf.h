/* stm32-4xx_hal_conf.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef __STM32L4xx_HAL_CONF_H
#define __STM32L4xx_HAL_CONF_H

#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED

 /* Many ST examples define this in stm32l4xx_hal_conf.h */
#ifndef TICK_INT_PRIORITY
    #define TICK_INT_PRIORITY 0U
#endif

#include "stm32l4xx_hal_def.h"

/* Pull in headers for the enabled modules */
#if defined(HAL_CORTEX_MODULE_ENABLED)
    #include "stm32l4xx_hal_cortex.h"
#endif
#if defined(HAL_FLASH_MODULE_ENABLED)
    #include "stm32l4xx_hal_flash.h"
    #include "stm32l4xx_hal_flash_ex.h"
#endif
#if defined(HAL_RCC_MODULE_ENABLED)
    #include "stm32l4xx_hal_rcc.h"
#endif

#define assert_param(expr) ((void)0U)

#endif /* __STM32L4xx_HAL_CONF_H */
