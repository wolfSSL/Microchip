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
 * test-refactor/wh_test_groups.h
 *
 * Portable entry points for the three test groups. The port's
 * main() owns the client/server contexts and hands them to the
 * group functions, which run every suite that belongs to the
 * group (gated by the applicable compile-time config flags).
 *
 *   - Misc:   standalone suites, no client or server needed
 *   - Server: server-side suites; takes a whServerContext*
 *   - Client: client-side suites; takes a whClientContext*
 *             (the server must already be running -- on
 *             single-process ports the port sets it up before
 *             calling into this group)
 *
 * A client-only port calls Client (and optionally Misc).
 * A server-only port calls Server (and optionally Misc).
 * A combined port calls all three.
 */

#ifndef WH_TEST_GROUPS_H_
#define WH_TEST_GROUPS_H_

#include "wolfhsm/wh_client.h"
#include "wolfhsm/wh_server.h"


int whTestGroup_Misc(void);
int whTestGroup_Server(whServerContext* server);
int whTestGroup_Client(whClientContext* client);

/*
 * Run a single test outside the portable registry, print its
 * result in the standard format, and feed the summary tally.
 * Used by ports to invoke platform-specific tests (e.g. POSIX
 * host-sim suites) so they appear in the final tally alongside
 * the portable groups. Returns the test's rc unchanged.
 */
int whTestGroup_RunOne(const char* name, int (*fn)(void*), void* ctx);

/*
 * Print a wolfCrypt-style tally ("All N tests passed!" or
 * "N passed, M skipped, K failed of T tests") using the
 * counters accumulated by whTestGroup_{Misc,Server,Client}.
 * Call once from main after the last group returns.
 * Returns 0 if no failures, non-zero otherwise.
 */
int whTestGroup_Summary(void);

#endif /* WH_TEST_GROUPS_H_ */
