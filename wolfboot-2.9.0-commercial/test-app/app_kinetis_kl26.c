/* app_kinetis_kl26.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
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
#include "target.h"
#include "wolfboot/wolfboot.h"

/* FRDM-KL26Z onboard RGB LED (all active-low common-anode):
 *   blue  = D5
 *   green = E31
 *   red   = E29
 */
#define LED_BLUE_GPIO   GPIOD
#define LED_BLUE_PORT   PORTD
#define LED_BLUE_CLOCK  kCLOCK_PortD
#define LED_BLUE_PIN    5U

#define LED_GREEN_GPIO  GPIOE
#define LED_GREEN_PORT  PORTE
#define LED_GREEN_CLOCK kCLOCK_PortE
#define LED_GREEN_PIN   31U

void main(void)
{
    gpio_pin_config_t led_config = { kGPIO_DigitalOutput, 1 };
    uint32_t version = wolfBoot_current_firmware_version();

    CLOCK_EnableClock(LED_BLUE_CLOCK);
    CLOCK_EnableClock(LED_GREEN_CLOCK);
    PORT_SetPinMux(LED_BLUE_PORT,  LED_BLUE_PIN,  kPORT_MuxAsGpio);
    PORT_SetPinMux(LED_GREEN_PORT, LED_GREEN_PIN, kPORT_MuxAsGpio);
    GPIO_PinInit(LED_BLUE_GPIO,  LED_BLUE_PIN,  &led_config);
    GPIO_PinInit(LED_GREEN_GPIO, LED_GREEN_PIN, &led_config);
    /* Pins are active-low */
    GPIO_SetPinsOutput(LED_BLUE_GPIO,  1U << LED_BLUE_PIN);
    GPIO_SetPinsOutput(LED_GREEN_GPIO, 1U << LED_GREEN_PIN);

    if (version == 1) {
        GPIO_ClearPinsOutput(LED_BLUE_GPIO,  1U << LED_BLUE_PIN);
    }
    else {
        GPIO_ClearPinsOutput(LED_GREEN_GPIO, 1U << LED_GREEN_PIN);
        wolfBoot_success();
    }

    while (1)
        __WFI();
}
