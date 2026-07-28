/* stm32wba_flash.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WBA_FLASH_H
#define WHAL_STM32WBA_FLASH_H

#include <wolfHAL/flash/flash.h>
#include <wolfHAL/timeout.h>

/*
 * @file stm32wba_flash.h
 * @brief STM32WBA flash driver configuration.
 *
 * The STM32WBA embedded flash provides:
 * - Up to 1 MB organized in 8 KB pages (128 pages)
 * - 128-bit (flash-word) programming
 * - Non-secure register variants (NSCR1, NSSR, NSKEYR)
 * - TrustZone support (this driver uses non-secure registers)
 *
 * Key register differences from STM32H5:
 * - NSKEYR at offset 0x008 (not 0x004)
 * - No separate NSCCR register (errors cleared via NSSR)
 * - Single bank (no BKSEL bit)
 */

/*
 * @brief STM32WBA flash driver configuration.
 */
typedef struct whal_Stm32wba_Flash_Cfg {
    size_t startAddr;          /* Flash region start address */
    size_t size;               /* Flash region size in bytes */
    whal_Timeout *timeout;     /* Optional timeout for poll loops */
} whal_Stm32wba_Flash_Cfg;

/*
 * @brief Driver instance for the STM32WBA embedded flash controller.
 */
extern const whal_FlashDriver whal_Stm32wba_Flash_Driver;
/*
 * @brief Platform-owned device singleton. Defined in the driver TU
 * from the WHAL_CFG_STM32WBA_FLASH_DEV initializer in board.h.
 */
extern const whal_Flash whal_Stm32wba_Flash_Dev;

/*
 * @brief Initialize the STM32WBA flash driver. Validates cfg.
 *
 * @param flashDev Flash device instance.
 *
 * @retval WHAL_SUCCESS Driver is ready.
 * @retval WHAL_EINVAL  Null pointer or missing cfg.
 */
whal_Error whal_Stm32wba_Flash_Init(whal_Flash *flashDev);

/*
 * @brief Deinitialize the STM32WBA flash driver.
 *
 * @param flashDev Flash device instance.
 *
 * @retval WHAL_SUCCESS Driver is deinitialized.
 * @retval WHAL_EINVAL  Null pointer.
 */
whal_Error whal_Stm32wba_Flash_Deinit(whal_Flash *flashDev);

/*
 * @brief Re-lock the STM32WBA flash for writes (sets NSCR1.LOCK).
 *
 * @param flashDev Flash device instance.
 * @param addr     Range start (ignored — flash is globally locked).
 * @param len      Range length (ignored).
 *
 * @retval WHAL_SUCCESS Flash is locked.
 * @retval WHAL_EINVAL  Null pointer.
 */
whal_Error whal_Stm32wba_Flash_Lock(whal_Flash *flashDev, size_t addr, size_t len);

/*
 * @brief Unlock the STM32WBA flash for writes via the NSKEYR sequence.
 *
 * @param flashDev Flash device instance.
 * @param addr     Range start (ignored — flash is globally unlocked).
 * @param len      Range length (ignored).
 *
 * @retval WHAL_SUCCESS Flash is unlocked.
 * @retval WHAL_EINVAL  Null pointer.
 * @retval WHAL_EHARDWARE Key sequence rejected.
 */
whal_Error whal_Stm32wba_Flash_Unlock(whal_Flash *flashDev, size_t addr, size_t len);

/*
 * @brief Read `dataSz` bytes from flash at `addr` into `data`.
 *
 * @param flashDev Flash device instance.
 * @param addr     Source address within the flash region.
 * @param data     Destination buffer.
 * @param dataSz   Number of bytes to read.
 *
 * @retval WHAL_SUCCESS Read completed.
 * @retval WHAL_EINVAL  Null pointer or address out of region.
 */
whal_Error whal_Stm32wba_Flash_Read(whal_Flash *flashDev, size_t addr, void *data, size_t dataSz);

/*
 * @brief Program `dataSz` bytes from `data` to flash at `addr`. Address and
 *        size must be 128-bit (flash-word) aligned.
 *
 * @param flashDev Flash device instance.
 * @param addr     Destination address within the flash region.
 * @param data     Source buffer.
 * @param dataSz   Number of bytes to write.
 *
 * @retval WHAL_SUCCESS Write completed.
 * @retval WHAL_EINVAL  Null pointer, misaligned address/size, or address out of region.
 * @retval WHAL_ETIMEOUT BSY did not clear within the configured timeout.
 * @retval WHAL_EHARDWARE Programming error reported in NSSR.
 */
whal_Error whal_Stm32wba_Flash_Write(whal_Flash *flashDev, size_t addr, const void *data, size_t dataSz);

/*
 * @brief Erase one or more 8 KB pages covering [addr, addr+dataSz).
 *
 * @param flashDev Flash device instance.
 * @param addr     First page address.
 * @param dataSz   Number of bytes to erase (rounded up to whole pages).
 *
 * @retval WHAL_SUCCESS Erase completed.
 * @retval WHAL_EINVAL  Null pointer or address out of region.
 * @retval WHAL_ETIMEOUT BSY did not clear within the configured timeout.
 * @retval WHAL_EHARDWARE Erase error reported in NSSR.
 */
whal_Error whal_Stm32wba_Flash_Erase(whal_Flash *flashDev, size_t addr, size_t dataSz);

/*
 * @brief Set the flash wait-state latency in FLASH_ACR.LATENCY. Must be
 *        programmed before raising HCLK above the previous latency's
 *        maximum supported frequency.
 *
 * @param flashDev Flash device instance.
 * @param latency  Wait state count (0–15).
 *
 * @retval WHAL_SUCCESS Latency updated.
 * @retval WHAL_EINVAL  Null pointer.
 */
whal_Error whal_Stm32wba_Flash_Ext_SetLatency(whal_Flash *flashDev, uint8_t latency);

#endif /* WHAL_STM32WBA_FLASH_H */
