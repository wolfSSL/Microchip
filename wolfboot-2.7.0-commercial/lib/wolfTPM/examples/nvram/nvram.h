/* nvram.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _NVRAM_EXAMPLE_H_
#define _NVRAM_EXAMPLE_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_NVRAM_Store_Example(void* userCtx, int argc, char *argv[]);
int TPM2_NVRAM_Read_Example(void* userCtx, int argc, char *argv[]);
int TPM2_NVRAM_Counter_Example(void* userCtx, int argc, char *argv[]);
int TPM2_PCR_Seal_With_Policy_Auth_NV_Test(void* userCtx, int argc, char *argv[]);
int TPM2_PCR_Seal_With_Policy_Auth_NV_External_Test(void* userCtx, int argc, char *argv[]);
int TPM2_NVRAM_PolicyNV_Example(void* userCtx, int argc, char *argv[]);
int TPM2_NVRAM_Extend_Example(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _NVRAM_EXAMPLE_H_ */
