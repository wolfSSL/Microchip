/* tpm2_winapi.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM2_WINAPI_H_
#define _TPM2_WINAPI_H_

#include <wolftpm/tpm2.h>
#include <wolftpm/tpm2_packet.h>

#ifdef __cplusplus
    extern "C" {
#endif

/* TPM2 IO for using TPM through the Winapi kernel driver */
WOLFTPM_LOCAL int TPM2_WinApi_SendCommand(TPM2_CTX* ctx, TPM2_Packet* packet);

/* Cleanup winpi context */
WOLFTPM_LOCAL int TPM2_WinApi_Cleanup(TPM2_CTX* ctx);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _TPM2_WINAPI_H_ */
