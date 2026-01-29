/* auth.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _WOLFSSH_TESTS_AUTH_H_
#define _WOLFSSH_TESTS_AUTH_H_

#include <wolfssh/test.h>

int wolfSSH_AuthTest(int argc, char** argv);

typedef struct thread_args {
    int return_code;
    tcp_ready* signal;
} thread_args;

#endif /* _WOLFSSH_TESTS_AUTH_H_ */
