/* stm32n6_hash.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32N6_HASH_H
#define WHAL_STM32N6_HASH_H

/**
 * @file stm32n6_hash.h
 * @brief STM32N6 HASH driver (alias for STM32WBA HASH).
 *
 * The STM32N6 HASH peripheral is register-compatible with the STM32WBA HASH
 * (CR/DIN/STR/HRAx/IMR/SR/CSRx at identical offsets). This header re-exports
 * under STM32N6-specific names.
 */

#include <wolfHAL/crypto/stm32wba_hash.h>

typedef whal_Stm32wba_Hash_Cfg whal_Stm32n6_Hash_Cfg;

typedef whal_Stm32wba_HmacSha1_State   whal_Stm32n6_HmacSha1_State;
typedef whal_Stm32wba_HmacSha224_State  whal_Stm32n6_HmacSha224_State;
typedef whal_Stm32wba_HmacSha256_State  whal_Stm32n6_HmacSha256_State;

#define whal_Stm32n6_Hash_Dev       whal_Stm32wba_Hash_Dev
#define whal_Stm32n6_Sha1_Dev       whal_Stm32wba_Sha1_Dev
#define whal_Stm32n6_Sha224_Dev     whal_Stm32wba_Sha224_Dev
#define whal_Stm32n6_Sha256_Dev     whal_Stm32wba_Sha256_Dev
#define whal_Stm32n6_HmacSha1_Dev   whal_Stm32wba_HmacSha1_Dev
#define whal_Stm32n6_HmacSha224_Dev whal_Stm32wba_HmacSha224_Dev
#define whal_Stm32n6_HmacSha256_Dev whal_Stm32wba_HmacSha256_Dev

#define whal_Stm32n6_Hash_CryptoDriver    whal_Stm32wba_Hash_CryptoDriver

#define whal_Stm32n6_Hash_Sha1Driver      whal_Stm32wba_Hash_Sha1Driver
#define whal_Stm32n6_Hash_Sha224Driver    whal_Stm32wba_Hash_Sha224Driver
#define whal_Stm32n6_Hash_Sha256Driver    whal_Stm32wba_Hash_Sha256Driver
#define whal_Stm32n6_Hash_HmacSha1Driver  whal_Stm32wba_Hash_HmacSha1Driver
#define whal_Stm32n6_Hash_HmacSha224Driver whal_Stm32wba_Hash_HmacSha224Driver
#define whal_Stm32n6_Hash_HmacSha256Driver whal_Stm32wba_Hash_HmacSha256Driver

/* Config initializer macro aliases. The N6 board.h supplies the bodies
 * under N6-prefixed names; the WBA driver source consumes the WBA names. */
#define WHAL_CFG_STM32WBA_HASH_DEV             WHAL_CFG_STM32N6_HASH_DEV
#define WHAL_CFG_STM32WBA_HASH_SHA1_DEV        WHAL_CFG_STM32N6_HASH_SHA1_DEV
#define WHAL_CFG_STM32WBA_HASH_SHA224_DEV      WHAL_CFG_STM32N6_HASH_SHA224_DEV
#define WHAL_CFG_STM32WBA_HASH_SHA256_DEV      WHAL_CFG_STM32N6_HASH_SHA256_DEV
#define WHAL_CFG_STM32WBA_HASH_HMAC_SHA1_DEV   WHAL_CFG_STM32N6_HASH_HMAC_SHA1_DEV
#define WHAL_CFG_STM32WBA_HASH_HMAC_SHA224_DEV WHAL_CFG_STM32N6_HASH_HMAC_SHA224_DEV
#define WHAL_CFG_STM32WBA_HASH_HMAC_SHA256_DEV WHAL_CFG_STM32N6_HASH_HMAC_SHA256_DEV

#endif /* WHAL_STM32N6_HASH_H */
