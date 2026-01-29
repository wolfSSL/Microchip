/* app_mcxa.c
 *
 * Test bare-metal boot-led-on application
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"

#include "wolfboot/wolfboot.h"
#include "target.h"

extern void hal_init(void);

/* init gpio for port 3 */
void gpio_portA_init(int pin)
{
    const port_pin_config_t GPIO_OUT_LED = {
        (uint16_t)kPORT_PullDisable,
        (uint16_t)kPORT_LowPullResistor,
        (uint16_t)kPORT_FastSlewRate,
        (uint16_t)kPORT_PassiveFilterDisable,
        (uint16_t)kPORT_OpenDrainDisable,
        (uint16_t)kPORT_LowDriveStrength,
        (uint16_t)kPORT_NormalDriveStrength,
        (uint16_t)kPORT_MuxAsGpio,
        (uint16_t)kPORT_UnlockRegister
    };

    const gpio_pin_config_t GPIO_OUT_LED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };


    /* Initialize GPIO functionality on pin */
    GPIO_PinInit(GPIOA, pin, &GPIO_OUT_LED_config);
    PORT_SetPinConfig(PORTA, pin, &GPIO_OUT_LED);
    GPIO_PinWrite(GPIOA, pin, 1);
}

void main(void)
{
    int i = 0;
    uint8_t* bootPart = (uint8_t*)WOLFBOOT_PARTITION_BOOT_ADDRESS;
    uint32_t bootVer = wolfBoot_get_blob_version(bootPart);
    /* Enable GPIO port clocks */
    CLOCK_EnableClock(kCLOCK_GpioA);
    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortC);
    gpio_portA_init(18);
    gpio_portA_init(19);
    gpio_portA_init(20);

    hal_init();
    if (bootVer == 1) {
        /* Blue LED ON, GPIOA port A pin 20 */
        GPIO_PinWrite(GPIOA, 20, 0);
        wolfBoot_update_trigger();
    }
    else {
        /* Green LED ON, GPIOA port A pin 19 */
        GPIO_PinWrite(GPIOA, 19, 0);
        /* mark boot successful */
        wolfBoot_success();
    }

    /* busy wait */
    while (1) {
        __WFI();
    }
}
