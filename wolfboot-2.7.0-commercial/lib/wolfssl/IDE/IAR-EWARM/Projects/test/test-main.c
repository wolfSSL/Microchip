/* test-main.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */



typedef struct func_args {
    int    argc;
    char** argv;
    int    return_code;
} func_args;

func_args args = { 0 } ;

extern int wolfcrypt_test(void *args) ;

main(void) {
    wolfcrypt_test(&args) ;
    return 0;
}

