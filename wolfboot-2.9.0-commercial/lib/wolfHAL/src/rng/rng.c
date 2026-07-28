/* rng.c
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
#include <wolfHAL/rng/rng.h>
#include <wolfHAL/error.h>

inline whal_Error whal_Rng_Init(whal_Rng *rngDev)
{
    if (!rngDev)
        return WHAL_EINVAL;
    if (!rngDev->driver || !rngDev->driver->Init)
        return WHAL_ENOTSUP;

    return rngDev->driver->Init(rngDev);
}

inline whal_Error whal_Rng_Deinit(whal_Rng *rngDev)
{
    if (!rngDev)
        return WHAL_EINVAL;
    if (!rngDev->driver || !rngDev->driver->Deinit)
        return WHAL_ENOTSUP;

    return rngDev->driver->Deinit(rngDev);
}

inline whal_Error whal_Rng_Generate(whal_Rng *rngDev, void *rngData, size_t rngDataSz)
{
    if (!rngDev || !rngData)
        return WHAL_EINVAL;
    if (!rngDev->driver || !rngDev->driver->Generate)
        return WHAL_ENOTSUP;

    return rngDev->driver->Generate(rngDev, rngData, rngDataSz);
}
