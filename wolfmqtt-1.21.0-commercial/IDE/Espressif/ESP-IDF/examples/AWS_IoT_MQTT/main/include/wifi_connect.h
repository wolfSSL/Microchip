/* wifi_connect.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef _WIFI_CONNECT_H_
#define _WIFI_CONNECT_H_

#include <esp_idf_version.h>
#include <esp_log.h>

/* ESP lwip */
#define EXAMPLE_ESP_MAXIMUM_RETRY       CONFIG_ESP_MAXIMUM_RETRY

#define TLS_SMP_SERVER_TASK_NAME         "tls_sever_example"
#define TLS_SMP_SERVER_TASK_WORDS        22240
#define TLS_SMP_SERVER_TASK_PRIORITY     8

#define TLS_SMP_WIFI_SSID                CONFIG_WIFI_SSID
#define TLS_SMP_WIFI_PASS                CONFIG_WIFI_PASSWORD

#define USE_WIFI_EXAMPLE
#ifdef USE_WIFI_EXAMPLE
    #include <protocol_examples_common.h> /* see project CMakeLists.txt */
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

#ifdef  USE_MY_PRIVATE_CONFIG
    #if defined(WOLFSSL_CMAKE_SYSTEM_NAME_WINDOWS)
        #include "/workspace/my_private_config.h"
    #elif defined(WOLFSSL_CMAKE_SYSTEM_NAME_WSL)
        #include "/mnt/c/workspace/my_private_config.h"
    #elif defined(WOLFSSL_CMAKE_SYSTEM_NAME_LINUX)
        #include "~/workspace/my_private_config.h"
    #elif defined(WOLFSSL_CMAKE_SYSTEM_NAME_APPLE)
        #include "~/Documents/my_private_config.h"
    #else
        #warning "did not detect environment. using ~/my_private_config.h"
        #include "~/my_private_config.h"
	#endif
#else

    /*
    ** The examples use WiFi configuration that you can set via project
    ** configuration menu
    **
    ** If you'd rather not, just change the below entries to strings with
    ** the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
    */
    #ifdef CONFIG_ESP_WIFI_SSID
        #undef  EXAMPLE_ESP_WIFI_SSID
        #define EXAMPLE_ESP_WIFI_SSID CONFIG_ESP_WIFI_SSID
    #else
        #ifndef     EXAMPLE_ESP_WIFI_SSID
            #define EXAMPLE_ESP_WIFI_SSID "MYSSID_WIFI_CONNECT"
        #endif
    #endif

    #ifdef CONFIG_ESP_WIFI_PASSWORD
        #undef  EXAMPLE_ESP_WIFI_PASS
        #define EXAMPLE_ESP_WIFI_PASS CONFIG_ESP_WIFI_PASSWORD
    #else
        #ifndef     EXAMPLE_ESP_WIFI_PASS
            #define EXAMPLE_ESP_WIFI_PASS "MYPASSWORD_WIFI_CONNECT"
        #endif
    #endif
#endif

/* ESP lwip */
#define EXAMPLE_ESP_MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

int wifi_init_sta(void);

int wifi_show_ip(void);

#endif /* _WIFI_CONNECT_H_ */
