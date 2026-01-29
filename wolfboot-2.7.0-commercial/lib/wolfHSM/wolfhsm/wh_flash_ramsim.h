/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef WH_FLASH_RAMSIM_H_
#define WH_FLASH_RAMSIM_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

/* Configuration and context structures */
typedef struct {
    uint8_t* memory;
    uint32_t size;
    uint32_t sectorSize;
    uint32_t pageSize;
    uint8_t  erasedByte;
    const uint8_t* initData;  /* Optional initialization data */
    uint8_t WH_PAD[7];
} whFlashRamsimCfg;

typedef struct {
    uint8_t* memory;
    uint32_t size;
    uint32_t sectorSize;
    uint32_t pageSize;
    int      writeLocked;
    uint8_t  erasedByte;
    uint8_t WH_PAD[7];
} whFlashRamsimCtx;


/* Simulator function prototypes */
int whFlashRamsim_Init(void* context, const void* config);
int whFlashRamsim_Cleanup(void* context);
int whFlashRamsim_Program(void* context, uint32_t offset, uint32_t size,
                             const uint8_t* data);
int whFlashRamsim_Read(void* context, uint32_t offset, uint32_t size,
                          uint8_t* data);
int whFlashRamsim_Erase(void* context, uint32_t offset, uint32_t size);
int whFlashRamsim_Verify(void* context, uint32_t offset, uint32_t size,
                            const uint8_t* data);
int whFlashRamsim_BlankCheck(void* context, uint32_t offset, uint32_t size);
uint32_t whFlashRamsim_PartitionSize(void* context);
int whFlashRamsim_WriteLock(void* context, uint32_t offset, uint32_t size);
int whFlashRamsim_WriteUnlock(void* context, uint32_t offset, uint32_t size);

/* clang-format off */
#define WH_FLASH_RAMSIM_CB                              \
    {                                                   \
        .Init          = whFlashRamsim_Init,            \
        .Cleanup       = whFlashRamsim_Cleanup,         \
        .PartitionSize = whFlashRamsim_PartitionSize,   \
        .WriteLock     = whFlashRamsim_WriteLock,       \
        .WriteUnlock   = whFlashRamsim_WriteUnlock,     \
        .Read          = whFlashRamsim_Read,            \
        .Program       = whFlashRamsim_Program,         \
        .Erase         = whFlashRamsim_Erase,           \
        .Verify        = whFlashRamsim_Verify,          \
        .BlankCheck    = whFlashRamsim_BlankCheck,      \
    }
/* clang-format on */

#endif /* !WH_FLASH_RAMSIM_H_ */
