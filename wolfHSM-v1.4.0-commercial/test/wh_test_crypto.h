/*
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfHSM.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef WH_TEST_CRYPTO_H_
#define WH_TEST_CRYPTO_H_

#include "wolfhsm/wh_server.h"
#include "wolfhsm/wh_client.h"

int whTest_Crypto(void);
int whTest_CryptoClientConfig(whClientConfig* cf);
int whTest_CryptoServerConfig(whServerConfig* cfg);



#endif /* WH_TEST_COMM_H_ */
