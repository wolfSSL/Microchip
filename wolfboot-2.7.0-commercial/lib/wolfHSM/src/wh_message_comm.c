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
 * src/wh_message_comm.c
 */

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "wolfhsm/wh_comm.h"
#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_message.h"

#include "wolfhsm/wh_message_comm.h"

int wh_MessageComm_TranslateInitRequest(uint16_t magic,
        const whMessageCommInitRequest* src,
        whMessageCommInitRequest* dest)
{
    if (    (src == NULL) ||
            (dest == NULL)  ) {
        return WH_ERROR_BADARGS;
    }
    dest->client_id = wh_Translate32(magic, src->client_id);
    return 0;
}

int wh_MessageComm_TranslateInitResponse(uint16_t magic,
        const whMessageCommInitResponse* src,
        whMessageCommInitResponse* dest)
{
    if (    (src == NULL) ||
            (dest == NULL)  ) {
        return WH_ERROR_BADARGS;
    }
    dest->client_id = wh_Translate32(magic, src->client_id);
    dest->server_id = wh_Translate32(magic, src->server_id);
    return 0;
}

int wh_MessageComm_TranslateInfoResponse(uint16_t magic,
        const whMessageCommInfoResponse* src,
        whMessageCommInfoResponse* dest)
{
    if (    (src == NULL) ||
            (dest == NULL)  ) {
        return WH_ERROR_BADARGS;
    }
    memcpy(dest->version, src->version, sizeof(dest->version));
    memcpy(dest->build, src->build, sizeof(dest->build));
    dest->cfg_comm_data_len = wh_Translate32(magic, src->cfg_comm_data_len);
    dest->cfg_nvm_object_count = wh_Translate32(magic, src->cfg_nvm_object_count);
    dest->cfg_server_keycache_count = wh_Translate32(magic, src->cfg_server_keycache_count);
    dest->cfg_server_keycache_bufsize = wh_Translate32(magic, src->cfg_server_keycache_bufsize);
    dest->cfg_server_keycache_bigcount = wh_Translate32(magic, src->cfg_server_keycache_bigcount);
    dest->cfg_server_keycache_bigbufsize = wh_Translate32(magic, src->cfg_server_keycache_bigbufsize);
    dest->cfg_server_customcb_count = wh_Translate32(magic, src->cfg_server_customcb_count);
    dest->cfg_server_dmaaddr_count = wh_Translate32(magic, src->cfg_server_dmaaddr_count);
    dest->debug_state = wh_Translate32(magic, src->debug_state);
    dest->boot_state = wh_Translate32(magic, src->boot_state);
    dest->lifecycle_state = wh_Translate32(magic, src->lifecycle_state);
    dest->nvm_state = wh_Translate32(magic, src->nvm_state);
    return 0;
}


