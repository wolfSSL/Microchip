/*
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* common Espressif time_helper v5.6.3.001 */

#ifndef _TIME_HELPER_H
#define _TIME_HELPER_H

/* ESP-IDF uses a 64-bit signed integer to represent time_t starting from release v5.0
 * See: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html#year-2036-and-2038-overflow-issues
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <esp_err.h>

/* a function to show the current data and time */
esp_err_t esp_show_current_datetime();

/* worst case, if GitHub time not available, used fixed time */
esp_err_t set_fixed_default_time(void);

/* set time from string (e.g. GitHub commit time) */
esp_err_t set_time_from_string(const char* time_buffer);

/* set time from NTP servers,
 * also initially calls set_fixed_default_time or set_time_from_string */
esp_err_t set_time(void);

/* wait NTP_RETRY_COUNT seconds before giving up on NTP time */
esp_err_t set_time_wait_for_ntp(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* #ifndef _TIME_HELPER_H */
