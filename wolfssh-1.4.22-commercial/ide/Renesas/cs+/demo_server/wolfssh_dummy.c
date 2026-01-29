/* wolfssh_dummy.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/error-crypt.h>
#include <stdio.h>

/* used for checking bytes on wire for window adjust packet read */
void ws_Ioctl(int fd, int flag, int *ret)
{
  /* This needs to implement when using scp or sftp */
}

#define YEAR 2019
#define APR  4

static int tick = 0;

time_t time(time_t *t)
{
    return ((YEAR-1970)*365+30*APR)*24*60*60 + tick++;
}

#include <ctype.h>
int strncasecmp(const char *s1, const char * s2, unsigned int sz)
{
    for( ; sz>0; sz--, s1++, s2++){
            if(toupper(*s1) < toupper(*s2)){
            return -1;
        }
        if(toupper(*s1) > toupper(*s2)){
            return 1;
        }
    }
    return 0;	
}