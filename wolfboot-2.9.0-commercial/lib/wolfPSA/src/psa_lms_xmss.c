/* psa_lms_xmss.c
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

#if defined(WOLFSSL_PSA_ENGINE) && \
    (defined(WOLFSSL_HAVE_LMS) || defined(WOLFSSL_HAVE_XMSS))

#include <psa/crypto.h>
#include "psa_size.h"
#include "psa_pqc_internal.h"
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>

#ifdef WOLFSSL_HAVE_LMS
#include <wolfssl/wolfcrypt/wc_lms.h>

/*
 * Verify an LMS/HSS signature.
 *
 * pub     - raw HSS public key blob (RFC 8554 §6.1: u32str(L) || pub[0])
 * pub_len - byte length of pub
 * msg     - message that was signed
 * msg_len - byte length of msg
 * sig     - raw HSS signature blob
 * sig_len - byte length of sig
 *
 * The parameter set (levels/height/winternitz) is auto-derived from the
 * leading type fields in the public key by wc_LmsKey_ImportPubRaw when
 * the key is in INITED state (no SetParameters call required).
 *
 * wc_LmsKey_Verify() return convention: 0 = success, SIG_VERIFY_E = bad
 * signature, other negative values = internal/argument error.  There is
 * no separate *res out-parameter in the current wc_lms.h API.
 */
psa_status_t wolfpsa_lms_verify(const uint8_t *pub, size_t pub_len,
        const uint8_t *msg, size_t msg_len, const uint8_t *sig, size_t sig_len)
{
    int     ret;
    LmsKey  key;

    if (wolfpsa_check_word32_length(pub_len) != PSA_SUCCESS ||
        wolfpsa_check_word32_length(msg_len) != PSA_SUCCESS ||
        wolfpsa_check_word32_length(sig_len) != PSA_SUCCESS) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ret = wc_LmsKey_Init(&key, NULL, wolfPSA_GetDefaultDevID());
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    /* Import the raw public key; parameters are auto-derived from the
     * L/lmsType/lmOtsType fields encoded in the blob. */
    ret = wc_LmsKey_ImportPubRaw(&key, pub, (word32)pub_len);
    if (ret != 0) {
        wc_LmsKey_Free(&key);
        return wc_error_to_psa_status(ret);
    }

    ret = wc_LmsKey_Verify(&key, sig, (word32)sig_len,
                           msg, (int)msg_len);

    wc_LmsKey_Free(&key);

    if (ret == WC_NO_ERR_TRACE(SIG_VERIFY_E) || ret == -1) {
        return PSA_ERROR_INVALID_SIGNATURE;
    }
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    return PSA_SUCCESS;
}

#endif /* WOLFSSL_HAVE_LMS */

#ifdef WOLFSSL_HAVE_XMSS
#include <wolfssl/wolfcrypt/wc_xmss.h>

/*
 * Verify an XMSS or XMSS^MT signature.
 *
 * pub     - raw XMSS/XMSS^MT public key blob (RFC 8391: OID || root || SEED)
 * pub_len - byte length of pub
 * msg     - message that was signed
 * msg_len - byte length of msg
 * sig     - raw XMSS/XMSS^MT signature blob
 * sig_len - byte length of sig
 *
 * The parameter set is auto-derived from the 4-byte OID prefix in the public
 * key by wc_XmssKey_ImportPubRaw_ex when the key is in INITED state.
 * Because XMSS and XMSS^MT OID spaces overlap we try XMSS (is_xmssmt=0)
 * first; if the OID is not found in the XMSS table we retry with
 * is_xmssmt=1.  A second Init/Free pair is used for the retry so that
 * partial state from the first attempt does not carry over.
 *
 * wc_XmssKey_Verify() return convention: 0 = success, SIG_VERIFY_E / -1 =
 * bad signature, other negative values = internal/argument error.  There is
 * no separate *res out-parameter in the current wc_xmss.h API.
 */
psa_status_t wolfpsa_xmss_verify(const uint8_t *pub, size_t pub_len,
        const uint8_t *msg, size_t msg_len, const uint8_t *sig, size_t sig_len)
{
    int      ret;
    XmssKey  key;
    int      is_xmssmt;

    if (wolfpsa_check_word32_length(pub_len) != PSA_SUCCESS ||
        wolfpsa_check_word32_length(msg_len) != PSA_SUCCESS ||
        wolfpsa_check_word32_length(sig_len) != PSA_SUCCESS) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Try XMSS first (is_xmssmt = 0).  On OID lookup failure
     * (NOT_COMPILED_IN or BUFFER_E from a size mismatch) retry as
     * XMSS^MT (is_xmssmt = 1). */
    for (is_xmssmt = 0; is_xmssmt <= 1; is_xmssmt++) {
        ret = wc_XmssKey_Init(&key, NULL, wolfPSA_GetDefaultDevID());
        if (ret != 0) {
            return wc_error_to_psa_status(ret);
        }

        ret = wc_XmssKey_ImportPubRaw_ex(&key, pub, (word32)pub_len,
                                         is_xmssmt);
        if (ret == WC_NO_ERR_TRACE(NOT_COMPILED_IN) ||
            ret == WC_NO_ERR_TRACE(BUFFER_E)) {
            /* OID not found in this family's table; try the other. */
            wc_XmssKey_Free(&key);
            continue;
        }
        if (ret != 0) {
            /* Genuine import error (bad length, bad state, etc.). */
            wc_XmssKey_Free(&key);
            return wc_error_to_psa_status(ret);
        }

        /* Import succeeded; proceed to verify. */
        break;
    }

    if (ret != 0) {
        /* Neither XMSS nor XMSS^MT table recognised the OID. */
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ret = wc_XmssKey_Verify(&key, sig, (word32)sig_len,
                            msg, (int)msg_len);

    wc_XmssKey_Free(&key);

    if (ret == WC_NO_ERR_TRACE(SIG_VERIFY_E) || ret == -1) {
        return PSA_ERROR_INVALID_SIGNATURE;
    }
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    return PSA_SUCCESS;
}

#endif /* WOLFSSL_HAVE_XMSS */

#endif /* WOLFSSL_PSA_ENGINE && (WOLFSSL_HAVE_LMS || WOLFSSL_HAVE_XMSS) */
