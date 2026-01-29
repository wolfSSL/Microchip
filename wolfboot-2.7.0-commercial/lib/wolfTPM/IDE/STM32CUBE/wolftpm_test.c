/* wolftpm_test.c
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
#include "wolftpm_test.h"

#ifndef SINGLE_THREADED
    #include <cmsis_os.h>

    #ifdef WOLFSSL_DEBUG_MEMORY
        /* for memory debugging */
        #include <task.h>
    #endif
#endif

#include <stdio.h>
#include <string.h>

extern int TPM2_Wrapper_Test(void* userCtx);

#ifdef CMSIS_OS2_H_
void wolfTPMTest(void* argument)
#else
void wolfTPMTest(const void* argument)
#endif
{
    int ret = 0;

    printf("Running wolfTPM Wrap Test...\n");

    /* Run wolfTPM wrap test */
    ret = TPM2_Wrapper_Test((void*)argument);

    printf("wolfTPM wrap test: Return code %d\n", ret);

}
