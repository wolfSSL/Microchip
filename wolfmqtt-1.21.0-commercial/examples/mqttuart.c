/* mqttuart.c
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Include the autoconf generated config.h */
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "wolfmqtt/mqtt_client.h"
#include "examples/mqttnet.h"


/* TODO: Add includes for UART HW */

/* Include the example code */
#include "examples/mqttexample.h"


/* this code is a template for using UART for communication */
#if 0

/* Local context for callbacks */
typedef struct _UartContext {
    int uartPort;
    /* TODO: Add any other context info you want */
} UartContext;

/* Private functions */
static int NetConnect(void *context, const char* host, word16 port,
    int timeout_ms)
{
    UartContext *uartCtx = (UartContext*)context;
    (void)uartCtx;

    return 0;
}

static int NetWrite(void *context, const byte* buf, int buf_len,
    int timeout_ms)
{
    UartContext *uartCtx = (UartContext*)context;
    (void)uartCtx;

    /* TODO: Implement write call to your UART HW */

    return 0;
}

static int NetRead(void *context, byte* buf, int buf_len,
    int timeout_ms)
{
    UartContext *uartCtx = (UartContext*)context;
    (void)uartCtx;

    /* TODO: Implement read call to your UART HW */

    return 0;
}

static int NetDisconnect(void *context)
{
    UartContext *uartCtx = (UartContext*)context;
    (void)uartCtx;

    return 0;
}

/* Public Functions */
int MqttClientNet_Init(MqttNet* net, MQTTCtx* mqttCtx)
{
    if (net) {
        XMEMSET(net, 0, sizeof(MqttNet));
        net->connect = NetConnect;
        net->read = NetRead;
        net->write = NetWrite;
        net->disconnect = NetDisconnect;
        net->context = WOLFMQTT_MALLOC(sizeof(UartContext));
    }
    (void)mqttCtx;
    return 0;
}

int MqttClientNet_DeInit(MqttNet* net)
{
    if (net) {
        if (net->context) {
            WOLFMQTT_FREE(net->context);
        }
        XMEMSET(net, 0, sizeof(MqttNet));
    }
    return 0;
}

#endif
