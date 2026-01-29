/* wolfssl-arduino.cpp
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <Arduino.h>
#include "wolfssl.h"

/* Function to allow wolfcrypt to use Arduino Serial.print for debug messages.
 * See wolfssl/wolfcrypt/logging.c */

#if defined(__AVR__)
#include <avr/pgmspace.h>  /* Required for PROGMEM handling on AVR */
#endif

int wolfSSL_Arduino_Serial_Print(const char* const s)
{
    /* Reminder: Serial.print is only available in C++ */
    int is_progmem = 0;

#if defined(__AVR__)
    const char* t;
    t = s;

    /* Safely check if `s` is in PROGMEM, 0x8000 is typical for AVR flash */
    if (reinterpret_cast<uint16_t>(t) >= 0x8000) {
        while (pgm_read_byte(t)) {
            Serial.write(pgm_read_byte(t++));
        }
        Serial.println();
        is_progmem = 1;
    }
#endif

    /* Print normally for non-AVR boards or RAM-stored strings */
    if (!is_progmem) {
        Serial.println(s);
    }

    return 0;
};
