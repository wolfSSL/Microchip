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
#define NO_WOLFSSL_DIR
#define NO_WOLFSSL_STUB
#define NO_RC4
#define NO_OLD_SHA256
#define NO_PWDBASED
#define NO_PKCS12
#define NO_PKCS8
#define NO_DES3
#define NO_MD4
#define NO_FILESYSTEM
#define WOLFSSL_NO_CURRDIR
#define WOLFSSL_LOG_PRINTF
#define WOLFSSL_SMALL_STACK
#define WOLFSSL_DH_CONST
#define WOLFSSL_USER_IO

#define TFM_TIMING_RESISTANT
#define ECC_TIMING_RESISTANT
#define WC_RSA_BLINDING

#define SP_WORD_SIZE 32
#define WOLFSSL_SP_NO_DYN_STACK
#define WOLFSSL_SP_NO_3072
#define WOLFSSL_SP_MATH
#define WOLFSSL_SP_SMALL
#define WOLFSSL_SP_NO_MALLOC
#define WOLFSSL_SP_NONBLOCK
#define WOLFSSL_HAVE_SP_DH
#define WOLFSSL_HAVE_SP_ECC
#define WC_ECC_NONBLOCK
#define HAVE_AESGCM
#define HAVE_ECC
/* enable RSA if needed */
/*#efine WOLFSSL_HAVE_SP_RSA*/
/* disable if RSA is enabled */
#define NO_RSA

#define BENCH_EMBEDDED
#define USE_CERT_BUFFERS_256
#define SIZEOF_LONG_LONG 8

#define WOLFSSL_RENESAS_TSIP_CRYPTONLY
#if defined(WOLFSSL_RENESAS_TSIP_CRYPTONLY)
 #define WOLFSSL_RENESAS_RX72N
 #define WOLFSSL_RENESAS_TSIP
 #define WOLFSSL_RENESAS_TSIP_VER     121
 #define WOLF_CRYPTO_CB
 #define WOLFSSL_HAVE_MIN
 #define WOLFSSL_HAVE_MAX
#else
 #define NO_DEV_RANDOM
/* Warning: define your own seed gen */
 #define WOLFSSL_GENSEED_FORTEST
#endif

#define SINGLE_THREADED  /* or define RTOS  option */
#define WOLFSSL_NO_SOCK
#define WOLFSSL_LOG_PRINTF
#define TIME_OVERRIDES
#define XTIME    time
#define WOLFSSL_GMTIME
#define XGMTIME(c,t)  gmtime(c)
#define USE_WOLF_SUSECONDS_T
#define USE_WOLF_TIMEVAL_T

/*-- strcasecmp */
#define XSTRCASECMP(s1,s2) strcmp((s1),(s2))

#include "wolfssh_user_setting.h"
