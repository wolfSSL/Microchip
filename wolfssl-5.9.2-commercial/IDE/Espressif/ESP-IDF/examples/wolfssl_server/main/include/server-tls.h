/* server-tls.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef _SERVER_TLS_
#define _SERVER_TLS_

/* This example uses wolfssl test certificates */
#if 1
    /* See wolfssl/certs_test.h */
    #if defined(CONFIG_IDF_TARGET_ESP32C2) || \
        defined(CONFIG_IDF_TARGET_ESP8684) || \
        defined(CONFIG_IDF_TARGET_ESP8266)
        /* Use smaller certs for low-memory devices */
        #define USE_CERT_BUFFERS_1024
    #else
        #define USE_CERT_BUFFERS_2048
    #endif

    /* always include smallest testing 32 byte RSA/ECC keys */
    #define USE_CERT_BUFFERS_256
#else
    /* define your own certificate macros; see user_settings.h */
#endif

#include <wolfssl/wolfcrypt/settings.h> /* includes wolfSSL user-settings.h */
#include <wolfssl/ssl.h>
#include "sdkconfig.h"

#if defined(SINGLE_THREADED)
    #define WOLFSSL_ESP_TASK int
#else
    #include "freertos/FreeRTOS.h"
    #define WOLFSSL_ESP_TASK void
#endif

#ifdef CONFIG_WOLFSSL_TARGET_PORT
    #define TLS_SMP_DEFAULT_PORT  CONFIG_WOLFSSL_TARGET_PORT
#else
    #define TLS_SMP_DEFAULT_PORT  11111
#endif

typedef struct {
    int port;
    int loops;
} tls_args;

/* Function to show the ciphers available / in use. */
#if defined(DEBUG_WOLFSSL)
    int ShowCiphers(WOLFSSL* ssl);
#endif

/* This is the TLS Server function, possibly in an RTOS thread. */
WOLFSSL_ESP_TASK tls_smp_server_task(void *args);

/* init will create an RTOS task, otherwise server is simply function call. */
#if defined(SINGLE_THREADED)
    /* no init needed */
#else
    WOLFSSL_ESP_TASK tls_smp_server_init(void* args);
#endif
#endif /* _SERVER_TLS_ */
