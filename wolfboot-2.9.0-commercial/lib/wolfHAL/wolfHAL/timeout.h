/* timeout.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_TIMEOUT_H
#define WHAL_TIMEOUT_H

#include <wolfHAL/error.h>
#include <stdint.h>
#include <stddef.h>

/*
 * @file timeout.h
 * @brief Timeout abstraction for bounded polling and delays.
 *
 * The board sets timeoutTicks and a GetTick callback directly on a
 * whal_Timeout instance. Drivers use WHAL_TIMEOUT_START / WHAL_TIMEOUT_EXPIRED
 * macros for zero-overhead polling guards. When WHAL_CFG_NO_TIMEOUT is
 * defined, all timeout operations compile away completely.
 */

typedef struct {
    uint32_t timeoutTicks;
    uint32_t startTick;
    uint32_t (*GetTick)(void);
} whal_Timeout;

#ifdef WHAL_CFG_NO_TIMEOUT

#define WHAL_TIMEOUT_START(t)       ((void)(0))
#define WHAL_TIMEOUT_EXPIRED(t)     (0)

#else /* !WHAL_CFG_NO_TIMEOUT */

/*
 * @brief Snapshot the current tick.
 *
 * If @p t is NULL, this is a no-op so drivers can leave the timeout
 * pointer unset for unbounded polling.
 */
#define WHAL_TIMEOUT_START(t) do {                                          \
    if (t) {                                                                \
        (t)->startTick = (t)->GetTick();                                    \
    }                                                                       \
} while (0)

/*
 * @brief Evaluate to nonzero if the timeout has expired.
 *
 * Safe to call with a NULL pointer — returns 0 (not expired).
 */
#define WHAL_TIMEOUT_EXPIRED(t) \
    ((t) && ((uint32_t)((t)->GetTick() - (t)->startTick) >= (t)->timeoutTicks))

#endif /* WHAL_CFG_NO_TIMEOUT */

#endif /* WHAL_TIMEOUT_H */
