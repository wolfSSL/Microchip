/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
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
    if (NULL == client || NULL == allowlist) {
        return WH_ERROR_BADARGS;
    }

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
#endif /* WOLFHSM_CFG_DMA */
