/* eth.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/eth/eth.h>
#include <wolfHAL/error.h>

whal_Error whal_Eth_Init(whal_Eth *ethDev)
{
    if (!ethDev || !ethDev->driver || !ethDev->driver->Init)
        return WHAL_EINVAL;
    return ethDev->driver->Init(ethDev);
}

whal_Error whal_Eth_Deinit(whal_Eth *ethDev)
{
    if (!ethDev || !ethDev->driver || !ethDev->driver->Deinit)
        return WHAL_EINVAL;
    return ethDev->driver->Deinit(ethDev);
}

whal_Error whal_Eth_Start(whal_Eth *ethDev, uint8_t speed,
                                 uint8_t duplex)
{
    if (!ethDev || !ethDev->driver || !ethDev->driver->Start)
        return WHAL_EINVAL;
    return ethDev->driver->Start(ethDev, speed, duplex);
}

whal_Error whal_Eth_Stop(whal_Eth *ethDev)
{
    if (!ethDev || !ethDev->driver || !ethDev->driver->Stop)
        return WHAL_EINVAL;
    return ethDev->driver->Stop(ethDev);
}

whal_Error whal_Eth_Send(whal_Eth *ethDev, const void *frame,
                                 size_t len)
{
    if (!ethDev || !ethDev->driver || !ethDev->driver->Send || !frame)
        return WHAL_EINVAL;
    return ethDev->driver->Send(ethDev, frame, len);
}

whal_Error whal_Eth_Recv(whal_Eth *ethDev, void *frame, size_t *len)
{
    if (!ethDev || !ethDev->driver || !ethDev->driver->Recv || !frame || !len)
        return WHAL_EINVAL;
    return ethDev->driver->Recv(ethDev, frame, len);
}

whal_Error whal_Eth_MdioRead(whal_Eth *ethDev, uint8_t phyAddr,
                                     uint8_t reg, uint16_t *val)
{
    if (!ethDev || !ethDev->driver || !ethDev->driver->MdioRead || !val)
        return WHAL_EINVAL;
    return ethDev->driver->MdioRead(ethDev, phyAddr, reg, val);
}

whal_Error whal_Eth_MdioWrite(whal_Eth *ethDev, uint8_t phyAddr,
                                      uint8_t reg, uint16_t val)
{
    if (!ethDev || !ethDev->driver || !ethDev->driver->MdioWrite)
        return WHAL_EINVAL;
    return ethDev->driver->MdioWrite(ethDev, phyAddr, reg, val);
}
