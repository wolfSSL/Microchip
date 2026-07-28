/* create_object_class_test.c
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

#define TEST_DIR "./store/create_object_class_test"

static int run_test(void)
{
    CK_RV rv;
    CK_SESSION_HANDLE session = 0;
    CK_OBJECT_HANDLE obj = CK_INVALID_HANDLE;
    CK_OBJECT_CLASS secretClass = CKO_SECRET_KEY;
    CK_KEY_TYPE genericType = CKK_GENERIC_SECRET;
    CK_BBOOL ckFalse = CK_FALSE;
    byte keyData[16] = { 0 };
    CK_ATTRIBUTE noClassTmpl[] = {
        { CKA_KEY_TYPE, &genericType, sizeof(genericType) },
        { CKA_VALUE,    keyData,      sizeof(keyData)      },
        { CKA_PRIVATE,  &ckFalse,     sizeof(ckFalse)      },
    };
    CK_ULONG noClassTmplCnt = sizeof(noClassTmpl) / sizeof(*noClassTmpl);
    CK_ATTRIBUTE withClassTmpl[] = {
        { CKA_CLASS,    &secretClass, sizeof(secretClass) },
        { CKA_KEY_TYPE, &genericType, sizeof(genericType) },
        { CKA_VALUE,    keyData,      sizeof(keyData)      },
        { CKA_PRIVATE,  &ckFalse,     sizeof(ckFalse)      },
    };
    CK_ULONG withClassTmplCnt = sizeof(withClassTmpl) / sizeof(*withClassTmpl);

    rv = pkcs11_load();
    CHECK_RV(rv, "load library", CKR_OK);
    if (rv != CKR_OK)
        return -1;

    rv = pkcs11_open_session(&session);
    CHECK_RV(rv, "open session", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    rv = funcList->C_CreateObject(session, noClassTmpl, noClassTmplCnt, &obj);
    CHECK_RV(rv, "C_CreateObject(no CKA_CLASS)", CKR_TEMPLATE_INCOMPLETE);

    rv = funcList->C_CreateObject(session, withClassTmpl, withClassTmplCnt,
                                  &obj);
    CHECK_RV(rv, "C_CreateObject(with CKA_CLASS)", CKR_OK);

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

    printf("=== wolfPKCS11 C_CreateObject CKA_CLASS test ===\n");
    run_test();
    return pkcs11_test_summary();
}
