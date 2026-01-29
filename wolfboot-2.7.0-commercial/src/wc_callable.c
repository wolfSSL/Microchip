/* wc_callable.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifdef WOLFCRYPT_SECURE_MODE

#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/ssl.h"
#include "wolfssl/wolfcrypt/ecc.h"
#include "wolfssl/wolfcrypt/aes.h"
#include "wolfssl/wolfcrypt/random.h"
#include "wolfboot/wolfboot.h"
#include "wolfboot/wc_secure.h"
#include "hal.h"
#include <stdint.h>

static WC_RNG wcs_rng;

int CSME_NSE_API wcs_get_random(uint8_t *rand, uint32_t size)
{
    return wc_RNG_GenerateBlock(&wcs_rng, rand, size);
}

void wcs_Init(void)
{
    hal_trng_init();
    wc_InitRng(&wcs_rng);
}

#endif /* WOLFCRYPT_SECURE_MODE */
