/* tpm2_winapi.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolftpm/tpm2_types.h>

#ifdef WOLFTPM_WINAPI
#include <wolftpm/tpm2_winapi.h>

#include <windows.h>
#include <tbs.h>

/*
 * minGW doesn't define the structs necessary for TPM2, so the TBS
 * structures are defined here to match the windows API.
 */
#ifndef TBS_CONTEXT_VERSION_TWO
#define TBS_CONTEXT_VERSION_TWO 2

/**
 * This supports native windows API for TPM support. This uses the
 *  Windows TBSI (TPM Base Service Interface)
 */
typedef struct tdTBS_CONTEXT_PARAMS2
{
    UINT32  version;

    union
    {
        struct
        {
            UINT32 requestRaw : 1;     // if set to 1, request raw context
            UINT32 includeTpm12 : 1;   // if 1.2 device present, can use this
            UINT32 includeTpm20 : 1;   // if 2.0 device present, can use this
        };
        UINT32  asUINT32;
    };
} TBS_CONTEXT_PARAMS2, *PTBS_CONTEXT_PARAMS2;
typedef const TBS_CONTEXT_PARAMS2 *PCTBS_CONTEXT_PARAMS2;

#endif /* ! TBS_CONTEXT_VERSION_TWO */


/* Talk to a TPM device using Windows TBS */
int TPM2_WinApi_SendCommand(TPM2_CTX* ctx, TPM2_Packet* packet)
{
    int rc = 0;
    TBS_CONTEXT_PARAMS2 tbs_params;
    tbs_params.version = TBS_CONTEXT_VERSION_TWO;
    tbs_params.includeTpm12 = 0;
    tbs_params.includeTpm20 = 1;


    /* open, if not already open */
    if (ctx->winCtx.tbs_context == NULL) {
        rc = Tbsi_Context_Create((TBS_CONTEXT_PARAMS*)&tbs_params,
                                 &ctx->winCtx.tbs_context);
    }

    /* send the command to the device.  Error if the device send fails. */
    if (rc == 0) {
        uint32_t tmp = packet->size;
        rc = Tbsip_Submit_Command(ctx->winCtx.tbs_context,
                                  TBS_COMMAND_LOCALITY_ZERO,
                                  TBS_COMMAND_PRIORITY_NORMAL,
                                  packet->buf,
                                  packet->pos,
                                  packet->buf,
                                  (UINT32*)&tmp);
        packet->pos = tmp;
    }

    return rc;
}

int TPM2_WinApi_Cleanup(TPM2_CTX* ctx)
{
    int rc = TPM_RC_SUCCESS;
    if (ctx->winCtx.tbs_context != NULL) {
        rc = Tbsip_Context_Close(ctx->winCtx.tbs_context);
        ctx->winCtx.tbs_context = NULL;
    }

    return rc;
}

#endif
