/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WH_BENCH_UTILS_H
#define WH_BENCH_UTILS_H

#include "wolfhsm/wh_settings.h"

/* Define the WH_BENCH_PRINTF macro */
#if defined(WOLFHSM_CFG_BENCH_CUSTOM_PRINTF)
#define WH_BENCH_PRINTF WOLFHSM_CFG_BENCH_CUSTOM_PRINTF
#else
#include <stdio.h> /* use default printf */
#define WH_BENCH_PRINTF printf
#define WH_BENCH_SNPRINTF snprintf
#endif

#endif /* WH_BENCH_UTILS_H_ */