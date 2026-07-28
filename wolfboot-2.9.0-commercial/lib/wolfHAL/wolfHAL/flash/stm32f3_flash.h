/* stm32f3_flash.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32F3_FLASH_H
#define WHAL_STM32F3_FLASH_H

/*
 * @file stm32f3_flash.h
 * @brief STM32F3 flash driver (alias for STM32F0 flash).
 *
 * The STM32F3 embedded flash uses the same register layout as the STM32F0:
 * ACR/KEYR/SR/CR/AR with identical bit positions, 2 KB page erase, and
 * half-word (16-bit) programming.
 */

#include <wolfHAL/flash/stm32f0_flash.h>

typedef whal_Stm32f0_Flash_Cfg whal_Stm32f3_Flash_Cfg;

#define whal_Stm32f3_Flash_Dev whal_Stm32f0_Flash_Dev

#define WHAL_STM32F3_FLASH_LATENCY_0 WHAL_STM32F0_FLASH_LATENCY_0
#define WHAL_STM32F3_FLASH_LATENCY_1 WHAL_STM32F0_FLASH_LATENCY_1
#define WHAL_STM32F3_FLASH_LATENCY_2 2

#ifndef WHAL_CFG_STM32F3_FLASH_DIRECT_API_MAPPING
#define whal_Stm32f3_Flash_Driver whal_Stm32f0_Flash_Driver
#define whal_Stm32f3_Flash_Init   whal_Stm32f0_Flash_Init
#define whal_Stm32f3_Flash_Deinit whal_Stm32f0_Flash_Deinit
#define whal_Stm32f3_Flash_Lock   whal_Stm32f0_Flash_Lock
#define whal_Stm32f3_Flash_Unlock whal_Stm32f0_Flash_Unlock
#define whal_Stm32f3_Flash_Read   whal_Stm32f0_Flash_Read
#define whal_Stm32f3_Flash_Write  whal_Stm32f0_Flash_Write
#define whal_Stm32f3_Flash_Erase  whal_Stm32f0_Flash_Erase
#endif /* !WHAL_CFG_STM32F3_FLASH_DIRECT_API_MAPPING */

#define whal_Stm32f3_Flash_Ext_SetLatency whal_Stm32f0_Flash_Ext_SetLatency

/* Config initializer macro alias. The F3 board.h supplies the body under
 * the F3-prefixed name; the F0 driver source consumes the F0 name. */
#define WHAL_CFG_STM32F0_FLASH_DEV WHAL_CFG_STM32F3_FLASH_DEV

#endif /* WHAL_STM32F3_FLASH_H */
