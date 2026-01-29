/* user_settings.h
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* used by TOPPERS OS */
#ifndef _TOPPERS_USER_SETTINGS_H
#define _TOPPERS_USER_SETTINGS_H

#ifdef TOPPERS
    #define WOLFMQTT_USER_SETTINGS
    #define ENABLE_MQTT_TLS
    #define WOLFSSL_BASE64_ENCODE
    #define WOLFMQTT_NO_TIMEOUT
#endif

#endif /* _TOPPERS_USER_SETTINGS_H */
