/* seal.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _SEAL_H_
#define _SEAL_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_Seal_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Unseal_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Seal_PCR_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Seal_PolicyAuth_Example(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _SEAL_H_ */
