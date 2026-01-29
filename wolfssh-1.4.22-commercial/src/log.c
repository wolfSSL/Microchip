/* log.c
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


#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssh/ssh.h>
#include <wolfssh/log.h>
#include <wolfssh/error.h>

#include <stdlib.h>
#include <stdarg.h>
#ifndef FREESCALE_MQX
    #include <stdio.h>
    #ifndef WOLFSSH_NO_TIMESTAMP
        #include <time.h>
    #endif
#endif


#ifndef WOLFSSH_DEFAULT_LOG_WIDTH
    #define WOLFSSH_DEFAULT_LOG_WIDTH 120
#endif


#ifndef WOLFSSL_NO_DEFAULT_LOGGING_CB
    static void DefaultLoggingCb(enum wolfSSH_LogLevel, const char *const);
    static wolfSSH_LoggingCb logFunction = DefaultLoggingCb;
#else /* WOLFSSH_NO_DEFAULT_LOGGING_CB */
    static wolfSSH_LoggingCb logFunction = NULL;
#endif /* WOLFSSH_NO_DEFAULT_LOGGING_CB */


#if defined(DEBUG_WOLFSSH) || defined(WOLFSSH_SSHD)
    static enum wolfSSH_LogLevel logLevel = WS_LOG_DEFAULT;
    static int logEnable = 0;
#endif


/* turn debugging on if supported */
void wolfSSH_Debugging_ON(void)
{
#if defined(DEBUG_WOLFSSH) || defined(WOLFSSH_SSHD)
    logEnable = 1;
#endif
}


/* turn debugging off */
void wolfSSH_Debugging_OFF(void)
{
#if defined(DEBUG_WOLFSSH) || defined(WOLFSSH_SSHD)
    logEnable = 0;
#endif
}


/* set logging callback function */
void wolfSSH_SetLoggingCb(wolfSSH_LoggingCb logF)
{
    if (logF)
        logFunction = logF;
}


int wolfSSH_LogEnabled(void)
{
#if defined(DEBUG_WOLFSSH) || defined(WOLFSSH_SSHD)
    return logEnable;
#else
    return 0;
#endif
}


#if defined(DEBUG_WOLFSSH) || defined(WOLFSSH_SSHD)
#ifndef WOLFSSH_NO_DEFAULT_LOGGING_CB
/* log level string */
static const char* GetLogStr(enum wolfSSH_LogLevel level)
{
    switch (level) {
        case WS_LOG_INFO:
            return "INFO";

        case WS_LOG_WARN:
            return "WARNING";

        case WS_LOG_ERROR:
            return "ERROR";

        case WS_LOG_DEBUG:
            return "DEBUG";

        case WS_LOG_USER:
            return "USER";

        case WS_LOG_SFTP:
            return "SFTP";

        case WS_LOG_SCP:
            return "SCP";

        case WS_LOG_AGENT:
            return "AGENT";

        case WS_LOG_CERTMAN:
            return "CERTMAN";

        default:
            return "UNKNOWN";
    }
}

void DefaultLoggingCb(enum wolfSSH_LogLevel level, const char *const msgStr)
{
    char timeStr[24];
    timeStr[0] = '\0';
#ifndef WOLFSSH_NO_TIMESTAMP
    {
        time_t  current;
        struct  tm local;

        current = WTIME(NULL);
        if (WLOCALTIME(&current, &local)) {
            /* make pretty */
            strftime(timeStr, sizeof(timeStr), "%F %T ", &local);
        }
    }
#endif /* WOLFSSH_NO_TIMESTAMP */
    #ifndef WOLFSSH_LOG_PRINTF
    fprintf(stdout, "%s[%s] %s\r\n", timeStr, GetLogStr(level), msgStr);
    #else
    printf("%s[%s] %s\r\n", timeStr, GetLogStr(level), msgStr);
    #endif
}
#endif /* WOLFSSH_NO_DEFAULT_LOGGING_CB */


/* our default logger */
void wolfSSH_Log(enum wolfSSH_LogLevel level, const char *const fmt, ...)
{
    va_list vlist;
    char    msgStr[WOLFSSH_DEFAULT_LOG_WIDTH];

    if (level < logLevel)
        return;   /* don't need to output */

    /* format msg */
    va_start(vlist, fmt);
    WVSNPRINTF(msgStr, sizeof(msgStr)-1, fmt, vlist);
    va_end(vlist);

    if (logFunction)
        logFunction(level, msgStr);
}

#else
void DefaultLoggingCb(enum wolfSSH_LogLevel level, const char *const msgStr)
{
    WOLFSSH_UNUSED(level);
    WOLFSSH_UNUSED(msgStr);
}

void wolfSSH_Log(enum wolfSSH_LogLevel level, const char *const fmt, ...)
{
    WOLFSSH_UNUSED(logFunction);
    WOLFSSH_UNUSED(level);
    WOLFSSH_UNUSED(fmt);
}

#endif  /* DEBUG_WOLFSSH */
