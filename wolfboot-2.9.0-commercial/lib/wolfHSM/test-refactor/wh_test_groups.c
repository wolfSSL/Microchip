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
 * test-refactor/wh_test_groups.c
 *
 * Portable group entry points. Each walks its slice of the
 * generated test registry (see wh_test_list.c) -- one array per
 * group. Tests whose feature gate is off are resolved by the
 * linker to the weak skip stub and surface as SKIPPED at
 * runtime.
 *
 * Output format follows wolfCrypt convention:
 *     whTest_Foo                    test passed!
 *     whTest_Bar                    test skipped
 *     whTest_Baz                    test FAILED (rc=-5)
 * with a final whTestGroup_Summary() tally.
 */

#include <string.h>

#include "wolfhsm/wh_settings.h"

#include "wh_test_common.h"
#include "wh_test_groups.h"
#include "wh_test_list.h"
#include "wh_test_port.h"

/* Column at which "test passed!" / "test skipped" / "test FAILED"
 * starts. Pad the test name with spaces to line these up. Pick
 * something a bit wider than the longest current name so future
 * tests don't force a reformat. */
#define WH_TEST_NAME_COL 40

/* Per-process tallies. The POSIX port runs the groups
 * sequentially (misc inline, then server, then client), so no
 * locking is needed. Ports that invoke groups from concurrent
 * threads must serialize the calls or add their own lock. */
static int whTestPassed  = 0;
static int whTestSkipped = 0;
static int whTestFailed  = 0;

static void whTest_PrintResult(const char* name, int rc)
{
    int pad = WH_TEST_NAME_COL - (int)strlen(name);
    if (pad < 1) {
        pad = 1;
    }
    WOLFHSM_CFG_PRINTF("%s%*s", name, pad, "");

    if (rc == 0) {
        WOLFHSM_CFG_PRINTF("test passed!\n");
        whTestPassed++;
    }
    else if (rc == WH_TEST_SKIPPED) {
        WOLFHSM_CFG_PRINTF("test skipped\n");
        whTestSkipped++;
    }
    else {
        WOLFHSM_CFG_PRINTF("test FAILED (rc=%d)\n", rc);
        whTestFailed++;
    }
}

int whTestGroup_RunOne(const char* name, int (*fn)(void*), void* ctx)
{
    int rc;

    if (name == NULL || fn == NULL) {
        whTest_PrintResult(name != NULL ? name : "<unnamed test>",
                           WH_TEST_SKIPPED);
        return WH_TEST_SKIPPED;
    }
    
    rc = fn(ctx);
    whTest_PrintResult(name, rc);
    return rc;
}

int whTestGroup_Misc(void)
{
    size_t i;

    for (i = 0; i < whTestsMiscCount; i++) {
        int rc = whTestGroup_RunOne(whTestsMisc[i].name,
                                    whTestsMisc[i].fn, NULL);

        if (rc != WH_ERROR_OK && rc != WH_TEST_SKIPPED) {
            /* Bail out after the first failure so the user need not
             * dig through the test logs. */
            return rc;
        }
    }

    return WH_ERROR_OK;
}

int whTestGroup_Server(whServerContext* server)
{
    size_t i;

    for (i = 0; i < whTestsServerCount; i++) {
        int rc = whTestPort_ResetServer(server);
        if (rc != WH_ERROR_OK) {
            return rc;
        }

        rc = whTestGroup_RunOne(whTestsServer[i].name,
                                whTestsServer[i].fn, server);
        if (rc != WH_ERROR_OK && rc != WH_TEST_SKIPPED) {
            return rc;
        }
    }

    return WH_ERROR_OK;
}

int whTestGroup_Client(whClientContext* client)
{
    size_t i;

    for (i = 0; i < whTestsClientCount; i++) {
        int rc = whTestPort_ResetClient(client);
        if (rc != WH_ERROR_OK) {
            return rc;
        }

        rc = whTestGroup_RunOne(whTestsClient[i].name,
                                whTestsClient[i].fn, client);
        if (rc != WH_ERROR_OK && rc != WH_TEST_SKIPPED) {
            return rc;
        }
    }

    return WH_ERROR_OK;
}

int whTestGroup_Summary(void)
{
    int total = whTestPassed + whTestSkipped + whTestFailed;

    if (whTestFailed == 0 && whTestSkipped == 0) {
        WOLFHSM_CFG_PRINTF("All %d tests passed!\n", total);
    }
    else {
        WOLFHSM_CFG_PRINTF(
            "%d passed, %d skipped, %d failed of %d tests\n",
            whTestPassed, whTestSkipped, whTestFailed, total);
    }

    return whTestFailed == 0 ? WH_ERROR_OK : WH_ERROR_ABORTED;
}
