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
 * src/wh_flash_ramsim.c
 *
 */

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>
#include <stddef.h>  /* For NULL */

#include <string.h>
#include <stdbool.h>

#include "wolfhsm/wh_error.h"

#include "wolfhsm/wh_flash_ramsim.h"

/** Forward declarations */
static bool isMemoryErased(whFlashRamsimCtx* context, uint32_t offset,
                           uint32_t size);


static bool isMemoryErased(whFlashRamsimCtx* context, uint32_t offset,
                           uint32_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i) {
        if (context->memory[offset + i] != context->erasedByte) {
            return false;
        }
    }
    return true;
}


/* Simulator functions */
int whFlashRamsim_Init(void* context, const void* config)
{
    whFlashRamsimCtx*       ctx = (whFlashRamsimCtx*)context;
    const whFlashRamsimCfg* cfg = (const whFlashRamsimCfg*)config;

    if (ctx == NULL || cfg == NULL || (cfg->sectorSize == 0) ||
        (cfg->pageSize == 0) || (cfg->sectorSize % cfg->pageSize != 0) ||
        cfg->memory == NULL || cfg->size == 0) {
        return WH_ERROR_BADARGS;
    }

    memset(ctx, 0, sizeof(*ctx));
    ctx->size        = cfg->size;
    ctx->sectorSize  = cfg->sectorSize;
    ctx->pageSize    = cfg->pageSize;
    ctx->memory      = cfg->memory;
    ctx->erasedByte  = cfg->erasedByte;
    ctx->writeLocked = 0;

    /* Initialize memory based on initData or simulate starting from erased flash */
    if (cfg->initData != NULL) {
        memcpy(ctx->memory, cfg->initData, ctx->size);
    } else {
        memset(ctx->memory, ctx->erasedByte, ctx->size);
    }

    return WH_ERROR_OK;
}

int whFlashRamsim_Cleanup(void* context)
{
    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    return WH_ERROR_OK;
}

int whFlashRamsim_Program(void* context, uint32_t offset, uint32_t size,
                          const uint8_t* data)
{
    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;

    if (    (ctx == NULL) ||
            (ctx->memory == NULL) ||
            (ctx->pageSize == 0) ||
            ((data == NULL) && (size != 0))) {
        return WH_ERROR_BADARGS;
    }

    /* Ensure offset and size are within bounds and size is a multiple of page
     * size */
    if (offset + size > ctx->size || size % ctx->pageSize != 0) {
        return WH_ERROR_BADARGS;
    }

    /* Check if the target area is already erased */
    if (!isMemoryErased(ctx, offset, size)) {
        return WH_ERROR_NOTBLANK;
    }

    /* Check that partition isn't locked */
    if (size > 0 && ctx->writeLocked) {
        return WH_ERROR_LOCKED;
    }

    /* Perform the programming operation */
    if (size != 0) {
        memcpy(ctx->memory + offset, data, size);
    }
    return WH_ERROR_OK;
}

int whFlashRamsim_Read(void* context, uint32_t offset, uint32_t size,
                       uint8_t* data)
{
    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;

    if (    (ctx == NULL) ||
            (ctx->memory == NULL) ||
            ((offset + size) > ctx->size) ||
            ((data == NULL) && (size !=0))) {
        return WH_ERROR_BADARGS;
    }

    if (size != 0) {
        memcpy(data, ctx->memory + offset, size);
    }
    return WH_ERROR_OK;
}

int whFlashRamsim_Erase(void* context, uint32_t offset, uint32_t size)
{
    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;

    if (    (ctx == NULL) ||
            (ctx->memory == NULL) ||
            ((offset + size) > ctx->size)) {
        return WH_ERROR_BADARGS;
    }

    if (offset % ctx->sectorSize != 0 || size % ctx->sectorSize != 0) {
        return WH_ERROR_BADARGS;
    }

    /* Check that partition isn't locked */
    if ((size != 0) && (ctx->writeLocked)) {
        return WH_ERROR_LOCKED;
    }

    /* Perform the erase */
    if (size != 0) {
        memset(ctx->memory + offset, ctx->erasedByte, size);
    }
    return WH_ERROR_OK;
}

int whFlashRamsim_Verify(void* context, uint32_t offset, uint32_t size,
                         const uint8_t* data)
{
    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;
    if (    (ctx == NULL) ||
            (ctx->memory == NULL) ||
            ((offset + size) > ctx->size) ||
            ((data == NULL) && (size != 0))) {
        return WH_ERROR_BADARGS;
    }

    /* Check stored data equals input data */
    if (size != 0) {
        if(memcmp(ctx->memory + offset, data, size) != 0) {
            return WH_ERROR_NOTVERIFIED;
        }
    }
    return WH_ERROR_OK;
}


int whFlashRamsim_BlankCheck(void* context, uint32_t offset, uint32_t size)
{
    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;

    if (    (ctx == NULL) ||
            (ctx->memory == NULL) ||
            ((offset + size) > ctx->size)) {
        return WH_ERROR_BADARGS;
    }

    if (!isMemoryErased(ctx, offset, size)) {
        return WH_ERROR_NOTBLANK;
    }

    return WH_ERROR_OK;
}


uint32_t whFlashRamsim_PartitionSize(void* context)
{
    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;

    if (ctx == NULL) {
        /* Invalid context.  Must return positive size, so 0 */
        return 0;
    }

    return ctx->sectorSize;
}


int whFlashRamsim_WriteLock(void* context, uint32_t offset, uint32_t size)
{
    (void)offset;
    (void)size;

    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    ctx->writeLocked = 1;

    return WH_ERROR_OK;
}


int whFlashRamsim_WriteUnlock(void* context, uint32_t offset, uint32_t size)
{
    (void)offset;
    (void)size;
    whFlashRamsimCtx* ctx = (whFlashRamsimCtx*)context;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    ctx->writeLocked = 0;

    return WH_ERROR_OK;
}
