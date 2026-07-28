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
 * src/wh_log_ringbuf.c
 *
 * Ring buffer logging backend implementation
 */

#include <stddef.h> /* For NULL */
#include <string.h> /* For memset, memcpy */

#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_log.h"
#include "wolfhsm/wh_log_ringbuf.h"

#ifdef WOLFHSM_CFG_LOGGING

int whLogRingbuf_Init(void* context, const void* config)
{
    whLogRingbufContext*      ctx = (whLogRingbufContext*)context;
    const whLogRingbufConfig* cfg  = (const whLogRingbufConfig*)config;
    size_t                    capacity;

    if (ctx == NULL || cfg == NULL || cfg->buffer == NULL ||
        cfg->buffer_size < sizeof(whLogEntry)) {
        return WH_ERROR_BADARGS;
    }

    /* Calculate capacity (number of complete entries that fit in buffer) */
    capacity = cfg->buffer_size / sizeof(whLogEntry);
    /* Capacity must be able to hold at least one log entry, specifically to
     * prevent divide-by-zeros in the rollover logic */
    if (capacity == 0) {
        return WH_ERROR_BADARGS;
    }

    /* Initialize context */
    memset(ctx, 0, sizeof(*ctx));
    ctx->entries     = (whLogEntry*)cfg->buffer;
    ctx->capacity    = capacity;
    ctx->count       = 0;
    ctx->initialized = 1;

    return WH_ERROR_OK;
}

int whLogRingbuf_Cleanup(void* context)
{
    whLogRingbufContext* ctx = (whLogRingbufContext*)context;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    if (ctx->initialized) {
        (void)whLogRingbuf_Clear(ctx);
        ctx->initialized = 0;
    }

    return WH_ERROR_OK;
}

int whLogRingbuf_AddEntry(void* context, const whLogEntry* entry)
{
    whLogRingbufContext* ctx = (whLogRingbufContext*)context;
    size_t               head;

    if ((ctx == NULL) || (entry == NULL)) {
        return WH_ERROR_BADARGS;
    }

    if (!ctx->initialized) {
        return WH_ERROR_ABORTED;
    }

    /* Calculate head position from count */
    head = ctx->count % ctx->capacity;

    /* Copy entry to ring buffer at head position */
    memcpy(&ctx->entries[head], entry, sizeof(whLogEntry));

    /* Increment count freely to track total messages written */
    ctx->count++;

    return WH_ERROR_OK;
}

int whLogRingbuf_Export(void* context, void* export_arg)
{
    (void)context;
    (void)export_arg;
    return WH_ERROR_OK;
}

int whLogRingbuf_Iterate(void* context, whLogIterateCb iterate_cb,
                         void* iterate_arg)
{
    whLogRingbufContext* ctx = (whLogRingbufContext*)context;
    size_t               capacity;
    size_t               num_entries;
    size_t               start_idx;
    size_t               i;
    int                  ret = 0;

    if ((ctx == NULL) || (iterate_cb == NULL)) {
        return WH_ERROR_BADARGS;
    }

    if (!ctx->initialized) {
        return WH_ERROR_ABORTED;
    }

    /* If buffer is empty, nothing to iterate */
    if (ctx->count == 0) {
        return WH_ERROR_OK;
    }

    capacity = ctx->capacity;

    /* Calculate actual number of entries in buffer (capped at capacity) */
    num_entries = (ctx->count < capacity) ? ctx->count : capacity;

    /* Determine starting index for iteration:
     * - If not full: start at 0 (oldest entry)
     * - If full: start at head (oldest entry, about to be overwritten)
     *   head = count % capacity
     */
    if (ctx->count < capacity) {
        start_idx = 0;
    }
    else {
        start_idx = ctx->count % capacity;
    }

    /* Iterate through entries in chronological order */
    for (i = 0; i < num_entries; i++) {
        size_t idx = (start_idx + i) % capacity;
        ret        = iterate_cb(iterate_arg, &ctx->entries[idx]);
        if (ret != 0) {
            /* User callback requested early termination */
            break;
        }
    }

    return ret;
}

int whLogRingbuf_Clear(void* context)
{
    whLogRingbufContext* ctx = (whLogRingbufContext*)context;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    /* Reset ring buffer state */
    ctx->count = 0;

    /* Zero the log entries */
    memset(ctx->entries, 0, ctx->capacity * sizeof(whLogEntry));

    return WH_ERROR_OK;
}

#endif /* WOLFHSM_CFG_LOGGING */
