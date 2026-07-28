/*
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * wolfhsm/wh_server_auth.h
 *
 * Server-side Auth Manager API
 */

#ifndef WOLFHSM_WH_SERVER_AUTH_H_
#define WOLFHSM_WH_SERVER_AUTH_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

#include "wolfhsm/wh_server.h"

#ifdef WOLFHSM_CFG_ENABLE_SERVER

/**
 * @brief Handles incoming authentication and authorization requests.
 *
 * This function processes incoming auth request messages from the communication
 * server and dispatches them to the appropriate auth manager functions.
 *
 * @param[in] server Pointer to the server context.
 * @param[in] magic The magic number for the request.
 * @param[in] action The action ID of the request.
 * @param[in] seq The sequence number of the request.
 * @param[in] req_size The size of the request packet.
 * @param[in,out] req_packet Pointer to the request packet data. Credential
 *     fields may be zeroized in place after processing.
 * @param[out] out_resp_size Pointer to store the size of the response packet.
 * @param[out] resp_packet Pointer to store the response packet data.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int wh_Server_HandleAuthRequest(whServerContext* server, uint16_t magic,
                                uint16_t action, uint16_t seq,
                                uint16_t req_size, void* req_packet,
                                uint16_t* out_resp_size, void* resp_packet);

#endif /* WOLFHSM_CFG_ENABLE_SERVER */

#endif /* !WOLFHSM_WH_SERVER_AUTH_H_ */
