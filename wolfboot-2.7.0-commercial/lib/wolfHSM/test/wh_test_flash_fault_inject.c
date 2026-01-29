/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>
#include <stddef.h> /* For NULL */

#include <string.h>
#include <stdbool.h>

#include "wolfhsm/wh_error.h"
#include "wh_test_flash_fault_inject.h"

int whFlashFaultInject_Init(void* context, const void* config)
{
    whFlashFaultInjectCtx*       ctx = (whFlashFaultInjectCtx*)context;
    const whFlashFaultInjectCfg* cfg = (const whFlashFaultInjectCfg*)config;

    if (ctx == NULL || cfg == NULL || cfg->realCb == NULL) {
        return WH_ERROR_BADARGS;
    }

    memset(ctx, 0, sizeof(*ctx));
    ctx->realCb  = cfg->realCb;
    ctx->realCtx = cfg->realCtx;

    if (cfg->realCb->Init != NULL)
        return cfg->realCb->Init(cfg->realCtx, cfg->realCfg);

    return WH_ERROR_OK;
}

int whFlashFaultInject_Cleanup(void* context)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if (ctx == NULL || ctx->realCb == NULL) {
        return WH_ERROR_BADARGS;
    }
    if (ctx->realCb->Cleanup != NULL)
        return ctx->realCb->Cleanup(ctx->realCtx);

    return WH_ERROR_OK;
}

int whFlashFaultInject_Program(void* context, uint32_t offset, uint32_t size,
                               const uint8_t* data)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if ((ctx == NULL) || (ctx->realCb == NULL))
        return WH_ERROR_BADARGS;
    /* Check if we need to simulate a failure */
    if (ctx->failAfterPrograms > 0) {
        ctx->failAfterPrograms--;
        if (ctx->failAfterPrograms == 0)
            return WH_ERROR_ABORTED;
    }

    if (ctx->realCb->Program != NULL)
        return ctx->realCb->Program(ctx->realCtx, offset, size, data);

    return WH_ERROR_OK;
}

int whFlashFaultInject_Read(void* context, uint32_t offset, uint32_t size,
                            uint8_t* data)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if ((ctx == NULL) || (ctx->realCb == NULL))
        return WH_ERROR_BADARGS;

    if (ctx->realCb->Read != NULL)
        return ctx->realCb->Read(ctx->realCtx, offset, size, data);

    return WH_ERROR_OK;
}

int whFlashFaultInject_Erase(void* context, uint32_t offset, uint32_t size)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if ((ctx == NULL) || (ctx->realCb == NULL))
        return WH_ERROR_BADARGS;

    if (ctx->realCb->Erase != NULL)
        return ctx->realCb->Erase(ctx->realCtx, offset, size);

    return WH_ERROR_OK;
}

int whFlashFaultInject_Verify(void* context, uint32_t offset, uint32_t size,
                              const uint8_t* data)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if ((ctx == NULL) || (ctx->realCb == NULL))
        return WH_ERROR_BADARGS;

    if (ctx->realCb->Verify != NULL)
        return ctx->realCb->Verify(ctx->realCtx, offset, size, data);

    return WH_ERROR_OK;
}

int whFlashFaultInject_BlankCheck(void* context, uint32_t offset, uint32_t size)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if ((ctx == NULL) || (ctx->realCb == NULL))
        return WH_ERROR_BADARGS;

    if (ctx->realCb->BlankCheck != NULL)
        return ctx->realCb->BlankCheck(ctx->realCtx, offset, size);

    return WH_ERROR_OK;
}

uint32_t whFlashFaultInject_PartitionSize(void* context)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if ((ctx == NULL) || (ctx->realCb == NULL))
        return WH_ERROR_BADARGS;

    if (ctx->realCb->PartitionSize != NULL)
        return ctx->realCb->PartitionSize(ctx->realCtx);

    return WH_ERROR_OK;
}

int whFlashFaultInject_WriteLock(void* context, uint32_t offset, uint32_t size)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if ((ctx == NULL) || (ctx->realCb == NULL))
        return WH_ERROR_BADARGS;

    if (ctx->realCb->WriteLock != NULL)
        return ctx->realCb->WriteLock(ctx->realCtx, offset, size);

    return WH_ERROR_OK;
}

int whFlashFaultInject_WriteUnlock(void* context, uint32_t offset,
                                   uint32_t size)
{
    whFlashFaultInjectCtx* ctx = (whFlashFaultInjectCtx*)context;

    if ((ctx == NULL) || (ctx->realCb == NULL))
        return WH_ERROR_BADARGS;

    if (ctx->realCb->WriteUnlock != NULL)
        return ctx->realCb->WriteUnlock(ctx->realCtx, offset, size);

    return WH_ERROR_OK;
}
