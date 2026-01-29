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
 * wolfhsm/wh_message_comm.h
 *
 * Comm component message action enumerations and definitions.
 *
 */

#ifndef WOLFHSM_WH_MESSAGE_COMM_H_
#define WOLFHSM_WH_MESSAGE_COMM_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

#include "wolfhsm/wh_comm.h"

/* Comm component message kinds */
enum WH_MESSAGE_COMM_ACTION_ENUM {
    WH_MESSAGE_COMM_ACTION_NONE      = 0x00,
    WH_MESSAGE_COMM_ACTION_INIT      = 0x01,
    WH_MESSAGE_COMM_ACTION_KEEPALIVE = 0x02,
    WH_MESSAGE_COMM_ACTION_CLOSE     = 0x03,
    WH_MESSAGE_COMM_ACTION_INFO      = 0x04,
    WH_MESSAGE_COMM_ACTION_ECHO      = 0x05,
};

/* Info request/response data sizes*/
enum WH_INFO_ENUM {
    WH_INFO_VERSION_LEN = 9,
    WH_INFO_BUILD_LEN   = 9,
};


/* Generic error response message. */
typedef struct {
    int return_code;
} whMessageComm_ErrorResponse;

int wh_MessageComm_GetErrorResponse(uint16_t magic,
        const void* data,
        int *out_return_code);

typedef struct {
    uint32_t client_id;
} whMessageCommInitRequest;

int wh_MessageComm_TranslateInitRequest(uint16_t magic,
        const whMessageCommInitRequest* src,
        whMessageCommInitRequest* dest);


typedef struct {
    uint32_t client_id;
    uint32_t server_id;
} whMessageCommInitResponse;

int wh_MessageComm_TranslateInitResponse(uint16_t magic,
        const whMessageCommInitResponse* src,
        whMessageCommInitResponse* dest);


typedef struct {
    uint32_t cfg_comm_data_len;
    uint32_t cfg_nvm_object_count;
    uint32_t cfg_server_keycache_count;
    uint32_t cfg_server_keycache_bufsize;
    uint32_t cfg_server_keycache_bigcount;
    uint32_t cfg_server_keycache_bigbufsize;
    uint32_t cfg_server_customcb_count;
    uint32_t cfg_server_dmaaddr_count;
    uint32_t debug_state;
    uint32_t boot_state;
    uint32_t lifecycle_state;
    uint32_t nvm_state;
    uint8_t version[WH_INFO_VERSION_LEN];
    uint8_t build[WH_INFO_BUILD_LEN];
    uint8_t WH_PAD[6];
} whMessageCommInfoResponse;

int wh_MessageComm_TranslateInfoResponse(uint16_t magic,
        const whMessageCommInfoResponse* src,
        whMessageCommInfoResponse* dest);


#endif /* !WOLFHSM_WH_MESSAGE_COMM_H_ */
