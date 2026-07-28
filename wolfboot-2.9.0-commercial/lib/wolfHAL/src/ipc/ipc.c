/* ipc.c
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
#include <wolfHAL/ipc/ipc.h>
#include <wolfHAL/error.h>

inline whal_Error whal_Ipc_Init(whal_Ipc *ipcDev)
{
    if (!ipcDev || !ipcDev->driver || !ipcDev->driver->Init) {
        return WHAL_EINVAL;
    }

    return ipcDev->driver->Init(ipcDev);
}

inline whal_Error whal_Ipc_Deinit(whal_Ipc *ipcDev)
{
    if (!ipcDev || !ipcDev->driver || !ipcDev->driver->Deinit) {
        return WHAL_EINVAL;
    }

    return ipcDev->driver->Deinit(ipcDev);
}

inline whal_Error whal_Ipc_Send(whal_Ipc *ipcDev, const void *data, size_t dataSz)
{
    if (!ipcDev || !ipcDev->driver || !ipcDev->driver->Send || !data) {
        return WHAL_EINVAL;
    }

    return ipcDev->driver->Send(ipcDev, data, dataSz);
}

inline whal_Error whal_Ipc_Recv(whal_Ipc *ipcDev, void *data, size_t dataSz)
{
    if (!ipcDev || !ipcDev->driver || !ipcDev->driver->Recv || !data) {
        return WHAL_EINVAL;
    }

    return ipcDev->driver->Recv(ipcDev, data, dataSz);
}
