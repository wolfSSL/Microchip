/* tpm2_param_enc.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM2_PARAM_ENC_H_
#define _TPM2_PARAM_ENC_H_

#include <wolftpm/tpm2.h>
#include <wolftpm/tpm2_packet.h>

#ifdef __cplusplus
    extern "C" {
#endif

WOLFTPM_API int TPM2_KDFa(
    TPM_ALG_ID hashAlg, TPM2B_DATA *keyIn,
    const char *label, TPM2B_NONCE *contextU, TPM2B_NONCE *contextV,
    BYTE *key, UINT32 keySz
);

WOLFTPM_LOCAL int TPM2_CalcHmac(TPMI_ALG_HASH authHash, TPM2B_AUTH* auth,
    const TPM2B_DIGEST* hash, const TPM2B_NONCE* nonceNew,
    const TPM2B_NONCE* nonceOld, TPMA_SESSION sessionAttributes,
    TPM2B_AUTH* hmac);
WOLFTPM_LOCAL int TPM2_CalcRpHash(TPMI_ALG_HASH authHash,
    TPM_CC cmdCode, BYTE* param, UINT32 paramSz, TPM2B_DIGEST* hash);
WOLFTPM_LOCAL int TPM2_CalcCpHash(TPMI_ALG_HASH authHash, TPM_CC cmdCode,
    TPM2B_NAME* name1, TPM2B_NAME* name2, TPM2B_NAME* name3,
    BYTE* param, UINT32 paramSz, TPM2B_DIGEST* hash);

/* Perform encryption over the first parameter of a TPM packet */
WOLFTPM_LOCAL TPM_RC TPM2_ParamEnc_CmdRequest(TPM2_AUTH_SESSION *session,
                                BYTE *paramData, UINT32 paramSz);
WOLFTPM_LOCAL TPM_RC TPM2_ParamDec_CmdResponse(TPM2_AUTH_SESSION *session,
                                BYTE *paramData, UINT32 paramSz);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _TPM2_PARAM_ENC_H_ */
