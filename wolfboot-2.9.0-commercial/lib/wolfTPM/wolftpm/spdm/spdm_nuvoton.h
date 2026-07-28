/* spdm_nuvoton.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Nuvoton TPM SPDM Support
 *
 * Nuvoton-specific SPDM functions (GetStatus, SetOnlyMode).
 * Shared TCG code is in spdm_tcg.h / spdm_tcg.c.
 *
 * The Nuvoton NPCT75x TPM uses a simplified SPDM flow:
 *   GET_VERSION -> GET_PUB_KEY -> KEY_EXCHANGE -> GIVE_PUB_KEY -> FINISH
 *
 * Notable differences from standard SPDM:
 * - No GET_CAPABILITIES or NEGOTIATE_ALGORITHMS (Algorithm Set B is fixed)
 * - Uses vendor-defined commands for identity key exchange
 * - TCG binding headers wrap all SPDM messages
 *
 * Reference: Nuvoton SPDM Guidance Rev 1.11
 */

#ifndef WOLFSPDM_NUVOTON_H
#define WOLFSPDM_NUVOTON_H

/* Include shared TCG declarations */
#include <wolftpm/spdm/spdm_tcg.h>

#ifdef WOLFSPDM_NUVOTON

#ifdef __cplusplus
extern "C" {
#endif

/* ----- Nuvoton SPDM Status ----- */

typedef struct WOLFSPDM_NUVOTON_STATUS {
    int     spdmEnabled;
    int     sessionActive;
    int     spdmOnlyLocked;
    byte    specVersionMajor;
    byte    specVersionMinor;
} WOLFSPDM_NUVOTON_STATUS;

/* ----- Nuvoton-Only Functions ----- */

WOLFTPM_API int wolfSPDM_Nuvoton_GetStatus(
    WOLFSPDM_CTX* ctx,
    WOLFSPDM_NUVOTON_STATUS* status);

WOLFTPM_API int wolfSPDM_Nuvoton_SetOnlyMode(
    WOLFSPDM_CTX* ctx,
    int lock);

#ifdef __cplusplus
}
#endif

#endif /* WOLFSPDM_NUVOTON */

#endif /* WOLFSPDM_NUVOTON_H */
