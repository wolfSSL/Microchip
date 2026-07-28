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
 * wolfhsm/wh_log_printf.h
 *
 * Printf logging backend that simply prints out log entries as they are added,
 * with no backing store.
 */

#ifndef WOLFHSM_WH_LOG_PRINTF_H_
#define WOLFHSM_WH_LOG_PRINTF_H_

#include "wolfhsm/wh_settings.h"
#include "wolfhsm/wh_log.h"

#include <stddef.h>

/* Printf configuration structure */
typedef struct whLogPrintfConfig_t {
    int logIfNotDebug; /* When non-zero, log entries are printed even if
                        * WOLFHSM_CFG_DEBUG is not defined. When zero, entries
                        * are only printed if WOLFHSM_CFG_DEBUG is defined. This
                        * flag applies to all log levels */
} whLogPrintfConfig;

/* Printf context structure */
typedef struct whLogPrintfContext_t {
    int initialized;   /* Initialization flag */
    int logIfNotDebug; /* Copied from config */
} whLogPrintfContext;

/* Callback functions */
int whLogPrintf_Init(void* context, const void* config);
int whLogPrintf_AddEntry(void* context, const whLogEntry* entry);

/* Convenience macro for callback table initialization.
 */
/* clang-format off */
#define WH_LOG_PRINTF_CB                   \
    {                                      \
        .Init     = whLogPrintf_Init,      \
        .Cleanup  = NULL,                  \
        .AddEntry = whLogPrintf_AddEntry,  \
        .Export   = NULL,                  \
        .Iterate  = NULL,                  \
        .Clear    = NULL,                  \
    }
/* clang-format on */

#endif /* !WOLFHSM_WH_LOG_PRINTF_H_ */
