/* management.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _FLUSH_H_
#define _FLUSH_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_Flush_Tool(void* userCtx, int argc, char *argv[]);
int TPM2_Clear_Tool(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _FLUSH_H_ */
