/* net_libwebsockets.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_NET_LIBWEBSOCKETS_H
#define WOLFMQTT_NET_LIBWEBSOCKETS_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "wolfmqtt/mqtt_client.h"
#include "examples/mqttnet.h"

#ifdef ENABLE_MQTT_WEBSOCKET
#define WOLFMQTT_LWS_RX_BUF_SIZE 4096

/* Function declarations */
int NetWebsocket_Connect(void *context, const char* host, word16 port, 
    int timeout_ms);
int NetWebsocket_Read(void *context, byte* buf, int buf_len, 
    int timeout_ms);
int NetWebsocket_Write(void *context, const byte* buf, int buf_len, 
    int timeout_ms);
int NetWebsocket_Disconnect(void *context);

#endif /* ENABLE_MQTT_WEBSOCKET */

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* WOLFMQTT_NET_LIBWEBSOCKETS_H */
