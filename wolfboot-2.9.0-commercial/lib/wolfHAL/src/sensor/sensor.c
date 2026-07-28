/* sensor.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/sensor/sensor.h>
#include <wolfHAL/error.h>

inline whal_Error whal_Sensor_Init(whal_Sensor *dev)
{
    if (!dev || !dev->driver || !dev->driver->Init) {
        return WHAL_EINVAL;
    }

    return dev->driver->Init(dev);
}

inline whal_Error whal_Sensor_Deinit(whal_Sensor *dev)
{
    if (!dev || !dev->driver || !dev->driver->Deinit) {
        return WHAL_EINVAL;
    }

    return dev->driver->Deinit(dev);
}

inline whal_Error whal_Sensor_Read(whal_Sensor *dev, void *data)
{
    if (!dev || !dev->driver || !dev->driver->Read || !data) {
        return WHAL_EINVAL;
    }

    return dev->driver->Read(dev, data);
}
