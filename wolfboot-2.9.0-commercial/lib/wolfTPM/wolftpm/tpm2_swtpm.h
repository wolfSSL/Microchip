/* tpm2_swtpm.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM2_SWTPM_H_
#define _TPM2_SWTPM_H_

#ifdef WOLFTPM_SWTPM

#include <wolftpm/tpm2.h>
#include <wolftpm/tpm2_packet.h>

#ifdef __cplusplus
    extern "C" {
#endif

/* copy from TpmTcpProtocol.h */
#if 0
#define TPM_SIGNAL_POWER_ON         1
#define TPM_SIGNAL_POWER_OFF        2
#define TPM_SIGNAL_NV_ON            11
#endif

#define TPM_SEND_COMMAND            8
#define TPM_SESSION_END             20
#if 0
#define TPM_STOP                    21
#endif

/* TPM2 IO for using TPM through a Socket connection */
WOLFTPM_LOCAL int TPM2_SWTPM_SendCommand(TPM2_CTX* ctx, TPM2_Packet* packet);

/* Validate a swtpm-reported response size against the receive buffer size */
WOLFTPM_API int TPM2_SwtpmValidateRspSz(int packetSize, uint32_t rspSz);

#ifdef WOLFTPM_SWTPM_UART
/* Close the persistent UART FD during final TPM context cleanup */
WOLFTPM_LOCAL void TPM2_SwtpmCloseUART(TPM2_CTX* ctx);
#endif

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* WOLFTPM_SWTPM */

#endif /* _TPM2_SWTPM_H_ */
