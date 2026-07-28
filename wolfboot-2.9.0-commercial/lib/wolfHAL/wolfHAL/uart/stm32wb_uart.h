/* stm32wb_uart.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_STM32WB_UART_H
#define WHAL_STM32WB_UART_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/uart/uart.h>
#include <wolfHAL/timeout.h>
/*
 * @file stm32wb_uart.h
 * @brief STM32WB UART driver — polled variant.
 */

/*
 * @brief Compute UART BRR register value.
 */
#define WHAL_STM32WB_UART_BRR(clk, baud)   ((clk) / (baud))

/*
 * @brief Compute LPUART BRR register value.
 */
#define WHAL_STM32WB_LPUART_BRR(clk, baud) ((uint32_t)(((uint64_t)(clk) * 256) / (baud)))

/* Polled UART */

/*
 * @brief Polled UART configuration.
 */
typedef struct whal_Stm32wb_Uart_Cfg {
    uint32_t brr;
    whal_Timeout *timeout;
} whal_Stm32wb_Uart_Cfg;

/*
 * @brief Single-instance device struct. Defined in the driver TU
 * from the WHAL_CFG_STM32WB_UART_DEV initializer in board.h.
 */
#if defined(WHAL_CFG_STM32WB_UART_SINGLE_INSTANCE) || \
    defined(WHAL_CFG_STM32H5_UART_SINGLE_INSTANCE) || \
    defined(WHAL_CFG_STM32C0_UART_SINGLE_INSTANCE) || \
    defined(WHAL_CFG_STM32N6_UART_SINGLE_INSTANCE) || \
    defined(WHAL_CFG_STM32WBA_UART_SINGLE_INSTANCE) || \
    defined(WHAL_CFG_STM32WB0_UART_SINGLE_INSTANCE)
extern const whal_Uart whal_Stm32wb_Uart_Dev;
#endif

#if !defined(WHAL_CFG_STM32WB_UART_DIRECT_API_MAPPING) && \
    !defined(WHAL_CFG_STM32WB_UART_DMA_DIRECT_API_MAPPING) && \
    !defined(WHAL_CFG_STM32H5_UART_DIRECT_API_MAPPING) && \
    !defined(WHAL_CFG_STM32C0_UART_DIRECT_API_MAPPING) && \
    !defined(WHAL_CFG_STM32N6_UART_DIRECT_API_MAPPING) && \
    !defined(WHAL_CFG_STM32WBA_UART_DIRECT_API_MAPPING) && \
    !defined(WHAL_CFG_STM32WB0_UART_DIRECT_API_MAPPING)
/*
 * @brief Polled UART driver. Implements Init, Deinit, Send, Recv.
 */
extern const whal_UartDriver whal_Stm32wb_Uart_Driver;

/*
 * @brief Initialize the STM32WB UART peripheral.
 *
 * @param uartDev UART device instance.
 *
 * @retval WHAL_SUCCESS Initialization completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Stm32wb_Uart_Init(whal_Uart *uartDev);

/*
 * @brief Deinitialize the STM32WB UART peripheral.
 *
 * @param uartDev UART device instance.
 *
 * @retval WHAL_SUCCESS Deinit completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Stm32wb_Uart_Deinit(whal_Uart *uartDev);

/*
 * @brief Transmit a buffer over UART (blocking, polled).
 *
 * @param uartDev UART device instance.
 * @param data    Buffer to transmit.
 * @param dataSz  Number of bytes to transmit.
 *
 * @retval WHAL_SUCCESS All bytes transmitted.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Stm32wb_Uart_Send(whal_Uart *uartDev, const void *data, size_t dataSz);

/*
 * @brief Receive a buffer over UART (blocking, polled).
 *
 * @param uartDev UART device instance.
 * @param data    Receive buffer.
 * @param dataSz  Number of bytes to receive.
 *
 * @retval WHAL_SUCCESS All bytes received.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Stm32wb_Uart_Recv(whal_Uart *uartDev, void *data, size_t dataSz);
#endif /* !WHAL_CFG_UART_API_MAPPING */

#endif /* WHAL_STM32WB_UART_H */
