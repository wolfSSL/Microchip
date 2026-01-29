/* fwclient.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_FWCLIENT_H
#define WOLFMQTT_FWCLIENT_H

#include "examples/mqttexample.h"

#define FIRMWARE_CLIIENT_ID     "WolfMQTTFWClient"
#define FIRMWARE_DEF_SAVE_AS    "firmware.bin"


/* Exposed functions */
int fwclient_test(MQTTCtx *mqttCtx);

#if defined(NO_MAIN_DRIVER)
int fwclient_main(int argc, char** argv);
#endif

#endif /* WOLFMQTT_FWCLIENT_H */
