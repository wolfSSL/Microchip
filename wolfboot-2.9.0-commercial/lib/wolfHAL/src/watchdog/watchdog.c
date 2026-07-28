/* watchdog.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/watchdog/watchdog.h>
#include <wolfHAL/error.h>

inline whal_Error whal_Watchdog_Init(whal_Watchdog *wdgDev)
{
    if (!wdgDev || !wdgDev->driver || !wdgDev->driver->Init) {
        return WHAL_EINVAL;
    }

    return wdgDev->driver->Init(wdgDev);
}

inline whal_Error whal_Watchdog_Deinit(whal_Watchdog *wdgDev)
{
    if (!wdgDev || !wdgDev->driver || !wdgDev->driver->Deinit) {
        return WHAL_EINVAL;
    }

    return wdgDev->driver->Deinit(wdgDev);
}

inline whal_Error whal_Watchdog_Refresh(whal_Watchdog *wdgDev)
{
    if (!wdgDev || !wdgDev->driver || !wdgDev->driver->Refresh) {
        return WHAL_EINVAL;
    }

    return wdgDev->driver->Refresh(wdgDev);
}
