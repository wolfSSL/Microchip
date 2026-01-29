/* clock_set.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _CLOCK_SET_H_
#define _CLOCK_SET_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_ClockSet_Test(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _CLOCK_SET_H_ */
