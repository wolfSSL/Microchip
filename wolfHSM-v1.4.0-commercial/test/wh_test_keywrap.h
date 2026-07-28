/*
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfHSM.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef WH_TEST_KEYWRAP_H_
#define WH_TEST_KEYWRAP_H_

#include "wolfhsm/wh_server.h"
#include "wolfhsm/wh_client.h"

int whTest_Client_KeyWrap(whClientContext* ctx);
int whTest_KeyWrapClientConfig(whClientConfig* cf);

#endif /* WH_TEST_COMM_H_ */
