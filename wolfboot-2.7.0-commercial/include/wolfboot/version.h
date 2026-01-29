/* version.h
 *
 * The wolfBoot library version
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_VERSION_H
#define WOLFBOOT_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif


#define LIBWOLFBOOT_VERSION_STRING "2.7.0"
#define LIBWOLFBOOT_VERSION_HEX 0x02070000

#ifndef WOLFBOOT_VERSION
    #define WOLFBOOT_VERSION LIBWOLFBOOT_VERSION_HEX
#endif

#ifdef __cplusplus
}
#endif

#endif /* WOLFBOOT_VERSION_H */
