/* sn-client.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_SNCLIENT_H
#define WOLFMQTT_SNCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "examples/mqttexample.h"


/* Exposed functions */
int sn_test(MQTTCtx *mqttCtx);
int sn_testQoSn1(MQTTCtx *mqttCtx);
int sn_multithread_test(MQTTCtx *mqttCtx);

#if defined(NO_MAIN_DRIVER)
int sn_main(int argc, char** argv);
int sn_QoSn1_main(int argc, char** argv);
int sn_multithread_main(int argc, char** argv);
#endif


#ifdef __cplusplus
}
#endif

#endif /* WOLFMQTT_SNCLIENT_H */
