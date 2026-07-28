/* spdm_psk.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Shared SPDM PSK Support (DSP0274 1.2+)
 *
 * Standard SPDM PSK protocol:
 * - PSK_EXCHANGE / PSK_EXCHANGE_RSP
 * - PSK_FINISH / PSK_FINISH_RSP
 * - PSK key derivation (HKDF-Extract with PSK)
 * - Shared PSK connection flow
 *
 * Vendor-specific PSK provisioning commands (PSK_SET, PSK_CLEAR, etc.)
 * remain in the vendor files (spdm_nations.c, etc.).
 */

#ifndef WOLFSPDM_PSK_H
#define WOLFSPDM_PSK_H

#include <wolftpm/spdm/spdm_types.h>

#ifdef WOLFTPM_SPDM_PSK

#ifdef __cplusplus
extern "C" {
#endif

/* ----- PSK Context Setup ----- */

WOLFTPM_API int wolfSPDM_SetPSK(WOLFSPDM_CTX* ctx,
    const byte* psk, word32 pskSz,
    const byte* hint, word32 hintSz);

/* ----- PSK Message Builders/Parsers ----- */

WOLFTPM_API int wolfSPDM_BuildPskExchange(WOLFSPDM_CTX* ctx,
    byte* buf, word32* bufSz);

WOLFTPM_API int wolfSPDM_ParsePskExchangeRsp(WOLFSPDM_CTX* ctx,
    const byte* buf, word32 bufSz);

WOLFTPM_API int wolfSPDM_BuildPskFinish(WOLFSPDM_CTX* ctx,
    byte* buf, word32* bufSz);

WOLFTPM_API int wolfSPDM_ParsePskFinishRsp(WOLFSPDM_CTX* ctx,
    const byte* buf, word32 bufSz);

/* ----- PSK Key Derivation ----- */

WOLFTPM_API int wolfSPDM_DeriveHandshakeKeysPsk(WOLFSPDM_CTX* ctx,
    const byte* th1Hash);

/* ----- Shared PSK Connection Flow ----- */

/**
 * Perform PSK SPDM connection.
 * GET_VERSION -> GET_CAPABILITIES -> NEGOTIATE_ALGORITHMS ->
 * PSK_EXCHANGE -> PSK_FINISH -> app key derivation.
 *
 * @param ctx       wolfSPDM context (must have PSK set via wolfSPDM_SetPSK)
 * @return WOLFSPDM_SUCCESS or negative error code
 */
WOLFTPM_API int wolfSPDM_ConnectPsk(WOLFSPDM_CTX* ctx);

/* Backward compatibility */
#define wolfSPDM_ConnectNationsPsk wolfSPDM_ConnectPsk

#ifdef __cplusplus
}
#endif

#endif /* WOLFTPM_SPDM_PSK */

#endif /* WOLFSPDM_PSK_H */
