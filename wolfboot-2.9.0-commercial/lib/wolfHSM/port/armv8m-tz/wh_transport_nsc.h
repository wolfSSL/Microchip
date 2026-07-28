/*
 * port/armv8m-tz/wh_transport_nsc.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*
 * Synchronous TrustZone NSC bridge transport for wolfHSM.
 *
 * The non-secure (client) side calls a single ARMv8-M Cortex-M
 * cmse_nonsecure_entry veneer (`wcs_wolfhsm_transmit`) provided by the
 * secure-side host. The veneer hands the request to the secure-side
 * server context, runs `wh_Server_HandleRequestMessage` once inline,
 * and returns the response in the same call. There is no polling,
 * notify counter, or async producer/consumer — Send delivers the
 * response, Recv just hands it back.
 *
 * The transport is target-agnostic across ARMv8-M TrustZone parts;
 * the target-specific NSC veneer is provided by the host.
 */

#ifndef WH_TRANSPORT_NSC_H_
#define WH_TRANSPORT_NSC_H_

#include "wolfhsm/wh_settings.h"

#ifdef WOLFHSM_CFG_PORT_ARMV8M_TZ_NSC

#include <stdint.h>
#include "wolfhsm/wh_comm.h"

#define WH_TRANSPORT_NSC_BUFFER_SIZE WH_COMM_MTU

/*
 * Non-secure (client) context. Owns the response buffer in NS .bss.
 * Not internally thread-safe.
 */
typedef struct {
    uint8_t  rsp_buf[WH_TRANSPORT_NSC_BUFFER_SIZE];
    uint16_t last_rsp_size;
    uint8_t  initialized;
    uint8_t  WH_PAD[5]; /* trailing slack */
} whTransportNscClientContext;

/* Empty config; Init accepts NULL since there is nothing to read. */
typedef struct {
    uint8_t WH_PAD[1];
} whTransportNscClientConfig;

/*
 * Secure-side server context. Populated by the NSC veneer per call:
 * before invoking `wh_Server_HandleRequestMessage` the host sets
 * req_buf/req_size/rsp_buf/rsp_capacity; after the dispatcher returns,
 * the host reads rsp_size to pass back to the non-secure caller.
 */
typedef struct {
    const uint8_t* req_buf;
    uint8_t*       rsp_buf;
    uint16_t       req_size;
    uint16_t       rsp_capacity;
    uint16_t       rsp_size;        /* set by Send, read by veneer */
    uint8_t        request_pending; /* set by veneer, cleared by Recv */
    uint8_t        WH_PAD[1];
} whTransportNscServerContext;

typedef struct {
    uint8_t WH_PAD[1];
} whTransportNscServerConfig;

int wh_TransportNsc_ClientInit(void* c, const void* cf,
                               whCommSetConnectedCb connectcb,
                               void*                connectcb_arg);
int wh_TransportNsc_ClientSend(void* c, uint16_t len, const void* data);
int wh_TransportNsc_ClientRecv(void* c, uint16_t* out_len, void* data);
int wh_TransportNsc_ClientCleanup(void* c);

int wh_TransportNsc_ServerInit(void* c, const void* cf,
                               whCommSetConnectedCb connectcb,
                               void*                connectcb_arg);
int wh_TransportNsc_ServerRecv(void* c, uint16_t* out_len, void* data);
int wh_TransportNsc_ServerSend(void* c, uint16_t len, const void* data);
int wh_TransportNsc_ServerCleanup(void* c);

#define WH_TRANSPORT_NSC_CLIENT_CB                 \
    {                                              \
        .Init    = wh_TransportNsc_ClientInit,     \
        .Send    = wh_TransportNsc_ClientSend,     \
        .Recv    = wh_TransportNsc_ClientRecv,     \
        .Cleanup = wh_TransportNsc_ClientCleanup,  \
    }

#define WH_TRANSPORT_NSC_SERVER_CB                 \
    {                                              \
        .Init    = wh_TransportNsc_ServerInit,     \
        .Recv    = wh_TransportNsc_ServerRecv,     \
        .Send    = wh_TransportNsc_ServerSend,     \
        .Cleanup = wh_TransportNsc_ServerCleanup,  \
    }

#endif /* WOLFHSM_CFG_PORT_ARMV8M_TZ_NSC */

#endif /* WH_TRANSPORT_NSC_H_ */
