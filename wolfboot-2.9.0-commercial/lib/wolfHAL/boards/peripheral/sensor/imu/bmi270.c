/* bmi270.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "bmi270.h"
#include <wolfHAL/sensor/imu/bmi270_sensor.h>
#include "board.h"

/*
 * Bosch BMI270 — 6-axis IMU (accelerometer + gyroscope)
 *
 * - I2C address: 0x68 (SDO low)
 * - Standard mode (100 kHz) or Fast mode (400 kHz)
 * - Requires 8192-byte config blob upload during init
 *
 * The config blob is not bundled with wolfHAL. Obtain it from the Bosch
 * Sensortec BMI270_SensorAPI repository and provide it from your board.h:
 *
 *     extern const uint8_t whal_bmi270_config_data[];
 *     #define WHAL_BMI270_CONFIG_DATA_SZ 8192
 *
 * with a matching definition compiled into your application.
 */

whal_I2c_ComCfg g_bmi270ComCfg = {
    .freq = 400000, /* 400 kHz fast mode */
    .addr = WHAL_BMI270_ADDR_LOW,
    .addrSz = 7,
};

whal_Sensor g_whalBmi270 = {
    .driver = &whal_Bmi270_Driver,
    .cfg = &(whal_Bmi270_Cfg) {
        .i2c = BOARD_I2C_DEV,
        .comCfg = &g_bmi270ComCfg,
        .configData = whal_bmi270_config_data,
        .configDataSz = WHAL_BMI270_CONFIG_DATA_SZ,
        .DelayMs = Board_WaitMs,
    },
};
