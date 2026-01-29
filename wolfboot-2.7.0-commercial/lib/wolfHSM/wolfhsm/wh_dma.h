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
 * wolfhsm/wh_dma.h
 *
 * Common DMA API for client and server
 */

#include <stdint.h>
#include <stddef.h>

#ifndef WOLFHSM_WH_COMMON_DMA_H_
#define WOLFHSM_WH_COMMON_DMA_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

/* This is the same for both client and server, the client cares about when the
 * server is about to access its memory and the server cares about when it is
 * about to access the clients memory. */
typedef enum {
    /* Indicates server is about to read from client memory */
    WH_DMA_OPER_CLIENT_READ_PRE = 0,
    /* Indicates server has just read from client memory */
    WH_DMA_OPER_CLIENT_READ_POST = 1,
    /* Indicates server is about to write to client memory */
    WH_DMA_OPER_CLIENT_WRITE_PRE = 2,
    /* Indicates server has just written to client memory */
    WH_DMA_OPER_CLIENT_WRITE_POST = 3,
} whDmaOper;

#ifdef WOLFHSM_CFG_DMA_CUSTOM_CLIENT_COPY
typedef enum {
    WH_DMA_COPY_OPER_CLIENT_READ  = 0,
    WH_DMA_COPY_OPER_CLIENT_WRITE = 1,
} whDmaCopyOper;
#endif /* WOLFHSM_CFG_DMA_CUSTOM_CLIENT_COPY */

/* Flags embedded in request/response structs provided by client */
typedef struct {
    uint8_t cacheForceInvalidate : 1;
    uint8_t : 7;
} whDmaFlags;

/* Common DMA address entry within the allowed tables */
typedef struct {
    void*  addr;
    size_t size;
} whDmaAddr;
typedef whDmaAddr whDmaAddrList[WOLFHSM_CFG_DMAADDR_COUNT];

/* Holds allowable client read/write addresses */
typedef struct {
    whDmaAddrList readList;  /* Allowed client read addresses */
    whDmaAddrList writeList; /* Allowed client write addresses */
} whDmaAddrAllowList;

int wh_Dma_CheckMemOperAgainstAllowList(const whDmaAddrAllowList* allowlist,
                                        whDmaOper oper, void* addr, size_t len);

#endif /* WOLFHSM_WH_COMMON_DMA_H_ */
