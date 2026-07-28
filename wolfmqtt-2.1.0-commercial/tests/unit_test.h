/* unit_test.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_UNIT_TEST_H
#define WOLFMQTT_UNIT_TEST_H

#include "wolfmqtt/mqtt_types.h"
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Color Output Support
 * ============================================================================ */

#ifndef UNIT_TEST_NO_COLOR
    #if defined(_WIN32) || defined(_WIN64)
        /* Windows - disable colors by default */
        #define UT_COLOR_RESET   ""
        #define UT_COLOR_RED     ""
        #define UT_COLOR_GREEN   ""
        #define UT_COLOR_YELLOW  ""
        #define UT_COLOR_CYAN    ""
    #else
        /* ANSI escape codes for Unix-like systems */
        #define UT_COLOR_RESET   "\033[0m"
        #define UT_COLOR_RED     "\033[1;31m"
        #define UT_COLOR_GREEN   "\033[1;32m"
        #define UT_COLOR_YELLOW  "\033[1;33m"
        #define UT_COLOR_CYAN    "\033[1;36m"
    #endif
#else
    #define UT_COLOR_RESET   ""
    #define UT_COLOR_RED     ""
    #define UT_COLOR_GREEN   ""
    #define UT_COLOR_YELLOW  ""
    #define UT_COLOR_CYAN    ""
#endif

/* ============================================================================
 * Test Framework State
 *
 * Global counters are defined in the main translation unit (where
 * UNIT_TEST_IMPLEMENTATION is defined) and declared as extern elsewhere.
 * ============================================================================ */

#ifdef UNIT_TEST_IMPLEMENTATION
    /* Define storage in the main file */
    int ut_global_pass_count = 0;
    int ut_global_fail_count = 0;
#else
    /* Declare as extern in other files */
    extern int ut_global_pass_count;
    extern int ut_global_fail_count;
#endif

/* Per-suite and per-test state (file-local, OK to be static)
 * These may be unused in files that only define main(), so mark them as
 * potentially unused to avoid warnings with strict compilation flags. */
#if defined(__GNUC__) || defined(__clang__)
    #define UT_MAYBE_UNUSED __attribute__((unused))
#else
    #define UT_MAYBE_UNUSED
#endif

static int ut_suite_pass_count UT_MAYBE_UNUSED;
static int ut_suite_fail_count UT_MAYBE_UNUSED;
static const char* ut_suite_name UT_MAYBE_UNUSED;
static void (*ut_suite_setup)(void) UT_MAYBE_UNUSED;
static void (*ut_suite_teardown)(void) UT_MAYBE_UNUSED;
static int ut_current_test_failed UT_MAYBE_UNUSED;

/* ============================================================================
 * Assertion Macros
 * ============================================================================ */

