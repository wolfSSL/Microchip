/* common.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFSSH_COMMON_H
#define WOLFSSH_COMMON_H
int ClientLoadCA(WOLFSSH_CTX* ctx, const char* caCert);
int ClientUsePubKey(const char* pubKeyName, int userEcc, void* heap);
int ClientSetPrivateKey(const char* privKeyName, int userEcc,
        void* heap, const char* tpmKeyAuth);
int ClientUseCert(const char* certName, void* heap);
int ClientSetEcho(int type);
int ClientUserAuth(byte authType,
        WS_UserAuthData* authData, void* ctx);
int ClientPublicKeyCheck(const byte* pubKey, word32 pubKeySz, void* ctx);
void ClientIPOverride(int flag);
void ClientFreeBuffers(const char* pubKeyName, const char* privKeyName,
        void* heap);
#ifdef WOLFSSH_TPM
int ClientSetTpm(WOLFSSH* ssh);
#endif

#endif /* WOLFSSH_COMMON_H */

