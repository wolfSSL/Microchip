/* aead_null_aad_test.c
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

#define TEST_DIR "./store/aead_null_aad_test"

static int run_test(void)
{
    CK_RV rv;
    CK_SESSION_HANDLE session = 0;
    CK_OBJECT_HANDLE aesKey = CK_INVALID_HANDLE;
    CK_OBJECT_CLASS secretClass = CKO_SECRET_KEY;
    CK_KEY_TYPE aesType = CKK_AES;
    CK_BBOOL ckTrue = CK_TRUE;
    CK_BBOOL ckFalse = CK_FALSE;
    CK_MECHANISM mech;
    CK_GCM_PARAMS gcm;
    CK_CCM_PARAMS ccm;
    byte iv[12];
    byte aad[16];
    byte plain[32], enc[64];
    CK_ULONG encSz;
    CK_ATTRIBUTE aesTmpl[] = {
        { CKA_CLASS,    &secretClass, sizeof(secretClass) },
        { CKA_KEY_TYPE, &aesType,     sizeof(aesType)     },
        { CKA_VALUE,    aes_128_key,  sizeof(aes_128_key) },
        { CKA_ENCRYPT,  &ckTrue,      sizeof(ckTrue)      },
        { CKA_PRIVATE,  &ckFalse,     sizeof(ckFalse)     },
    };
    CK_ULONG aesTmplCnt = sizeof(aesTmpl) / sizeof(*aesTmpl);

    XMEMSET(iv, 9, sizeof(iv));
    XMEMSET(aad, 5, sizeof(aad));
    XMEMSET(plain, 7, sizeof(plain));

    rv = pkcs11_load();
    CHECK_RV(rv, "load library", CKR_OK);
    if (rv != CKR_OK)
        return -1;

    rv = pkcs11_open_session(&session);
    CHECK_RV(rv, "open session", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    rv = funcList->C_CreateObject(session, aesTmpl, aesTmplCnt, &aesKey);
    CHECK_RV(rv, "C_CreateObject(AES key)", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    /* GCM: NULL AAD pointer with a non-zero AAD length must be rejected.
     * Skip if AES-GCM is not built in. */
    XMEMSET(&gcm, 0, sizeof(gcm));
    gcm.pIv = iv;
    gcm.ulIvLen = sizeof(iv);
    gcm.pAAD = NULL;
    gcm.ulAADLen = sizeof(aad);
    gcm.ulTagBits = 128;
    mech.mechanism = CKM_AES_GCM;
    mech.pParameter = &gcm;
    mech.ulParameterLen = sizeof(gcm);
    rv = funcList->C_EncryptInit(session, &mech, aesKey);
    if (rv == CKR_MECHANISM_INVALID) {
        printf("SKIP: AES-GCM not supported in this build\n");
        test_passed++;
    }
    else {
        CHECK_RV(rv, "C_EncryptInit GCM (NULL AAD, len 16)",
                 CKR_MECHANISM_PARAM_INVALID);

        /* The canonical no-AAD form (NULL pointer, zero length) is valid. */
        XMEMSET(&gcm, 0, sizeof(gcm));
        gcm.pIv = iv;
        gcm.ulIvLen = sizeof(iv);
        gcm.pAAD = NULL;
        gcm.ulAADLen = 0;
        gcm.ulTagBits = 128;
        mech.mechanism = CKM_AES_GCM;
        mech.pParameter = &gcm;
        mech.ulParameterLen = sizeof(gcm);
        rv = funcList->C_EncryptInit(session, &mech, aesKey);
        CHECK_RV(rv, "C_EncryptInit GCM (NULL AAD, len 0)", CKR_OK);
        if (rv == CKR_OK) {
            encSz = sizeof(enc);
            rv = funcList->C_Encrypt(session, plain, sizeof(plain), enc,
                                     &encSz);
            CHECK_RV(rv, "C_Encrypt GCM (no AAD) completes", CKR_OK);
        }

        /* A non-NULL AAD pointer with zero length is also a valid no-AAD
         * encoding and must be accepted. */
        XMEMSET(&gcm, 0, sizeof(gcm));
        gcm.pIv = iv;
        gcm.ulIvLen = sizeof(iv);
        gcm.pAAD = aad;
        gcm.ulAADLen = 0;
        gcm.ulTagBits = 128;
        mech.mechanism = CKM_AES_GCM;
        mech.pParameter = &gcm;
        mech.ulParameterLen = sizeof(gcm);
        rv = funcList->C_EncryptInit(session, &mech, aesKey);
        CHECK_RV(rv, "C_EncryptInit GCM (non-NULL AAD, len 0)", CKR_OK);
        if (rv == CKR_OK) {
            encSz = sizeof(enc);
            rv = funcList->C_Encrypt(session, plain, sizeof(plain), enc,
                                     &encSz);
            CHECK_RV(rv, "C_Encrypt GCM (non-NULL AAD, len 0) completes",
                     CKR_OK);
        }
    }

    /* CCM: same mismatch; skip if AES-CCM is not built in. */
    XMEMSET(&ccm, 0, sizeof(ccm));
    ccm.ulDataLen = sizeof(plain);
    ccm.pIv = iv;
    ccm.ulIvLen = sizeof(iv) - 5; /* 7-byte nonce is valid for CCM */
    ccm.pAAD = NULL;
    ccm.ulAADLen = sizeof(aad);
    ccm.ulMacLen = 16;
    mech.mechanism = CKM_AES_CCM;
    mech.pParameter = &ccm;
    mech.ulParameterLen = sizeof(ccm);
    rv = funcList->C_EncryptInit(session, &mech, aesKey);
    if (rv == CKR_MECHANISM_INVALID) {
        printf("SKIP: AES-CCM not supported in this build\n");
        test_passed++;
    }
    else {
        CHECK_RV(rv, "C_EncryptInit CCM (NULL AAD, len 16)",
                 CKR_MECHANISM_PARAM_INVALID);
    }

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

    printf("=== wolfPKCS11 AEAD NULL-AAD mismatch test ===\n");
    run_test();
    return pkcs11_test_summary();
}
