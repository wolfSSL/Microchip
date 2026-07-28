/* user_settings.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Minimal user_settings.h reproducing the bug state. */
#ifndef WOLFSSL_FREERTOS_MEM_TRACK_REPRO_USER_SETTINGS_H
#define WOLFSSL_FREERTOS_MEM_TRACK_REPRO_USER_SETTINGS_H

#define FREERTOS
#define FREERTOS_TCP
#define NO_FILESYSTEM
#define WOLFSSL_NO_SOCK
#define USE_WOLFSSL_MEMORY
#define WOLFSSL_TRACK_MEMORY
#define WOLFSSL_DEBUG_MEMORY
#define WOLFSSL_DEBUG_MEMORY_PRINT
#define DEBUG_WOLFSSL

/* Intentionally NOT defined: SINGLE_THREADED, WOLFSSL_STATIC_MEMORY */

#endif
