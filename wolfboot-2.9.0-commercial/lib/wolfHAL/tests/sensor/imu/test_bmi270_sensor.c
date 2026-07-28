/* test_bmi270_sensor.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/wolfHAL.h>
#include <wolfHAL/sensor/sensor.h>
#include <wolfHAL/sensor/imu/bmi270_sensor.h>
#include "board.h"
#include "peripheral.h"
#include "test.h"

/*
 * BMI270 IMU test suite.
 *
 * Requires a BMI270 connected to the board's I2C bus.
 * The board must provide g_whalBmi270 via the peripheral config.
 */

static void Test_Bmi270_Read(void)
{
    whal_Bmi270_Data data = {0};

    WHAL_ASSERT_EQ(whal_Sensor_Read(
                       g_peripheralSensor[PERIPHERAL_SENSOR_BMI270].dev,
                       &data),
                   WHAL_SUCCESS);

    /* At rest, at least one accel axis should be non-zero (gravity) */
    WHAL_ASSERT_NEQ(data.accelX | data.accelY | data.accelZ, 0);
}

static void Test_Bmi270_ReadMultiple(void)
{
    whal_Bmi270_Data data1 = {0};
    whal_Bmi270_Data data2 = {0};

    WHAL_ASSERT_EQ(whal_Sensor_Read(
                       g_peripheralSensor[PERIPHERAL_SENSOR_BMI270].dev,
                       &data1),
                   WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Sensor_Read(
                       g_peripheralSensor[PERIPHERAL_SENSOR_BMI270].dev,
                       &data2),
                   WHAL_SUCCESS);

    /* Both reads should have non-zero accel (gravity) */
    WHAL_ASSERT_NEQ(data1.accelX | data1.accelY | data1.accelZ, 0);
    WHAL_ASSERT_NEQ(data2.accelX | data2.accelY | data2.accelZ, 0);
}

void whal_Test_Bmi270_Sensor(void)
{
    WHAL_TEST_SUITE_START("bmi270");
    WHAL_TEST(Test_Bmi270_Read);
    WHAL_TEST(Test_Bmi270_ReadMultiple);
    WHAL_TEST_SUITE_END();
}
