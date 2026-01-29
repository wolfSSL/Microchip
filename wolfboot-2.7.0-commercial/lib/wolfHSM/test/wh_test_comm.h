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
 * test/wh_test_comm.h
 *
 */

#ifndef TEST_WH_TEST_COMM_H_
#define TEST_WH_TEST_COMM_H_

/*
 * Runs the comms tests using a memory transport backend.
 * Returns 0 on success and a non-zero error code on failure
 */
int whTest_CommMem(void);

/* Runs all the comms tests using a memory transport as the backend, and
 * optionally using the POSIX TCP backend if WOLFHSM_CFG_TEST_POSIX is defined.
 *
 * Multithreaded tests are also run if WOLFHSM_CFG_TEST_POSIX is defined.
 *
 * Returns 0 on success and a non-zero error code on failure
 */
int whTest_Comm(void);

#endif /* TEST_WH_TEST_COMM_H_ */
