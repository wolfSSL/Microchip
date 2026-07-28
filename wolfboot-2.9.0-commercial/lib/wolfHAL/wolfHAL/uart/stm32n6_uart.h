/* stm32n6_uart.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32N6_UART_H
#define WHAL_STM32N6_UART_H

/**
 * @file stm32n6_uart.h
 * @brief STM32N6 UART driver (alias for STM32WB UART).
 *
 * The STM32N6 USART peripheral is register-compatible with the STM32WB USART
 * (CR1/CR2/CR3/BRR/GTPR/RTOR/RQR/ISR/ICR/RDR/TDR/PRESC at identical offsets).
 * This header re-exports under STM32N6-specific names.
 */

#include <wolfHAL/uart/stm32wb_uart.h>

typedef whal_Stm32wb_Uart_Cfg whal_Stm32n6_Uart_Cfg;

#define whal_Stm32n6_Uart_Dev whal_Stm32wb_Uart_Dev

#ifndef WHAL_CFG_STM32N6_UART_DIRECT_API_MAPPING
#define whal_Stm32n6_Uart_Driver whal_Stm32wb_Uart_Driver
#define whal_Stm32n6_Uart_Init   whal_Stm32wb_Uart_Init
#define whal_Stm32n6_Uart_Deinit whal_Stm32wb_Uart_Deinit
#define whal_Stm32n6_Uart_Send   whal_Stm32wb_Uart_Send
#define whal_Stm32n6_Uart_Recv   whal_Stm32wb_Uart_Recv
#endif /* !WHAL_CFG_STM32N6_UART_DIRECT_API_MAPPING */

#define WHAL_STM32N6_UART_BRR   WHAL_STM32WB_UART_BRR
#define WHAL_STM32N6_LPUART_BRR WHAL_STM32WB_LPUART_BRR

#endif /* WHAL_STM32N6_UART_H */
