/* psa_engine.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/**
 * Platform Security Architecture (PSA) Engine header
 *
 * If WOLFSSL_PSA_ENGINE is defined, wolfSSL provides an implementation of the
 * PSA Crypto API that calls wolfCrypt APIs.
 *
 */

#ifndef WOLFSSL_PSA_ENGINE_H
#define WOLFSSL_PSA_ENGINE_H

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#if defined(WOLFSSL_PSA_ENGINE)

#include <psa/crypto.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/visibility.h>

#ifndef NO_AES
#include <wolfssl/wolfcrypt/aes.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* wolfCrypt error code to PSA status code conversion */
WOLFSSL_LOCAL psa_status_t wc_error_to_psa_status(int ret);

/* Default wolfCrypt devId threaded through wolfPSA's internal wc_*Init()
 * calls. Defaults to INVALID_DEVID so that operations execute locally.
 * Set to a registered crypto_cb devId (e.g. via wc_CryptoCb_RegisterDevice)
 * to route every wolfPSA-issued wolfCrypt call through that callback —
 * this is the integration hook for crypto offload backends such as
 * wolfHSM or a hardware accelerator. Safe to call before psa_crypto_init().
 *
 * Threading: the default devId is held in a process-global variable read
 * by every wolfPSA-internal wc_*Init() invocation. Callers must set it
 * during single-threaded initialisation (before any PSA operation is
 * issued) or otherwise serialise the setter with external synchronisation;
 * concurrent calls to wolfPSA_SetDefaultDevID() while PSA operations are
 * in flight are not supported.
 *
 * Returns 0 on success. */
WOLFSSL_API int wolfPSA_SetDefaultDevID(int devId);

/* Returns the devId previously set with wolfPSA_SetDefaultDevID() or
 * INVALID_DEVID if none has been set. */
WOLFSSL_API int wolfPSA_GetDefaultDevID(void);

#ifdef __cplusplus
}
#endif

#endif /* WOLFSSL_PSA_ENGINE */
#endif /* WOLFSSL_PSA_ENGINE_H */
