/* psa_random.c
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
#include <wolfpsa/psa_random.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/mem_track.h>
#include <wolfssl/wolfcrypt/random.h>

extern int wolfPSA_CryptoIsInitialized(void);

/* Generate random bytes */
psa_status_t psa_generate_random(uint8_t *output, size_t output_size)
{
    int ret;
    WC_RNG rng;

    if (!wolfPSA_CryptoIsInitialized()) {
        return PSA_ERROR_BAD_STATE;
    }

    if (output == NULL && output_size > 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (output_size > UINT32_MAX) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    wolfpsa_trace("psa_generate_random(%zu)", output_size);
    
    /* Initialize the RNG */
    ret = wc_InitRng(&rng);
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }
    
    /* Generate random bytes */
    ret = wc_RNG_GenerateBlock(&rng, output, (word32)output_size);
    
    /* Free the RNG */
    wc_FreeRng(&rng);
    
    if (ret != 0) {
        return wc_error_to_psa_status(ret);
    }
    
    return PSA_SUCCESS;
}

#endif /* WOLFSSL_PSA_ENGINE */
