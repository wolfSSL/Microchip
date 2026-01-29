/* wolfssh_test.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFSSH_TEST_H_
#define WOLFSSH_TEST_H_

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssh/settings.h>

#include "../../tests/unit.h"
#include "../../tests/api.h"
#include "../../tests/testsuite.h"

#ifndef SINGLE_THREADED
#include <cmsis_os.h>
#endif

#ifdef CMSIS_OS2_H_
void wolfSSHTest(void* argument);
#else
void wolfSSHTest(void const * argument);
#endif

#endif /* WOLFSSH_TEST_H_ */
