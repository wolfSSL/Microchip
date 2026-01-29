/* fwpush.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_FWPUSH_H
#define WOLFMQTT_FWPUSH_H

#include "examples/mqttexample.h"

#define FIRMWARE_PUSH_CLIENT_ID "WolfMQTTFwPush"
#define FIRMWARE_PUSH_DEF_FILE  "examples/publish.dat"

/* Structure to pass into the publish callback
 * using the publish->ctx pointer */
typedef struct FwpushCBdata_s {
    const char *filename;
    byte *data;
    FILE *fp;
} FwpushCBdata;

/* Exposed functions */
int fwpush_test(MQTTCtx *mqttCtx);

#if defined(NO_MAIN_DRIVER)
int fwpush_main(int argc, char** argv);
#endif

#endif /* WOLFMQTT_FWPUSH_H */
