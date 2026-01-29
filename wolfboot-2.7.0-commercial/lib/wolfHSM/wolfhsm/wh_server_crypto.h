/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * wolfhsm/wh_server_crypto.h
 *
 */

#ifndef WOLFHSM_WH_SERVER_CRYPTO_H_
#define WOLFHSM_WH_SERVER_CRYPTO_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#ifndef WOLFHSM_CFG_NO_CRYPTO

#include <stdint.h>

#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/wolfcrypt/types.h"
#include "wolfssl/wolfcrypt/rsa.h"
#include "wolfssl/wolfcrypt/curve25519.h"
#include "wolfssl/wolfcrypt/ecc.h"
#include "wolfssl/wolfcrypt/aes.h"
#include "wolfssl/wolfcrypt/sha256.h"
#include "wolfssl/wolfcrypt/cmac.h"

#include "wolfhsm/wh_server.h"

int wh_Server_HandleCryptoRequest(whServerContext* ctx, uint16_t magic,
                                  uint16_t action, uint16_t seq,
                                  uint16_t req_size, const void* req_packet,
                                  uint16_t* out_resp_size, void* resp_packet);

int wh_Server_HandleCryptoDmaRequest(whServerContext* ctx, uint16_t magic,
                                     uint16_t action, uint16_t seq,
                                     uint16_t req_size, const void* req_packet,
                                     uint16_t* out_resp_size,
                                     void*     resp_packet);

#ifndef NO_RSA

/* Store a RsaKey into a server key cache with optional metadata */
int wh_Server_CacheImportRsaKey(whServerContext* ctx, RsaKey* key,
        whKeyId keyId, whNvmFlags flags, uint32_t label_len, uint8_t* label);

/* Restore a RsaKey from a server key cache */
int wh_Server_CacheExportRsaKey(whServerContext* ctx, whKeyId keyId,
        RsaKey* key);
#endif /* !NO_RSA */

#ifdef HAVE_ECC
int wh_Server_EccKeyCacheImport(whServerContext* ctx, ecc_key* key,
        whKeyId keyId, whNvmFlags flags, uint16_t label_len, uint8_t* label);

int wh_Server_EccKeyCacheExport(whServerContext* ctx, whKeyId keyId,
        ecc_key* key);
#endif

#ifdef HAVE_CURVE25519

/* Store a curve25519_key into a server key cache with optional metadata */
int wh_Server_CacheImportCurve25519Key(whServerContext* server,
        curve25519_key* key,
        whKeyId keyId, whNvmFlags flags, uint16_t label_len, uint8_t* label);
/* Restore a curve25519_key from a server key cache */
int wh_Server_CacheExportCurve25519Key(whServerContext* server, whKeyId keyId,
        curve25519_key* key);
#endif /* HAVE_CURVE25519 */

#ifdef HAVE_DILITHIUM
/* Store a MlDsaKey into a server key cache with optional metadata */
int wh_Server_MlDsaKeyCacheImport(whServerContext* ctx, MlDsaKey* key,
                                  whKeyId keyId, whNvmFlags flags,
                                  uint16_t label_len, uint8_t* label);
/* Restore a MlDsaKey from a server key cache */
int wh_Server_MlDsaKeyCacheExport(whServerContext* ctx, whKeyId keyId,
                                  MlDsaKey* key);
#endif /* HAVE_DILITHIUM */

#ifdef HAVE_HKDF
/* Store HKDF output into a server key cache with optional metadata */
int wh_Server_HkdfKeyCacheImport(whServerContext* ctx, const uint8_t* keyData,
                                 uint32_t keySize, whKeyId keyId,
                                 whNvmFlags flags, uint16_t label_len,
                                 uint8_t* label);
#endif /* HAVE_HKDF */

#ifdef HAVE_CMAC_KDF
/* Store CMAC KDF output into a server key cache with optional metadata */
int wh_Server_CmacKdfKeyCacheImport(whServerContext* ctx,
                                    const uint8_t* keyData, uint32_t keySize,
                                    whKeyId keyId, whNvmFlags flags,
                                    uint16_t label_len, uint8_t* label);
#endif /* HAVE_CMAC_KDF */

#endif /* !WOLFHSM_CFG_NO_CRYPTO */

#endif /* !WOLFHSM_WH_SERVER_CRYPTO_H_ */
