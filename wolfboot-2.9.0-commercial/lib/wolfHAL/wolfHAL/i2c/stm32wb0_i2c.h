/* stm32wb0_i2c.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB0_I2C_H
#define WHAL_STM32WB0_I2C_H

/**
 * @file stm32wb0_i2c.h
 * @brief STM32WB0 I2C driver (alias for STM32WB I2C).
 *
 * The STM32WB0 I2C peripheral is register-compatible with the wider
 * STM32 V2 I2C (CR1, CR2, TIMINGR, ISR, ICR, RXDR, TXDR layout per
 * RM0529 section 21.6). This header re-exports the STM32WB I2C driver
 * types and symbols under STM32WB0-specific names.
 */

#include <wolfHAL/i2c/stm32wb_i2c.h>

typedef whal_Stm32wb_I2c_Cfg whal_Stm32wb0_I2c_Cfg;

#define whal_Stm32wb0_I2c_Dev whal_Stm32wb_I2c_Dev

#ifndef WHAL_CFG_STM32WB0_I2C_DIRECT_API_MAPPING
#define whal_Stm32wb0_I2c_Driver   whal_Stm32wb_I2c_Driver
#define whal_Stm32wb0_I2c_Init     whal_Stm32wb_I2c_Init
#define whal_Stm32wb0_I2c_Deinit   whal_Stm32wb_I2c_Deinit
#define whal_Stm32wb0_I2c_StartCom whal_Stm32wb_I2c_StartCom
#define whal_Stm32wb0_I2c_EndCom   whal_Stm32wb_I2c_EndCom
#define whal_Stm32wb0_I2c_Transfer whal_Stm32wb_I2c_Transfer
#endif /* !WHAL_CFG_STM32WB0_I2C_DIRECT_API_MAPPING */

/* Config initializer macro alias. The WB0 board.h supplies the body under
 * the WB0-prefixed name; the WB driver source consumes the WB name. */
#define WHAL_CFG_STM32WB_I2C_DEV WHAL_CFG_STM32WB0_I2C_DEV

#endif /* WHAL_STM32WB0_I2C_H */
