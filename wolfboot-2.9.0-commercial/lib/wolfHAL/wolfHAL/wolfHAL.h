/* wolfHAL.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFHAL_H
#define WOLFHAL_H

/*
 * @file wolfHAL.h
 * @brief Convenience umbrella header that pulls in all core wolfHAL modules.
 */

#include <wolfHAL/error.h>
#include <wolfHAL/reg.h>

/* Pass WHAL_INTERNAL_DEV as the dev argument when the driver has direct
 * API mapping enabled AND is single-instance. The driver reads its dev
 * struct (e.g. whal_Stm32wb_Iwdg_Dev) from board.h and ignores whatever
 * gets passed in. */
#define WHAL_INTERNAL_DEV  ((void *)0)

/* Initializer for a dispatcher stub. Use when two drivers share the same
 * generic type on one board (e.g. on-chip flash + SPI NOR). The stub
 * carries only the vtable so the generic whal_<Type>_* dispatch can route
 * to the right driver; the driver itself reads .base and .cfg from its
 * own singleton in board.h, so they're left unset here. */
#define WHAL_DISPATCH_STUB(driver_ptr)  { .driver = (driver_ptr) }

#include <wolfHAL/gpio/gpio.h>
#include <wolfHAL/uart/uart.h>
#include <wolfHAL/flash/flash.h>
#include <wolfHAL/block/block.h>
#include <wolfHAL/rng/rng.h>
#include <wolfHAL/spi/spi.h>
#include <wolfHAL/i2c/i2c.h>
#include <wolfHAL/timer/timer.h>
#include <wolfHAL/ipc/ipc.h>
#include <wolfHAL/timeout.h>
#include <wolfHAL/crypto/crypto.h>
#include <wolfHAL/dma/dma.h>
#include <wolfHAL/irq/irq.h>
#include <wolfHAL/watchdog/watchdog.h>
#include <wolfHAL/eth/eth.h>
#include <wolfHAL/eth_phy/eth_phy.h>
#include <wolfHAL/sensor/sensor.h>

#endif /* WOLFHAL_H */
