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
 * wolfhsm_cfg.h
 *
 * wolfHSM compile-time options for the test-refactor suite. Sibling of
 * test/config/wolfhsm_cfg.h; the two are intentionally allowed to diverge
 * as the refactor matures.
 */

#ifndef WOLFHSM_CFG_H_
#define WOLFHSM_CFG_H_

#include "port/posix/posix_time.h"
#define WOLFHSM_CFG_PORT_GETTIME posixGetTime

#define WOLFHSM_CFG_COMM_DATA_LEN (1024 * 8)

#define WOLFHSM_CFG_GLOBAL_KEYS

#define WOLFHSM_CFG_LOGGING

#define WOLFHSM_CFG_NVM_OBJECT_COUNT 30
#define WOLFHSM_CFG_SERVER_KEYCACHE_COUNT 9
#define WOLFHSM_CFG_SERVER_KEYCACHE_BUFSIZE 300
#define WOLFHSM_CFG_DMAADDR_COUNT 8
#define WOLFHSM_CFG_SERVER_CUSTOMCB_COUNT 6

#define WOLFHSM_CFG_CERTIFICATE_MANAGER
#define WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT

#define WOLFHSM_CFG_SERVER_IMG_MGR

#ifndef WOLFHSM_CFG_NO_CRYPTO
#define WOLFHSM_CFG_KEYWRAP
#endif

#define WOLFHSM_CFG_SERVER_NVM_FLASH_LOG

/* WOLFHSM_CFG_TEST_ALLOW_PERSISTENT_NVM_ARTIFACTS is intentionally NOT
 * defined here. Not implemented yet. */

#define WOLFHSM_CFG_ENABLE_TIMEOUT

#endif /* WOLFHSM_CFG_H_ */
