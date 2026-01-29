/* loader.h
 *
 * Public key information for the signed images
 *
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef LOADER_H
#define LOADER_H

#ifdef __cplusplus
extern "C" {
#endif

#define ED25519_IMAGE_SIGNATURE_SIZE (64)
#define ED448_IMAGE_SIGNATURE_SIZE (114)

#if defined(WOLFBOOT_SIGN_ECC256) || defined(WOLFBOOT_SECONDARY_SIGN_ECC256)
#define ECC_IMAGE_SIGNATURE_SIZE (64)
#elif defined(WOLFBOOT_SIGN_ECC384) || defined(WOLFBOOT_SECONDARY_SIGN_ECC384)
#define ECC_IMAGE_SIGNATURE_SIZE (96)
#elif defined(WOLFBOOT_SIGN_ECC521) || defined(WOLFBOOT_SECONDARY_SIGN_ECC521)
#define ECC_IMAGE_SIGNATURE_SIZE (132)
#endif

#if defined(WOLFBOOT_SIGN_RSA2048) || defined(WOLFBOOT_SECONDARY_SIGN_RSA2048)
#define RSA_IMAGE_SIGNATURE_SIZE (256)
#elif defined(WOLFBOOT_SIGN_RSA3072) || defined(WOLFBOOT_SECONDARY_SIGN_RSA3072)
#define RSA_IMAGE_SIGNATURE_SIZE (384)
#elif defined(WOLFBOOT_SIGN_RSA4096) || defined(WOLFBOOT_SECONDARY_SIGN_RSA4096)
#define RSA_IMAGE_SIGNATURE_SIZE (512)
#endif

#ifndef ML_DSA_IMAGE_SIGNATURE_SIZE
#define ML_DSA_IMAGE_SIGNATURE_SIZE (3309)
#endif


void wolfBoot_start(void);

#if defined(ARCH_ARM) && defined(WOLFBOOT_ARMORED)

/* attempt to jump 5 times to self, causing loop that cannot be glitched past */
#define wolfBoot_panic() \
    asm volatile("b ."); \
    asm volatile("b .-2"); \
    asm volatile("b .-4"); \
    asm volatile("b .-6"); \
    asm volatile("b .-8");

#elif defined(ARCH_SIM)
#include <stdlib.h>
#include <stdio.h>
static inline void wolfBoot_panic(void)
{
    fprintf(stderr, "wolfBoot: PANIC!\n");
    exit('P');
}
#elif defined UNIT_TEST
static int wolfBoot_panicked = 0;
static inline void wolfBoot_panic(void)
{
    fprintf(stderr, "wolfBoot: PANIC!\n");
    wolfBoot_panicked++;
}
#else
#include "printf.h"
static inline void wolfBoot_panic(void)
{
    wolfBoot_printf("wolfBoot: PANIC!\n");
    while(1)
        ;
}
#endif

#ifdef WOLFCRYPT_SECURE_MODE
void wcs_Init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* LOADER_H */
