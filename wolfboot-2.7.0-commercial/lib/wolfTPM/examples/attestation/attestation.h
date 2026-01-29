/* attestation.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _ATTESTATION_H_
#define _ATTESTATION_H_

#ifdef __cplusplus
    extern "C" {
#endif

#define CRED_SECRET_SIZE 32

int TPM2_MakeCredential_Example(void* userCtx, int argc, char *argv[]);
int TPM2_ActivateCredential_Example(void* userCtx, int argc, char *argv[]);
int TPM2_Certify_Example(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _ATTESTATION_H_ */
