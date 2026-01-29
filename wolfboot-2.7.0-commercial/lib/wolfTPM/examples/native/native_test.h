/* native_test.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _NATIVE_TEST_H_
#define _NATIVE_TEST_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_Native_Test(void* userCtx);
int TPM2_Native_TestArgs(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _NATIVE_TEST_H_ */
