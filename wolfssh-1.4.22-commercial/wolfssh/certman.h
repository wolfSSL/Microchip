/* certman.h
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
 * The certman module contains utility functions wrapping the wolfSSL
 * certificate manager functions to validate user certificates.
 */


#ifndef _WOLFSSH_CERTMAN_H_
#define _WOLFSSH_CERTMAN_H_

#include <wolfssh/settings.h>
#include <wolfssh/port.h>

#ifdef __cplusplus
extern "C" {
#endif


struct WOLFSSH_CERTMAN;
typedef struct WOLFSSH_CERTMAN WOLFSSH_CERTMAN;


WOLFSSH_API
WOLFSSH_CERTMAN* wolfSSH_CERTMAN_new(void* heap);

WOLFSSH_API
void wolfSSH_CERTMAN_free(WOLFSSH_CERTMAN* cm);

WOLFSSH_API
int wolfSSH_CERTMAN_LoadRootCA_buffer(WOLFSSH_CERTMAN* cm,
        const unsigned char* rootCa, word32 rootCaSz);

WOLFSSH_API
int wolfSSH_CERTMAN_VerifyCerts_buffer(WOLFSSH_CERTMAN* cm,
        const unsigned char* cert, word32 certSz, word32 certCount);


#ifdef __cplusplus
}
#endif

#endif /* _WOLFSSH_CERTMAN_H_ */
