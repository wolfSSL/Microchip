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
 * port/posix/posix_time.h
 *
 * POSIX time helper returning the current time in microseconds.
 */

#ifndef PORT_POSIX_POSIX_TIME_H_
#define PORT_POSIX_POSIX_TIME_H_

#include <stdint.h>

uint64_t posixGetTime(void);

#endif /* PORT_POSIX_POSIX_TIME_H_ */
