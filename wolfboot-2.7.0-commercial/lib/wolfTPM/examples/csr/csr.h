/* csr.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM_CSR_EXAMPLE_H_
#define _TPM_CSR_EXAMPLE_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_CSR_Example(void* userCtx);
int TPM2_CSR_ExampleArgs(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _TPM_CSR_EXAMPLE_H_ */
