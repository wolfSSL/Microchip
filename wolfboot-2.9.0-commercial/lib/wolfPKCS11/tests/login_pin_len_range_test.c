/* login_pin_len_range_test.c
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
#include <string.h>

#ifndef WOLFSSL_USER_SETTINGS
    #include <wolfssl/options.h>
#endif
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/misc.h>

#ifndef WOLFPKCS11_USER_SETTINGS
    #include <wolfpkcs11/options.h>
#endif
#include <wolfpkcs11/pkcs11.h>

#ifndef HAVE_PKCS11_STATIC
#include <dlfcn.h>
#endif

#include "testdata.h"
#include "pkcs11_test_util.h"

#define TEST_DIR "./store/login_pin_len_range_test"

/* Longer than WP11_MAX_PIN_LEN (32), so checkPinLen reports CKR_PIN_LEN_RANGE
 * regardless of the WP11_MIN_PIN_LEN build setting. */
static const char* tooLongPin =
    "0123456789012345678901234567890123456789";

static int run_test(void)
{
    CK_RV rv;
    CK_SESSION_HANDLE session = 0;
    CK_ULONG pinLen = (CK_ULONG)XSTRLEN(tooLongPin);

    rv = pkcs11_load();
    CHECK_RV(rv, "load library", CKR_OK);
    if (rv != CKR_OK)
        return -1;

    rv = pkcs11_open_session(&session);
    CHECK_RV(rv, "open session", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    rv = funcList->C_Login(session, CKU_USER, (CK_UTF8CHAR_PTR)tooLongPin,
                           pinLen);
    CHECK_RV(rv, "C_Login(CKU_USER, over-length PIN)", CKR_PIN_LEN_RANGE);

    rv = funcList->C_Login(session, CKU_SO, (CK_UTF8CHAR_PTR)tooLongPin,
                           pinLen);
    CHECK_RV(rv, "C_Login(CKU_SO, over-length PIN)", CKR_PIN_LEN_RANGE);

out:
    if (session != 0)
        funcList->C_CloseSession(session);
    funcList->C_Finalize(NULL);
    pkcs11_unload();
    return 0;
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

#ifndef WOLFPKCS11_NO_ENV
    XSETENV("WOLFPKCS11_TOKEN_PATH", TEST_DIR, 1);
#endif

    printf("=== wolfPKCS11 C_Login PIN length range test ===\n");
    run_test();
    return pkcs11_test_summary();
}
