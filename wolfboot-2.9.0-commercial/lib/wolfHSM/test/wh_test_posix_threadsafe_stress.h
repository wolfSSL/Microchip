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
 * test/wh_test_posix_threadsafe_stress.h
 *
 * POSIX multithreaded stress test for thread safety validation.
 * This test uses POSIX threading primitives (pthreads).
 */

#ifndef TEST_WH_TEST_POSIX_THREADSAFE_STRESS_H_
#define TEST_WH_TEST_POSIX_THREADSAFE_STRESS_H_

/*
 * Runs multithreaded stress tests for thread safety validation.
 * Tests concurrent access to shared NVM and global key cache from
 * multiple client threads via separate server contexts.
 *
 * Requires: WOLFHSM_CFG_THREADSAFE, WOLFHSM_CFG_TEST_POSIX,
 *           WOLFHSM_CFG_GLOBAL_KEYS
 *
 * Returns 0 on success, non-zero on failure.
 */
int whTest_ThreadSafeStress(void);

#endif /* TEST_WH_TEST_POSIX_THREADSAFE_STRESS_H_ */
