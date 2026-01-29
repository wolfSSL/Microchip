/* app_stm32u5.c
 *
 * Test bare-metal application.
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "system.h"
#include "hal.h"
#include "wolfboot/wolfboot.h"
#include "target.h"

#ifdef STM32_DISCOVERY
#define LED_BOOT_PIN (7) /* PH7 - Discovery - Green Led */
#define LED_USR_PIN (6)  /* PH6 - Discovery  - Red Led */
#else
#define LED_BOOT_PIN (7) /* PC7 - Nucleo-U575ZI-Q - Green Led */
#define LED_USR_PIN (2)  /* PG2 - Nucleo-U575ZI-Q - Red Led */
#endif

/*Non-Secure */
#define RCC_BASE            (0x46020C00)   /* RM0456 - Table 4 */
#define PWR_BASE            (0x46020800)   /* RM0456 - Table 4 */
#define GPIOC_BASE 0x42020800
#define GPIOG_BASE 0x42021800
#define GPIOH_BASE 0x42021C00

#define GPIOC_MODER (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_PUPDR (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))
#define GPIOC_BSRR  (*(volatile uint32_t *)(GPIOC_BASE + 0x18))

#define GPIOG_MODER (*(volatile uint32_t *)(GPIOG_BASE + 0x00))
#define GPIOG_PUPDR (*(volatile uint32_t *)(GPIOG_BASE + 0x0C))
#define GPIOG_BSRR  (*(volatile uint32_t *)(GPIOG_BASE + 0x18))

#define GPIOH_MODER (*(volatile uint32_t *)(GPIOH_BASE + 0x00))
#define GPIOH_PUPDR (*(volatile uint32_t *)(GPIOH_BASE + 0x0C))
#define GPIOH_BSRR  (*(volatile uint32_t *)(GPIOH_BASE + 0x18))

#define RCC_AHB2ENR1_CLOCK_ER (*(volatile uint32_t *)(RCC_BASE + 0x8C ))
#define GPIOC_AHB2ENR1_CLOCK_ER (1 << 2)
#define GPIOG_AHB2ENR1_CLOCK_ER (1 << 6)
#define GPIOH_AHB2ENR1_CLOCK_ER (1 << 7)

#define PWR_CR2              (*(volatile uint32_t *)(PWR_BASE + 0x04))
#define PWR_CR2_IOSV         (1 << 9)

static void boot_led_on(void)
{
    uint32_t reg;
    uint32_t pin = LED_BOOT_PIN;

#ifdef STM32_DISCOVERY
    RCC_AHB2ENR1_CLOCK_ER|= GPIOH_AHB2ENR1_CLOCK_ER;
#else
    RCC_AHB2ENR1_CLOCK_ER|= GPIOC_AHB2ENR1_CLOCK_ER;
#endif
    /* Delay after an RCC peripheral clock enabling */
    reg = RCC_AHB2ENR1_CLOCK_ER;

#if 0
    /* Disabled, may not need it */
    PWR_CR2 |= PWR_CR2_IOSV;
#endif

#ifdef STM32_DISCOVERY
    reg = GPIOH_MODER & ~(0x03 << (pin * 2));
    GPIOH_MODER = reg | (1 << (pin * 2));
    GPIOH_PUPDR &= ~(0x03 << (pin * 2));
    GPIOH_BSRR |= (1 << (pin + 16));
#else
    reg = GPIOC_MODER & ~(0x03 << (pin * 2));
    GPIOC_MODER = reg | (1 << (pin * 2));
    GPIOC_PUPDR &= ~(0x03 << (pin * 2));
    GPIOC_BSRR |= (1 << pin);
#endif
}

static void boot_led_off(void)
{
#ifdef STM32_DISCOVERY
    GPIOH_BSRR |= (1 << (LED_BOOT_PIN));
#else
    GPIOC_BSRR |= (1 << (LED_BOOT_PIN + 16));
#endif
}

void usr_led_on(void)
{
    uint32_t reg;
    uint32_t pin = LED_USR_PIN;

#ifdef STM32_DISCOVERY
    RCC_AHB2ENR1_CLOCK_ER|= GPIOH_AHB2ENR1_CLOCK_ER;
#else
    RCC_AHB2ENR1_CLOCK_ER|= GPIOG_AHB2ENR1_CLOCK_ER;
#endif
    /* Delay after an RCC peripheral clock enabling */
    reg = RCC_AHB2ENR1_CLOCK_ER;

#ifdef STM32_DISCOVERY
    reg = GPIOH_MODER & ~(0x03 << (pin * 2));
    GPIOH_MODER = reg | (1 << (pin * 2));
    GPIOH_PUPDR &= ~(0x03 << (pin * 2));
    GPIOH_BSRR |= (1 << (pin + 16));
#else
    reg = GPIOG_MODER & ~(0x03 << (pin * 2));
    GPIOG_MODER = reg | (1 << (pin * 2));
    GPIOG_PUPDR &= ~(0x03 << (pin * 2));
    GPIOG_BSRR |= (1 << pin);
#endif
}

void usr_led_off(void)
{
#ifdef STM32_DISCOVERY
    GPIOH_BSRR |= (1 << (LED_USR_PIN));
#else
    GPIOG_BSRR |= (1 << (LED_USR_PIN + 16));
#endif
}

void main(void)
{
    hal_init();
    boot_led_on();
    usr_led_on();
    boot_led_off();
    if (wolfBoot_current_firmware_version() > 1)
        boot_led_on();
    while(1)
        ;
}
