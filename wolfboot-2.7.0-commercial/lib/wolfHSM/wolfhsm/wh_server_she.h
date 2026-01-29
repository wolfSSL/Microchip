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
 * wolfhsm/wh_server_she.h
 *
 */

#ifndef WOLFHSM_WH_SERVER_SHE_H
#define WOLFHSM_WH_SERVER_SHE_H

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

#include "wolfhsm/wh_server.h"

#ifndef WOLFHSM_CFG_NO_CRYPTO
#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/wolfcrypt/types.h"
#include "wolfssl/wolfcrypt/aes.h"
#include "wolfssl/wolfcrypt/cmac.h"
#endif /* !WOLFHSM_CFG_NO_CRYPTO */

#if defined(WOLFHSM_CFG_SHE_EXTENSION)

typedef struct {
    uint8_t  sbState;
    uint8_t  cmacKeyFound;
    uint8_t  ramKeyPlain;
    uint8_t  uidSet;
    uint32_t blSize;
    uint32_t blSizeReceived;
    uint32_t rndInited;

#ifndef WOLFHSM_CFG_NO_CRYPTO
#ifndef NO_AES
    Aes sheAes[1];
#endif /* !NO_AES*/
#ifdef WOLFSSL_CMAC
    Cmac sheCmac[1];
#endif /* WOLFSSL_CMAC */
#endif /* !WOLFHSM_CFG_NO_CRYPTO*/

    uint8_t  prngState[WH_SHE_KEY_SZ];
    uint8_t  prngKey[WH_SHE_KEY_SZ];
    uint8_t  uid[WH_SHE_UID_SZ];
} whServerSheContext;

int wh_Server_HandleSheRequest(whServerContext* server, uint16_t magic,
                               uint16_t action, uint16_t req_size,
                               const void* req_packet, uint16_t* out_resp_size,
                               void* resp_packet);
#endif /* WOLFHSM_CFG_SHE_EXTENSION */

#endif /* !WOLFHSM_WH_SERVER_SHE_H */
