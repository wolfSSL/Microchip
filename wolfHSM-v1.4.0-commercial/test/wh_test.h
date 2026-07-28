/*
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfHSM.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef WH_TEST_H_
#define WH_TEST_H_

#include "wolfhsm/wh_client.h"

/*
 * WOLFHSM_CFG_TEST_POSIX : Run tests using POSIX transport
 *
 * WOLFHSM_CFG_TEST_CLIENT_ONLY : Run client-only tests connecting to a running
 *                                server. The default is using a TCP transport
 *                                connection. When another specific transports
 *                                are enabled then they will be used instead i.e
 *                                WOLFHSM_CFG_TLS will use TLS transport.
 */
int whTest_Unit(void);
int whTest_ClientConfig(whClientConfig* clientCfg);

#endif /* WH_TEST_H_ */
