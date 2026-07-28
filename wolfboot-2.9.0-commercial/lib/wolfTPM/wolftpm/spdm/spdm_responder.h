/* spdm_responder.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* SPDM responder. Lives above fwtpm's transport HAL and reuses wolfSPDM
 * crypto + framing helpers, flipped to answer requester-driven messages. */

#ifndef WOLFSPDM_RESPONDER_H
#define WOLFSPDM_RESPONDER_H

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolftpm/spdm/spdm.h>

#ifdef WOLFTPM_SPDM_RESPONDER

#ifdef __cplusplus
extern "C" {
#endif

struct WOLFSPDM_RESP_CTX;
typedef struct WOLFSPDM_RESP_CTX WOLFSPDM_RESP_CTX;

/* Dispatcher for tunneled TPM2_CMD payloads. fwtpm_server wires this to
 * FWTPM_ProcessCommand; unit tests wire a stub. */
typedef int (*WOLFSPDM_RESP_TPM_CB)(void* userCtx,
    const byte* cmd, word32 cmdSz,
    byte* resp, word32 respBufSz, word32* respSz);

WOLFTPM_API int wolfSPDM_RespInit(WOLFSPDM_RESP_CTX* ctx);
WOLFTPM_API void wolfSPDM_RespFree(WOLFSPDM_RESP_CTX* ctx);

/* RESP_CTX embeds the requester CTX + four MAX_MSG_SIZE working buffers
 * (4 * 4096) + identity/PSK material + tpm callback + flags. Static buffer
 * is sized for that worst case; spdm_responder.c has a compile-time assert
 * so it can't silently undersize. */
#define WOLFSPDM_RESP_CTX_STATIC_SIZE  \
    (WOLFSPDM_CTX_STATIC_SIZE + (4 * WOLFSPDM_MAX_MSG_SIZE) + 1024)
WOLFTPM_API int wolfSPDM_RespGetCtxSize(void);

WOLFTPM_API int wolfSPDM_RespSetMode(WOLFSPDM_RESP_CTX* ctx,
    int useTcg, int usePsk);

WOLFTPM_API int wolfSPDM_RespSetPSK(WOLFSPDM_RESP_CTX* ctx,
    const byte* psk, word32 pskSz,
    const byte* hint, word32 hintSz);

/* privKey: 48 bytes (P-384 scalar). pubKey: 96 bytes (X||Y, big-endian). */
WOLFTPM_API int wolfSPDM_RespSetIdentityKey(WOLFSPDM_RESP_CTX* ctx,
    const byte* privKey, word32 privSz,
    const byte* pubKey, word32 pubSz);

WOLFTPM_API int wolfSPDM_RespSetTpmCallback(WOLFSPDM_RESP_CTX* ctx,
    WOLFSPDM_RESP_TPM_CB cb, void* userCtx);

WOLFTPM_API void wolfSPDM_RespSetDebug(WOLFSPDM_RESP_CTX* ctx, int enable);

/* Returns WOLFSPDM_E_FRAMING on a non-TCG inbound frame. Callers MUST drop
 * the connection on E_FRAMING; never fall through to the TPM parser. */
WOLFTPM_API int wolfSPDM_RespHandleMessage(WOLFSPDM_RESP_CTX* ctx,
    const byte* inBuf, word32 inSz,
    byte* outBuf, word32* outSz);

WOLFTPM_API void wolfSPDM_RespReset(WOLFSPDM_RESP_CTX* ctx);

/* SPDMONLY lock: when 1, the transport must reject plaintext TPM frames.
 * Toggled by the requester via SPDMONLY vendor command. */
WOLFTPM_API int wolfSPDM_RespIsLocked(const WOLFSPDM_RESP_CTX* ctx);

#ifdef __cplusplus
}
#endif

#endif /* WOLFTPM_SPDM_RESPONDER */

#endif /* WOLFSPDM_RESPONDER_H */
