/* stm32wb0_pka.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB0_PKA_H
#define WHAL_STM32WB0_PKA_H

/**
 * @file stm32wb0_pka.h
 * @brief STM32WB0 public-key accelerator driver (alias for STM32WB PKA).
 *
 * The STM32WB0 PKA peripheral is register-compatible with the STM32WB
 * PKA:
 *   - PKA_CR/SR/CLRFR at offsets 0x00/0x04/0x08 with matching bit
 *     positions (EN=0, START=1, MODE[13:8], PROCENDIE/F=17,
 *     RAMERRIE/F=19, ADDRERRIE/F=20).
 *   - Identical opcode list and operating modes (RM0529 sections
 *     13.4.1–13.4.18).
 *   - Identical PKA RAM layout (PKA_RAM at +0x400). Modular
 *     exponentiation operand offsets at 0x400/0x404/0x594/0xA44/0xBD0/
 *     0xD5C are verified against RM0529 Table 38.
 * This header re-exports the STM32WB PKA driver symbols under
 * STM32WB0-specific names.
 */

#include <wolfHAL/crypto/stm32wb_pka.h>

typedef whal_Stm32wb_Pka_Cfg whal_Stm32wb0_Pka_Cfg;

#define whal_Stm32wb0_Pka_Dev whal_Stm32wb_Pka_Dev

#ifndef WHAL_CFG_STM32WB0_PKA_INIT_DIRECT_API_MAPPING
#define whal_Stm32wb0_Pka_Init           whal_Stm32wb_Pka_Init
#define whal_Stm32wb0_Pka_Deinit         whal_Stm32wb_Pka_Deinit
#define whal_Stm32wb0_Pka_CryptoDriver   whal_Stm32wb_Pka_CryptoDriver
#endif /* !WHAL_CFG_STM32WB0_PKA_INIT_DIRECT_API_MAPPING */

#ifndef WHAL_CFG_STM32WB0_PKA_DIRECT_API_MAPPING
#define whal_Stm32wb0_Pka_ModExp    whal_Stm32wb_Pka_ModExp
#define whal_Stm32wb0_Pka_ModInv    whal_Stm32wb_Pka_ModInv
#define whal_Stm32wb0_Pka_ModReduce whal_Stm32wb_Pka_ModReduce
#define whal_Stm32wb0_Pka_IntMul    whal_Stm32wb_Pka_IntMul
#define whal_Stm32wb0_Pka_IntSub    whal_Stm32wb_Pka_IntSub
#define whal_Stm32wb0_Pka_RsaCrtExp whal_Stm32wb_Pka_RsaCrtExp
#endif /* !WHAL_CFG_STM32WB0_PKA_DIRECT_API_MAPPING */

/* Config initializer macro alias. The WB0 board.h supplies the body under
 * the WB0-prefixed name; the WB driver source consumes the WB name. */
#define WHAL_CFG_STM32WB_PKA_DEV WHAL_CFG_STM32WB0_PKA_DEV

#endif /* WHAL_STM32WB0_PKA_H */
