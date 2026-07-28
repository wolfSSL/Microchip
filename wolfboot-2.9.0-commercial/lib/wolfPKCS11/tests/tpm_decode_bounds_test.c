/* tpm_decode_bounds_test.c
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
    #include <wolfpkcs11/config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WOLFSSL_USER_SETTINGS
    #include <wolfssl/options.h>
#endif
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/error-crypt.h>

#ifndef WOLFPKCS11_USER_SETTINGS
    #include <wolfpkcs11/options.h>
#endif
#include <wolfpkcs11/pkcs11.h>

#if defined(WOLFPKCS11_TPM) && defined(DEBUG_WOLFPKCS11) && \
    (!defined(NO_RSA) || defined(HAVE_ECC))

/* DEBUG_WOLFPKCS11-only hook exported by libwolfpkcs11. */
extern int WP11_Test_DecodeTpmKey(CK_SLOT_ID slotId, unsigned char* keyData,
    int keyDataLen);

static int test_passed = 0;
static int test_failed = 0;

/*
 * Decode a truncated blob of total length 'len'. When len >= 2 the first two
 * bytes carry pubAreaSize. The blob is allocated to exactly 'len' bytes so any
 * read past it is a heap overflow. The patched decoder must return BUFFER_E.
 */
static void run_case(int len, unsigned short pubAreaSize, const char* label)
{
    unsigned char* buf;
    int ret;

    /* Allocate exactly len bytes (at least 1 so the pointer is non-NULL) so an
     * out-of-bounds read is detectable. */
    buf = (unsigned char*)malloc(len < 1 ? 1 : (size_t)len);
    if (buf == NULL) {
        fprintf(stderr, "FAIL: %s: malloc\n", label);
        test_failed++;
        return;
    }
    if (len >= 2)
        memcpy(buf, &pubAreaSize, sizeof(pubAreaSize));

    ret = WP11_Test_DecodeTpmKey(1, buf, len);
    free(buf);

    if (ret == BUFFER_E) {
        printf("PASS: %s (BUFFER_E)\n", label);
        test_passed++;
    }
    else {
        fprintf(stderr, "FAIL: %s: expected BUFFER_E, got %d\n", label, ret);
        test_failed++;
    }
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    printf("=== wolfPKCS11 TPM Decode Bounds Test ===\n\n");

    /* keyDataLen too small for the 2-byte pubAreaSize. */
    run_case(0, 0, "len=0 (no pubAreaSize)");
    run_case(1, 0, "len=1 (partial pubAreaSize)");

    /* pubAreaSize present but blob too small for the declared public area. */
    run_case(2, 0,   "len=2 pubAreaSize=0 (no public area)");
    run_case(3, 1,   "len=3 pubAreaSize=1 (public area truncated)");
    run_case(5, 4,   "len=5 pubAreaSize=4 (public area truncated)");
    run_case(6, 10,  "len=6 pubAreaSize=10 (public area truncated)");
    run_case(8, 32,  "len=8 pubAreaSize=32 (public area truncated)");

    /* pubAreaSize larger than the parse buffer must also be rejected. */
    run_case(4, 0xFFFF, "len=4 pubAreaSize=65535 (oversized)");

    printf("\n=== Test Results ===\n");
    printf("Tests passed: %d\n", test_passed);
    printf("Tests failed: %d\n", test_failed);
    if (test_failed == 0)
        printf("ALL TESTS PASSED!\n");
    else
        printf("SOME TESTS FAILED!\n");

    return (test_failed == 0) ? 0 : 1;
}

#else /* !WOLFPKCS11_TPM || !DEBUG_WOLFPKCS11 */

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    printf("TPM/debug not available, skipping TPM decode bounds test\n");
    return 0;
}

#endif
