/* FreeRTOS.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Stub FreeRTOS.h for the mem_track.h reproducer.
 *
 * Provides the minimum typedefs the wolfSSL header chain needs while
 * pretending to be a non-Linux multi-threaded FreeRTOS target. */
#ifndef WOLFSSL_REPRO_FREERTOS_H
#define WOLFSSL_REPRO_FREERTOS_H

typedef void *SemaphoreHandle_t;
typedef void *xSemaphoreHandle;
typedef void *TaskHandle_t;

/* mem_track.h calls these directly under #ifdef FREERTOS. Declarations
 * only; the test compiles -c and never links. */
extern void *pvPortMalloc(unsigned long size);
extern void  vPortFree(void *ptr);

#endif
