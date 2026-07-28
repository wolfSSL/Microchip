/* login_another_user_test.c
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

#define TEST_DIR "./store/login_another_user_test"
#define WOLFPKCS11_TOKEN_FILENAME "wp11_token_0000000000000001"

static byte* soPin = (byte*)"password123456";
static CK_ULONG soPinLen = 14;
static byte* userPin = (byte*)"wolfpkcs11-test";
static CK_ULONG userPinLen = 15;

static void cleanup_store(void)
{
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s" PATH_SEP "%s", TEST_DIR,
             WOLFPKCS11_TOKEN_FILENAME);
    (void)remove(filepath);
}

static int run_test(void)
{
    CK_RV rv;
    CK_C_INITIALIZE_ARGS args;
    CK_SLOT_ID slotList[16];
    CK_ULONG slotCount = sizeof(slotList) / sizeof(slotList[0]);
    CK_SLOT_ID slot = 0;
    CK_SESSION_HANDLE session = 0;
    int sessFlags = CKF_SERIAL_SESSION | CKF_RW_SESSION;
    /* 32-byte space-padded label as required by C_InitToken. */
    CK_UTF8CHAR label[32];

    XMEMSET(label, ' ', sizeof(label));
    XMEMCPY(label, "another-user-test", 17);

    /* Start from an uninitialized token. */
    cleanup_store();

    rv = pkcs11_load();
    CHECK_RV(rv, "load library", CKR_OK);
    if (rv != CKR_OK)
        return -1;

    XMEMSET(&args, 0, sizeof(args));
    args.flags = CKF_OS_LOCKING_OK;
    rv = funcList->C_Initialize(&args);
    CHECK_RV(rv, "C_Initialize", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    rv = funcList->C_GetSlotList(CK_TRUE, slotList, &slotCount);
    CHECK_RV(rv, "C_GetSlotList", CKR_OK);
    if (rv != CKR_OK || slotCount == 0)
        goto out;
    slot = slotList[0];

    /* C_InitToken (sets the SO PIN) requires no open session. */
    rv = funcList->C_InitToken(slot, soPin, soPinLen, label);
    CHECK_RV(rv, "C_InitToken", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    rv = funcList->C_OpenSession(slot, sessFlags, NULL, NULL, &session);
    CHECK_RV(rv, "C_OpenSession", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    /* SO logged in: a second SO login is the same user type. */
    rv = funcList->C_Login(session, CKU_SO, soPin, soPinLen);
    CHECK_RV(rv, "C_Login(SO)", CKR_OK);

    rv = funcList->C_Login(session, CKU_SO, soPin, soPinLen);
    CHECK_RV(rv, "C_Login(SO) again -> ALREADY_LOGGED_IN",
             CKR_USER_ALREADY_LOGGED_IN);

    rv = funcList->C_Login(session, CKU_USER, userPin, userPinLen);
    CHECK_RV(rv, "C_Login(USER) while SO -> ANOTHER_ALREADY_LOGGED_IN",
             CKR_USER_ANOTHER_ALREADY_LOGGED_IN);

    /* Set the user PIN (requires SO login) for the second phase. */
    rv = funcList->C_InitPIN(session, userPin, userPinLen);
    CHECK_RV(rv, "C_InitPIN", CKR_OK);

    rv = funcList->C_Logout(session);
    CHECK_RV(rv, "C_Logout(SO)", CKR_OK);

    /* USER logged in: a second USER login is the same user type. */
    rv = funcList->C_Login(session, CKU_USER, userPin, userPinLen);
    CHECK_RV(rv, "C_Login(USER)", CKR_OK);

    rv = funcList->C_Login(session, CKU_USER, userPin, userPinLen);
    CHECK_RV(rv, "C_Login(USER) again -> ALREADY_LOGGED_IN",
             CKR_USER_ALREADY_LOGGED_IN);

    rv = funcList->C_Login(session, CKU_SO, soPin, soPinLen);
    CHECK_RV(rv, "C_Login(SO) while USER -> ANOTHER_ALREADY_LOGGED_IN",
             CKR_USER_ANOTHER_ALREADY_LOGGED_IN);

    funcList->C_Logout(session);

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

    printf("=== wolfPKCS11 C_Login another-user test ===\n");
    run_test();
    return pkcs11_test_summary();
}
