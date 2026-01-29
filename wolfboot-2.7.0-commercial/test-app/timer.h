/* timer.h
 *
 * Test bare-metal blinking led application
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

int pwm_init(uint32_t clock, uint32_t threshold);
int timer_init(uint32_t clock, uint32_t scaler, uint32_t interval);

#endif /* !TIMER_H_INCLUDED */
