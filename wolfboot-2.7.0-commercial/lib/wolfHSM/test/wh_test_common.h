/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef WH_TEST_COMMON_H_
#define WH_TEST_COMMON_H_

#include "wolfhsm/wh_settings.h"

#include <stdio.h>
#if !defined(WOLFHSM_CFG_TEST_ASSERT_FUNC)
#include <assert.h>
#endif

#include <wolfhsm/wh_nvm.h>
#include <wolfhsm/wh_flash_ramsim.h>
#include <wolfhsm/wh_nvm_flash.h>
#include <wolfhsm/wh_nvm_flash_log.h>

#define WH_TEST_FAIL (-1)
#define WH_TEST_SUCCESS (0)
#define WH_TEST_DEFAULT_CLIENT_ID (1)

/* Test-specific print macro that always prints (replacement for printf in tests)
 * This internally uses WOLFHSM_CFG_PRINTF for consistency */
#define WH_TEST_PRINT WOLFHSM_CFG_PRINTF

/* Test-specific debug print with function and line info
 * This internally uses WOLFHSM_CFG_PRINTF for consistency */
#ifdef WOLFHSM_CFG_TEST_VERBOSE
#if !defined(__CCRH__)
#define WH_TEST_DEBUG_PRINT(fmt, ...) \
    WOLFHSM_CFG_PRINTF("[%s:%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
#define WH_TEST_DEBUG_PRINT(...) WH_TEST_DEBUG_PRINT2(__VA_ARGS__, "")
#define WH_TEST_DEBUG_PRINT2(fmt, ...) \
    WOLFHSM_CFG_PRINTF("[%s:%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#endif
#else
#define WH_TEST_DEBUG_PRINT(...) \
    do {                    \
    } while (0)
#endif

/* Helper macro to print a message, prefixed by ERROR, along with caller source
 * file info */
#if !defined(__CCRH__)
#define WH_ERROR_PRINT(fmt, ...) \
    WOLFHSM_CFG_PRINTF("ERROR [%s:%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#else
#define WH_ERROR_PRINT(...) WH_ERROR_PRINT2(__VA_ARGS__, "")
#define WH_ERROR_PRINT2(fmt, ...) \
    WOLFHSM_CFG_PRINTF("ERROR [%s:%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#endif
/*
 * Helper macro for test error propagation
 * Evaluates the "call" argument, and if not equal to zero, displays the
 * stringified call argument along with caller source file info and
 * causes the calling function to return the value of "call"
 */
#define WH_TEST_RETURN_ON_FAIL(call)                 \
    do {                                             \
        int ret = (call);                            \
        if (ret != 0) {                              \
            WH_ERROR_PRINT(#call ": ret=%d\n", ret); \
            return ret;                              \
        }                                            \
    } while (0)


/*
 * Helper macro for test error propagation
 * Mimics "assert" semantics by evaluating the "statement" argument, and if not
 * true, displays the stringified argument along with caller source file info
 * and causes the calling function to return the value of WH_TEST_FAIL
 */
#define WH_TEST_ASSERT_RETURN(statement)                 \
    do {                                                 \
        if (!(statement)) {                              \
            WH_ERROR_PRINT("(" #statement ") failed\n"); \
            return WH_TEST_FAIL;                         \
        }                                                \
    } while (0)

#if defined(WOLFHSM_CFG_TEST_ASSERT_FUNC)
#define WH_TEST_ASSERT(condition) WOLFHSM_CFG_TEST_ASSERT_FUNC((condition))
#else
#define WH_TEST_ASSERT(condition) assert((condition))
#endif

/*
 * Helper macro for test error propagation
 * Wraps stdlib assert() with a custom error message
 */
#define WH_TEST_ASSERT_MSG(condition, message, ...)                        \
    do {                                                                   \
        if (!(condition)) {                                                \
            WOLFHSM_CFG_PRINTF("\n\n***TEST FAILURE***\nin %s:%s():%d: " message "\n", \
                   __FILE__, __func__, __LINE__, ##__VA_ARGS__);           \
            WH_TEST_ASSERT(condition);                                             \
        }                                                                  \
    } while (0)


typedef enum {
    WH_NVM_TEST_BACKEND_FLASH = 0,
#if defined(WOLFHSM_CFG_SERVER_NVM_FLASH_LOG)
    WH_NVM_TEST_BACKEND_FLASH_LOG,
#endif
    WH_NVM_TEST_BACKEND_COUNT
} whTestNvmBackendType;

/* union helper struct to be able to test more than one NVM implementation */
typedef struct {
    union {
        struct {
            whNvmFlashContext nvmFlashCtx;
            whNvmFlashConfig  nvmFlashCfg;
        };
#if defined(WOLFHSM_CFG_SERVER_NVM_FLASH_LOG)
        struct {
            whNvmFlashLogContext nvmFlashLogCtx;
            whNvmFlashLogConfig  nvmFlashLogCfg;
        };
#endif /* WOLFHSM_CFG_SERVER_NVM_FLASH_LOG */
    };
} whTestNvmBackendUnion;

int whTest_NvmCfgBackend(whTestNvmBackendType   type,
                         whTestNvmBackendUnion* nvmSetup, whNvmConfig* nvmCfg,
                         whFlashRamsimCfg* fCfg, whFlashRamsimCtx* fCtx,
                         const whFlashCb* fCb);
#endif /* WH_TEST_COMMON_H_ */
