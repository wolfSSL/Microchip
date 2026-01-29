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
 * test/wh_test_nvm_flash.h
 *
 */
#ifndef TEST_WH_TEST_NVM_FLASH_H_
#define TEST_WH_TEST_NVM_FLASH_H_

#include "wolfhsm/wh_nvm_flash.h"

/*
 * Runs all the NVM flash tests using a RAM-based flash memory simulator, and
 * optionally using a POSIX file simulator if WOLFHSM_CFG_TEST_POSIX is defined.
 * Returns 0 on success, and a non-zero error code on failure
 */
int whTest_NvmFlash(void);

/*
 * Runs low-level flash tests on a custom NVM flash configuration. Useful to
 * test your FLASH HAL implementation. This will erase the first partition.
 * Returns 0 on success, and a non-zero error code on failure
 */
int whTest_FlashCfg(const whFlashCb* fcb, void* fctx, const void* cfg);

/*
 * Runs NVM flash tests on a custom NVM flash configuration. Useful to test your
 * NVM HAL implementation
 * Returns 0 on success, and a non-zero error code on failure
 */
int whTest_NvmFlashCfg(whNvmFlashConfig* cfg);

/*
 * Tests the NVM Flash recovery mechanism by simulating failures during state
 * programming operations. Tests the system's ability to recover from
 * partial writes to nfState fields.
 * Returns 0 on success, and a non-zero error code on failure
 */
int whTest_NvmFlash_Recovery(void);

#endif /* TEST_WH_TEST_NVM_FLASH_H_ */
