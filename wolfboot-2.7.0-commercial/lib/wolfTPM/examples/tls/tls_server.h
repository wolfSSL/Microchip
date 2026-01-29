/* tls_server.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM_TLS_SERVER_H_
#define _TPM_TLS_SERVER_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_TLS_Server(void* userCtx);
int TPM2_TLS_ServerArgs(void* userCtx, int argc, char* argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _TPM_TLS_SERVER_H_ */
