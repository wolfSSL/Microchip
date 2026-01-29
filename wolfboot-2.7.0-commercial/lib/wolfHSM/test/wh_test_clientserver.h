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
 * wolfhsm/test/wh_test_clientserver.h
 *
 */
#ifndef TEST_WH_TEST_CLIENTSERVER_H_
#define TEST_WH_TEST_CLIENTSERVER_H_

#include "wolfhsm/wh_server.h"
#include "wolfhsm/wh_client.h"

/*
 * Runs the client/server async tests in a single thread using a memory
 * transport backend.
 *
 * Multithreaded tests are also run if WOLFHSM_CFG_TEST_POSIX is defined.
 * Returns 0 on success and a non-zero error code on failure
 */
int whTest_ClientServer(void);
int whTest_ClientServerClientConfig(whClientConfig* clientCfg);
int whTest_ServerCfgLoop(whServerConfig* serverCfg);

#endif /* TEST_WH_TEST_CLIENTSERVER_H_ */
