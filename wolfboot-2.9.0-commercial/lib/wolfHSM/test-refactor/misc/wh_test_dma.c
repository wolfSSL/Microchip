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
 * test-refactor/misc/wh_test_dma.c
 *
 * DMA allow-list boundary checks. Pure unit test of
 * wh_Dma_CheckMemOperAgainstAllowList: builds in-memory allow
 * lists, exercises basic accept/reject, end-address overflow,
 * and the write-list path. Needs no client, server, or port
 * fixture.
 */

#include "wolfhsm/wh_settings.h"

#ifdef WOLFHSM_CFG_DMA

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_dma.h"

#include "wh_test_common.h"
#include "wh_test_list.h"


static int _whTest_DmaAllowListBasic(void)
{
    int                rc;
    whDmaAddrAllowList allowList;

    memset(&allowList, 0, sizeof(allowList));

    allowList.readList[0].addr = (void*)((uintptr_t)0x10000);
    allowList.readList[0].size = 0x10000;

    rc = wh_Dma_CheckMemOperAgainstAllowList(
        &allowList, WH_DMA_OPER_CLIENT_READ_PRE,
        (void*)((uintptr_t)0x10000), 0x1000);
    WH_TEST_ASSERT_RETURN(rc == WH_ERROR_OK);

    rc = wh_Dma_CheckMemOperAgainstAllowList(
        &allowList, WH_DMA_OPER_CLIENT_READ_PRE,
        (void*)((uintptr_t)0x30000), 0x1000);
    WH_TEST_ASSERT_RETURN(rc == WH_ERROR_ACCESS);

    rc = wh_Dma_CheckMemOperAgainstAllowList(
        &allowList, WH_DMA_OPER_CLIENT_READ_PRE,
        (void*)((uintptr_t)0x10000), 0);
    WH_TEST_ASSERT_RETURN(rc == WH_ERROR_BADARGS);

    rc = wh_Dma_CheckMemOperAgainstAllowList(
        NULL, WH_DMA_OPER_CLIENT_READ_PRE,
        (void*)((uintptr_t)0x10000), 0x1000);
    WH_TEST_ASSERT_RETURN(rc == WH_ERROR_OK);

    return WH_ERROR_OK;
}


static int _whTest_DmaAllowListOverflow(void)
{
    int                rc;
    whDmaAddrAllowList allowList;
    uintptr_t          maliciousAddr;
    size_t             maliciousSize;

    memset(&allowList, 0, sizeof(allowList));

    /*
     * Allow list region: [0x10000, 0x20000)
     * Craft a request whose endAddr wraps around to land inside
     * the allow list. Without overflow protection the start/end
     * comparisons both pass and incorrectly grant access to the
     * top of the address space.
     */
    allowList.readList[0].addr = (void*)((uintptr_t)0x10000);
    allowList.readList[0].size = 0x10000;

    maliciousAddr = UINTPTR_MAX - 0xFF;
    maliciousSize = 0x20100;

    rc = wh_Dma_CheckMemOperAgainstAllowList(
        &allowList, WH_DMA_OPER_CLIENT_READ_PRE,
        (void*)maliciousAddr, maliciousSize);
    WH_TEST_ASSERT_RETURN(rc != WH_ERROR_OK);

    /* addr=UINTPTR_MAX, size=1 -> end wraps to 0 */
    rc = wh_Dma_CheckMemOperAgainstAllowList(
        &allowList, WH_DMA_OPER_CLIENT_READ_PRE,
        (void*)UINTPTR_MAX, 1);
    WH_TEST_ASSERT_RETURN(rc != WH_ERROR_OK);

    /* addr=1, size=UINTPTR_MAX -> end wraps to 0 */
    rc = wh_Dma_CheckMemOperAgainstAllowList(
        &allowList, WH_DMA_OPER_CLIENT_READ_PRE,
        (void*)((uintptr_t)1), (size_t)UINTPTR_MAX);
    WH_TEST_ASSERT_RETURN(rc != WH_ERROR_OK);

    /* Same overflow vector against the write list. */
    memset(&allowList, 0, sizeof(allowList));
    allowList.writeList[0].addr = (void*)((uintptr_t)0x10000);
    allowList.writeList[0].size = 0x10000;

    rc = wh_Dma_CheckMemOperAgainstAllowList(
        &allowList, WH_DMA_OPER_CLIENT_WRITE_PRE,
        (void*)maliciousAddr, maliciousSize);
    WH_TEST_ASSERT_RETURN(rc != WH_ERROR_OK);

    return WH_ERROR_OK;
}


int whTest_Dma(void* ctx)
{
    (void)ctx;

    WH_TEST_RETURN_ON_FAIL(_whTest_DmaAllowListBasic());
    WH_TEST_RETURN_ON_FAIL(_whTest_DmaAllowListOverflow());

    return WH_ERROR_OK;
}

#endif /* WOLFHSM_CFG_DMA */
