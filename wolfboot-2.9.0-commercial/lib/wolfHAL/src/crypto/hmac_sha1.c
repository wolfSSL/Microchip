/* hmac_sha1.c
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

whal_Error whal_HmacSha1_Oneshot(whal_HmacSha1 *dev,
                                 const void *key, size_t keySz,
                                 const void *in, size_t inSz,
                                 void *digest, size_t digestSz)
{
    if (!dev || !dev->driver || !dev->driver->Oneshot)
        return WHAL_ENOTSUP;
    return dev->driver->Oneshot(dev, key, keySz, in, inSz, digest, digestSz);
}

whal_Error whal_HmacSha1_Start(whal_HmacSha1 *dev,
                               const void *key, size_t keySz)
{
    if (!dev || !dev->driver || !dev->driver->Start)
        return WHAL_ENOTSUP;
    return dev->driver->Start(dev, key, keySz);
}

whal_Error whal_HmacSha1_Process(whal_HmacSha1 *dev,
                                 const void *in, size_t inSz)
{
    if (!dev || !dev->driver || !dev->driver->Process)
        return WHAL_ENOTSUP;
    return dev->driver->Process(dev, in, inSz);
}

whal_Error whal_HmacSha1_Finalize(whal_HmacSha1 *dev,
                                  void *digest, size_t digestSz)
{
    if (!dev || !dev->driver || !dev->driver->Finalize)
        return WHAL_ENOTSUP;
    return dev->driver->Finalize(dev, digest, digestSz);
}
