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
 * test/wh_test_timeout.h
 *
 */

#ifndef TEST_WH_TEST_TIMEOUT_H_
#define TEST_WH_TEST_TIMEOUT_H_

#include "wolfhsm/wh_client.h"

/**
 * Runs timeout module tests against the given client configuration.
 *
 * @param[in] config Client configuration with timeout support enabled.
 * @return 0 on success and a non-zero error code on failure.
 */
int whTest_TimeoutClientConfig(whClientConfig* config);

/**
 * Runs timeout tests using a default POSIX configuration.
 *
 * @return 0 on success and a non-zero error code on failure.
 */
int whTest_TimeoutPosix(void);

#endif /* TEST_WH_TEST_TIMEOUT_H_ */
