/* ocsp_responder.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFSSL_OCSP_RESPONDER_EXAMPLE_H
#define WOLFSSL_OCSP_RESPONDER_EXAMPLE_H

#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/ssl.h>
#include <wolfssl/test.h>

#ifdef __cplusplus
extern "C" {
#endif

THREAD_RETURN WOLFSSL_THREAD ocsp_responder_test(void* args);

#ifdef __cplusplus
}
#endif

#endif /* WOLFSSL_OCSP_RESPONDER_EXAMPLE_H */
