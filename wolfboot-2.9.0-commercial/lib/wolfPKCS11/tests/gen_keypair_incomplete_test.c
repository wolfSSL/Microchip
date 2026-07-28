/* gen_keypair_incomplete_test.c
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

#define TEST_DIR "./store/gen_keypair_incomplete_test"

/* Generate a key pair with the given public template. CKA_PRIVATE=FALSE on
 * the private template keeps the keys public so no C_Login is needed. The
 * mechanism is skipped if it is not built in. */
static void check_incomplete(CK_SESSION_HANDLE session, CK_MECHANISM_TYPE mech,
                             CK_ATTRIBUTE* pubTmpl, CK_ULONG pubCnt,
                             const char* op)
{
    CK_RV rv;
    CK_MECHANISM mechanism;
    CK_BBOOL ckFalse = CK_FALSE;
    CK_ATTRIBUTE privTmpl[] = {
        { CKA_PRIVATE, &ckFalse, sizeof(ckFalse) },
    };
    CK_OBJECT_HANDLE pub = CK_INVALID_HANDLE;
    CK_OBJECT_HANDLE priv = CK_INVALID_HANDLE;

    XMEMSET(&mechanism, 0, sizeof(mechanism));
    mechanism.mechanism = mech;

    rv = funcList->C_GenerateKeyPair(session, &mechanism, pubTmpl, pubCnt,
                                     privTmpl,
                                     sizeof(privTmpl) / sizeof(*privTmpl),
                                     &pub, &priv);
    if (rv == CKR_MECHANISM_INVALID) {
        printf("SKIP: %s (mechanism not supported)\n", op);
        test_passed++;
        return;
    }
    CHECK_RV(rv, op, CKR_TEMPLATE_INCOMPLETE);
    if (rv == CKR_OK) {
        funcList->C_DestroyObject(session, pub);
        funcList->C_DestroyObject(session, priv);
    }
}

static int run_test(void)
{
    CK_RV rv;
    CK_SESSION_HANDLE session = 0;
    CK_BBOOL ckTrue = CK_TRUE;
    CK_ATTRIBUTE rsaPub[] = {        /* missing CKA_MODULUS_BITS */
        { CKA_ENCRYPT, &ckTrue, sizeof(ckTrue) },
        { CKA_VERIFY,  &ckTrue, sizeof(ckTrue) },
    };
    CK_ATTRIBUTE ecPub[] = {         /* missing CKA_EC_PARAMS */
        { CKA_VERIFY,  &ckTrue, sizeof(ckTrue) },
    };
    CK_ATTRIBUTE dhPub[] = {         /* missing CKA_PRIME and CKA_BASE */
        { CKA_DERIVE,  &ckTrue, sizeof(ckTrue) },
    };

    rv = pkcs11_load();
    CHECK_RV(rv, "load library", CKR_OK);
    if (rv != CKR_OK)
        return -1;

    rv = pkcs11_open_session(&session);
    CHECK_RV(rv, "open session", CKR_OK);
    if (rv != CKR_OK)
        goto out;

    check_incomplete(session, CKM_RSA_PKCS_KEY_PAIR_GEN, rsaPub,
                     sizeof(rsaPub) / sizeof(*rsaPub),
                     "RSA keygen without CKA_MODULUS_BITS");
    check_incomplete(session, CKM_EC_KEY_PAIR_GEN, ecPub,
                     sizeof(ecPub) / sizeof(*ecPub),
                     "EC keygen without CKA_EC_PARAMS");
    check_incomplete(session, CKM_DH_PKCS_KEY_PAIR_GEN, dhPub,
                     sizeof(dhPub) / sizeof(*dhPub),
                     "DH keygen without CKA_PRIME/CKA_BASE");

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

    printf("=== wolfPKCS11 C_GenerateKeyPair incomplete-template test ===\n");
    run_test();
    return pkcs11_test_summary();
}
