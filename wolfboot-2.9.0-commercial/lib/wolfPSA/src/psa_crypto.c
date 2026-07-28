/* psa_crypto.c
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
#include "psa_trace.h"
#include <wolfpsa/psa_engine.h>
#include <wolfssl/wolfcrypt/wc_port.h>

static int g_psa_crypto_initialized = 0;

int wolfPSA_CryptoIsInitialized(void)
{
    return g_psa_crypto_initialized;
}

psa_status_t psa_crypto_init(void)
{
    int ret;

    wolfpsa_trace("psa_crypto_init()");

    if (g_psa_crypto_initialized) {
        return PSA_SUCCESS;
    }

    ret = wolfCrypt_Init();
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }

    g_psa_crypto_initialized = 1;
    return PSA_SUCCESS;
}

#endif /* WOLFSSL_PSA_ENGINE */
