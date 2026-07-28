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
 * port/posix/posix_timeout.h
 *
 * POSIX implementation of the wolfHSM timeout abstraction.
 * Uses CLOCK_MONOTONIC for time measurement.
 */

#ifndef PORT_POSIX_POSIX_TIMEOUT_H_
#define PORT_POSIX_POSIX_TIMEOUT_H_

#include "wolfhsm/wh_settings.h"

#ifdef WOLFHSM_CFG_ENABLE_TIMEOUT

#include <stdint.h>

#include "wolfhsm/wh_timeout.h"

/* Configuration for POSIX timeout backend */
typedef struct posixTimeoutConfig_t {
    uint64_t timeoutUs; /* Timeout duration in microseconds; 0 = no timeout */
} posixTimeoutConfig;

/* Context structure holding timer state */
typedef struct posixTimeoutContext_t {
    uint64_t startUs;     /* Snapshot of start time */
    uint64_t timeoutUs;   /* Configured timeout duration */
    int      running;     /* 1 if timer is running, 0 otherwise */
    int      initialized; /* 1 if initialized, 0 otherwise */
} posixTimeoutContext;

/* Callback functions matching whTimeoutCb interface */
int posixTimeout_Init(void* context, const void* config);
int posixTimeout_Cleanup(void* context);
int posixTimeout_Set(void* context, uint64_t timeoutUs);
int posixTimeout_Start(void* context);
int posixTimeout_Stop(void* context);
int posixTimeout_Expired(void* context, int* expired);

/* Convenience macro for callback table initialization */
/* clang-format off */
#define POSIX_TIMEOUT_CB                     \
    {                                        \
        .init    = posixTimeout_Init,        \
        .cleanup = posixTimeout_Cleanup,     \
        .set     = posixTimeout_Set,         \
        .start   = posixTimeout_Start,       \
        .stop    = posixTimeout_Stop,        \
        .expired = posixTimeout_Expired,     \
    }
/* clang-format on */

#endif /* WOLFHSM_CFG_ENABLE_TIMEOUT */

#endif /* !PORT_POSIX_POSIX_TIMEOUT_H_ */
