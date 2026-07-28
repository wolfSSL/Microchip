/* psa_engine.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
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

#include <wolfssl/wolfcrypt/settings.h>

#if defined(WOLFSSL_PSA_ENGINE)

#include <psa/crypto.h>
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/cryptocb.h>

/* Runtime-settable devId threaded through every wolfPSA-internal
 * wc_*Init()/wc_NewRsaKey() call. INVALID_DEVID (the default) keeps
 * the original behaviour: wolfCrypt runs the operation locally. */
static int wolfPSA_default_devid = INVALID_DEVID;

int wolfPSA_SetDefaultDevID(int devId)
{
    wolfPSA_default_devid = devId;
    return 0;
}

int wolfPSA_GetDefaultDevID(void)
{
    return wolfPSA_default_devid;
}

/* wolfCrypt error code to PSA status code conversion */
psa_status_t wc_error_to_psa_status(int ret)
{
    psa_status_t status;

    if (ret == 0) {
        return PSA_SUCCESS;
    }

    switch (ret) {
        case NOT_COMPILED_IN:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
        case BAD_FUNC_ARG:
            status = PSA_ERROR_INVALID_ARGUMENT;
            break;
        case ECC_BAD_ARG_E:
        case ECC_CURVE_OID_E:
        case ECC_PRIV_KEY_E:
        case ECC_OUT_OF_RANGE_E:
        case ECC_PRIVATEONLY_E:
            status = PSA_ERROR_INVALID_ARGUMENT;
            break;
        case BUFFER_E:
            status = PSA_ERROR_BUFFER_TOO_SMALL;
            break;
        case MEMORY_E:
            status = PSA_ERROR_INSUFFICIENT_MEMORY;
            break;
        case WC_HW_E:
            status = PSA_ERROR_HARDWARE_FAILURE;
            break;
        case SIG_VERIFY_E:
            status = PSA_ERROR_INVALID_SIGNATURE;
            break;
        case AES_GCM_AUTH_E:
        case AES_CCM_AUTH_E:
        case AES_EAX_AUTH_E:
        case AES_SIV_AUTH_E:
        case MAC_CMP_FAILED_E:
            status = PSA_ERROR_INVALID_SIGNATURE;
            break;
        case RNG_FAILURE_E:
            status = PSA_ERROR_INSUFFICIENT_ENTROPY;
            break;
        case BAD_PADDING_E:
            status = PSA_ERROR_INVALID_PADDING;
            break;
        case BAD_STATE_E:
            status = PSA_ERROR_BAD_STATE;
            break;
        default:
            status = PSA_ERROR_GENERIC_ERROR;
            break;
    }

    return status;
}

#endif /* WOLFSSL_PSA_ENGINE */
