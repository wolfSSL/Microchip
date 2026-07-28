/* stm32wba_i2c.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Forward STM32WBA I2C config flags to STM32WB */
#ifdef WHAL_CFG_STM32WBA_I2C_DIRECT_API_MAPPING
#define WHAL_CFG_STM32WB_I2C_DIRECT_API_MAPPING
#endif
#ifdef WHAL_CFG_STM32WBA_I2C_SINGLE_INSTANCE
#define WHAL_CFG_STM32WB_I2C_SINGLE_INSTANCE
#endif

#include "stm32wb_i2c.c"
