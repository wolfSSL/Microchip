/* wolfentropy.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFENTROPY_H
#define WOLFENTROPY_H

#include <wolfssl/wolfcrypt/types.h>

#ifdef HAVE_ENTROPY_MEMUSE

#if defined(ENTROPY_SCALE_FACTOR) && FIPS_VERSION3_GE(5,2,4) && \
    FIPS_VERSION3_NE(6,0,0)
    #error "ENTROPY_SCALE_FACTOR defined elsewhere than wolfEntropy.h"
#endif

#if FIPS_VERSION3_GE(5,2,4) && FIPS_VERSION3_NE(6,0,0)
    /* Do not allow default fallback to /dev/urandom when in FIPS mode that
     * supports ESV */
    #define ENTROPY_MEMUSE_FORCE_FAILURE
#endif

#ifndef ENTROPY_SCALE_FACTOR
    /* The entropy scale factor should be the whole number inverse of the
     * minimum bits of entropy per bit of NDRNG output. */
    /* Full strength, conditioned entropy is requested of MemUse Entropy. */
    #if defined(HAVE_FIPS) && defined(HAVE_FIPS_VERSION) && \
        (HAVE_FIPS_VERSION >= 2)
        #define ENTROPY_SCALE_FACTOR (4)
    #else
        #define ENTROPY_SCALE_FACTOR (1)
    #endif
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/* Maximum entropy bits that can be produced. */
#define MAX_ENTROPY_BITS    256

/* For generating data for assessment. */
WOLFSSL_API int wc_Entropy_GetRawEntropy(unsigned char* raw, int cnt);
WOLFSSL_API int wc_Entropy_Get(int bits, unsigned char* entropy, word32 len);
WOLFSSL_API int wc_Entropy_OnDemandTest(void);

WOLFSSL_LOCAL int Entropy_Init(void);
WOLFSSL_LOCAL void Entropy_Final(void);

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* HAVE_ENTROPY_MEMUSE */
#endif /* WOLFENTROPY_H */
