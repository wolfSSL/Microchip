/* echoserver.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef _WOLFSSH_EXAMPLES_ECHOSERVER_H_
#define _WOLFSSH_EXAMPLES_ECHOSERVER_H_


THREAD_RETURN WOLFSSH_THREAD echoserver_test(void* args);
int wolfSSH_Echoserver(int argc, char** argv);


#endif /* _WOLFSSH_EXAMPLES_ECHOSERVER_H_ */
