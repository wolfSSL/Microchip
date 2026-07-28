/* i2c.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/i2c/i2c.h>
#include <wolfHAL/error.h>

inline whal_Error whal_I2c_Init(whal_I2c *i2cDev)
{
    if (!i2cDev || !i2cDev->driver || !i2cDev->driver->Init) {
        return WHAL_EINVAL;
    }

    return i2cDev->driver->Init(i2cDev);
}

inline whal_Error whal_I2c_Deinit(whal_I2c *i2cDev)
{
    if (!i2cDev || !i2cDev->driver || !i2cDev->driver->Deinit) {
        return WHAL_EINVAL;
    }

    return i2cDev->driver->Deinit(i2cDev);
}

inline whal_Error whal_I2c_StartCom(whal_I2c *i2cDev, whal_I2c_ComCfg *comCfg)
{
    if (!i2cDev || !i2cDev->driver || !i2cDev->driver->StartCom || !comCfg) {
        return WHAL_EINVAL;
    }

    return i2cDev->driver->StartCom(i2cDev, comCfg);
}

inline whal_Error whal_I2c_EndCom(whal_I2c *i2cDev)
{
    if (!i2cDev || !i2cDev->driver || !i2cDev->driver->EndCom) {
        return WHAL_EINVAL;
    }

    return i2cDev->driver->EndCom(i2cDev);
}

inline whal_Error whal_I2c_Transfer(whal_I2c *i2cDev, whal_I2c_Msg *msgs,
                                    size_t numMsgs)
{
    if (!i2cDev || !i2cDev->driver || !i2cDev->driver->Transfer || !msgs) {
        return WHAL_EINVAL;
    }

    return i2cDev->driver->Transfer(i2cDev, msgs, numMsgs);
}
