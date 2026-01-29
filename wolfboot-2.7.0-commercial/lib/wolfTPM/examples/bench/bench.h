/* bench.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _WRAP_BENCH_H_
#define _WRAP_BENCH_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_Wrapper_BenchArgs(void* userCtx, int argc, char *argv[]);
int TPM2_Wrapper_Bench(void* userCtx);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _WRAP_BENCH_H_ */
