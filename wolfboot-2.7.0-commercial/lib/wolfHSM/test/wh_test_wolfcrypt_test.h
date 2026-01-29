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
 * test/wh_test_wolfcrypt_test.h
 *
 */

#ifndef TEST_WH_TEST_WOLFCRYPT_TEST_H_
#define TEST_WH_TEST_WOLFCRYPT_TEST_H_

/*
 * Runs wolfCrypt test suite on top of wolfHSM using a memory transport backend.
 * and optionally the POSIX TCP backent if WOLFHSM_CFG_TEST_POSIX is defined
 *
 * Returns 0 on success and a non-zero error code on failure
 */
int whTest_WolfCryptTestCfg(whClientConfig* config);
int whTest_WolfCryptTest(void);

#endif /* TEST_WH_TEST_WOLFCRYPT_TEST_H_ */
