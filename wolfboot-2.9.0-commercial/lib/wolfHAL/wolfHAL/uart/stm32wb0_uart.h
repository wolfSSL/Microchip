/* stm32wb0_uart.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB0_UART_H
#define WHAL_STM32WB0_UART_H

/**
 * @file stm32wb0_uart.h
 * @brief STM32WB0 UART driver (alias for STM32WB UART).
 *
 * The STM32WB0 USART peripheral is register-compatible with the STM32WB
 * USART (FIFO USART variant: CR1.FIFOEN at bit 29, BRR at 0x0C, ISR at
 * 0x1C, RDR at 0x24, TDR at 0x28). This header re-exports the STM32WB
 * UART driver types and symbols under STM32WB0-specific names.
 */

#include <wolfHAL/uart/stm32wb_uart.h>

typedef whal_Stm32wb_Uart_Cfg whal_Stm32wb0_Uart_Cfg;

#define whal_Stm32wb0_Uart_Dev whal_Stm32wb_Uart_Dev

#ifndef WHAL_CFG_STM32WB0_UART_DIRECT_API_MAPPING
#define whal_Stm32wb0_Uart_Driver whal_Stm32wb_Uart_Driver
#define whal_Stm32wb0_Uart_Init   whal_Stm32wb_Uart_Init
#define whal_Stm32wb0_Uart_Deinit whal_Stm32wb_Uart_Deinit
#define whal_Stm32wb0_Uart_Send   whal_Stm32wb_Uart_Send
#define whal_Stm32wb0_Uart_Recv   whal_Stm32wb_Uart_Recv
#endif /* !WHAL_CFG_STM32WB0_UART_DIRECT_API_MAPPING */

/**
 * @brief Baud rate register helpers (re-exported from STM32WB).
 */
#define WHAL_STM32WB0_UART_BRR   WHAL_STM32WB_UART_BRR
#define WHAL_STM32WB0_LPUART_BRR WHAL_STM32WB_LPUART_BRR

/* Config initializer macro alias. The WB0 board.h supplies the body under
 * the WB0-prefixed name; the WB driver source consumes the WB name. */
#define WHAL_CFG_STM32WB_UART_DEV WHAL_CFG_STM32WB0_UART_DEV

#endif /* WHAL_STM32WB0_UART_H */
