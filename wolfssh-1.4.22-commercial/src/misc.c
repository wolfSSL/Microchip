/* misc.c
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
 * The misc module contains inline functions. This file is either included
 * into source files or built separately depending on the inline configure
 * option.
 */


#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#ifdef WOLFSSL_USER_SETTINGS
#include <wolfssl/wolfcrypt/settings.h>
#else
#include <wolfssl/options.h>
#endif

#ifndef WOLFSSH_MISC_C
#define WOLFSSH_MISC_C


#include <wolfssh/misc.h>
#include <wolfssh/log.h>


#ifdef NO_INLINE
    #define STATIC
#else
    #define STATIC static
#endif


/* Check for if compiling misc.c when not needed. */
#if !defined(WOLFSSH_MISC_INCLUDED) && !defined(NO_INLINE) && \
    !defined(WOLFSSH_IGNORE_FILE_WARN)

    #ifndef _MSC_VER
        #warning "misc.c does not need to be compiled when using inline (NO_INLINE not defined))"
    #else
        #pragma message("warning: misc.c does not need to be compiled when using inline (NO_INLINE not defined))")
    #endif

#else /* !WOLFSSL_MISC_INCLUDED && !NO_INLINE && !WOLFSSH_IGNORE_FILE_WARN */


#ifndef min
STATIC INLINE word32 min(word32 a, word32 b)
{
    return a > b ? b : a;
}
#endif /* min */


/* convert opaque to 32 bit integer */
STATIC INLINE void ato32(const byte* c, word32* u32)
{
    *u32 = (c[0] << 24) | (c[1] << 16) | (c[2] << 8) | c[3];
}


/* convert 32 bit integer to opaque */
STATIC INLINE void c32toa(word32 u32, byte* c)
{
    c[0] = (u32 >> 24) & 0xff;
    c[1] = (u32 >> 16) & 0xff;
    c[2] = (u32 >>  8) & 0xff;
    c[3] =  u32 & 0xff;
}


/* Make sure compiler doesn't skip */
STATIC INLINE void ForceZero(const void* mem, word32 length)
{
    volatile byte* z = (volatile byte*)mem;

    while (length--) *z++ = 0;
}


/* check all length bytes for equality, return 0 on success */
STATIC INLINE int ConstantCompare(const byte* a, const byte* b,
                                  word32 length)
{
    word32 i;
    word32 compareSum = 0;

    for (i = 0; i < length; i++) {
        compareSum |= a[i] ^ b[i];
    }

    return compareSum;
}


#undef STATIC


#endif /* !WOLFSSL_MISC_INCLUDED && !NO_INLINE */


#endif /* WOLFSSH_MISC_C */
