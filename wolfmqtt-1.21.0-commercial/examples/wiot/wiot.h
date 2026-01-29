/* wiot.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_WIOT_H
#define WOLFMQTT_WIOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "examples/mqttexample.h"


/* Exposed functions */
int wiot_test(MQTTCtx *mqttCtx);

#if defined(NO_MAIN_DRIVER)
int wiot_main(int argc, char** argv);
#endif

#ifdef __cplusplus
}
#endif

#endif /* WOLFMQTT_WIOT_H */
