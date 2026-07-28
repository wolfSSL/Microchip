/* sensor.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_SENSOR_H
#define WHAL_SENSOR_H

#include <wolfHAL/error.h>
#include <stdint.h>
#include <stddef.h>

/*
 * @file sensor.h
 * @brief Generic sensor abstraction and driver interface.
 *
 * Provides a bus-agnostic API for reading sensor data. Each sensor
 * driver implements the vtable and uses the appropriate bus (I2C, SPI,
 * etc.) internally. The Read function fills a driver-defined data
 * struct passed as a void pointer.
 */

typedef struct whal_Sensor whal_Sensor;

/*
 * @brief Driver vtable for sensor devices.
 */
typedef struct {
    /* Initialize the sensor hardware. */
    whal_Error (*Init)(whal_Sensor *dev);
    /* Deinitialize the sensor hardware. */
    whal_Error (*Deinit)(whal_Sensor *dev);
    /* Read sensor data into a driver-defined data struct. */
    whal_Error (*Read)(whal_Sensor *dev, void *data);
} whal_SensorDriver;

/*
 * @brief Sensor device instance tying a driver and configuration.
 */
struct whal_Sensor {
    const whal_SensorDriver *driver;
    void *cfg;
};

/*
 * @brief Initialize a sensor device and its driver.
 *
 * @param dev Pointer to the sensor instance to initialize.
 *
 * @retval WHAL_SUCCESS Driver-specific init completed.
 * @retval WHAL_EINVAL  Null pointer or driver rejected configuration.
 */
whal_Error whal_Sensor_Init(whal_Sensor *dev);
/*
 * @brief Deinitialize a sensor device and release resources.
 *
 * @param dev Pointer to the sensor instance to deinitialize.
 *
 * @retval WHAL_SUCCESS Driver-specific deinit completed.
 * @retval WHAL_EINVAL  Null pointer or driver refused to deinit.
 */
whal_Error whal_Sensor_Deinit(whal_Sensor *dev);
/*
 * @brief Read sensor data into a driver-defined data struct.
 *
 * Fetches a new sample from the hardware and fills the provided
 * data struct. The struct type is defined by each sensor driver.
 *
 * @param dev  Pointer to the sensor instance.
 * @param data Pointer to a driver-defined data struct to fill.
 *
 * @retval WHAL_SUCCESS Data read successfully.
 * @retval WHAL_EINVAL  Null pointer or driver error.
 */
whal_Error whal_Sensor_Read(whal_Sensor *dev, void *data);

#endif /* WHAL_SENSOR_H */
