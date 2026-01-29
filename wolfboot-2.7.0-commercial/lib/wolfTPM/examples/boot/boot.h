/* boot.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _BOOT_SECURE_EXAMPLES_H_
#define _BOOT_SECURE_EXAMPLES_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_Boot_SecureROT_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Boot_SecretSeal_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Boot_SecretUnseal_Example(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _BOOT_SECURE_EXAMPLES_H_ */
