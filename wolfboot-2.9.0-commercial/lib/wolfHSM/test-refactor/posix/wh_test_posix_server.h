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
 * test-refactor/wh_test_posix_server.h
 *
 * POSIX server-side init. Allocates the NVM, crypto,
 * transport, and server backing state the test main needs,
 * and wires them into a whServerContext. A real target would
 * do this in its normal boot flow; this file stands in for
 * that flow in the POSIX test harness.
 *
 * Also exposes the shared mem-transport config so the POSIX
 * client side can wire its end onto the same
 * request/response buffers.
 */

#ifndef WH_TEST_POSIX_SERVER_H_
#define WH_TEST_POSIX_SERVER_H_

#include "wolfhsm/wh_server.h"
#include "wolfhsm/wh_transport_mem.h"

/*
 * Initialize the server context plus all backing state
 * (flash, NVM, crypto, transport). Caller owns `server`.
 */
int whTestPosix_Server_Init(whServerContext* server);

/*
 * Tear down the server context plus backing state. Matches
 * Server_Init one-for-one.
 */
int whTestPosix_Server_Cleanup(whServerContext* server);

/*
 * Returns the shared mem-transport config (buffers + sizes).
 * Used by the POSIX client side to wire its end onto the
 * same buffers the server publishes through.
 */
whTransportMemConfig* whTestPosix_Server_GetTransportConfig(void);

#endif /* WH_TEST_POSIX_SERVER_H_ */
