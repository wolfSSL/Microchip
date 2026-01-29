/* wolfssl.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Edit with caution. This is an Arduino-library specific header for wolfSSL */

#ifndef WOLFSSL_USER_SETTINGS
    /* Should already be defined in settings.h for #if defined(ARDUINO) */
    #define WOLFSSL_USER_SETTINGS
#endif

#include <Arduino.h>

/* wolfSSL user_settings.h must be included from settings.h
 * Make all configurations changes in user_settings.h
 * Do not edit wolfSSL `settings.h` or `config.h` files.
 * Do not explicitly include user_settings.h in any source code.
 * Each Arduino sketch that uses wolfSSL must have: #include "wolfssl.h"
 * C/C++ source files can use: #include <wolfssl/wolfcrypt/settings.h>
 * The wolfSSL "settings.h" must be included in each source file using wolfSSL.
 * The wolfSSL "settings.h" must be listed before any other wolfSSL include.
 */
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/ssl.h>

#ifndef WOLFSSL_ARDUINO_H
#define WOLFSSL_ARDUINO_H

/* Declare a helper function to be used in wolfssl/wolfcrypt/logging.c */
int wolfSSL_Arduino_Serial_Print(const char* const s);

#endif /* WOLFSSL_ARDUINO_H */
