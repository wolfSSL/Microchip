/* psa_trace.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFPSA_PSA_TRACE_H
#define WOLFPSA_PSA_TRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static inline void wolfpsa_trace(const char* fmt, ...)
{
    const char* enabled = getenv("WOLFPSA_TRACE");
    va_list args;

    if (enabled == NULL || enabled[0] == '\0') {
        return;
    }

    va_start(args, fmt);
    fputs("wolfpsa: ", stderr);
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
    va_end(args);
}

#endif /* WOLFPSA_PSA_TRACE_H */
