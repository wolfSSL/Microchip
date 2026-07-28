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
 * test-refactor/client-server/wh_test_wolfcrypt.c
 *
 * Runs the upstream wolfCrypt test suite against a live wolfHSM
 * client. The Makefile sets WC_USE_DEVID so wolfCrypt routes its
 * ops through the cryptocb the client registered at init time.
 */

#include "wolfhsm/wh_settings.h"

#if !defined(WOLFHSM_CFG_NO_CRYPTO) && \
    defined(WOLFHSM_CFG_TEST_WOLFCRYPTTEST)

#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/wolfcrypt/types.h"
#include "wolfcrypt/test/test.h"

#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_client.h"

#include "wh_test_common.h"
#include "wh_test_list.h"

int whTest_WolfCryptTest(whClientContext* ctx)
{
    (void)ctx;
    return (int)wolfcrypt_test(NULL);
}

#endif /* !WOLFHSM_CFG_NO_CRYPTO && WOLFHSM_CFG_TEST_WOLFCRYPTTEST */
