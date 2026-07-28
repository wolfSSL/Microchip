/* dma.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/dma/dma.h>

inline whal_Error whal_Dma_Init(whal_Dma *dmaDev)
{
    if (!dmaDev || !dmaDev->driver || !dmaDev->driver->Init) {
        return WHAL_EINVAL;
    }

    return dmaDev->driver->Init(dmaDev);
}

inline whal_Error whal_Dma_Deinit(whal_Dma *dmaDev)
{
    if (!dmaDev || !dmaDev->driver || !dmaDev->driver->Deinit) {
        return WHAL_EINVAL;
    }

    return dmaDev->driver->Deinit(dmaDev);
}

inline whal_Error whal_Dma_Configure(whal_Dma *dmaDev, size_t ch,
                                     const void *chCfg)
{
    if (!dmaDev || !dmaDev->driver || !dmaDev->driver->Configure || !chCfg) {
        return WHAL_EINVAL;
    }

    return dmaDev->driver->Configure(dmaDev, ch, chCfg);
}

inline whal_Error whal_Dma_Start(whal_Dma *dmaDev, size_t ch)
{
    if (!dmaDev || !dmaDev->driver || !dmaDev->driver->Start) {
        return WHAL_EINVAL;
    }

    return dmaDev->driver->Start(dmaDev, ch);
}

inline whal_Error whal_Dma_Stop(whal_Dma *dmaDev, size_t ch)
{
    if (!dmaDev || !dmaDev->driver || !dmaDev->driver->Stop) {
        return WHAL_EINVAL;
    }

    return dmaDev->driver->Stop(dmaDev, ch);
}
