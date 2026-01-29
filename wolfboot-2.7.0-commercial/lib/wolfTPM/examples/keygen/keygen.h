/* keygen.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _KEYGEN_H_
#define _KEYGEN_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_CreatePrimaryKey_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Keygen_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Keyload_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Keyimport_Example(void* userCtx, int argc, char *argv[]);
int TPM2_ExternalImport_Example(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _KEYGEN_H_ */
