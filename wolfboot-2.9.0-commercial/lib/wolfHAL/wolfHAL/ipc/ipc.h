/* ipc.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_IPC_H
#define WHAL_IPC_H

#include <stdint.h>
#include <stddef.h>
#include <wolfHAL/error.h>

/*
 * @file ipc.h
 * @brief Generic IPC abstraction and driver interface.
 */

typedef struct whal_Ipc whal_Ipc;

/*
 * @brief Driver vtable for IPC devices.
 */
typedef struct {
    /* Initialize the IPC hardware. */
    whal_Error (*Init)(whal_Ipc *ipcDev);
    /* Deinitialize the IPC hardware. */
    whal_Error (*Deinit)(whal_Ipc *ipcDev);
    /* Transmit a buffer. */
    whal_Error (*Send)(whal_Ipc *ipcDev, const void *data, size_t dataSz);
    /* Receive into a buffer. */
    whal_Error (*Recv)(whal_Ipc *ipcDev, void *data, size_t dataSz);
} whal_IpcDriver;

/*
 * @brief IPC device instance with a base address, driver vtable, and platform-specific cfg.
 */
struct whal_Ipc {
    const size_t base;
    const whal_IpcDriver *driver;
    void *cfg;
};

/*
 * @brief Initializes an IPC device and its driver.
 *
 * @param ipcDev Pointer to the IPC instance to initialize.
 *
 * @retval WHAL_SUCCESS Driver-specific init completed.
 * @retval WHAL_EINVAL  Null pointer or driver rejected configuration.
 */
whal_Error whal_Ipc_Init(whal_Ipc *ipcDev);

/*
 * @brief Deinitializes an IPC device and releases resources.
 *
 * @param ipcDev Pointer to the IPC instance to deinitialize.
 *
 * @retval WHAL_SUCCESS Driver-specific deinit completed.
 * @retval WHAL_EINVAL  Null pointer or driver refused to deinit.
 */
whal_Error whal_Ipc_Deinit(whal_Ipc *ipcDev);

/*
 * @brief Sends a buffer over the IPC channel.
 *
 * @param ipcDev Pointer to the IPC instance.
 * @param data   Buffer to transmit.
 * @param dataSz Number of bytes to send.
 *
 * @retval WHAL_SUCCESS Buffer was queued or transmitted.
 * @retval WHAL_EINVAL  Null pointer or driver failed to send.
 */
whal_Error whal_Ipc_Send(whal_Ipc *ipcDev, const void *data, size_t dataSz);

/*
 * @brief Receives data from the IPC channel into a buffer.
 *
 * @param ipcDev Pointer to the IPC instance.
 * @param data   Destination buffer.
 * @param dataSz Maximum number of bytes to read.
 *
 * @retval WHAL_SUCCESS Buffer was filled or receive started.
 * @retval WHAL_EINVAL  Null pointer or driver failed to receive.
 */
whal_Error whal_Ipc_Recv(whal_Ipc *ipcDev, void *data, size_t dataSz);

#endif /* WHAL_IPC_H */
