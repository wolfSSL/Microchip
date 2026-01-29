/* pcr.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _PCR_H_
#define _PCR_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_PCR_Read_Test(void* userCtx, int argc, char *argv[]);
int TPM2_PCR_Extend_Test(void* userCtx, int argc, char *argv[]);
int TPM2_PCR_Reset_Test(void* userCtx, int argc, char *argv[]);
int TPM2_PCR_Policy_Test(void* userCtx, int argc, char *argv[]);
int TPM2_PCR_PolicySign_Example(void* userCtx, int argc, char *argv[]);
int TPM2_PCR_Seal_With_Policy_Auth_Test(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _PCR_H_ */
