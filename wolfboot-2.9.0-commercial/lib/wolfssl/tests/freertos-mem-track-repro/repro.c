/* repro.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Reproduces the memLock / pthread.h compile failure reported by the
 * FreeRTOS/Xtensa customer in wolfSSL 5.9.1. The bug is preprocessor-only
 * so it triggers on any host once __linux__/__MACH__/__ZEPHYR__ are
 * suppressed via -U flags. WOLFSSL_USER_SETTINGS is supplied by run.sh. */
#include "user_settings.h"
#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/wolfcrypt/mem_track.h"

int main(void) { return 0; }
