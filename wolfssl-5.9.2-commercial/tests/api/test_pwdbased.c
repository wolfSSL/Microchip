/* test_pwdbased.c
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <tests/unit.h>
#include <wolfssl/wolfcrypt/pwdbased.h>
#include <tests/api/api.h>
#include <tests/api/test_pwdbased.h>

/* test that wc_PBKDF1_ex rejects iterations <= 0 */
int test_wc_PBKDF1_ex_iterations(void)
{
    EXPECT_DECLS;
#if defined(HAVE_PBKDF1) && !defined(NO_PWDBASED) && !defined(NO_SHA) && \
    !defined(HAVE_SELFTEST) && (!defined(HAVE_FIPS) || FIPS_VERSION3_GE(7,0,0))

    static const byte passwd[] = { 'p', 'a', 's', 's' };
    static const byte salt[]   = { 0x78, 0x57, 0x8E, 0x5a,
                                   0x5d, 0x63, 0xcb, 0x06 };
    byte derived[16];

    ExpectIntEQ(wc_PBKDF1_ex(derived, (int)sizeof(derived), NULL, 0,
                    passwd, (int)sizeof(passwd),
                    salt, (int)sizeof(salt), 0, WC_SHA, HEAP_HINT),
                BAD_FUNC_ARG);
    ExpectIntEQ(wc_PBKDF1_ex(derived, (int)sizeof(derived), NULL, 0,
                    passwd, (int)sizeof(passwd),
                    salt, (int)sizeof(salt), -1, WC_SHA, HEAP_HINT),
                BAD_FUNC_ARG);
#endif
    return EXPECT_RESULT();
}

/* test that wc_PBKDF2_ex rejects iterations <= 0 */
int test_wc_PBKDF2_ex_iterations(void)
{
    EXPECT_DECLS;
#if defined(HAVE_PBKDF2) && !defined(NO_PWDBASED) && !defined(NO_HMAC) && \
    !defined(NO_SHA256) && !defined(HAVE_SELFTEST) && \
    (!defined(HAVE_FIPS) || FIPS_VERSION3_GE(7,0,0))
    static const byte passwd[] = { 'p', 'a', 's', 's' };
    static const byte salt[]   = { 0x78, 0x57, 0x8E, 0x5a,
                                   0x5d, 0x63, 0xcb, 0x06 };
    byte derived[24];

    ExpectIntEQ(wc_PBKDF2_ex(derived, passwd, (int)sizeof(passwd),
                    salt, (int)sizeof(salt), 0,
                    (int)sizeof(derived), WC_SHA256, HEAP_HINT, INVALID_DEVID),
                BAD_FUNC_ARG);
    ExpectIntEQ(wc_PBKDF2_ex(derived, passwd, (int)sizeof(passwd),
                    salt, (int)sizeof(salt), -1,
                    (int)sizeof(derived), WC_SHA256, HEAP_HINT, INVALID_DEVID),
                BAD_FUNC_ARG);
#endif
    return EXPECT_RESULT();
}
