/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * wolfhsm/wh_flash.h
 *
 * Abstract library to implement a flash-like back end.
 *
 */

#ifndef WOLFHSM_WH_FLASH_H_
#define WOLFHSM_WH_FLASH_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

typedef struct {
    int (*Init)(void* context,const void* config);
    int (*Cleanup)(void* context);

/**
 * @brief Returns the partition size in bytes (usually half of the total size).
 *
 * The partition size is the minimum size that the NVM Flash driver will erase
 * when using a wh_flash interface.  This also represents the offset alignment.
 *
 * @param[in] context Pointer to the flash context.
 * @return uint32_t Returns 0 on error, >0 for the partition size
 */
    uint32_t (*PartitionSize)(void* context);

/**
 * @brief Requests a write lock on at least the requested offset and size.
 *
 * Mark at least the requested area as "locked", meaning requests to program or
 * erase this area will return an error.  Locks are not nested, so a single
 * unlock request is sufficient.  Repeated locking of the same area is not an
 * error.
 *
 * @param[in] context Pointer to the flash context.
 * @param[in] offset Offset in bytes to the start of the requested locked area
 * @param[in] size Size in bytes of the requested locked area
 * @return int Returns 0 on success, <0 on error WH_ERROR_*
 */
    int (*WriteLock)(void* context,
            uint32_t offset, uint32_t size);
/**
 * @brief Requests a write unlock on at least the requested offset and size.
 *
 * Mark at least the requested area as "unlocked", meaning requests to program
 * or erase this area will not return an error.  Repeated unlocking of the same
 * area is not an error.
 *
 * @param[in] context Pointer to the flash context.
 * @param[in] offset Offset in bytes to the start of the requested unlocked area
 * @param[in] size Size in bytes of the unrequested locked area
 * @return int Returns 0 on success, <0 on error WH_ERROR_*
 */
    int (*WriteUnlock)(void* context,
            uint32_t offset, uint32_t size);

/**
 * @brief Read from requested offset and size into data.
 *
 * Copy data from the flash partition into the buffer pointed to be data.  It is
 * an error to pass data==NULL and size!=0.  If size==0, then the offset should
 * be tested to for validity.
 *
 * @param[in] context Pointer to the flash context.
 * @param[in] offset Offset in bytes to the start of the requested area
 * @param[in] size Size in bytes of the requested area
 * @param[in] data Pointer to buffer of at least size bytes
 * @return int Returns 0 on success, <0 on error WH_ERROR_*
 */
    int (*Read)(void* context,
            uint32_t offset, uint32_t size, uint8_t* data);

/**
 * @brief Program at the requested offset and size from data.
 *
 * Copy data from the buffer pointed to be data into the flash partition.  It is
 * an error to pass data==NULL and size!=0.  If size==0, then the offset should
 * be tested to for validity.  Most flash devices must be Erased before
 * Programming, but this function is not expected to Erase automatically.
 * Offset must honor any restrictions of the device.
 *
 * @param[in] context Pointer to the flash context.
 * @param[in] offset Offset in bytes to the start of the requested area
 * @param[in] size Size in bytes of the requested area
 * @param[in] data Pointer to buffer of at least size bytes
 * @return int Returns 0 on success, <0 on error WH_ERROR_*
 */
    int (*Program)(void* context,
            uint32_t offset, uint32_t size, const uint8_t* data);

/**
 * @brief Erase at the requested offset and size.
 *
 * Erase the flash at the requested offset and size.  The device will likely
 * erase a larger size that around the requested offset, with this library
 * assuming that size and granularity is the Partition Size.  If size==0, then
 * the offset should be tested to for validity.
 *
 * @param[in] context Pointer to the flash context.
 * @param[in] offset Offset in bytes to the start of the requested area
 * @param[in] size Size in bytes of the requested area
 * @return int Returns 0 on success, <0 on error WH_ERROR_*
 */
    int (*Erase)(void* context,
            uint32_t offset, uint32_t size);

/**
 * @brief Read from requested offset and size to verify is matches data.
 *
 * Compare the contents of the flash with the contents pointed to by data.  It
 * is an error to pass data==NULL and size!=0.  If size==0, then the offset
 * should be tested to for validity.
 *
 * @param[in] context Pointer to the flash context.
 * @param[in] offset Offset in bytes to the start of the requested area
 * @param[in] size Size in bytes of the requested area
 * @param[in] data Pointer to buffer of at least size bytes
 * @return int Returns 0 on success, <0 on error WH_ERROR_*
 */
    int (*Verify)(void* context,
            uint32_t offset, uint32_t size, const uint8_t* data);

/**
 * @brief Check the requested offset and size is erased on the flash.
 *
 * Check that the contents of the flash are erased for the requested area. If
 * size==0, then the offset should be tested to for validity.
 *
 * @param[in] context Pointer to the flash context.
 * @param[in] offset Offset in bytes to the start of the requested area
 * @param[in] size Size in bytes of the requested area
 * @return int Returns 0 on success, <0 on error WH_ERROR_*
 */
    int (*BlankCheck)(void* context,
            uint32_t offset, uint32_t size);
} whFlashCb;

#endif /* !WOLFHSM_WH_FLASH_H_ */
