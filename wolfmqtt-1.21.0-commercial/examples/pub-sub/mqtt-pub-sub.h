/* mqtt-pub-sub
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_PUB_SUB_H
#define WOLFMQTT_PUB_SUB_H

#ifdef __cplusplus
extern "C" {
#endif


/* Exposed functions */
int pub_client(MQTTCtx *mqttCtx);
int sub_client(MQTTCtx *mqttCtx);

#if defined(NO_MAIN_DRIVER)
int mqttPub_main(int argc, char** argv);
int mqttSub_main(int argc, char** argv);
#endif

#ifdef __cplusplus
}
#endif

#endif /* WOLFMQTT_PUB_SUB_H */
