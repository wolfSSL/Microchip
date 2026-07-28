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
 * test/wh_test_log.h
 *
 */

#ifndef TEST_WH_TEST_LOG_H_
#define TEST_WH_TEST_LOG_H_

#include <stdint.h>

#include "wolfhsm/wh_log.h"

/*
 * Configuration structure for backend testing
 */
typedef struct {
    const char* backend_name;    /* Backend name for test output */
    whLogCb*    cb;              /* Backend callback table */
    void*       config;          /* Backend-specific config */
    size_t      config_size;     /* Size of config structure */
    void*       backend_context; /* Pre-allocated backend context */

    /* Capabilities */
    int expected_capacity;   /* Max entries (-1 = unlimited) */
    int supports_concurrent; /* supports multithreaded use */

    /* Optional hooks */
    int (*setup)(void** context);   /* Setup hook (optional) */
    int (*teardown)(void* context); /* Teardown hook (optional) */
    void* test_context;             /* Context for setup/teardown */
} whTestLogBackendTestConfig;

/*
 * Runs all generic test suites for the built-in backends.
 * Returns 0 on success, non-zero on failure.
 */
int whTest_LogBackend_RunAll(whTestLogBackendTestConfig* cfg);


/*
 * Runs all logging module tests including frontend API, macros, and
 * POSIX file backend tests (if WOLFHSM_CFG_TEST_POSIX is defined).
 *
 * Returns 0 on success and a non-zero error code on failure
 */
int whTest_Log(void);

#endif /* TEST_WH_TEST_LOG_H_ */
