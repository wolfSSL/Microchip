/* test_ipc.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/wolfHAL.h>
#include "board.h"
#include "test.h"

static void Test_Ipc_InitDeinit(void)
{
    WHAL_ASSERT_EQ(whal_Ipc_Init(BOARD_IPC_DEV), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Ipc_Deinit(BOARD_IPC_DEV), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Ipc_Init(BOARD_IPC_DEV), WHAL_SUCCESS);
}

static void Test_Ipc_SendNull(void)
{
    WHAL_ASSERT_EQ(whal_Ipc_Send(BOARD_IPC_DEV, NULL, 0), WHAL_EINVAL);
}

static void Test_Ipc_RecvNull(void)
{
    WHAL_ASSERT_EQ(whal_Ipc_Recv(BOARD_IPC_DEV, NULL, 0), WHAL_EINVAL);
}

void whal_Test_Ipc(void)
{
    WHAL_TEST_SUITE_START("ipc");
    WHAL_TEST(Test_Ipc_InitDeinit);
    WHAL_TEST(Test_Ipc_SendNull);
    WHAL_TEST(Test_Ipc_RecvNull);
    WHAL_TEST_SUITE_END();
}
