/* user_settings.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#define WOLFCRYPT_ONLY
#define NO_ERROR_STRINGS

#define NO_MAIN_DRIVER
#define NO_WRITEV
#define NO_DEV_RANDOM
#define NO_WOLFSSL_DIR 
#define NO_WOLFSSL_STUB
#define NO_DYNAMIC_ARRAY       /* for compilers not allowed dynamic size array */ 
#define NO_RC4
#define NO_OLD_SHA256
#define NO_FILESYSTEM

#define WOLFSSL_NO_CURRDIR
#define WOLFSSL_LOG_PRINTF
#define WOLFSSL_SMALL_STACK
#define WOLFSSL_DH_CONST
#define WOLFSSL_USER_IO

#define TFM_TIMING_RESISTANT
#define ECC_TIMING_RESISTANT
#define WC_RSA_BLINDING

#define HAVE_TLS_EXTENSIONS
#define HAVE_SUPPORTED_CURVES
#define HAVE_AESGCM
#define WOLFSSL_SHA512
#define WOLFSSL_SHA384
#define HAVE_ECC

#define BENCH_EMBEDDED
#define USE_CERT_BUFFERS_2048
#define SIZEOF_LONG_LONG 8
#define USER_TIME
#define XTIME time
#define USE_WOLF_SUSECONDS_T
#define USE_WOLF_TIMEVAL_T
#define WOLFSSL_GENSEED_FORTEST /* Wardning: define your own seed gen */

#define SINGLE_THREADED  /* or define RTOS  option */

#include "wolfssh_csplus_usersettings.h"
