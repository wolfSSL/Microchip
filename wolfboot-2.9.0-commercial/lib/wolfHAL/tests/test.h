/* test.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_TEST_H
#define WHAL_TEST_H

#include <stdarg.h>
#include <stddef.h>

/*
 * Minimal test framework for wolfHAL.
 *
 * Provides test runner macros, assertions, and pass/fail tracking.
 * The print backend (whal_Test_Puts) is implemented per-harness:
 *   - core: libc puts
 *   - hw:  UART send
 */

/* Provided by each harness */
void whal_Test_Puts(const char *s);

/* Convert an integer to decimal in a static buffer (no libc dependency) */
static inline const char *whal_Test_Itoa(int val)
{
    static char buf[16];
    char *p = buf + sizeof(buf) - 1;
    int neg = 0;

    *p = '\0';
    if (val < 0) {
        neg = 1;
        val = -val;
    }

    do {
        *--p = '0' + (val % 10);
        val /= 10;
    } while (val);

    if (neg)
        *--p = '-';

    return p;
}

/* Minimal printf: supports %d, %s, and %%. Calls whal_Test_Puts once. */
static inline void whal_Test_Printf(const char *fmt, ...)
{
    static char buf[128];
    char *out = buf;
    char *end = buf + sizeof(buf) - 1;
    va_list ap;

    va_start(ap, fmt);
    while (*fmt && out < end) {
        if (*fmt != '%') {
            *out++ = *fmt++;
            continue;
        }
        fmt++;
        if (*fmt == 'd') {
            const char *s = whal_Test_Itoa(va_arg(ap, int));
            while (*s && out < end)
                *out++ = *s++;
        }
        else if (*fmt == 's') {
            const char *s = va_arg(ap, const char *);
            while (*s && out < end)
                *out++ = *s++;
        }
        else if (*fmt == '%') {
            *out++ = '%';
        }
        fmt++;
    }
    va_end(ap);

    *out = '\0';
    whal_Test_Puts(buf);
}

extern int g_whalTestPassed;
extern int g_whalTestFailed;
extern int g_whalTestSkipped;
extern int g_whalTestCurFailed;
extern int g_whalTestCurSkipped;

#define WHAL_TEST_SUITE_START(name)                  \
    do {                                        \
        whal_Test_Printf("\n=== " name " ===\n"); \
    } while (0)

#define WHAL_TEST_SUITE_END() \
    do { } while (0)

#define WHAL_SKIP()                              \
    do {                                    \
        g_whalTestCurSkipped = 1;              \
        return;                             \
    } while (0)

#define WHAL_TEST(fn)                            \
    do {                                    \
        g_whalTestCurFailed = 0;               \
        g_whalTestCurSkipped = 0;              \
        fn();                               \
        if (g_whalTestCurSkipped) {             \
            whal_Test_Printf(#fn ": SKIP\n");    \
            g_whalTestSkipped++;                \
        }                                   \
        else if (g_whalTestCurFailed) {         \
            whal_Test_Printf(#fn ": FAIL\n");    \
            g_whalTestFailed++;                 \
        }                                   \
        else {                              \
            whal_Test_Printf(#fn ": PASS\n");    \
            g_whalTestPassed++;                 \
        }                                   \
    } while (0)

#define WHAL_ASSERT_EQ(a, b)                                         \
    do {                                                        \
        int _a = (int)(a);                                      \
        int _b = (int)(b);                                      \
        if (_a != _b) {                                         \
            whal_Test_Printf("  ASSERT_EQ failed at %s:%d\n",  \
                            __FILE__, __LINE__);                \
            whal_Test_Printf("  got: %d, expected: %d\n",      \
                            _a, _b);                            \
            g_whalTestCurFailed = 1;                            \
            return;                                             \
        }                                                       \
    } while (0)

#define WHAL_ASSERT_NEQ(a, b)                                        \
    do {                                                        \
        if ((a) == (b)) {                                       \
            whal_Test_Printf("  ASSERT_NEQ failed at %s:%d\n", \
                            __FILE__, __LINE__);                \
            g_whalTestCurFailed = 1;                            \
            return;                                             \
        }                                                       \
    } while (0)

#define WHAL_ASSERT_MEM_EQ(a, b, len)                                \
    do {                                                        \
        const unsigned char *_a = (const unsigned char *)(a);   \
        const unsigned char *_b = (const unsigned char *)(b);   \
        for (size_t _i = 0; _i < (len); _i++) {                \
            if (_a[_i] != _b[_i]) {                             \
                whal_Test_Printf("  ASSERT_MEM_EQ failed at "  \
                                "%s:%d, byte offset: %d\n",    \
                                __FILE__, __LINE__, (int)_i);   \
                g_whalTestCurFailed = 1;                        \
                return;                                         \
            }                                                   \
        }                                                       \
    } while (0)

#define WHAL_ASSERT_MEM_NEQ(a, b, len)                               \
    do {                                                             \
        const unsigned char *_a = (const unsigned char *)(a);        \
        const unsigned char *_b = (const unsigned char *)(b);        \
        int _differ = 0;                                             \
        for (size_t _i = 0; _i < (len); _i++) {                      \
            if (_a[_i] != _b[_i]) { _differ = 1; break; }            \
        }                                                            \
        if (!_differ) {                                              \
            whal_Test_Printf("  ASSERT_MEM_NEQ failed at %s:%d\n",  \
                             __FILE__, __LINE__);                    \
            g_whalTestCurFailed = 1;                                 \
            return;                                                  \
        }                                                            \
    } while (0)

#define WHAL_TEST_SUMMARY()                                  \
    do {                                                \
        whal_Test_Printf("\n");                                  \
        whal_Test_Printf("--- Results ---\n");                   \
        whal_Test_Printf("Skipped: %d\n", g_whalTestSkipped);   \
        whal_Test_Printf("Passed: %d\n", g_whalTestPassed);     \
        whal_Test_Printf("Failed: %d\n", g_whalTestFailed);     \
    } while (0)

#endif /* WHAL_TEST_H */
