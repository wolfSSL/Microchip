/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef WH_TEST_MULTICLIENT_H_
#define WH_TEST_MULTICLIENT_H_

/**
 * @brief Multi-client test framework and test suite
 *
 * This test module provides a framework for testing features that require
 * multiple clients connecting to separate servers sharing a common NVM context.
 *
 * The framework provides generic setup/teardown for:
 * - Two client contexts with separate transport memory configs
 * - Two server contexts sharing a single NVM context
 * - Shared flash/NVM and crypto initialization
 * - Sequential single-threaded test execution using memory transport
 *
 * Current test suites:
 * - Global keys: Tests shared key functionality across multiple clients
 *
 * Future test suites can be added for features like:
 * - Access control policies
 * - Shared counter synchronization
 * - Cross-client key operations
 *
 * @return 0 on success, error code on failure
 */
int whTest_MultiClient(void);

#endif /* WH_TEST_MULTICLIENT_H_ */
