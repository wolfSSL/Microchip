/* stm32h5_uart.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32H5_UART_H
#define WHAL_STM32H5_UART_H

/*
 * @file stm32h5_uart.h
 * @brief STM32H5 UART driver (alias for STM32WB UART).
 *
 * The STM32H5 USART peripheral is register-compatible with the STM32WB USART.
 * This header re-exports the STM32WB UART driver types and symbols under
 * STM32H5-specific names. The underlying implementation is shared.
 */

#include <wolfHAL/uart/stm32wb_uart.h>

typedef whal_Stm32wb_Uart_Cfg whal_Stm32h5_Uart_Cfg;

#define whal_Stm32h5_Uart_Dev whal_Stm32wb_Uart_Dev

/*
 * @brief Compute UART BRR register value.
 *
 * @param clk  Peripheral clock frequency in Hz.
 * @param baud Desired baud rate.
 */
#define WHAL_STM32H5_UART_BRR(clk, baud)   WHAL_STM32WB_UART_BRR(clk, baud)

/*
 * @brief Compute LPUART BRR register value.
 *
 * @param clk  Peripheral clock frequency in Hz.
 * @param baud Desired baud rate.
 */
#define WHAL_STM32H5_LPUART_BRR(clk, baud) WHAL_STM32WB_LPUART_BRR(clk, baud)

#ifndef WHAL_CFG_STM32H5_UART_DIRECT_API_MAPPING
#define whal_Stm32h5_Uart_Driver whal_Stm32wb_Uart_Driver
#define whal_Stm32h5_Uart_Init   whal_Stm32wb_Uart_Init
#define whal_Stm32h5_Uart_Deinit whal_Stm32wb_Uart_Deinit
#define whal_Stm32h5_Uart_Send   whal_Stm32wb_Uart_Send
#define whal_Stm32h5_Uart_Recv   whal_Stm32wb_Uart_Recv
#endif /* !WHAL_CFG_STM32H5_UART_DIRECT_API_MAPPING */

#endif /* WHAL_STM32H5_UART_H */
