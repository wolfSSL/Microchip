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
 * port/posix/posix_lock.h
 *
 * POSIX pthread_mutex-based implementation of the wolfHSM lock abstraction.
 * Provides thread-safe synchronization for shared resources.
 *
 * Each posixLockContext instance contains a single mutex. Create one
 * context per shared resource (e.g., one for NVM, one for crypto).
 */

#ifndef PORT_POSIX_POSIX_LOCK_H_
#define PORT_POSIX_POSIX_LOCK_H_

#include "wolfhsm/wh_settings.h"

#ifdef WOLFHSM_CFG_THREADSAFE

#include <pthread.h>

#include "wolfhsm/wh_lock.h"

/* Configuration for POSIX lock backend */
typedef struct posixLockConfig_t {
    const pthread_mutexattr_t* attr; /* Mutex attributes, NULL for defaults */
} posixLockConfig;

/* Context structure containing a single mutex for one resource */
typedef struct posixLockContext_t {
    pthread_mutex_t mutex;
    int             initialized;
} posixLockContext;

/* Callback functions matching whLockCb interface */
int posixLock_Init(void* context, const void* config);
int posixLock_Cleanup(void* context);
int posixLock_Acquire(void* context);
int posixLock_Release(void* context);

/* Convenience macro for callback table initialization */
/* clang-format off */
#define POSIX_LOCK_CB                     \
    {                                     \
        .init    = posixLock_Init,        \
        .cleanup = posixLock_Cleanup,     \
        .acquire = posixLock_Acquire,     \
        .release = posixLock_Release,     \
    }
/* clang-format on */

#endif /* WOLFHSM_CFG_THREADSAFE */

#endif /* !PORT_POSIX_POSIX_LOCK_H_ */
