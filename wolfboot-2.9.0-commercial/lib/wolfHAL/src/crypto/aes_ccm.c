/* aes_ccm.c
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

whal_Error whal_AesCcm_Oneshot(whal_AesCcm *dev, whal_Crypto_Dir dir,
                               const void *key, size_t keySz,
                               const void *nonce, size_t nonceSz,
                               const void *aad, size_t aadSz,
                               const void *in, void *out, size_t sz,
                               void *tag, size_t tagSz)
{
    if (!dev || !dev->driver || !dev->driver->Oneshot)
        return WHAL_ENOTSUP;
    return dev->driver->Oneshot(dev, dir, key, keySz, nonce, nonceSz,
                                aad, aadSz, in, out, sz, tag, tagSz);
}

whal_Error whal_AesCcm_Start(whal_AesCcm *dev, whal_Crypto_Dir dir,
                             const void *key, size_t keySz,
                             const void *nonce, size_t nonceSz,
                             const void *aad, size_t aadSz,
                             size_t tagSz, size_t sz)
{
    if (!dev || !dev->driver || !dev->driver->Start)
        return WHAL_ENOTSUP;
    return dev->driver->Start(dev, dir, key, keySz, nonce, nonceSz,
                              aad, aadSz, tagSz, sz);
}

whal_Error whal_AesCcm_Process(whal_AesCcm *dev,
                               const void *in, void *out, size_t sz)
{
    if (!dev || !dev->driver || !dev->driver->Process)
        return WHAL_ENOTSUP;
    return dev->driver->Process(dev, in, out, sz);
}

whal_Error whal_AesCcm_Finalize(whal_AesCcm *dev,
                                void *tag, size_t tagSz)
{
    if (!dev || !dev->driver || !dev->driver->Finalize)
        return WHAL_ENOTSUP;
    return dev->driver->Finalize(dev, tag, tagSz);
}
