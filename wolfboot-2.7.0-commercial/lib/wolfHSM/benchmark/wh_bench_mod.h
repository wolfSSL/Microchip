/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WH_BENCH_MODULE_H_
#define WH_BENCH_MODULE_H_

#include "wolfhsm/wh_settings.h"

#include "wolfhsm/wh_client.h"

#include "wh_bench_ops.h"
#include "wh_bench_utils.h"
#include "wh_bench_data.h"

#ifndef WOLFHSM_CFG_BENCH_CRYPT_ITERS
#define WOLFHSM_CFG_BENCH_CRYPT_ITERS 100
#endif

#ifndef WOLFHSM_CFG_BENCH_KG_ITERS
#define WOLFHSM_CFG_BENCH_KG_ITERS 10
#endif

#ifndef WOLFHSM_CFG_BENCH_PK_ITERS
#define WOLFHSM_CFG_BENCH_PK_ITERS 10
#endif


/**
 * @brief Function prototype for a generic benchmark module function.
 *
 * A benchmark module function implements a specific benchmark test using the
 * benchmark context and operation id for timing on the supplied client context.
 *
 * @param client  Pointer to the client context to use for the benchmark
 * @param benchCtx Pointer to the benchmark context to use for timing
 * @param opId    The id of the operation to benchmark
 * @param params  Optional parameters for the benchmark
 *
 * @return 0 on success, or a negative error code on failure
 */
typedef int (*wh_BenchModuleFunc)(whClientContext*  client,
                                  whBenchOpContext* benchCtx, int opId,
                                  void* params);


#endif /* WH_BENCH_MODULE_H_ */