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
 * src/wh_keyid.c
 *
 * KeyId helper function implementations for wolfHSM
 */

#include "wolfhsm/wh_keyid.h"

whKeyId wh_KeyId_TranslateFromClient(uint16_t type, uint16_t clientId,
                                     whKeyId reqId)
{
    uint16_t user = clientId;
    whKeyId  id   = reqId & WH_KEYID_MASK;

#ifdef WOLFHSM_CFG_GLOBAL_KEYS
    /* Convert global flag to USER=0 */
    if ((reqId & WH_KEYID_CLIENT_GLOBAL_FLAG) != 0) {
        user = WH_KEYUSER_GLOBAL;
    }
#endif

#ifdef WOLFHSM_CFG_KEYWRAP
    /* Convert wrapped flag to TYPE=WH_KETYPE_WRAPPED */
    if ((reqId & WH_KEYID_CLIENT_WRAPPED_FLAG) != 0) {
        type = WH_KEYTYPE_WRAPPED;
    }
#endif

    return WH_MAKE_KEYID(type, user, id);
}

whKeyId wh_KeyId_TranslateToClient(whKeyId serverId)
{
    whKeyId clientId = WH_KEYID_ID(serverId);

#ifdef WOLFHSM_CFG_GLOBAL_KEYS
    /* Convert USER=0 to global flag */
    if (WH_KEYID_USER(serverId) == WH_KEYUSER_GLOBAL) {
        clientId |= WH_KEYID_CLIENT_GLOBAL_FLAG;
    }
#endif

#ifdef WOLFHSM_CFG_KEYWRAP
    /* Convert TYPE=WRAPPED to wrapped flag */
    if (WH_KEYID_TYPE(serverId) == WH_KEYTYPE_WRAPPED) {
        clientId |= WH_KEYID_CLIENT_WRAPPED_FLAG;
    }
#endif

    return clientId;
}
