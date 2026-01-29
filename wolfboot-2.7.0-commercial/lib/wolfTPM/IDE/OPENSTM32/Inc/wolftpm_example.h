/* wolftpm_example.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef WOLFTPM_EXAMPLE_H_
#define WOLFTPM_EXAMPLE_H_

#include <stm32f4xx_hal.h>
#include <stm32f4xx.h>
#include <cmsis_os.h>

#ifndef WOLFSSL_USER_SETTINGS
	#include <wolfssl/options.h>
#endif
#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/ssl.h>
#include <wolfcrypt/test/test.h>
#include <wolfcrypt/benchmark/benchmark.h>

#include <wolftpm/tpm2.h>

void wolfTPMDemo(void const * argument);


#endif /* WOLFTPM_EXAMPLE_H_ */
