/* benchmark-main.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfcrypt/benchmark/benchmark.h>

typedef struct func_args {
    int    argc;
    char** argv;
    int    return_code;
} func_args;

func_args args = { 0 } ;

extern double current_time(int reset) ;

main(void) {
    benchmark_test(&args) ;
    return 0;
}
