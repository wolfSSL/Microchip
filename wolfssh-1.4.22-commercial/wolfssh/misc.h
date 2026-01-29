/* misc.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifndef _WOLFSSH_MISC_H_
#define _WOLFSSH_MISC_H_


#ifdef __cplusplus
    extern "C" {
#endif


#include <wolfssl/wolfcrypt/types.h>
#include <wolfssh/settings.h>
#include <wolfssh/port.h>


#ifdef NO_INLINE


#ifndef min
WOLFSSH_LOCAL word32 min(word32, word32);
#endif /* min */

WOLFSSH_LOCAL void ato32(const byte*, word32*);
WOLFSSH_LOCAL void c32toa(word32, byte*);
WOLFSSH_LOCAL void ForceZero(const void*, word32);
WOLFSSH_LOCAL int ConstantCompare(const byte*, const byte*, word32);


#endif /* NO_INLINE */


#ifdef __cplusplus
    }   /* extern "C" */
#endif

#endif /* _WOLFSSH_MISC_H_ */

