/*
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef WH_TEST_LIST_H_
#define WH_TEST_LIST_H_

#include <stddef.h>

/*
 * Portable weak-symbol attribute.
 *
 * wh_test_list.c defines a weak stub for every test. If the real test
 * is compiled in, its strong definition overrides the stub at link time.
 * If not, the stub remains and returns WH_TEST_SKIPPED.
 *
 * Usage:
 *   WH_TEST_WEAK(foo) int foo(void* ctx) { ... }
 *
 * The name is only needed for pragma-based toolchains; others ignore it.
 *
 * Supported toolchains:
 *   GCC, Clang, ARM, TI   -> __attribute__((weak))
 *   IAR                   -> __weak
 *   Renesas (CC-RH/RL/RX) -> _Pragma("weak <name>")
 *
 * Add new toolchains explicitly. A missing definition here will either
 * cause link errors or let the stub override the real test.
 */
#define WH_TEST_WEAK_STR_(s) #s
#if defined(__GNUC__) || defined(__clang__) || \
    defined(__ARMCC_VERSION) || defined(__CC_ARM) || \
    defined(__TI_COMPILER_VERSION__)
#define WH_TEST_WEAK(name) __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define WH_TEST_WEAK(name) __weak
#elif defined(__CCRH__) || defined(__CCRL__) || defined(__CCRX__)
#define WH_TEST_WEAK(name) _Pragma(WH_TEST_WEAK_STR_(weak name))
#else
#error "WH_TEST_WEAK: add a weak-symbol spelling for this toolchain"
#endif

/*
 * Sentinel returned by the weak skip stubs. Picked to be distinct
 * from any error code a real test would return and from 0 (pass).
 */
#define WH_TEST_SKIPPED (-777)

/*
 * Declares a test prototype and provides a weak default stub.
 * wh_test_list.c uses WH_TEST_DECL(name) for every registered test.
 *
 * If the real test is compiled in, its strong definition overrides
 * this stub at link time. Otherwise, the stub remains and the test
 * is reported as SKIPPED.
 *
 * The trailing dummy struct lets callers safely end the macro with
 * a semicolon, which avoids issues under strict C90.
 */
#define WH_TEST_DECL(name)                                               \
    WH_TEST_WEAK(name) int name(void* ctx)                               \
    { (void)ctx; return WH_TEST_SKIPPED; }                               \
    struct whTest_decl_dummy_##name

/* Function pointer type for test functions. 
 * Test functions actually take a context pointer, but using void* greatly 
 * simplifies the API */
typedef int (*whTestFn)(void* ctx);

typedef struct whTestCase {
    const char* name;
    whTestFn    fn;
} whTestCase;

/*
 * Per-group registries, defined in wh_test_list.c. Each group gets
 * its own array so the runner walks only the relevant tests.
 */
extern const whTestCase whTestsMisc[];
extern const size_t     whTestsMiscCount;

extern const whTestCase whTestsServer[];
extern const size_t     whTestsServerCount;

extern const whTestCase whTestsClient[];
extern const size_t     whTestsClientCount;

#endif /* WH_TEST_LIST_H_ */
