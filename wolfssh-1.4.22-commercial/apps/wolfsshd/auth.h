/* auth.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFAUTH_H
#define WOLFAUTH_H

#if 0
typedef struct USER_NODE USER_NODE;

USER_NODE* AddNewUser(USER_NODE* list, byte type, const byte* username,
                       word32 usernameSz, const byte* value, word32 valueSz);
#endif

void SetAuthKeysPattern(const char* pattern);
int DefaultUserAuth(byte authType, WS_UserAuthData* authData, void* ctx);
int DefaultUserAuthTypes(WOLFSSH* ssh, void* ctx);

typedef struct WOLFSSHD_AUTH WOLFSSHD_AUTH;

/*
 * Returns WSSHD_AUTH_SUCCESS if user found, WSSHD_AUTH_FAILURE if user not
 * found, and negative values if an error occurs during checking.
 */
typedef int (*CallbackCheckUser)(const char* usr);


/*
 * Returns WSSHD_AUTH_SUCCESS if user found, WSSHD_AUTH_FAILURE if user not
 * found, and negative values if an error occurs during checking.
 */
typedef int (*CallbackCheckPassword)(const char* usr, const byte* psw,
    word32 pswSz, WOLFSSHD_AUTH* authCtx);

/*
 * Returns WSSHD_AUTH_SUCCESS if public key ok, WSSHD_AUTH_FAILURE if key not
 * ok, and negative values if an error occurs during checking.
 */
typedef int (*CallbackCheckPublicKey)(const char* usr,
                                      const WS_UserAuthData_PublicKey* pubKey,
                                      const char* usrCaKeysFile, WOLFSSHD_AUTH* authCtx);

WOLFSSHD_AUTH* wolfSSHD_AuthCreateUser(void* heap, const WOLFSSHD_CONFIG* conf);
int wolfSSHD_AuthFreeUser(WOLFSSHD_AUTH* auth);
int wolfSSHD_AuthReducePermissions(WOLFSSHD_AUTH* auth);
int wolfSSHD_AuthRaisePermissions(WOLFSSHD_AUTH* auth);
int wolfSSHD_AuthReducePermissionsUser(WOLFSSHD_AUTH* auth, WUID_T uid,
    WGID_T gid);
int wolfSSHD_AuthSetGroups(const WOLFSSHD_AUTH* auth, const char* usr,
    WGID_T gid);
long wolfSSHD_AuthGetGraceTime(const WOLFSSHD_AUTH* auth);
WOLFSSHD_CONFIG* wolfSSHD_AuthGetUserConf(const WOLFSSHD_AUTH* auth,
        const char* usr, const char* host,
        const char* localAdr, word16* localPort, const char* RDomain,
        const char* adr);
#ifdef _WIN32
HANDLE wolfSSHD_GetAuthToken(const WOLFSSHD_AUTH* auth);
int wolfSSHD_GetHomeDirectory(WOLFSSHD_AUTH* auth, WOLFSSH* ssh, WCHAR* out, int outSz);
#endif
#endif /* WOLFAUTH_H */
