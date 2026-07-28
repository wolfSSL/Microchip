/* wc_callable.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
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

#ifdef WOLFBOOT_TZ_FWTPM
#include "wolfboot/wcs_fwtpm.h"
#endif

/* wcs_get_random is a cmse_nonsecure_entry veneer: the rand pointer and size
 * arrive from the non-secure caller and are used as the write target of
 * wc_RNG_GenerateBlock. Validate the whole range lives in the non-secure world
 * before writing, otherwise an NS caller could aim the RNG output at Secure SRAM
 * (a confused-deputy write primitive). The check verifies only the
 * Secure/Non-secure attribution (CMSE_NONSECURE); the MPU read/write permission
 * bits are deliberately not required, as they read back as 0 when the NS MPU is
 * disabled (NO_MPU) and do not constrain Secure accesses to NS memory anyway.
 * Outside a CMSE secure build there is no security boundary, so the check
 * collapses to a non-NULL pass-through. */
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#include <arm_cmse.h>
#define WOLFBOOT_WCS_NS_RW(p, sz) \
    cmse_check_address_range((void*)(p), (size_t)(sz), CMSE_NONSECURE)
#else
#define WOLFBOOT_WCS_NS_RW(p, sz) ((void*)(p))
#endif

#ifdef WOLFCRYPT_TZ_WOLFHSM
#include "wolfboot/wcs_wolfhsm.h"
#endif

static WC_RNG wcs_rng;

int CSME_NSE_API wcs_get_random(uint8_t *rand, uint32_t size)
{
    if (WOLFBOOT_WCS_NS_RW(rand, size) == NULL) {
        return BAD_FUNC_ARG;
    }
    return wc_RNG_GenerateBlock(&wcs_rng, rand, size);
}

void wcs_Init(void)
{
    hal_trng_init();
    wc_InitRng(&wcs_rng);
#ifdef WOLFBOOT_TZ_FWTPM
    wcs_fwtpm_init();
#endif
#ifdef WOLFCRYPT_TZ_WOLFHSM
    wcs_wolfhsm_init();
#endif
}

#endif /* WOLFCRYPT_SECURE_MODE */
