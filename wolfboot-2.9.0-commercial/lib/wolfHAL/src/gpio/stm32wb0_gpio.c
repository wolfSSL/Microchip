/* stm32wb0_gpio.c
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
#include "board.h"  /* provides WHAL_CFG_STM32WB0_GPIO_DEV initializer */
#include <wolfHAL/error.h>
#include <wolfHAL/gpio/gpio.h>
#include <wolfHAL/gpio/stm32wb0_gpio.h>
#include <wolfHAL/reg.h>
#include <wolfHAL/bitops.h>

const whal_Gpio whal_Stm32wb0_Gpio_Dev = WHAL_CFG_STM32WB0_GPIO_DEV;

/*
 * STM32WB0 GPIO register layout — per-port block uses standard STM32
 * offsets, but ports are 0x100000 (1 MB) apart rather than the usual
 * 0x400. Only ports A (0x48000000) and B (0x48100000) exist.
 */
#define GPIO_PORT_STRIDE  0x100000u

#define GPIO_MODE_REG    0x00 /* MODER:   2 bits/pin */
#define GPIO_OUTTYPE_REG 0x04 /* OTYPER:  1 bit/pin */
#define GPIO_SPEED_REG   0x08 /* OSPEEDR: 2 bits/pin */
#define GPIO_PULL_REG    0x0C /* PUPDR:   2 bits/pin */
#define GPIO_IDR_REG     0x10
#define GPIO_ODR_REG     0x14
#define GPIO_ALTFNL_REG  0x20 /* AFRL:    4 bits/pin for pins 0..7 */
#define GPIO_ALTFNH_REG  0x24 /* AFRH:    4 bits/pin for pins 8..15 */

#ifdef WHAL_CFG_STM32WB0_GPIO_DIRECT_API_MAPPING
#define whal_Stm32wb0_Gpio_Init   whal_Gpio_Init
#define whal_Stm32wb0_Gpio_Deinit whal_Gpio_Deinit
#define whal_Stm32wb0_Gpio_Get    whal_Gpio_Get
#define whal_Stm32wb0_Gpio_Set    whal_Gpio_Set
#endif /* WHAL_CFG_STM32WB0_GPIO_DIRECT_API_MAPPING */

static inline whal_Error whal_Stm32wb0_Gpio_InitPin(whal_Stm32wb0_Gpio_PinCfg cfg)
{
    uint8_t pin = WHAL_STM32WB0_GPIO_GET_PIN(cfg);
    size_t portBase;
    uint8_t pos2;
    size_t mask2, mask1;

    if (pin > 15)
        return WHAL_EINVAL;

    portBase = whal_Stm32wb0_Gpio_Dev.base +
               (WHAL_STM32WB0_GPIO_GET_PORT(cfg) * GPIO_PORT_STRIDE);
    pos2 = pin << 1;
    mask2 = WHAL_BITMASK(2) << pos2;
    mask1 = 1UL << pin;

    whal_Reg_Update(portBase, GPIO_MODE_REG, mask2,
                    WHAL_STM32WB0_GPIO_GET_MODE(cfg) << pos2);
    whal_Reg_Update(portBase, GPIO_SPEED_REG, mask2,
                    WHAL_STM32WB0_GPIO_GET_SPEED(cfg) << pos2);
    whal_Reg_Update(portBase, GPIO_PULL_REG, mask2,
                    WHAL_STM32WB0_GPIO_GET_PULL(cfg) << pos2);
    whal_Reg_Update(portBase, GPIO_OUTTYPE_REG, mask1,
                    WHAL_STM32WB0_GPIO_GET_OUTTYPE(cfg) << pin);

    if (WHAL_STM32WB0_GPIO_GET_MODE(cfg) == WHAL_STM32WB0_GPIO_MODE_ALTFN) {
        uint8_t afPos = (pin & 7) << 2;

        whal_Reg_Update(portBase,
                        (pin < 8) ? GPIO_ALTFNL_REG : GPIO_ALTFNH_REG,
                        WHAL_BITMASK(4) << afPos,
                        WHAL_STM32WB0_GPIO_GET_ALTFN(cfg) << afPos);
    }

    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb0_Gpio_Init(whal_Gpio *gpioDev)
{
    const whal_Stm32wb0_Gpio_Cfg *cfg =
        (const whal_Stm32wb0_Gpio_Cfg *)whal_Stm32wb0_Gpio_Dev.cfg;
    const whal_Stm32wb0_Gpio_PinCfg *pinCfg = cfg->pinCfg;
    whal_Error err;
    (void)gpioDev;

    for (size_t i = 0; i < cfg->pinCount; ++i) {
        err = whal_Stm32wb0_Gpio_InitPin(pinCfg[i]);
        if (err)
            return err;
    }
    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb0_Gpio_Deinit(whal_Gpio *gpioDev)
{
    (void)gpioDev;
    return WHAL_SUCCESS;
}

static whal_Error whal_Stm32wb0_Gpio_SetOrGet(whal_Gpio *gpioDev, size_t idx,
                                              size_t *value, uint8_t set)
{
    const whal_Stm32wb0_Gpio_Cfg *cfg =
        (const whal_Stm32wb0_Gpio_Cfg *)whal_Stm32wb0_Gpio_Dev.cfg;
    whal_Stm32wb0_Gpio_PinCfg pinCfg;
    uint8_t port, pin;
    size_t portBase, mask;
    (void)gpioDev;

    if (!value)
        return WHAL_EINVAL;

    pinCfg = cfg->pinCfg[idx];
    port = WHAL_STM32WB0_GPIO_GET_PORT(pinCfg);
    pin  = WHAL_STM32WB0_GPIO_GET_PIN(pinCfg);

    if (pin > 15)
        return WHAL_EINVAL;

    portBase = whal_Stm32wb0_Gpio_Dev.base + (port * GPIO_PORT_STRIDE);
    mask = 1UL << pin;

    if (set) {
        whal_Reg_Update(portBase, GPIO_ODR_REG, mask,
                        whal_SetBits(mask, pin, *value));
    } else {
        whal_Reg_Get(portBase, GPIO_IDR_REG, mask, pin, value);
    }
    return WHAL_SUCCESS;
}

whal_Error whal_Stm32wb0_Gpio_Get(whal_Gpio *gpioDev, size_t pin, size_t *value)
{
    return whal_Stm32wb0_Gpio_SetOrGet(gpioDev, pin, value, 0);
}

whal_Error whal_Stm32wb0_Gpio_Set(whal_Gpio *gpioDev, size_t pin, size_t value)
{
    return whal_Stm32wb0_Gpio_SetOrGet(gpioDev, pin, &value, 1);
}

#ifndef WHAL_CFG_STM32WB0_GPIO_DIRECT_API_MAPPING
const whal_GpioDriver whal_Stm32wb0_Gpio_Driver = {
    .Init   = whal_Stm32wb0_Gpio_Init,
    .Deinit = whal_Stm32wb0_Gpio_Deinit,
    .Get    = whal_Stm32wb0_Gpio_Get,
    .Set    = whal_Stm32wb0_Gpio_Set,
};
#endif /* !WHAL_CFG_STM32WB0_GPIO_DIRECT_API_MAPPING */
