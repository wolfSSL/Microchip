/* gpio.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_GPIO_H
#define WHAL_GPIO_H

#include <wolfHAL/error.h>
#include <stddef.h>

/*
 * @file gpio.h
 * @brief Generic GPIO abstraction and driver interface.
 */

typedef struct whal_Gpio whal_Gpio;

/*
 * @brief Driver vtable for GPIO devices.
 */
typedef struct {
    /* Initialize GPIO hardware and configured pins. */
    whal_Error (*Init)(whal_Gpio *gpioDev); 
    /* Deinitialize GPIO hardware. */
    whal_Error (*Deinit)(whal_Gpio *gpioDev); 
    /* Read a pin value. */
    whal_Error (*Get)(whal_Gpio *gpioDev, size_t pin, size_t *value); 
    /* Write a pin value. */
    whal_Error (*Set)(whal_Gpio *gpioDev, size_t pin, size_t value); 
} whal_GpioDriver;

/*
 * @brief GPIO device instance containing driver and configuration data.
 */
struct whal_Gpio {
    const size_t base;
    const whal_GpioDriver *driver;
    const void *cfg;
};

/*
 * @brief Initialize a GPIO device and its pins.
 *
 * @param gpioDev GPIO instance to initialize.
 *
 * @retval WHAL_SUCCESS Driver-specific init completed.
 * @retval WHAL_EINVAL   Null pointer.
 * @retval WHAL_ENOTSUP Operation not implemented by this driver.
 */
whal_Error whal_Gpio_Init(whal_Gpio *gpioDev);
/*
 * @brief Deinitialize a GPIO device.
 *
 * @param gpioDev GPIO instance to deinitialize.
 *
 * @retval WHAL_SUCCESS Driver-specific deinit completed.
 * @retval WHAL_EINVAL   Null pointer.
 * @retval WHAL_ENOTSUP Operation not implemented by this driver.
 */
whal_Error whal_Gpio_Deinit(whal_Gpio *gpioDev);
/*
 * @brief Read the state of a pin.
 *
 * @param gpioDev GPIO instance containing the pin.
 * @param pin     Pin index into the configured pin table.
 * @param value   Storage for the sampled pin value.
 *
 * @retval WHAL_SUCCESS Pin value stored in @p value.
 * @retval WHAL_EINVAL   Null pointer or bad pin.
 * @retval WHAL_ENOTSUP Operation not implemented by this driver.
 */
whal_Error whal_Gpio_Get(whal_Gpio *gpioDev, size_t pin, size_t *value);
/*
 * @brief Set the state of a pin.
 *
 * @param gpioDev GPIO instance containing the pin.
 * @param pin     Pin index into the configured pin table.
 * @param value   Output value to drive (typically 0 or 1).
 *
 * @retval WHAL_SUCCESS Pin updated.
 * @retval WHAL_EINVAL   Null pointer or bad pin.
 * @retval WHAL_ENOTSUP Operation not implemented by this driver.
 */
whal_Error whal_Gpio_Set(whal_Gpio *gpioDev, size_t pin, size_t value);

#endif /* WHAL_GPIO_H */
