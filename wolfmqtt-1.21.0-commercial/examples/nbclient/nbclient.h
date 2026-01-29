/* nbclient.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_NBCLIENT_H
#define WOLFMQTT_NBCLIENT_H

#include "examples/mqttexample.h"


/* Exposed functions */
int mqttclient_test(MQTTCtx *mqttCtx);

#if defined(NO_MAIN_DRIVER)
int mqttclient_main(int argc, char** argv);
#endif

#endif /* WOLFMQTT_NBCLIENT_H */
