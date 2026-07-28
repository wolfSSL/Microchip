/* reg.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/reg.h>

whal_Error whal_Reg_ReadPoll(size_t base, size_t offset,
                             size_t mask, size_t value,
                             whal_Timeout *timeout)
{
#ifdef WHAL_CFG_NO_TIMEOUT
    (void)(timeout);
#endif
    WHAL_TIMEOUT_START(timeout);
    while ((whal_Reg_Read(base, offset) & mask) != value) {
        if (WHAL_TIMEOUT_EXPIRED(timeout))
            return WHAL_ETIMEOUT;
    }
    return WHAL_SUCCESS;
}
