/* awsiot.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_AWSIOT_H
#define WOLFMQTT_AWSIOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "examples/mqttexample.h"


/* Exposed functions */
int awsiot_test(MQTTCtx *mqttCtx);
#ifdef NO_MAIN_DRIVER
int awsiot_main(int argc, char** argv);
#endif

#ifdef __cplusplus
}
#endif


#endif /* WOLFMQTT_AWSIOT_H */
