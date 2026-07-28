/* stm32u5_aes.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32U5_AES_H
#define WHAL_STM32U5_AES_H

/**
 * @file stm32u5_aes.h
 * @brief STM32U5 AES driver (alias for STM32WB AES).
 *
 * The STM32U5 AES peripheral is register-compatible with the STM32WB AES.
 * This header re-exports the STM32WB AES driver types and symbols under
 * STM32U5-specific names.
 */

#include <wolfHAL/crypto/stm32wb_aes.h>

typedef whal_Stm32wb_Aes_Cfg whal_Stm32u5_Aes_Cfg;

typedef whal_Stm32wb_AesGcm_State whal_Stm32u5_AesGcm_State;
typedef whal_Stm32wb_AesCcm_State whal_Stm32u5_AesCcm_State;

#define whal_Stm32u5_Aes_Dev     whal_Stm32wb_Aes_Dev
#define whal_Stm32u5_AesEcb_Dev  whal_Stm32wb_AesEcb_Dev
#define whal_Stm32u5_AesCbc_Dev  whal_Stm32wb_AesCbc_Dev
#define whal_Stm32u5_AesCtr_Dev  whal_Stm32wb_AesCtr_Dev
#define whal_Stm32u5_AesGcm_Dev  whal_Stm32wb_AesGcm_Dev
#define whal_Stm32u5_AesGmac_Dev whal_Stm32wb_AesGmac_Dev
#define whal_Stm32u5_AesCcm_Dev  whal_Stm32wb_AesCcm_Dev

#define whal_Stm32u5_Aes_CryptoDriver whal_Stm32wb_Aes_CryptoDriver

#define whal_Stm32u5_Aes_EcbDriver  whal_Stm32wb_Aes_EcbDriver
#define whal_Stm32u5_Aes_CbcDriver  whal_Stm32wb_Aes_CbcDriver
#define whal_Stm32u5_Aes_CtrDriver  whal_Stm32wb_Aes_CtrDriver
#define whal_Stm32u5_Aes_GcmDriver  whal_Stm32wb_Aes_GcmDriver
#define whal_Stm32u5_Aes_GmacDriver whal_Stm32wb_Aes_GmacDriver
#define whal_Stm32u5_Aes_CcmDriver  whal_Stm32wb_Aes_CcmDriver

/* Config initializer macro aliases. The U5 board.h supplies the bodies
 * under U5-prefixed names; the WB driver source consumes the WB names. */
#define WHAL_CFG_STM32WB_AES_DEV      WHAL_CFG_STM32U5_AES_DEV
#define WHAL_CFG_STM32WB_AES_ECB_DEV  WHAL_CFG_STM32U5_AES_ECB_DEV
#define WHAL_CFG_STM32WB_AES_CBC_DEV  WHAL_CFG_STM32U5_AES_CBC_DEV
#define WHAL_CFG_STM32WB_AES_CTR_DEV  WHAL_CFG_STM32U5_AES_CTR_DEV
#define WHAL_CFG_STM32WB_AES_GCM_DEV  WHAL_CFG_STM32U5_AES_GCM_DEV
#define WHAL_CFG_STM32WB_AES_GMAC_DEV WHAL_CFG_STM32U5_AES_GMAC_DEV
#define WHAL_CFG_STM32WB_AES_CCM_DEV  WHAL_CFG_STM32U5_AES_CCM_DEV

#endif /* WHAL_STM32U5_AES_H */
