/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#include "wh_bench_mod.h"
#include "wolfhsm/wh_error.h"


#if !defined(WOLFHSM_CFG_NO_CRYPTO) && defined(WOLFHSM_CFG_BENCH_ENABLE)
#include "wolfssl/wolfcrypt/random.h"

#if !defined(WC_NO_RNG)

int _benchRng(whClientContext* client, whBenchOpContext* ctx, int id, int devId)
{
    (void)client;

    int      ret = 0;
    WC_RNG   rng;
    int      i              = 0;
    int      rngInitialized = 0;
    uint8_t* out            = WH_BENCH_DATA_OUT_BUFFER;
    word32   outLen         = WOLFHSM_CFG_BENCH_DATA_BUFFER_SIZE;

    ret = wc_InitRng_ex(&rng, NULL, devId);
    if (ret != 0) {
        WH_BENCH_PRINTF("Failed to wc_InitRng_ex %d\n", ret);
        return ret;
    }
    rngInitialized = 1;

    ret = wh_Bench_SetDataSize(ctx, id, outLen);
    if (ret != 0) {
        WH_BENCH_PRINTF("Failed to wh_Bench_SetDataSize %d\n", ret);
        return ret;
    }

    for (i = 0; i < WOLFHSM_CFG_BENCH_CRYPT_ITERS; i++) {
        int benchStartRet;
        int benchStopRet;
        int genRet;

        /* Defer error checking until after all operations are complete */
        benchStartRet = wh_Bench_StartOp(ctx, id);
        genRet        = wc_RNG_GenerateBlock(&rng, out, outLen);
        benchStopRet  = wh_Bench_StopOp(ctx, id);

        /* Check for errors after all operations are complete */
        if (benchStartRet != 0) {
            WH_BENCH_PRINTF("Failed to wh_Bench_StartOp: %d\n", benchStartRet);
            ret = benchStartRet;
            break;
        }
        if (genRet != 0) {
            WH_BENCH_PRINTF("Failed to wc_RNG_GenerateBlock %d\n", genRet);
            ret = genRet;
            break;
        }
        if (benchStopRet != 0) {
            WH_BENCH_PRINTF("Failed to wh_Bench_StopOp: %d\n", benchStopRet);
            ret = benchStopRet;
            break;
        }
    }

    if (rngInitialized) {
        wc_FreeRng(&rng);
    }

    return ret;
}

int wh_Bench_Mod_Rng(whClientContext* client, whBenchOpContext* ctx, int id,
                     void* params)
{
    (void)params;

    return _benchRng(client, ctx, id, WH_DEV_ID);
}

#endif /* !defined(WC_NO_RNG) */

#endif /* !WOLFHSM_CFG_NO_CRYPTO && WOLFHSM_CFG_BENCH_ENABLE */
