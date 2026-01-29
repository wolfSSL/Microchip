/* wolftpm_test.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFTPM_TEST_H_
#define WOLFTPM_TEST_H_

#include <wolftpm/tpm2_types.h>

#ifndef SINGLE_THREADED
#include <cmsis_os.h>
#endif

#ifdef CMSIS_OS2_H_
void wolfTPMTest(void* argument);
#else
void wolfTPMTest(void const * argument);
#endif

#endif /* WOLFTPM_TEST_H_ */