#define ASSERT_TRUE(cond) \
    do { \
        if (!(cond)) { \
            PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: " \
                   "ASSERT_TRUE(" #cond ") failed", __FILE__, __LINE__); \
            ut_current_test_failed = 1; \
            return; \
        } \
    } while (0)

#define ASSERT_FALSE(cond) \
    do { \
        if (cond) { \
            PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: " \
                   "ASSERT_FALSE(" #cond ") failed", __FILE__, __LINE__); \
            ut_current_test_failed = 1; \
            return; \
        } \
    } while (0)

#define ASSERT_EQ(expected, actual) \
    do { \
        long long _exp = (long long)(expected); \
        long long _act = (long long)(actual); \
        if (_exp != _act) { \
            PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: " \
                   "ASSERT_EQ(" #expected ", " #actual ") failed: " \
                   "expected %lld, got %lld", __FILE__, __LINE__, _exp, _act); \
            ut_current_test_failed = 1; \
            return; \
        } \
    } while (0)

#define ASSERT_NE(a, b) \
    do { \
        long long _a = (long long)(a); \
        long long _b = (long long)(b); \
        if (_a == _b) { \
            PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: " \
                   "ASSERT_NE(" #a ", " #b ") failed: both are %lld", \
                   __FILE__, __LINE__, _a); \
            ut_current_test_failed = 1; \
            return; \
        } \
    } while (0)

#define ASSERT_NULL(ptr) \
    do { \
        if ((ptr) != NULL) { \
            PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: " \
                   "ASSERT_NULL(" #ptr ") failed: pointer is not NULL", \
                   __FILE__, __LINE__); \
            ut_current_test_failed = 1; \
            return; \
        } \
    } while (0)

#define ASSERT_NOT_NULL(ptr) \
    do { \
        if ((ptr) == NULL) { \
            PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: " \
                   "ASSERT_NOT_NULL(" #ptr ") failed: pointer is NULL", \
                   __FILE__, __LINE__); \
            ut_current_test_failed = 1; \
            return; \
        } \
    } while (0)

#define ASSERT_STR_EQ(expected, actual) \
    do { \
        const char* _exp = (expected); \
        const char* _act = (actual); \
        if (_exp == NULL || _act == NULL || strcmp(_exp, _act) != 0) { \
            PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: " \
                   "ASSERT_STR_EQ(" #expected ", " #actual ") failed: " \
                   "expected \"%s\", got \"%s\"", __FILE__, __LINE__, \
                   _exp ? _exp : "(null)", _act ? _act : "(null)"); \
            ut_current_test_failed = 1; \
            return; \
        } \
    } while (0)

#define ASSERT_MEM_EQ(expected, actual, size) \
    do { \
        const void* _exp = (expected); \
        const void* _act = (actual); \
        size_t _size = (size); \
        if (_exp == NULL || _act == NULL || memcmp(_exp, _act, _size) != 0) { \
            PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: " \
                   "ASSERT_MEM_EQ(" #expected ", " #actual ", %zu) failed", \
                   __FILE__, __LINE__, _size); \
            ut_current_test_failed = 1; \
            return; \
        } \
    } while (0)

#define FAIL(msg) \
    do { \
        PRINTF("  " UT_COLOR_RED "FAIL" UT_COLOR_RESET ": %s:%d: %s", \
               __FILE__, __LINE__, (msg)); \
        ut_current_test_failed = 1; \
        return; \
    } while (0)

/* ============================================================================
 * Test Definition and Execution Macros
 * ============================================================================ */

/* Define a test function */
#define TEST(name) static void test_##name(void)

/* Run a single test */
#define RUN_TEST(name) \
    do { \
        ut_current_test_failed = 0; \
        if (ut_suite_setup) ut_suite_setup(); \
        test_##name(); \
        if (ut_suite_teardown) ut_suite_teardown(); \
        if (ut_current_test_failed) { \
            ut_suite_fail_count++; \
            PRINTF("  " UT_COLOR_RED "[FAIL]" UT_COLOR_RESET " %s", #name); \
        } else { \
            ut_suite_pass_count++; \
            PRINTF("  " UT_COLOR_GREEN "[PASS]" UT_COLOR_RESET " %s", #name); \
        } \
    } while (0)

/* Begin a test suite */
#define TEST_SUITE_BEGIN(name, setup_fn, teardown_fn) \
    do { \
        ut_suite_pass_count = 0; \
        ut_suite_fail_count = 0; \
        ut_suite_name = (name); \
        ut_suite_setup = (setup_fn); \
        ut_suite_teardown = (teardown_fn); \
        PRINTF("\n" UT_COLOR_CYAN "=== Test Suite: %s ===" UT_COLOR_RESET, \
               ut_suite_name); \
    } while (0)

/* End a test suite and report results */
#define TEST_SUITE_END() \
    do { \
        int total = ut_suite_pass_count + ut_suite_fail_count; \
        PRINTF(UT_COLOR_CYAN "--- Suite Results: %s ---" UT_COLOR_RESET, \
               ut_suite_name); \
        PRINTF("  Passed: " UT_COLOR_GREEN "%d" UT_COLOR_RESET \
               ", Failed: " UT_COLOR_RED "%d" UT_COLOR_RESET \
               ", Total: %d\n", \
               ut_suite_pass_count, ut_suite_fail_count, total); \
        ut_global_pass_count += ut_suite_pass_count; \
        ut_global_fail_count += ut_suite_fail_count; \
    } while (0)

/* ============================================================================
 * Global Test Runner Macros
 * ============================================================================ */

/* Initialize the global test runner */
#define TEST_RUNNER_BEGIN() \
    do { \
        ut_global_pass_count = 0; \
        ut_global_fail_count = 0; \
        PRINTF(UT_COLOR_CYAN \
               "============================================\n" \
               "         wolfMQTT Unit Test Runner\n" \
               "============================================" \
               UT_COLOR_RESET); \
    } while (0)

/* Report global results and return exit code */
#define TEST_RUNNER_END() \
    do { \
        int total = ut_global_pass_count + ut_global_fail_count; \
        PRINTF(UT_COLOR_CYAN \
               "============================================\n" \
               "              Final Results\n" \
               "============================================" \
               UT_COLOR_RESET); \
        PRINTF("  Total Passed: " UT_COLOR_GREEN "%d" UT_COLOR_RESET, \
               ut_global_pass_count); \
        PRINTF("  Total Failed: " UT_COLOR_RED "%d" UT_COLOR_RESET, \
               ut_global_fail_count); \
        PRINTF("  Total Tests:  %d", total); \
        if (ut_global_fail_count > 0) { \
            PRINTF("\n" UT_COLOR_RED "TESTS FAILED" UT_COLOR_RESET); \
            return 1; \
        } else { \
            PRINTF("\n" UT_COLOR_GREEN "ALL TESTS PASSED" UT_COLOR_RESET); \
            return 0; \
        } \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* WOLFMQTT_UNIT_TEST_H */
