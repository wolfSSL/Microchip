/* stm32f3_uart.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef WHAL_CFG_STM32F3_UART_DIRECT_API_MAPPING
#define WHAL_CFG_STM32F0_UART_DIRECT_API_MAPPING
#endif
#ifdef WHAL_CFG_STM32F3_UART_SINGLE_INSTANCE
#define WHAL_CFG_STM32F0_UART_SINGLE_INSTANCE
#endif
#include "stm32f0_uart.c"
