/* wrap_test.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _WRAP_TEST_H_
#define _WRAP_TEST_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_Wrapper_Test(void* userCtx);
int TPM2_Wrapper_TestArgs(void* userCtx, int argc, char *argv[]);

int TPM2_Wrapper_Caps(void* userCtx);
int TPM2_Wrapper_CapsArgs(void* userCtx, int argc, char *argv[]);

int TPM2_Wrapper_Hmac(void* userCtx);
int TPM2_Wrapper_HmacArgs(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _WRAP_TEST_H_ */
