/* block.c
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
#include <wolfHAL/block/block.h>
#include <wolfHAL/error.h>

inline whal_Error whal_Block_Init(whal_Block *blockDev)
{
    if (!blockDev)
        return WHAL_EINVAL;
    if (!blockDev->driver || !blockDev->driver->Init)
        return WHAL_ENOTSUP;

    return blockDev->driver->Init(blockDev);
}

inline whal_Error whal_Block_Deinit(whal_Block *blockDev)
{
    if (!blockDev)
        return WHAL_EINVAL;
    if (!blockDev->driver || !blockDev->driver->Deinit)
        return WHAL_ENOTSUP;

    return blockDev->driver->Deinit(blockDev);
}

inline whal_Error whal_Block_Read(whal_Block *blockDev, uint32_t block,
                                  void *data, uint32_t blockCount)
{
    if (!blockDev || !data)
        return WHAL_EINVAL;
    if (!blockDev->driver || !blockDev->driver->Read)
        return WHAL_ENOTSUP;

    return blockDev->driver->Read(blockDev, block, data, blockCount);
}

inline whal_Error whal_Block_Write(whal_Block *blockDev, uint32_t block,
                                   const void *data, uint32_t blockCount)
{
    if (!blockDev || !data)
        return WHAL_EINVAL;
    if (!blockDev->driver || !blockDev->driver->Write)
        return WHAL_ENOTSUP;

    return blockDev->driver->Write(blockDev, block, data, blockCount);
}

inline whal_Error whal_Block_Erase(whal_Block *blockDev, uint32_t block,
                                   uint32_t blockCount)
{
    if (!blockDev)
        return WHAL_EINVAL;
    if (!blockDev->driver || !blockDev->driver->Erase)
        return WHAL_ENOTSUP;

    return blockDev->driver->Erase(blockDev, block, blockCount);
}
