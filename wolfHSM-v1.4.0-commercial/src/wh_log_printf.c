/*
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfHSM.
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

int whLogPrintf_Init(void* c, const void* cf)
{
    whLogPrintfContext*      context = (whLogPrintfContext*)c;
    const whLogPrintfConfig* config  = (const whLogPrintfConfig*)cf;

    if (context == NULL) {
        return WH_ERROR_BADARGS;
    }

    /* Initialize context */
    memset(context, 0, sizeof(*context));

    /* Copy config if provided, otherwise use defaults */
    if (config != NULL) {
        context->logIfNotDebug = config->logIfNotDebug;
    }
    else {
        context->logIfNotDebug = 0;
    }

    context->initialized = 1;

    return WH_ERROR_OK;
}


int whLogPrintf_AddEntry(void* c, const whLogEntry* entry)
{
    whLogPrintfContext* context = (whLogPrintfContext*)c;

    if ((context == NULL) || (entry == NULL)) {
        return WH_ERROR_BADARGS;
    }

    if (!context->initialized) {
        return WH_ERROR_ABORTED;
    }

    /* Conditional logging:
     * - If logIfNotDebug is true: always log
     * - If logIfNotDebug is false: only log if WOLFHSM_CFG_DEBUG is defined
     */
#ifndef WOLFHSM_CFG_DEBUG
    if (!context->logIfNotDebug) {
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
