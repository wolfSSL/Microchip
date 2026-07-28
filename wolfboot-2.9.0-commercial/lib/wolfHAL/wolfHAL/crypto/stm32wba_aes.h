/* stm32wba_aes.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WBA_AES_H
#define WHAL_STM32WBA_AES_H

/**
 * @file stm32wba_aes.h
 * @brief STM32WBA AES driver (alias for STM32WB AES).
 *
 * The STM32WBA AES peripheral is register-compatible with the STM32WB AES.
 * This header re-exports the STM32WB AES driver types and symbols under
 * STM32WBA-specific names.
 */

#include <wolfHAL/crypto/stm32wb_aes.h>

typedef whal_Stm32wb_Aes_Cfg whal_Stm32wba_Aes_Cfg;

typedef whal_Stm32wb_AesGcm_State whal_Stm32wba_AesGcm_State;
typedef whal_Stm32wb_AesCcm_State whal_Stm32wba_AesCcm_State;

#define whal_Stm32wba_Aes_Dev     whal_Stm32wb_Aes_Dev
#define whal_Stm32wba_AesEcb_Dev  whal_Stm32wb_AesEcb_Dev
#define whal_Stm32wba_AesCbc_Dev  whal_Stm32wb_AesCbc_Dev
#define whal_Stm32wba_AesCtr_Dev  whal_Stm32wb_AesCtr_Dev
#define whal_Stm32wba_AesGcm_Dev  whal_Stm32wb_AesGcm_Dev
#define whal_Stm32wba_AesGmac_Dev whal_Stm32wb_AesGmac_Dev
#define whal_Stm32wba_AesCcm_Dev  whal_Stm32wb_AesCcm_Dev

#define whal_Stm32wba_Aes_CryptoDriver whal_Stm32wb_Aes_CryptoDriver

#define whal_Stm32wba_Aes_EcbDriver  whal_Stm32wb_Aes_EcbDriver
#define whal_Stm32wba_Aes_CbcDriver  whal_Stm32wb_Aes_CbcDriver
#define whal_Stm32wba_Aes_CtrDriver  whal_Stm32wb_Aes_CtrDriver
#define whal_Stm32wba_Aes_GcmDriver  whal_Stm32wb_Aes_GcmDriver
#define whal_Stm32wba_Aes_GmacDriver whal_Stm32wb_Aes_GmacDriver
#define whal_Stm32wba_Aes_CcmDriver  whal_Stm32wb_Aes_CcmDriver

/* Config initializer macro aliases. The WBA board.h supplies the bodies
 * under WBA-prefixed names; the WB driver source consumes the WB names. */
#define WHAL_CFG_STM32WB_AES_DEV      WHAL_CFG_STM32WBA_AES_DEV
#define WHAL_CFG_STM32WB_AES_ECB_DEV  WHAL_CFG_STM32WBA_AES_ECB_DEV
#define WHAL_CFG_STM32WB_AES_CBC_DEV  WHAL_CFG_STM32WBA_AES_CBC_DEV
#define WHAL_CFG_STM32WB_AES_CTR_DEV  WHAL_CFG_STM32WBA_AES_CTR_DEV
#define WHAL_CFG_STM32WB_AES_GCM_DEV  WHAL_CFG_STM32WBA_AES_GCM_DEV
#define WHAL_CFG_STM32WB_AES_GMAC_DEV WHAL_CFG_STM32WBA_AES_GMAC_DEV
#define WHAL_CFG_STM32WB_AES_CCM_DEV  WHAL_CFG_STM32WBA_AES_CCM_DEV

#endif /* WHAL_STM32WBA_AES_H */
