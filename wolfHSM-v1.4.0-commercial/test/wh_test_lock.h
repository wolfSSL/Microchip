/*
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfHSM.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * test/wh_test_lock.h
 *
 * Thread-safety lock tests
 */
#ifndef TEST_WH_TEST_LOCK_H_
#define TEST_WH_TEST_LOCK_H_

#include "wolfhsm/wh_lock.h" /* For whLockConfig type */

/*
 * Runs all lock tests using the supplied lock configuration.
 *   - Tests lock lifecycle (init/cleanup) if lockConfig is not NULL
 *   - Tests NULL config results in no-op locking
 *   - Tests NVM with lock config
 *
 * @param lockConfig Pointer to lock configuration. If NULL, the lock lifecycle
 *                   test will be skipped but other tests will still run.
 * Returns 0 on success, and a non-zero error code on failure
 */
int whTest_LockConfig(whLockConfig* lockConfig);

#if defined(WOLFHSM_CFG_TEST_POSIX)

/*
 * Runs all lock tests using the POSIX lock backend ontop of POSIX sim
 *   - Tests lock lifecycle (init/cleanup)
 *   - Tests NULL config results in no-op locking
 *   - Tests NVM with lock config
 * Returns 0 on success, and a non-zero error code on failure
 */
int whTest_LockPosix(void);
#endif /* WOLFHSM_CFG_TEST_POSIX */

#endif /* TEST_WH_TEST_LOCK_H_ */
