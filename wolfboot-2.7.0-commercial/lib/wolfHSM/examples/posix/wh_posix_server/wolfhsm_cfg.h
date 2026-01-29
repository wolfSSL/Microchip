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
 * wolfhsm_cfg.h
 *
 * wolfHSM compile-time options.  Override here for your application
 */

#ifndef WOLFHSM_CFG_H_
#define WOLFHSM_CFG_H_

/** wolfHSM settings.  Simple overrides to show they work */
#define WOLFHSM_CFG_ENABLE_SERVER

#define WOLFHSM_CFG_HEXDUMP

/* Large enough for ML-DSA level 5 key */
#define WOLFHSM_CFG_COMM_DATA_LEN 5000

#define WOLFHSM_CFG_NVM_OBJECT_COUNT 30
#define WOLFHSM_CFG_SERVER_KEYCACHE_COUNT 9
#define WOLFHSM_CFG_SERVER_KEYCACHE_SIZE 1024
#define WOLFHSM_CFG_SERVER_KEYCACHE_BIG_BUFSIZE 4096

#define WOLFHSM_CFG_SERVER_DMAADDR_COUNT 8
#define WOLFHSM_CFG_SERVER_CUSTOMCB_COUNT 6

#define WOLFHSM_CFG_CERTIFICATE_MANAGER
#define WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT

#define XMEMFENCE() __atomic_thread_fence(__ATOMIC_SEQ_CST)

#define WOLFHSM_CFG_KEYWRAP_MAX_KEY_SIZE 5000

#ifndef WOLFHSM_CFG_NO_CRYPTO
#define WOLFHSM_CFG_KEYWRAP
#define WOLFHSM_CFG_GLOBAL_KEYS
#endif

#endif /* WOLFHSM_CFG_H_ */
