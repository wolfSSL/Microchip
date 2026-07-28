/* crypto.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/crypto/crypto.h>

whal_Error whal_Crypto_Init(whal_Crypto *dev)
{
    if (!dev)
        return WHAL_EINVAL;
    if (!dev->driver || !dev->driver->Init)
        return WHAL_ENOTSUP;
    return dev->driver->Init(dev);
}

whal_Error whal_Crypto_Deinit(whal_Crypto *dev)
{
    if (!dev)
        return WHAL_EINVAL;
    if (!dev->driver || !dev->driver->Deinit)
        return WHAL_ENOTSUP;
    return dev->driver->Deinit(dev);
}
