/* aes_gmac.c
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

whal_Error whal_AesGmac_Oneshot(whal_AesGmac *dev,
                                const void *key, size_t keySz,
                                const void *iv, size_t ivSz,
                                const void *aad, size_t aadSz,
                                void *tag, size_t tagSz)
{
    if (!dev || !dev->driver || !dev->driver->Oneshot)
        return WHAL_ENOTSUP;
    return dev->driver->Oneshot(dev, key, keySz, iv, ivSz,
                                aad, aadSz, tag, tagSz);
}
