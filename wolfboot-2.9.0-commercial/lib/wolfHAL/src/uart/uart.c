/* uart.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include <wolfHAL/uart/uart.h>
#include <wolfHAL/error.h>

inline whal_Error whal_Uart_Init(whal_Uart *uartDev)
{
    if (!uartDev)
        return WHAL_EINVAL;
    if (!uartDev->driver || !uartDev->driver->Init)
        return WHAL_ENOTSUP;

    return uartDev->driver->Init(uartDev);
}

inline whal_Error whal_Uart_Deinit(whal_Uart *uartDev)
{
    if (!uartDev)
        return WHAL_EINVAL;
    if (!uartDev->driver || !uartDev->driver->Deinit)
        return WHAL_ENOTSUP;

    return uartDev->driver->Deinit(uartDev);
}

inline whal_Error whal_Uart_Send(whal_Uart *uartDev, const void *data, size_t dataSz)
{
    if (!uartDev || !data)
        return WHAL_EINVAL;
    if (!uartDev->driver || !uartDev->driver->Send)
        return WHAL_ENOTSUP;

    return uartDev->driver->Send(uartDev, data, dataSz);
}

inline whal_Error whal_Uart_Recv(whal_Uart *uartDev, void *data, size_t dataSz)
{
    if (!uartDev || !data)
        return WHAL_EINVAL;
    if (!uartDev->driver || !uartDev->driver->Recv)
        return WHAL_ENOTSUP;

    return uartDev->driver->Recv(uartDev, data, dataSz);
}

inline whal_Error whal_Uart_SendAsync(whal_Uart *uartDev, const void *data, size_t dataSz)
{
    if (!uartDev || !data)
        return WHAL_EINVAL;
    if (!uartDev->driver || !uartDev->driver->SendAsync)
        return WHAL_ENOTSUP;

    return uartDev->driver->SendAsync(uartDev, data, dataSz);
}

inline whal_Error whal_Uart_RecvAsync(whal_Uart *uartDev, void *data, size_t dataSz)
{
    if (!uartDev || !data)
        return WHAL_EINVAL;
    if (!uartDev->driver || !uartDev->driver->RecvAsync)
        return WHAL_ENOTSUP;

    return uartDev->driver->RecvAsync(uartDev, data, dataSz);
}
