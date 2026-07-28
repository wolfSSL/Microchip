/* fwtpm_io.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _FWTPM_IO_H_
#define _FWTPM_IO_H_

#ifdef WOLFTPM_FWTPM

#include <wolftpm/fwtpm/fwtpm.h>

#ifdef __cplusplus
    extern "C" {
#endif

/* SWTPM TCP protocol commands (from TpmTcpProtocol.h) */
#define FWTPM_TCP_SIGNAL_POWER_ON       1
#define FWTPM_TCP_SIGNAL_POWER_OFF      2
#define FWTPM_TCP_SIGNAL_PHYS_PRES_ON   3
#define FWTPM_TCP_SIGNAL_PHYS_PRES_OFF  4
#define FWTPM_TCP_SIGNAL_HASH_START     5
#define FWTPM_TCP_SIGNAL_HASH_DATA      6
#define FWTPM_TCP_SIGNAL_HASH_END       9
#define FWTPM_TCP_SEND_COMMAND          8
#define FWTPM_TCP_SIGNAL_NV_ON         11
#define FWTPM_TCP_SIGNAL_CANCEL_ON     13
#define FWTPM_TCP_SIGNAL_CANCEL_OFF    14
#define FWTPM_TCP_SIGNAL_RESET         17
#define FWTPM_TCP_SESSION_END          20
#define FWTPM_TCP_STOP                 21

/* FWTPM_IO_CTX is defined in fwtpm.h (included above) */

#ifndef WOLFTPM_FWTPM_TIS
/*!
    \ingroup wolfTPM_fwTPM
    \brief Register a custom socket-transport HAL. Call before
    FWTPM_IO_Init to replace the default POSIX socket implementation
    (e.g. for a mocked or in-process transport).

    \return 0 on success
    \return BAD_FUNC_ARG if ctx or hal is NULL

    \param ctx pointer to an initialized FWTPM_CTX
    \param hal pointer to a caller-populated FWTPM_IO_HAL

    \sa FWTPM_IO_Init
*/
WOLFTPM_API int FWTPM_IO_SetHAL(FWTPM_CTX* ctx, FWTPM_IO_HAL* hal);
#endif

/*!
    \ingroup wolfTPM_fwTPM
    \brief Initialize the fwTPM transport. When no HAL has been
    registered, binds default TCP sockets on ctx->cmdPort and
    ctx->platPort.

    \return 0 on success
    \return negative on socket/bind error

    \param ctx pointer to an initialized FWTPM_CTX

    \sa FWTPM_IO_Cleanup
    \sa FWTPM_IO_ServerLoop
*/
WOLFTPM_API int FWTPM_IO_Init(FWTPM_CTX* ctx);

/*!
    \ingroup wolfTPM_fwTPM
    \brief Release transport resources (close sockets / release HAL).

    \param ctx pointer to an initialized FWTPM_CTX

    \sa FWTPM_IO_Init
*/
WOLFTPM_API void FWTPM_IO_Cleanup(FWTPM_CTX* ctx);

/*!
    \ingroup wolfTPM_fwTPM
    \brief Run the main fwTPM server loop. Blocks until ctx->running
    is cleared (by FWTPM_IO_RequestStop or a signal handler).

    \return 0 on clean shutdown
    \return negative on fatal transport error

    \param ctx pointer to an initialized FWTPM_CTX

    \sa FWTPM_IO_RequestStop
*/
WOLFTPM_API int FWTPM_IO_ServerLoop(FWTPM_CTX* ctx);

/*!
    \ingroup wolfTPM_fwTPM
    \brief Request the server loop to exit. Async-signal-safe: only
    sets a volatile sig_atomic_t flag that the loop polls, so this is
    safe to call from a signal handler.

    \sa FWTPM_IO_ServerLoop
*/
WOLFTPM_API void FWTPM_IO_RequestStop(void);

/*!
    \ingroup wolfTPM_fwTPM
    \brief Check whether an async stop has been requested via
    FWTPM_IO_RequestStop(). Used by transport loops (TIS, socket)
    to detect signal-driven shutdown.

    \return 1 if stop was requested, 0 otherwise

    \sa FWTPM_IO_RequestStop
*/
WOLFTPM_API int FWTPM_IO_IsStopRequested(void);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* WOLFTPM_FWTPM */

#endif /* _FWTPM_IO_H_ */
