/* mqttclient.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_MQTTCLIENT_H
#define WOLFMQTT_MQTTCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "examples/mqttexample.h"


/* Exposed functions */
int mqttclient_test(MQTTCtx *mqttCtx);

#if defined(NO_MAIN_DRIVER)
int mqttclient_main(int argc, char** argv);
#endif

#ifdef __cplusplus
}
#endif

#endif /* WOLFMQTT_MQTTCLIENT_H */
