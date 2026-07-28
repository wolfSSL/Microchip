/* user_settings.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFSSL_USER_SETTINGS_H
#define WOLFSSL_USER_SETTINGS_H

/* The build-config-matrix harness drives every algorithm feature via
 * wolfcrypt-native defines passed on the compiler command line by
 * build-test/build-variant.sh. This file only sets up invariants that are
 * always required (or always forbidden) regardless of the lane. */

#define WOLFCRYPT_ONLY
#define SINGLE_THREADED
#define WOLFSSL_PSA_ENGINE
#define NO_DSA

#endif /* WOLFSSL_USER_SETTINGS_H */
