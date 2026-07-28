/* wifi_connect.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef _WIFI_CONNECT_H_
#define _WIFI_CONNECT_H_

/* ESP lwip */
#define EXAMPLE_ESP_MAXIMUM_RETRY       CONFIG_ESP_MAXIMUM_RETRY

#define TLS_SMP_WIFI_SSID                CONFIG_WIFI_SSID
#define TLS_SMP_WIFI_PASS                CONFIG_WIFI_PASSWORD

#define USE_WIFI_EXAMPLE
#ifdef USE_WIFI_EXAMPLE
    #include "esp_netif.h"
    #include "protocol_examples_common.h" /* see project CMakeLists.txt */
#endif

/**
 ******************************************************************************
 ******************************************************************************
 ** USER APPLICATION SETTINGS BEGIN
 ******************************************************************************
 ******************************************************************************
 **/

/* when using a private config with plain text passwords,
 * file my_private_config.h should be excluded from git updates */
/* #define  USE_MY_PRIVATE_CONFIG */

/* Note that IntelliSense may not work properly in the next section for the
 * Espressif SDK 3.4 on the ESP8266. Macros should still be defined.
 * See the project-level Makefile. Example found in:
 * https://github.com/wolfSSL/wolfssl/tree/master/IDE/Espressif/ESP-IDF/examples/template
 *
 * The USE_MY_PRIVATE_[OS]_CONFIG is typically an environment variable that
 * triggers the make (not cmake) to add compiler defines.
 */
#if defined(USE_MY_PRIVATE_WINDOWS_CONFIG)
    #include "/workspace/my_private_config.h"
#elif defined(USE_MY_PRIVATE_WSL_CONFIG)
    #include "/mnt/c/workspace/my_private_config.h"
#elif defined(USE_MY_PRIVATE_LINUX_CONFIG)
    #include "~/workspace/my_private_config.h"
#elif defined(USE_MY_PRIVATE_MAC_CONFIG)
    #include "~/Documents/my_private_config.h"
#elif defined(USE_MY_PRIVATE_CONFIG)
    /* This section works best with cmake & non-environment variable setting */
    #if defined(WOLFSSL_CMAKE_SYSTEM_NAME_WINDOWS)
        #define WOLFSSL_CMAKE
        #include "/workspace/my_private_config.h"
    #elif defined(WOLFSSL_MAKE_SYSTEM_NAME_WINDOWS)
        #define WOLFSSL_MAKE
        #include "/workspace/my_private_config.h"
    #elif defined(WOLFSSL_CMAKE_SYSTEM_NAME_WSL)
        #define WOLFSSL_CMAKE
        #include "/mnt/c/workspace/my_private_config.h"
    #elif defined(WOLFSSL_MAKE_SYSTEM_NAME_WSL)
        #define WOLFSSL_MAKE
        #include "/mnt/c/workspace/my_private_config.h"
    #elif defined(WOLFSSL_CMAKE_SYSTEM_NAME_LINUX)
        #define WOLFSSL_CMAKE
        #include "~/workspace/my_private_config.h"
    #elif defined(WOLFSSL_MAKE_SYSTEM_NAME_LINUX)
        #define WOLFSSL_MAKE
        #include "~/workspace/my_private_config.h"
    #elif defined(WOLFSSL_CMAKE_SYSTEM_NAME_APPLE)
        #include "~/Documents/my_private_config.h"
    #elif defined(WOLFSSL_MAKE_SYSTEM_NAME_APPLE)
        #define WOLFSSL_MAKE
        #include "~/Documents/my_private_config.h"
    #elif defined(OS_WINDOWS)
        #include "/workspace/my_private_config.h"
    #else
        /* Edit as needed for your private config: */
        #warning "default private config using /workspace/my_private_config.h"
        #include "/workspace/my_private_config.h"
    #endif
#else

    /*
    ** The examples use WiFi configuration that you can set via project
    ** configuration menu
    **
    ** If you'd rather not, just change the below entries to strings with
    ** the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
    */
    #if defined(CONFIG_ESP_WIFI_SSID)
        /* tyically from ESP32 with ESP-IDF v4 to v5 */
        #define EXAMPLE_ESP_WIFI_SSID CONFIG_ESP_WIFI_SSID
    #elif defined(CONFIG_EXAMPLE_WIFI_SSID)
        /* typically from ESP8266 rtos-sdk/v3.4 */
        #define EXAMPLE_ESP_WIFI_SSID CONFIG_EXAMPLE_WIFI_SSID
    #else
        /* See new esp-sdk-lib.h helpers: */
        #ifndef EXAMPLE_ESP_WIFI_SSID
            #define EXAMPLE_ESP_WIFI_SSID "MYSSID_WIFI_CONNECT"
        #endif
    #endif

    #if defined(CONFIG_ESP_WIFI_PASSWORD)
        /* tyically from ESP32 with ESP-IDF v4 or v5 */
        #define EXAMPLE_ESP_WIFI_PASS CONFIG_ESP_WIFI_PASSWORD
    #elif defined(CONFIG_EXAMPLE_WIFI_SSID)
        /* typically from ESP8266 rtos-sdk/v3.4 */
        #define EXAMPLE_ESP_WIFI_PASS CONFIG_EXAMPLE_WIFI_PASSWORD
    #else
        /* See new esp-sdk-lib.h helpers: */
        #ifndef EXAMPLE_ESP_WIFI_PASS
            #define EXAMPLE_ESP_WIFI_PASS "MYPASSWORD_WIFI_CONNECT"
        #endif
    #endif
#endif

/* ESP lwip */
#define EXAMPLE_ESP_MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

int wifi_init_sta(void);

int wifi_show_ip(void);

#endif /* _WIFI_CONNECT_H_ */
