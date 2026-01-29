/* firmware.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFMQTT_FIRMWARE_H
#define WOLFMQTT_FIRMWARE_H

#ifdef __cplusplus
extern "C" {
#endif

#define FIRMWARE_TOPIC_NAME     "wolfMQTT/example/firmware"
#define FIRMWARE_MAX_BUFFER     2048
#define FIRMWARE_MAX_PACKET     (int)(FIRMWARE_MAX_BUFFER + sizeof(MqttPacket) + XSTRLEN(FIRMWARE_TOPIC_NAME) + MQTT_DATA_LEN_SIZE)
#define FIRMWARE_MQTT_QOS		MQTT_QOS_2

#define FIRMWARE_HASH_TYPE      WC_HASH_TYPE_SHA256
#define FIRMWARE_SIG_TYPE       WC_SIGNATURE_TYPE_ECC


/* Signature Len, Public Key Len, Firmware Len, Signature, Public Key, Data */
typedef struct _FirmwareHeader {
    word16 sigLen;
    word16 pubKeyLen;
    word32 fwLen;
} WOLFMQTT_PACK FirmwareHeader;

#ifdef __cplusplus
}
#endif

#endif /* WOLFMQTT_FIRMWARE_H */
