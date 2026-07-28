/* eth_phy.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/eth_phy/eth_phy.h>
#include <wolfHAL/error.h>

whal_Error whal_EthPhy_Init(whal_EthPhy *phyDev)
{
    if (!phyDev || !phyDev->driver || !phyDev->driver->Init)
        return WHAL_EINVAL;
    return phyDev->driver->Init(phyDev);
}

whal_Error whal_EthPhy_Deinit(whal_EthPhy *phyDev)
{
    if (!phyDev || !phyDev->driver || !phyDev->driver->Deinit)
        return WHAL_EINVAL;
    return phyDev->driver->Deinit(phyDev);
}

whal_Error whal_EthPhy_GetLinkState(whal_EthPhy *phyDev, uint8_t *up,
                                     uint8_t *speed, uint8_t *duplex)
{
    if (!phyDev || !phyDev->driver || !phyDev->driver->GetLinkState ||
        !up || !speed || !duplex)
        return WHAL_EINVAL;
    return phyDev->driver->GetLinkState(phyDev, up, speed, duplex);
}
