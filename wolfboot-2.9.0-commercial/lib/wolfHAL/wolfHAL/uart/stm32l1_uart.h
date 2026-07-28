/* stm32l1_uart.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32L1_UART_H
#define WHAL_STM32L1_UART_H

/*
 * @file stm32l1_uart.h
 * @brief STM32L1 UART driver (alias for STM32F4 UART).
 *
 * The STM32L1 USART uses the same USARTv1 register layout as the STM32F4
 * (SR/DR at 0x00/0x04, BRR at 0x08, CR1 at 0x0C).
 */

#include <wolfHAL/uart/stm32f4_uart.h>

typedef whal_Stm32f4_Uart_Cfg whal_Stm32l1_Uart_Cfg;

#define WHAL_STM32L1_UART_BRR WHAL_STM32F4_UART_BRR

#ifndef WHAL_CFG_STM32L1_UART_DIRECT_API_MAPPING
#define whal_Stm32l1_Uart_Driver    whal_Stm32f4_Uart_Driver
#define whal_Stm32l1_Uart_Init      whal_Stm32f4_Uart_Init
#define whal_Stm32l1_Uart_Deinit    whal_Stm32f4_Uart_Deinit
#define whal_Stm32l1_Uart_Send      whal_Stm32f4_Uart_Send
#define whal_Stm32l1_Uart_Recv      whal_Stm32f4_Uart_Recv
#define whal_Stm32l1_Uart_SendAsync whal_Stm32f4_Uart_SendAsync
#define whal_Stm32l1_Uart_RecvAsync whal_Stm32f4_Uart_RecvAsync
#endif /* !WHAL_CFG_STM32L1_UART_DIRECT_API_MAPPING */

#endif /* WHAL_STM32L1_UART_H */
