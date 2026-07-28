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
 * wolfhsm_cfg.h
 *
 * wolfHSM compile-time options.  Override here for your application
 */

#ifndef WOLFHSM_CFG_H_
#define WOLFHSM_CFG_H_

#include "port/posix/posix_time.h"
#define WOLFHSM_CFG_PORT_GETTIME posixGetTime


/** wolfHSM settings.  Simple overrides to show they work */
/* #define WOLFHSM_CFG_NO_CRYPTO */
/* #define WOLFHSM_CFG_SHE_EXTENSION */

#define WOLFHSM_CFG_COMM_DATA_LEN (1280 * 4)

/* Enable global keys feature for testing */
#define WOLFHSM_CFG_GLOBAL_KEYS

/* Enable logging feature for testing */
#define WOLFHSM_CFG_LOGGING

#define WOLFHSM_CFG_NVM_OBJECT_COUNT 30
#define WOLFHSM_CFG_SERVER_KEYCACHE_COUNT 9
#define WOLFHSM_CFG_SERVER_KEYCACHE_BUFSIZE 300
#define WOLFHSM_CFG_SERVER_KEYCACHE_BIG_COUNT 3
#define WOLFHSM_CFG_SERVER_KEYCACHE_BIG_BUFSIZE WOLFHSM_CFG_COMM_DATA_LEN
#define WOLFHSM_CFG_DMAADDR_COUNT 8
#define WOLFHSM_CFG_SERVER_CUSTOMCB_COUNT 6

#define WOLFHSM_CFG_CERTIFICATE_MANAGER
#define WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT

/* Enable Image Manager feature */
#define WOLFHSM_CFG_SERVER_IMG_MGR

#ifndef WOLFHSM_CFG_NO_CRYPTO
#define WOLFHSM_CFG_KEYWRAP
#endif

/* Test log-based NVM flash backend */
#define WOLFHSM_CFG_SERVER_NVM_FLASH_LOG

/* Allow persistent NVM artifacts in tests */
#define WOLFHSM_CFG_TEST_ALLOW_PERSISTENT_NVM_ARTIFACTS

#endif /* WOLFHSM_CFG_H_ */
