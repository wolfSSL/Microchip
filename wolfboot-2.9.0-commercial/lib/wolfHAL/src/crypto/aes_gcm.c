/* aes_gcm.c
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

whal_Error whal_AesGcm_Oneshot(whal_AesGcm *dev, whal_Crypto_Dir dir,
                               const void *key, size_t keySz,
                               const void *iv, size_t ivSz,
                               const void *aad, size_t aadSz,
                               const void *in, void *out, size_t sz,
                               void *tag, size_t tagSz)
{
    if (!dev || !dev->driver || !dev->driver->Oneshot)
        return WHAL_ENOTSUP;
    return dev->driver->Oneshot(dev, dir, key, keySz, iv, ivSz,
                                aad, aadSz, in, out, sz, tag, tagSz);
}

whal_Error whal_AesGcm_Start(whal_AesGcm *dev, whal_Crypto_Dir dir,
                             const void *key, size_t keySz,
                             const void *iv, size_t ivSz,
                             const void *aad, size_t aadSz)
{
    if (!dev || !dev->driver || !dev->driver->Start)
        return WHAL_ENOTSUP;
    return dev->driver->Start(dev, dir, key, keySz, iv, ivSz, aad, aadSz);
}

whal_Error whal_AesGcm_Process(whal_AesGcm *dev,
                               const void *in, void *out, size_t sz)
{
    if (!dev || !dev->driver || !dev->driver->Process)
        return WHAL_ENOTSUP;
    return dev->driver->Process(dev, in, out, sz);
}

whal_Error whal_AesGcm_Finalize(whal_AesGcm *dev,
                                void *tag, size_t tagSz)
{
    if (!dev || !dev->driver || !dev->driver->Finalize)
        return WHAL_ENOTSUP;
    return dev->driver->Finalize(dev, tag, tagSz);
}
