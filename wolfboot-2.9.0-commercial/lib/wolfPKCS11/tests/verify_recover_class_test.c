/* verify_recover_class_test.c
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

#define TEST_DIR "./store/verify_recover_class_test"

static int run_test(void)
{
    CK_RV rv;
    CK_SESSION_HANDLE session = 0;
    CK_MECHANISM mech;
    CK_OBJECT_HANDLE secret = CK_INVALID_HANDLE;
    CK_OBJECT_CLASS secretClass = CKO_SECRET_KEY;
    CK_KEY_TYPE genericType = CKK_GENERIC_SECRET;
    CK_BBOOL ckTrue = CK_TRUE;
    CK_BBOOL ckFalse = CK_FALSE;
    byte keyData[16] = { 0 };
    CK_ATTRIBUTE secretTmpl[] = {
        { CKA_CLASS,       &secretClass,  sizeof(secretClass)  },
        { CKA_KEY_TYPE,    &genericType,  sizeof(genericType)  },
        { CKA_VALUE,       keyData,       sizeof(keyData)      },
        { CKA_EXTRACTABLE, &ckTrue,       sizeof(ckTrue)       },
        /* Public so the object is reachable without C_Login. */
        { CKA_PRIVATE,     &ckFalse,      sizeof(ckFalse)      },
    };
    CK_ULONG secretTmplCnt = sizeof(secretTmpl) / sizeof(*secretTmpl);

    rv = pkcs11_load();
    CHECK_RV(rv, "load library", CKR_OK);
    if (rv != CKR_OK)
        return -1;

    rv = pkcs11_open_session(&session);
    CHECK_RV(rv, "open session", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    rv = funcList->C_CreateObject(session, secretTmpl, secretTmplCnt, &secret);
    CHECK_RV(rv, "C_CreateObject(secret key)", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    XMEMSET(&mech, 0, sizeof(mech));
    mech.mechanism = CKM_RSA_PKCS;

    /* A secret key is the wrong object class for verify-recover. */
    rv = funcList->C_VerifyRecoverInit(session, &mech, secret);
    CHECK_RV(rv, "C_VerifyRecoverInit(secret key handle)",
             CKR_KEY_TYPE_INCONSISTENT);

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

    printf("=== wolfPKCS11 C_VerifyRecoverInit wrong-class test ===\n");
    run_test();
    return pkcs11_test_summary();
}
