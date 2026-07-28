/*
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * src/wh_log_printf.c
 *
 * Printf-style logging backend implementation
 */

#include <stddef.h> /* For NULL */
#include <string.h> /* For memset, memcpy */

#include "wolfhsm/wh_settings.h"

#include "wolfhsm/wh_log_printf.h"
#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_log.h"

#ifdef WOLFHSM_CFG_LOGGING

int whLogPrintf_Init(void* context, const void* config)
{
    whLogPrintfContext*      ctx = (whLogPrintfContext*)context;
    const whLogPrintfConfig* cfg  = (const whLogPrintfConfig*)config;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    /* Initialize context */
    memset(ctx, 0, sizeof(*ctx));

    /* Copy config if provided, otherwise use defaults */
    if (cfg != NULL) {
        ctx->logIfNotDebug = cfg->logIfNotDebug;
    }
    else {
        ctx->logIfNotDebug = 0;
    }

    ctx->initialized = 1;

    return WH_ERROR_OK;
}


int whLogPrintf_AddEntry(void* context, const whLogEntry* entry)
{
    whLogPrintfContext* ctx = (whLogPrintfContext*)context;

    if ((ctx == NULL) || (entry == NULL)) {
        return WH_ERROR_BADARGS;
    }

    if (!ctx->initialized) {
        return WH_ERROR_ABORTED;
    }

    /* Conditional logging:
     * - If logIfNotDebug is true: always log
     * - If logIfNotDebug is false: only log if WOLFHSM_CFG_DEBUG is defined
     */
#ifndef WOLFHSM_CFG_DEBUG
    if (!ctx->logIfNotDebug) {
        return WH_ERROR_OK;
    }
#endif

    /* Format: [TIMESTAMP] [LEVEL] [FILE:LINE FUNC] MESSAGE */
    (void)WOLFHSM_CFG_PRINTF(
        "[%llu] [%s] [%s:%u %s] %.*s\n", (unsigned long long)entry->timestamp,
        wh_Log_LevelToString(entry->level),
        (entry->file != NULL) ? entry->file : "", entry->line,
        (entry->function != NULL) ? entry->function : "",
        (entry->msg_len <= WOLFHSM_CFG_LOG_MSG_MAX)
            ? (int)(entry->msg_len)
            : (int)WOLFHSM_CFG_LOG_MSG_MAX,
        entry->msg);

    return WH_ERROR_OK;
}

#endif /* WOLFHSM_CFG_LOGGING */
