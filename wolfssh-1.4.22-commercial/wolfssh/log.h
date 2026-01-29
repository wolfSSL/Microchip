/* log.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


/*
 * The log module contains the interface to the logging function. When
 * debugging is enabled and turned on, the logger will output to STDOUT.
 * A custom logging callback may be installed.
 */


#ifndef _WOLFSSH_LOG_H_
#define _WOLFSSH_LOG_H_

#include <wolfssh/settings.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef NO_TIMESTAMP
    /* The NO_TIMESTAMP tag is deprecated. Convert to new name. */
    #define WOLFSSH_NO_TIMESTAMP
#endif


enum wolfSSH_LogLevel {
    WS_LOG_CERTMAN = 9,
    WS_LOG_AGENT = 8,
    WS_LOG_SCP   = 7,
    WS_LOG_SFTP  = 6,
    WS_LOG_USER  = 5,
    WS_LOG_ERROR = 4,
    WS_LOG_WARN  = 3,
    WS_LOG_INFO  = 2,
    WS_LOG_DEBUG = 1,
    WS_LOG_DEFAULT = WS_LOG_DEBUG
};


typedef void (*wolfSSH_LoggingCb)(enum wolfSSH_LogLevel,
                                  const char *const logMsg);
WOLFSSH_API void wolfSSH_SetLoggingCb(wolfSSH_LoggingCb logF);
WOLFSSH_API int wolfSSH_LogEnabled(void);


#ifdef __GNUC__
    #define FMTCHECK __attribute__((format(printf,2,3)))
#else
    #define FMTCHECK
#endif /* __GNUC__ */


WOLFSSH_API void wolfSSH_Log(enum wolfSSH_LogLevel,
                             const char *const, ...) FMTCHECK;

#if defined(DEBUG_WOLFSSH) || defined(WOLFSSH_SSHD)
    #define WLOG(...) do { \
                      if (wolfSSH_LogEnabled()) \
                          wolfSSH_Log(__VA_ARGS__); \
                  } while (0)
#else
    #define WLOG(...) WC_DO_NOTHING
#endif

#define WLOG_EXPECT_MSGID(x) WLOG(WS_LOG_DEBUG, "Expecting message %d", (x))

#ifdef __cplusplus
}
#endif

#endif /* _WOLFSSH_LOG_H_ */

