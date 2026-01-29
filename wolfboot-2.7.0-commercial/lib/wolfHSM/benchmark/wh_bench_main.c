/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#include "wolfhsm/wh_settings.h"
#include "wh_bench.h"
#include "wh_bench_ops.h"
#include "wh_bench_utils.h"

#if defined(WOLFHSM_CFG_BENCH_ENABLE) && defined(WOLFHSM_CFG_BENCH_MAIN)

#include <wolfssl/version.h>
#include <string.h>
#include <stdlib.h>

void Usage(const char* exeName)
{
    WOLFHSM_CFG_PRINTF("Usage: %s --type <type> --module <module> --list\n", exeName);
    WOLFHSM_CFG_PRINTF("Type: mem, shm, tcp, dma\n");
    WOLFHSM_CFG_PRINTF("Module: index of the module to run\n");
    WOLFHSM_CFG_PRINTF("List: list all modules\n");
    exit(1);
}

int main(int argc, char** argv)
{
    int transport   = WH_BENCH_TRANSPORT_MEM;
    int moduleIndex = -1;
    int i;

    WH_BENCH_PRINTF("wolfHSM POSIX benchmark built with wolfSSL version %s\n",
                    LIBWOLFSSL_VERSION_STRING);

    /* Parse command-line arguments */
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--type") == 0 && i + 1 < argc) {
            const char* type = argv[++i];
            if (strcmp(type, "mem") == 0) {
                transport = WH_BENCH_TRANSPORT_MEM;
            }
            else if (strcmp(type, "shm") == 0) {
                transport = WH_BENCH_TRANSPORT_POSIX_SHM;
            }
            else if (strcmp(type, "tcp") == 0) {
                transport = WH_BENCH_TRANSPORT_POSIX_TCP;
            }
            else if (strcmp(type, "dma") == 0) {
                transport = WH_BENCH_TRANSPORT_POSIX_DMA;
            }
            else {
                WOLFHSM_CFG_PRINTF("Invalid transport type: %s\n", type);
                Usage(argv[0]);
                return -1;
            }
        }
        else if (strcmp(argv[i], "--module") == 0 && i + 1 < argc) {
            moduleIndex = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--list") == 0) {
            wh_Bench_ListModules();
            return 0;
        }
        else {
            WOLFHSM_CFG_PRINTF("Invalid argument: %s\n", argv[i]);
            Usage(argv[0]);
            return -1;
        }
    }

#if defined(WOLFHSM_CFG_TEST_POSIX)
    int ret = wh_Bench_ClientServer_Posix(transport, moduleIndex);
    if (ret != 0) {
        WH_BENCH_PRINTF("Memory transport benchmark failed: %d\n", ret);
        return ret;
    }
#else
    WH_BENCH_PRINTF(
        "POSIX thread benchmarks not enabled. Define WOLFHSM_CFG_TEST_POSIX "
        "to enable.\n");
#endif

    return 0;
}

#endif /* WOLFHSM_CFG_BENCH_ENABLE && WOLFHSM_CFG_BENCH_MAIN */
