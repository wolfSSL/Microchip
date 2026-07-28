/* gpio.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/gpio/gpio.h>
#include <wolfHAL/error.h>

inline whal_Error whal_Gpio_Init(whal_Gpio *gpioDev)
{
    if (!gpioDev)
        return WHAL_EINVAL;
    if (!gpioDev->driver || !gpioDev->driver->Init)
        return WHAL_ENOTSUP;

    return gpioDev->driver->Init(gpioDev);
}

inline whal_Error whal_Gpio_Deinit(whal_Gpio *gpioDev)
{
    if (!gpioDev)
        return WHAL_EINVAL;
    if (!gpioDev->driver || !gpioDev->driver->Deinit)
        return WHAL_ENOTSUP;

    return gpioDev->driver->Deinit(gpioDev);
}

inline whal_Error whal_Gpio_Get(whal_Gpio *gpioDev, size_t pin, size_t *value)
{
    if (!gpioDev || !value)
        return WHAL_EINVAL;
    if (!gpioDev->driver || !gpioDev->driver->Get)
        return WHAL_ENOTSUP;

    return gpioDev->driver->Get(gpioDev, pin, value);
}

inline whal_Error whal_Gpio_Set(whal_Gpio *gpioDev, size_t pin, size_t value)
{
    if (!gpioDev)
        return WHAL_EINVAL;
    if (!gpioDev->driver || !gpioDev->driver->Set)
        return WHAL_ENOTSUP;

    return gpioDev->driver->Set(gpioDev, pin, value);
}
