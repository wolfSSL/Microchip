/* wolfssh_test.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "wolfssh_test.h"

#ifndef SINGLE_THREADED
    #include <cmsis_os.h>

    #ifdef WOLFSSL_DEBUG_MEMORY
        /* for memory debugging */
        #include <task.h>
    #endif
#endif

#include <stdio.h>
#include <string.h>


#ifdef CMSIS_OS2_H_
void wolfSSHTest(void* argument)
#else
void wolfSSHTest(const void* argument)
#endif
{
    int ret = 0;
#if 0
    wolfSSL_Debugging_ON();
    wolfSSH_Debugging_ON();
#endif

    printf("Running wolfSSH Tests...\n");

    /* TODO: Uncomment once proper threading abstractions have been implemented
     * in wolfSSL */
    /* if (wolfSSH_TestsuiteTest(0, NULL))
        ret = -1; */
    if (wolfSSH_UnitTest(0, NULL))
        ret = -1;
    if (wolfSSH_ApiTest(0, NULL))
        ret = -1;

    printf("wolfSSH Test: Return code %d\n", ret);

}
