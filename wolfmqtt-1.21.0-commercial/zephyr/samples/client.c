/* client.c
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "wolfmqtt/mqtt_client.h"
#include "examples/mqttclient/mqttclient.h"

int main(void)
{
    int rc;
    MQTTCtx mqttCtx;

    /* init defaults */
    mqtt_init_ctx(&mqttCtx);

    mqttCtx.test_mode = 1;

    /* Set port as configured in scripts/broker_test/mosquitto.conf */
#if defined(WOLFMQTT_DEFAULT_TLS) && (WOLFMQTT_DEFAULT_TLS == 1)
    mqttCtx.port = 18883;
#else
    mqttCtx.port = 11883;
#endif

    rc = mqttclient_test(&mqttCtx);

    mqtt_free_ctx(&mqttCtx);

    if (rc == 0)
        PRINTF("Zephyr MQTT test passed");

    return (rc == 0) ? 0 : EXIT_FAILURE;
}
