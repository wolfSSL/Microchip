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
 * wolfhsm/wh_log_ringbuf.h
 *
 * Ring buffer logging backend with fixed capacity in RAM. Simple, portable,
 * and not thread-safe. Overwrites oldest entries when full.
 */

#ifndef WOLFHSM_WH_LOG_RINGBUF_H_
#define WOLFHSM_WH_LOG_RINGBUF_H_

#include "wolfhsm/wh_settings.h"
#include "wolfhsm/wh_log.h"

#include <stddef.h>

/* Ring buffer configuration structure */
typedef struct whLogRingbufConfig_t {
    void*  buffer;      /* User-supplied buffer */
    size_t buffer_size; /* Size of buffer in bytes */
} whLogRingbufConfig;

/* Ring buffer context structure */
typedef struct whLogRingbufContext_t {
    whLogEntry* entries;  /* Pointer to user-supplied buffer */
    size_t      capacity; /* Number of entries buffer can hold */
    size_t count; /* Total entries ever written (head = count % capacity) */
    int    initialized; /* Initialization flag */
} whLogRingbufContext;

/* Callback functions */
int whLogRingbuf_Init(void* context, const void* config);
int whLogRingbuf_Cleanup(void* context);
int whLogRingbuf_AddEntry(void* context, const whLogEntry* entry);
int whLogRingbuf_Export(void* context, void* export_arg);
int whLogRingbuf_Iterate(void* context, whLogIterateCb iterate_cb,
                         void* iterate_arg);
int whLogRingbuf_Clear(void* context);

/* Convenience macro for callback table initialization.
 */
/* clang-format off */
#define WH_LOG_RINGBUF_CB                                                     \
    {                                                                         \
        .Init = whLogRingbuf_Init,                                            \
        .Cleanup = whLogRingbuf_Cleanup,                                      \
        .AddEntry = whLogRingbuf_AddEntry,                                    \
        .Export = whLogRingbuf_Export,                                        \
        .Iterate = whLogRingbuf_Iterate,                                      \
        .Clear = whLogRingbuf_Clear,                                          \
    }
/* clang-format on */

#endif /* !WOLFHSM_WH_LOG_RINGBUF_H_ */
