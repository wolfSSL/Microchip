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
 * port/posix/posix_lock.c
 *
 * POSIX pthread_mutex-based implementation of the wolfHSM lock abstraction.
 * Each lock context contains a single mutex for one shared resource.
 */

#include "wolfhsm/wh_settings.h"

#ifdef WOLFHSM_CFG_THREADSAFE

#include <pthread.h>
#include <errno.h>

#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_lock.h"

#include "port/posix/posix_lock.h"

int posixLock_Init(void* context, const void* config)
{
    posixLockContext*          ctx  = (posixLockContext*)context;
    const posixLockConfig*     cfg  = (const posixLockConfig*)config;
    const pthread_mutexattr_t* attr = NULL;
    int                        rc;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    /* Already initialized? */
    if (ctx->initialized) {
        return WH_ERROR_OK;
    }

    /* Use attributes from config if provided */
    if (cfg != NULL) {
        attr = cfg->attr;
    }

    rc = pthread_mutex_init(&ctx->mutex, attr);
    if (rc != 0) {
        if (rc == EINVAL) {
            return WH_ERROR_BADARGS;
        }
        return WH_ERROR_ABORTED;
    }

    ctx->initialized = 1;
    return WH_ERROR_OK;
}

int posixLock_Cleanup(void* context)
{
    posixLockContext* ctx = (posixLockContext*)context;
    int               rc;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    /* Not initialized? */
    if (!ctx->initialized) {
        return WH_ERROR_OK;
    }

    rc = pthread_mutex_destroy(&ctx->mutex);
    if (rc != 0) {
        if (rc == EINVAL) {
            return WH_ERROR_BADARGS;
        }
        return WH_ERROR_ABORTED;
    }

    ctx->initialized = 0;
    return WH_ERROR_OK;
}

int posixLock_Acquire(void* context)
{
    posixLockContext* ctx = (posixLockContext*)context;
    int               rc;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    /* Not initialized? */
    if (!ctx->initialized) {
        return WH_ERROR_NOTREADY;
    }

    rc = pthread_mutex_lock(&ctx->mutex);
    if (rc != 0) {
        /* Trap error-checking mutex errors that indicate bugs */
        if (rc == EDEADLK) {
            /* Deadlock would occur - owner trying to re-acquire */
            return WH_ERROR_ABORTED;
        }
        if (rc == EINVAL) {
            return WH_ERROR_BADARGS;
        }
        return WH_ERROR_ABORTED;
    }

    return WH_ERROR_OK;
}

int posixLock_Release(void* context)
{
    posixLockContext* ctx = (posixLockContext*)context;
    int               rc;

    if (ctx == NULL) {
        return WH_ERROR_BADARGS;
    }

    /* Not initialized? */
    if (!ctx->initialized) {
        return WH_ERROR_NOTREADY;
    }

    rc = pthread_mutex_unlock(&ctx->mutex);
    if (rc != 0) {
        /* Trap error-checking mutex errors that indicate bugs */
        if (rc == EPERM) {
            /* Non-owner attempting to unlock */
            return WH_ERROR_LOCKED;
        }
        if (rc == EINVAL) {
            return WH_ERROR_BADARGS;
        }
        return WH_ERROR_ABORTED;
    }

    return WH_ERROR_OK;
}

#endif /* WOLFHSM_CFG_THREADSAFE */
