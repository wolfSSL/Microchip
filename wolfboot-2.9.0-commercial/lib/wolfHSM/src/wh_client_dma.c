/*
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * src/wh_client_dma.c
 */

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#ifdef WOLFHSM_CFG_DMA

#include <stdint.h>
#include <string.h>
#include <stddef.h>

#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_client.h"


int wh_Client_DmaRegisterAllowList(whClientContext*          client,
                                   const whDmaAddrAllowList* allowlist)
{
    if (NULL == client) {
        return WH_ERROR_BADARGS;
    }

    /* A NULL allowlist clears any previously registered list (no enforcement),
     * symmetric with wh_Client_DmaRegisterCb(NULL). */
    client->dma.dmaAddrAllowList = allowlist;

    return WH_ERROR_OK;
}

int wh_Client_DmaRegisterCb(whClientContext* client, whClientDmaClientMemCb cb)
{
    /* No NULL check for cb, since it is optional and always NULL checked before
     * it is called */
    if (NULL == client) {
        return WH_ERROR_BADARGS;
    }

    client->dma.cb = cb;

    return WH_ERROR_OK;
}


/* Processes the given client address and translates it into a value that the
 * server will understand. This can be used to map the address into a known
 * location of shared memory. This also handles post translate operations
 * given the whDmaOper passed in. */
int wh_Client_DmaProcessClientAddress(whClientContext* client,
                                      uintptr_t        clientAddr,
                                      void** xformedCliAddr, size_t len,
                                      whDmaOper oper, whDmaFlags flags)
{
    int rc = WH_ERROR_OK;

    if (NULL == xformedCliAddr) {
        return WH_ERROR_BADARGS;
    }

    /* Perform user-supplied address transformation, cache manipulation, etc */
    if (NULL != client->dma.cb) {
        rc = client->dma.cb(client, clientAddr, xformedCliAddr, len, oper,
                            flags);
        if (rc != WH_ERROR_OK) {
            return rc;
        }
    }
    else {
        /* Transformed address defaults to raw client address */
        *xformedCliAddr = (void*)((uintptr_t)clientAddr);
    }

    /* if the client has a allowlist registered, check address against it */
    if (rc == WH_ERROR_OK && len > 0) {
        rc = wh_Dma_CheckMemOperAgainstAllowList(client->dma.dmaAddrAllowList,
                                                 oper, *xformedCliAddr, len);
    }
    return rc;
}

int wh_Client_DmaAsyncPre(whClientContext* client, whClientDmaAsyncBuf* buf,
                          uintptr_t clientAddr, uint64_t len, whDmaOper preOper,
                          uintptr_t* outXformedAddr)
{
    int       rc       = WH_ERROR_OK;
    uintptr_t addr     = 0;
    whDmaOper postOper = WH_DMA_OPER_CLIENT_READ_POST;

    if (client == NULL || buf == NULL || outXformedAddr == NULL) {
        return WH_ERROR_BADARGS;
    }

    /* The POST always matches the PRE's direction, so derive it here rather
     * than have every caller pass (and risk mismatching) both halves. */
    switch (preOper) {
        case WH_DMA_OPER_CLIENT_READ_PRE:
            postOper = WH_DMA_OPER_CLIENT_READ_POST;
            break;
        case WH_DMA_OPER_CLIENT_WRITE_PRE:
            postOper = WH_DMA_OPER_CLIENT_WRITE_POST;
            break;
        default:
            /* Caller passed a POST or otherwise invalid operation, not a PRE. */
            return WH_ERROR_BADARGS;
    }

    /* Clear the whole slot up front so a skipped or failed PRE leaves nothing
     * for the matching POST (run in the Response) to act on. */
    memset(buf, 0, sizeof(*buf));
    *outXformedAddr = 0;

    /* Nothing to map (e.g. an optional buffer that is absent): leave the slot
     * cleared and report success with a 0 transformed address. */
    if (len == 0) {
        return WH_ERROR_OK;
    }

    rc = wh_Client_DmaProcessClientAddress(client, clientAddr, (void**)&addr,
                                           (size_t)len, preOper,
                                           (whDmaFlags){0});
    if (rc == WH_ERROR_OK) {
        buf->xformedAddr = addr;
        buf->clientAddr  = clientAddr;
        buf->sz          = len;
        buf->postOper    = postOper;
        *outXformedAddr  = addr;
    }
    return rc;
}

int wh_Client_DmaAsyncPost(whClientContext* client, whClientDmaAsyncBuf* buf)
{
    int       rc;
    uintptr_t addr;

    if (client == NULL || buf == NULL) {
        return WH_ERROR_BADARGS;
    }
    /* Nothing stashed (PRE was skipped or the slot was already cleaned up):
     * a legitimate no-op, distinct from the NULL-arg misuse above. */
    if (buf->sz == 0) {
        return WH_ERROR_OK;
    }

    addr = buf->xformedAddr;
    rc   = wh_Client_DmaProcessClientAddress(client, buf->clientAddr,
                                             (void**)&addr, (size_t)buf->sz,
                                             buf->postOper, (whDmaFlags){0});
    /* Clear the whole slot even on failure so a later Response cannot re-run
     * the POST; the failure is returned to the caller. */
    memset(buf, 0, sizeof(*buf));
    return rc;
}
#endif /* WOLFHSM_CFG_DMA */
