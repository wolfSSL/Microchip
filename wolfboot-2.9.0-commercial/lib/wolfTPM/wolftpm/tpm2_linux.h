/* tpm2_linux.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM2_LINUX_H_
#define _TPM2_LINUX_H_

#if defined(WOLFTPM_LINUX_DEV) || defined(WOLFTPM_LINUX_DEV_AUTODETECT)

#include <wolftpm/tpm2.h>
#include <wolftpm/tpm2_packet.h>

#ifdef __cplusplus
    extern "C" {
#endif

/* TPM2 IO for using TPM through the Linux kernel driver */
WOLFTPM_LOCAL int TPM2_LINUX_SendCommand(TPM2_CTX* ctx, TPM2_Packet* packet);

#ifdef WOLFTPM_LINUX_DEV_AUTODETECT
/* Try opening /dev/tpmrm0 then /dev/tpm0. Returns TPM_RC_SUCCESS if opened,
 * sets ctx->fd. On EACCES prints permission message and returns FAILURE.
 * Returns TPM_RC_INITIALIZE if device not found (caller should try SPI). */
WOLFTPM_LOCAL int TPM2_LINUX_TryOpen(TPM2_CTX* ctx);

/* Runtime dispatch: uses /dev/tpm0 if ctx->fd >= 0, otherwise TIS/SPI */
WOLFTPM_LOCAL int TPM2_LINUX_AUTODETECT_SendCommand(TPM2_CTX* ctx,
    TPM2_Packet* packet);
#endif

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* WOLFTPM_LINUX_DEV || WOLFTPM_LINUX_DEV_AUTODETECT */

#endif /* _TPM2_LINUX_H_ */
