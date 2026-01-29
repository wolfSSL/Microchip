/* va416x0.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef VA416X0_DEF_INCLUDED
#define VA416X0_DEF_INCLUDED

#include <stdint.h>
#include <stdbool.h>


/* HAL Configuration  */

/** Hardware version (define for VA416xx RevB) */
#define __MCU_HW_VER_REVB

/** Expected VREF voltage */
#define ADC_VREF         (3.3f)     /* units: volts */
#define ADC_VREF_MV      (3300ul)   /* units: millivolts */

/** SysTick setup */
#define SYSTICK_INTERVAL_MS (1u)    /* Interval in milliseconds between SysTick interrupts */
#define SYSTICK_PRIORITY    (7u)

/* remove I2C interrupts from build if not using */
#define __HAL_DISABLE_I2C0_MASTER
#define __HAL_DISABLE_I2C1_MASTER
#define __HAL_DISABLE_I2C2_MASTER
#define __HAL_DISABLE_I2C0_SLAVE
#define __HAL_DISABLE_I2C1_SLAVE
#define __HAL_DISABLE_I2C2_SLAVE

/* remove UART interrupts from build if not using */
#define __HAL_DISABLE_UART0
#define __HAL_DISABLE_UART1
#define __HAL_DISABLE_UART2

/** SPI setup */
#define __HAL_SPI_MODULE_ENABLED


/* Board specific configuration */
#ifndef XTAL
#define XTAL            (10000000UL)      /* 10 MHz xtal */
#endif
#ifndef EXTCLK
#define EXTCLK          (40000000UL)      /* EVK ext clk 40M */
#endif
#ifndef HBO
#define HBO             (18500000UL)      /* Internal clock */
#endif

/** Default pin IOCONFIG register. type: un_iocfg_reg_t - see va416xx_hal_ioconfig.h */
/** A pin's IOCONFIG is set to this by HAL_Iocfg_Init() if that pin is not in the cfg array */
#define DEFAULT_PIN_IOCFG   (IOCFG_REG_PULLDN) // internal pulldown enabled for input pin

/** Default pin direction (input/output) type: en_iocfg_dir_t - see va416xx_hal_ioconfig.h */
/** A pin's DIR is set to this by HAL_Iocfg_Init() if that pin is not in the cfg array */
#define DEFAULT_PIN_DIR     (en_iocfg_dir__input) // default pin input


/* PEB1-VA416XX-EVK */
/* DS2 - PG5 */
#define EVK_LED2_PORT    PORTG
#define EVK_LED2_BANK    VOR_GPIO->BANK[6]
#define EVK_LED2_PIN     (5)

/* DS4 - PF15 */
#define EVK_LED4_PORT    PORTF
#define EVK_LED4_BANK    VOR_GPIO->BANK[5]
#define EVK_LED4_PIN     (15)


/* AUX F-ram */
#define FRAM_AUX_SPI_BANK (1)
#define FRAM_AUX_SPI_CSN  (3)
#define FRAM_SIZE         (256 * 1024) /* 256KB */

/* ROM SPI info */
#define ROM_SPI_BANK  (3)
#define ROM_SPI_CSN   (0)


/* EDAC Configuration defaults */
#ifndef WOLFBOOT_EDAC_RAM_SCRUB
    #define WOLFBOOT_EDAC_RAM_SCRUB     1000
#endif
#ifndef WOLFBOOT_EDAC_ROM_SCRUB
    #define WOLFBOOT_EDAC_ROM_SCRUB     125
#endif


#endif /* VA416X0_DEF_INCLUDED */
