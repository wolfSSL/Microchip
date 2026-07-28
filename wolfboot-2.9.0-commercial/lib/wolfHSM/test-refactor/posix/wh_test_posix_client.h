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
 * test-refactor/wh_test_posix_client.h
 *
 * POSIX client-side init. Stands in for the normal boot-time
 * transport+client init a real firmware would do. Wires the
 * client onto the mem-transport buffers exposed by the POSIX
 * server side and performs the CommInit handshake. The port's
 * main is responsible for running a server thread that pumps
 * HandleRequestMessage -- this side does not touch the server
 * context.
 */

#ifndef WH_TEST_POSIX_CLIENT_H_
#define WH_TEST_POSIX_CLIENT_H_

#include "wolfhsm/wh_client.h"

/*
 * Initialize the client context plus transport state and
 * perform the CommInit handshake. The POSIX server side must
 * have been initialized first (its transport config supplies
 * the shared request/response buffers) and a server thread
 * must be actively processing requests when this is called.
 */
int whTestPosix_Client_Init(whClientContext* client);

int whTestPosix_Client_Cleanup(whClientContext* client);

#endif /* WH_TEST_POSIX_CLIENT_H_ */
