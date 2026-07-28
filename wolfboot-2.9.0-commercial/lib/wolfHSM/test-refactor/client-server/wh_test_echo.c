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
 * test-refactor/wh_test_echo.c
 *
 * Echo round-trip test. Uses blocking client APIs; the port
 * is responsible for pumping the server in parallel.
 */

#include <stdio.h>
#include <string.h>

#include "wolfhsm/wh_settings.h"
#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_client.h"

#include "wh_test_common.h"
#include "wh_test_list.h"

#define REPEAT_COUNT 10

/*
 * Echo a message to the server and verify the response
 * matches. Repeats several times with different payloads.
 */
int whTest_Echo(whClientContext* ctx)
{
    char     send_buf[WOLFHSM_CFG_COMM_DATA_LEN];
    char     recv_buf[WOLFHSM_CFG_COMM_DATA_LEN];
    uint16_t send_len = 0;
    uint16_t recv_len = 0;
    int      i;

    for (i = 0; i < REPEAT_COUNT; i++) {
        send_len = snprintf(send_buf, sizeof(send_buf),
            "Echo test %d", i);

        recv_len = 0;
        memset(recv_buf, 0, sizeof(recv_buf));

        WH_TEST_RETURN_ON_FAIL(
            wh_Client_Echo(ctx,
                send_len, send_buf,
                &recv_len, recv_buf));

        WH_TEST_ASSERT_RETURN(recv_len == send_len);
        WH_TEST_ASSERT_RETURN(
            memcmp(recv_buf, send_buf, recv_len) == 0);
    }

    return 0;
}
