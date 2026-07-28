/* casper_port.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef _CASPER_PORT_H_
#define _CASPER_PORT_H_

#include <wolfssl/wolfcrypt/settings.h>

int wc_casper_init(void);

#if !defined(NO_RSA) && defined(WOLFSSL_NXP_CASPER_RSA_PUB_EXPTMOD)
#include <wolfssl/wolfcrypt/rsa.h>

int casper_rsa_public_exptmod(
    const byte* in, word32 inLen, byte* out, word32* outLen, RsaKey* key
);
#endif /* !NO_RSA && WOLFSSL_NXP_CASPER_RSA_PUB_EXPTMOD */


#if defined(HAVE_ECC)
#include <wolfssl/wolfcrypt/ecc.h>

#ifdef WOLFSSL_NXP_CASPER_ECC_MULMOD
int casper_ecc_mulmod(
    const mp_int *m, ecc_point *P, ecc_point *R, int curve_id
);
#endif /* WOLFSSL_NXP_CASPER_ECC_MULMOD */

#ifdef WOLFSSL_NXP_CASPER_ECC_MUL2ADD
int casper_ecc_mul2add(
    const mp_int *m, ecc_point *P, const mp_int *n, ecc_point *Q,
    ecc_point *R, int curve_id
);
#endif /* WOLFSSL_NXP_CASPER_ECC_MUL2ADD */
#endif /* HAVE_ECC */

#endif /* _CASPER_PORT_H_ */
