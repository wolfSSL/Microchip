/* main.c
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdio.h>

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfcrypt/test/test.h>

#include <stdlib.h>

#include "xc.h"
#include "mcc_generated_files/mcc.h"

int main(void) {
    SYSTEM_Initialize();

    wolfcrypt_test(NULL);

    return 0;
}

