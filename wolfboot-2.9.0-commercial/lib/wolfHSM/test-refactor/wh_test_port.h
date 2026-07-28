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
 * test-refactor/wh_test_port.h
 *
 * Port-implemented hooks. Every port must implement these.
 */

#ifndef WH_TEST_PORT_H_
#define WH_TEST_PORT_H_

#include "wolfhsm/wh_client.h"
#include "wolfhsm/wh_server.h"

/*
 * Port-implemented reset hooks. whTestGroup_Server and
 * whTestGroup_Client invoke these before each test in the group
 * so the port can scrub any persistent state (NVM objects, key
 * cache, connection state, ...) the previous test left behind.
 * A non-zero return aborts the group with that rc. Implementations
 * may be empty stubs that return 0 if the port has nothing to reset.
 */
int whTestPort_ResetServer(whServerContext* server);
int whTestPort_ResetClient(whClientContext* client);

#endif /* WH_TEST_PORT_H_ */
