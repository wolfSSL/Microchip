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
 * wolfhsm/wh_server_counter.h
 *
 */

#ifndef WOLFHSM_WH_SERVER_COUNTER_H_
#define WOLFHSM_WH_SERVER_COUNTER_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

#include "wolfhsm/wh_server.h"

int wh_Server_HandleCounter(whServerContext* server, uint16_t magic,
                            uint16_t action, uint16_t req_size,
                            const void* req_packet, uint16_t* out_resp_size,
                            void* resp_packet);

#endif /* !WOLFHSM_WH_SERVER_COUNTER_H_ */
