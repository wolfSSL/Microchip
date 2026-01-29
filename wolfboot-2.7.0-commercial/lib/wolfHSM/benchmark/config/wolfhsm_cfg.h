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

#define WOLFHSM_CFG_ENABLE_CLIENT
#define WOLFHSM_CFG_ENABLE_SERVER

#define WOLFHSM_CFG_COMM_DATA_LEN (1280 * 4)

#define WOLFHSM_CFG_NVM_OBJECT_COUNT 30
#define WOLFHSM_CFG_SERVER_KEYCACHE_COUNT 9
#define WOLFHSM_CFG_SERVER_KEYCACHE_BUFSIZE 300
#define WOLFHSM_CFG_SERVER_KEYCACHE_BIG_COUNT 2
#define WOLFHSM_CFG_SERVER_KEYCACHE_BIG_BUFSIZE WOLFHSM_CFG_COMM_DATA_LEN
#define WOLFHSM_CFG_DMAADDR_COUNT 8
#define WOLFHSM_CFG_SERVER_CUSTOMCB_COUNT 6

#define WOLFHSM_CFG_CERTIFICATE_MANAGER
#define WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT

/* Benchmark configs */
#define WOLFHSM_CFG_BENCH_ENABLE
#define WOLFHSM_CFG_BENCH_MAIN
#endif /* WOLFHSM_CFG_H_ */
