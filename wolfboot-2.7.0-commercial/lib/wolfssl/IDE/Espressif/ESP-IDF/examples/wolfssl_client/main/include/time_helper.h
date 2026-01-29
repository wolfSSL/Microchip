/* time_helper.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* common Espressif time_helper v5.6.3.001 */

#ifndef _TIME_HELPER_H_
#define _TIME_HELPER_H_

/* ESP-IDF uses a 64-bit signed integer to represent time_t starting from
 * release v5.0 See Espressif api-reference/system/system_time
 */

#ifdef __cplusplus
extern "C" {
#endif

/* a function to show the current data and time */
int esp_show_current_datetime(void);

/* worst case, if GitHub time not available, used fixed time */
int set_fixed_default_time(void);

/* set time from string (e.g. GitHub commit time) */
int set_time_from_string(const char* time_buffer);

/* set time from NTP servers,
 * also initially calls set_fixed_default_time or set_time_from_string */
int set_time(void);

/* wait NTP_RETRY_COUNT seconds before giving up on NTP time */
int set_time_wait_for_ntp(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* #ifndef _TIME_HELPER_H_ */
