/* tls_client.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM_TLS_CLIENT_H_
#define _TPM_TLS_CLIENT_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_TLS_Client(void* userCtx);
int TPM2_TLS_ClientArgs(void* userCtx, int argc, char *argv[]);
int TLS_Client(void);
int TLS_ClientArgs(int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _TPM_TLS_CLIENT_H_ */
