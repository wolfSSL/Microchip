/* led.h
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

#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

int led_setup(void);
void led_on(void);
void led_off(void);
void led_toggle(void);
void led_pwm_setup(void);
void boot_led_on(void);
void boot_led_off(void);

#endif /* !GPIO_H_INCLUDED */
