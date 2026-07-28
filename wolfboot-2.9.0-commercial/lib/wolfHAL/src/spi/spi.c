/* spi.c
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
#include <wolfHAL/spi/spi.h>
#include <wolfHAL/error.h>

inline whal_Error whal_Spi_Init(whal_Spi *spiDev)
{
    if (!spiDev)
        return WHAL_EINVAL;
    if (!spiDev->driver || !spiDev->driver->Init)
        return WHAL_ENOTSUP;

    return spiDev->driver->Init(spiDev);
}

inline whal_Error whal_Spi_Deinit(whal_Spi *spiDev)
{
    if (!spiDev)
        return WHAL_EINVAL;
    if (!spiDev->driver || !spiDev->driver->Deinit)
        return WHAL_ENOTSUP;

    return spiDev->driver->Deinit(spiDev);
}

inline whal_Error whal_Spi_StartCom(whal_Spi *spiDev, whal_Spi_ComCfg *comCfg)
{
    if (!spiDev || !comCfg)
        return WHAL_EINVAL;
    if (!spiDev->driver || !spiDev->driver->StartCom)
        return WHAL_ENOTSUP;

    return spiDev->driver->StartCom(spiDev, comCfg);
}

inline whal_Error whal_Spi_EndCom(whal_Spi *spiDev)
{
    if (!spiDev)
        return WHAL_EINVAL;
    if (!spiDev->driver || !spiDev->driver->EndCom)
        return WHAL_ENOTSUP;

    return spiDev->driver->EndCom(spiDev);
}

inline whal_Error whal_Spi_SendRecv(whal_Spi *spiDev, const void *tx, size_t txLen, void *rx, size_t rxLen)
{
    if (!spiDev)
        return WHAL_EINVAL;
    if (!spiDev->driver || !spiDev->driver->SendRecv)
        return WHAL_ENOTSUP;

    return spiDev->driver->SendRecv(spiDev, tx, txLen, rx, rxLen);
}
