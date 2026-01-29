/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*
 * wolfhsm/wh_keycache.h
 *
 * Exists as a separate header so it can be consumed by server, server keystore,
 * and NVM layer without creating circular dependencies
 */

#ifndef WOLFHSM_WH_SERVER_CACHE_H_
#define WOLFHSM_WH_SERVER_CACHE_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"
#include "wolfhsm/wh_common.h"

#ifndef WOLFHSM_CFG_NO_CRYPTO

/** Server cache slot structures */
typedef struct whCacheSlot {
    uint8_t       committed;
    whNvmMetadata meta[1];
    uint8_t       buffer[WOLFHSM_CFG_SERVER_KEYCACHE_BUFSIZE];
} whCacheSlot;

typedef struct whBigCacheSlot {
    uint8_t       committed;
    whNvmMetadata meta[1];
    uint8_t       buffer[WOLFHSM_CFG_SERVER_KEYCACHE_BIG_BUFSIZE];
} whBigCacheSlot;

/**
 * @brief Unified key cache context
 *
 * Holds both regular and big cache arrays. Used for client-local caches
 * (embedded in whServerContext) and global caches (embedded in whNvmContext
 * when WOLFHSM_CFG_GLOBAL_KEYS is enabled).
 */
typedef struct whKeyCacheContext_t {
    whCacheSlot    cache[WOLFHSM_CFG_SERVER_KEYCACHE_COUNT];
    whBigCacheSlot bigCache[WOLFHSM_CFG_SERVER_KEYCACHE_BIG_COUNT];
} whKeyCacheContext;

#endif /* !WOLFHSM_CFG_NO_CRYPTO */

#endif /* !WOLFHSM_WH_SERVER_CACHE_H_ */
