/* keygen.h
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
 * The keygen module contains utility functions wrapping the wolfCrypt
 * key generation functions to product SSH friendly keys.
 */


#ifndef _WOLFSSH_KEYGEN_H_
#define _WOLFSSH_KEYGEN_H_

#include <wolfssh/settings.h>
#include <wolfssh/port.h>

#ifdef __cplusplus
extern "C" {
#endif


#define WOLFSSH_RSAKEY_DEFAULT_SZ 2048
#define WOLFSSH_RSAKEY_DEFAULT_E  65537
#define WOLFSSH_ECDSAKEY_PRIME256 256
#define WOLFSSH_ECDSAKEY_PRIME384 384
#define WOLFSSH_ECDSAKEY_PRIME521 521
#define WOLFSSH_ED25519KEY        256


WOLFSSH_API int wolfSSH_MakeRsaKey(byte* out, word32 outSz,
        word32 size, word32 e);
WOLFSSH_API int wolfSSH_MakeEcdsaKey(byte* out, word32 outSz, word32 size);
WOLFSSH_API int wolfSSH_MakeEd25519Key(byte* out, word32 outSz, word32 size);


#ifdef __cplusplus
}
#endif

#endif /* _WOLFSSH_KEYGEN_H_ */

