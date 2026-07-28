/* stm32f0_i2c.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32F0_I2C_H
#define WHAL_STM32F0_I2C_H

/*
 * @file stm32f0_i2c.h
 * @brief STM32F0 I2C driver (alias for STM32WB I2C).
 *
 * The STM32F0 I2C peripheral is register-compatible with the STM32WB I2C
 * (I2C v2 with CR1/CR2/TIMINGR). This header re-exports the STM32WB I2C
 * driver types and symbols under STM32F0-specific names.
 */

#include <wolfHAL/i2c/stm32wb_i2c.h>

typedef whal_Stm32wb_I2c_Cfg whal_Stm32f0_I2c_Cfg;

#ifndef WHAL_CFG_STM32F0_I2C_DIRECT_API_MAPPING
#define whal_Stm32f0_I2c_Driver   whal_Stm32wb_I2c_Driver
#define whal_Stm32f0_I2c_Init     whal_Stm32wb_I2c_Init
#define whal_Stm32f0_I2c_Deinit   whal_Stm32wb_I2c_Deinit
#define whal_Stm32f0_I2c_StartCom whal_Stm32wb_I2c_StartCom
#define whal_Stm32f0_I2c_EndCom   whal_Stm32wb_I2c_EndCom
#define whal_Stm32f0_I2c_Transfer whal_Stm32wb_I2c_Transfer
#endif /* !WHAL_CFG_STM32F0_I2C_DIRECT_API_MAPPING */

#endif /* WHAL_STM32F0_I2C_H */
