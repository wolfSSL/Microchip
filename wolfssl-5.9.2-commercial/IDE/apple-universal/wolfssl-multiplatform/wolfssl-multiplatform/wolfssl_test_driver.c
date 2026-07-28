/* wolfssl_test_driver.c
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "wolfssl_test_driver.h"

#ifndef WOLFSSL_USER_SETTINGS
#include <wolfssl/options.h>
#endif
#include <wolfssl/ssl.h>

#include "test.h"
#include "benchmark.h"
#include "simple_client_example.h"

typedef struct test_func_args {
    int argc;
    char** argv;
    int return_code;
} test_func_args;



void wolfssl_test(void)
{
    int ret;
    test_func_args args = {0};

#ifdef WC_RNG_SEED_CB
    wc_SetSeed_Cb(WC_GENERATE_SEED_DEFAULT);
#endif

    printf("Run wolfCrypt Test:\n");
    ret = wolfcrypt_test(&args);
    printf("\nResult of wolfcrypt_test() = %d\n\n", ret);

    printf("Run wolfCrypt Benchmark:\n");
    ret = benchmark_test(&args);
    printf("\nResult of benchmark_test() = %d\n\n", ret);

    printf("Run simple client test:\n");
    ret = simple_client_example();
    printf("\nResult of simple_client_test() = %d\n\n", ret);

}
