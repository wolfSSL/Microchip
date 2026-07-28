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
 * test/wh_test_auth.h
 */

#ifndef WOLFHSM_WH_TEST_AUTH_H_
#define WOLFHSM_WH_TEST_AUTH_H_

#include "wolfhsm/wh_server.h"
#include "wolfhsm/wh_client.h"

#ifdef WOLFHSM_CFG_ENABLE_AUTHENTICATION
#include "wolfhsm/wh_auth.h"
#include "wh_test_common.h"


/* Self-contained test that creates client and server with auth */
int whTest_AuthMEM(void);
int whTest_AuthTCP(whClientConfig* clientCfg);

/* Individual test functions that require a connected client */
int whTest_AuthLogin(whClientContext* client);
int whTest_AuthLogout(whClientContext* client);
int whTest_AuthAddUser(whClientContext* client);
int whTest_AuthMaxUsers(whClientContext* client);
int whTest_AuthDeleteUser(whClientContext* client);
int whTest_AuthSetPermissions(whClientContext* client);
int whTest_AuthSetCredentials(whClientContext* client);
int whTest_AuthRequestAuthorization(whClientContext* client);
int whTest_AuthKeyAuthorization(whClientContext* client);

#endif /* WOLFHSM_CFG_ENABLE_AUTHENTICATION */
#endif /* WOLFHSM_WH_TEST_AUTH_H_ */