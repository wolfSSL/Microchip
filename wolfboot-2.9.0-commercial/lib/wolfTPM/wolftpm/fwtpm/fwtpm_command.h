/* fwtpm_command.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _FWTPM_COMMAND_H_
#define _FWTPM_COMMAND_H_

#ifdef WOLFTPM_FWTPM

#include <wolftpm/fwtpm/fwtpm.h>

#ifdef __cplusplus
    extern "C" {
#endif

/*!
    \ingroup wolfTPM_fwTPM
    \brief Process one TPM 2.0 command. Parses the header from cmdBuf,
    dispatches the command, and writes a wire-format response into
    rspBuf. The return value signals transport-level success: a failure
    at the TPM command level (e.g. TPM_RC_AUTH_FAIL) is encoded inside
    the response and still returns TPM_RC_SUCCESS here.

    \return TPM_RC_SUCCESS on successful processing (inspect response
        header for the TPM-level return code)
    \return negative on fatal transport/parse error

    \param ctx pointer to an initialized FWTPM_CTX
    \param cmdBuf input command buffer (big-endian TPM packet)
    \param cmdSize size of cmdBuf in bytes
    \param rspBuf output response buffer (caller-allocated)
    \param rspSize in: capacity of rspBuf; out: bytes written
    \param locality TPM locality (0-4) reported by the transport

    \sa FWTPM_IO_ServerLoop
    \sa FWTPM_TIS_ServerLoop
*/
WOLFTPM_API int FWTPM_ProcessCommand(FWTPM_CTX* ctx,
    const byte* cmdBuf, int cmdSize,
    byte* rspBuf, int* rspSize, int locality);

/*!
    \brief Flush all transient objects, sessions, and sequences.

    Called when the active command client connection is replaced or closed so
    a subsequent client cannot inherit the previous client's transient state.
*/
WOLFTPM_API void FWTPM_ResetCommandClient(FWTPM_CTX* ctx);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* WOLFTPM_FWTPM */

#endif /* _FWTPM_COMMAND_H_ */
