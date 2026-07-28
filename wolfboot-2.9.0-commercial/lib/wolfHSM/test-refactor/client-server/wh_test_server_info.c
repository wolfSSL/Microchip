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
 * test-refactor/wh_test_server_info.c
 *
 * Server info query test. Uses blocking client APIs; the port
 * is responsible for pumping the server in parallel.
 */

#include <string.h>

#include "wolfhsm/wh_settings.h"
#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_client.h"
#include "wolfhsm/wh_message_comm.h"

#include "wh_test_common.h"
#include "wh_test_list.h"


/*
 * Query server info and verify the response contains
 * valid data.
 */
int whTest_ServerInfo(whClientContext* ctx)
{
    uint8_t  version[WH_INFO_VERSION_LEN + 1] = {0};
    uint8_t  build[WH_INFO_VERSION_LEN + 1]   = {0};
    uint32_t comm_data_len     = 0;
    uint32_t nvm_object_count  = 0;
    uint32_t keycache_count    = 0;
    uint32_t keycache_bufsize  = 0;
    uint32_t keycache_bigcount = 0;
    uint32_t keycache_bigbufsz = 0;
    uint32_t customcb_count    = 0;
    uint32_t dmaaddr_count     = 0;
    uint32_t debug_state       = 0;
    uint32_t boot_state        = 0;
    uint32_t lifecycle_state   = 0;
    uint32_t nvm_state         = 0;

    WH_TEST_RETURN_ON_FAIL(
        wh_Client_CommInfo(ctx,
            version, build,
            &comm_data_len,
            &nvm_object_count,
            &keycache_count,
            &keycache_bufsize,
            &keycache_bigcount,
            &keycache_bigbufsz,
            &customcb_count,
            &dmaaddr_count,
            &debug_state,
            &boot_state,
            &lifecycle_state,
            &nvm_state));

    /* Comm data length must be nonzero */
    WH_TEST_ASSERT_RETURN(comm_data_len > 0);

    return 0;
}
