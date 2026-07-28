/* stm32l5.c
 *
 * Test bare-metal application.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include "system.h"
#include "hal.h"
#include "uart_drv.h"
#include "wolfboot/wolfboot.h"
#include "wolfboot/wc_secure.h"
#include "target.h"

#ifdef SECURE_PKCS11
#include "test_pkcs11.h"
#include "wcs/user_settings.h"
#include <wolfssl/wolfcrypt/settings.h>
#endif

#define LED_BOOT_PIN (9)  /* PA9 - Nucleo - Red Led */
#define LED_USR_PIN (7)   /* PC7  - Nucleo  - Green Led */
#define LED_EXTRA_PIN (7) /* PB7  - Nucleo  - Blue Led */

/*Non-Secure */
#define RCC_BASE            (0x40021000)
#define PWR_BASE            (0x40007000)
#define GPIOA_BASE          0x42020000
#define GPIOB_BASE          0x42020400
#define GPIOC_BASE          0x42020800


#define GPIOA_MODER  (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_PUPDR  (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))
#define GPIOA_BSRR  (*(volatile uint32_t *)(GPIOA_BASE + 0x18))

#define GPIOB_MODER  (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_PUPDR  (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
#define GPIOB_BSRR  (*(volatile uint32_t *)(GPIOB_BASE + 0x18))

#define GPIOC_MODER  (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_PUPDR  (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))
#define GPIOC_BSRR  (*(volatile uint32_t *)(GPIOC_BASE + 0x18))

#define RCC_AHB2_CLOCK_ER (*(volatile uint32_t *)(RCC_BASE + 0x4C ))
#define GPIOA_AHB2_CLOCK_ER (1 << 0)
#define GPIOB_AHB2_CLOCK_ER (1 << 1)
#define GPIOC_AHB2_CLOCK_ER (1 << 2)

#define PWR_CR2              (*(volatile uint32_t *)(PWR_BASE + 0x04))
#define PWR_CR2_IOSV         (1 << 9)

static void boot_led_on(void)
{
    uint32_t reg;
    uint32_t pin = LED_BOOT_PIN;

    RCC_AHB2_CLOCK_ER|= GPIOA_AHB2_CLOCK_ER;
    /* Delay after an RCC peripheral clock enabling */
    reg = RCC_AHB2_CLOCK_ER;
    PWR_CR2 |= PWR_CR2_IOSV;

    reg = GPIOA_MODER & ~(0x03 << (pin * 2));
    GPIOA_MODER = reg | (1 << (pin * 2));
    GPIOA_PUPDR &= ~(0x03 << (pin * 2));
    GPIOA_BSRR |= (1 << (LED_BOOT_PIN));
}

static void boot_led_off(void)
{
    GPIOA_BSRR |= (1 << (LED_BOOT_PIN + 16));
}

void usr_led_on(void)
{
    uint32_t reg;
    uint32_t pin = LED_USR_PIN;

    RCC_AHB2_CLOCK_ER|= GPIOC_AHB2_CLOCK_ER;
    /* Delay after an RCC peripheral clock enabling */
    reg = RCC_AHB2_CLOCK_ER;

    reg = GPIOC_MODER & ~(0x03 << (pin * 2));
    GPIOC_MODER = reg | (1 << (pin * 2));
    GPIOC_PUPDR &= ~(0x03 << (pin * 2));
    GPIOC_BSRR |= (1 << (LED_USR_PIN));
}

void usr_led_off(void)
{
    GPIOC_BSRR |= (1 << (LED_USR_PIN + 16));
}

void extra_led_on(void)
{
    uint32_t reg;
    uint32_t pin = LED_EXTRA_PIN;

    RCC_AHB2_CLOCK_ER|= GPIOB_AHB2_CLOCK_ER;
    /* Delay after an RCC peripheral clock enabling */
    reg = RCC_AHB2_CLOCK_ER;

    reg = GPIOB_MODER & ~(0x03 << (pin * 2));
    GPIOB_MODER = reg | (1 << (pin * 2));
    GPIOB_PUPDR &= ~(0x03 << (pin * 2));
    GPIOB_BSRR |= (1 << (LED_EXTRA_PIN));
}

void extra_led_off(void)
{
    GPIOB_BSRR |= (1 << (LED_EXTRA_PIN + 16));
}

void main(void)
{
#ifdef SECURE_PKCS11
    int ret;

    boot_led_on();
    ret = test_pkcs11_start();
    if (ret != PKCS11_TEST_FAIL)
        usr_led_on();
#endif
    while(1)
        ;

    /* Never reached */
}
