/* client.h
 *
 * Minimal PSA client definitions for wolfBoot Zephyr integration.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_PSA_CLIENT_H_
#define WOLFBOOT_PSA_CLIENT_H_

#include <stddef.h>
#include <stdint.h>
#include "psa/error.h"

#ifndef __PSA_CLIENT_H__
#define __PSA_CLIENT_H__
#endif

typedef int32_t psa_handle_t;
typedef uint32_t rot_size_t;

#ifndef ROT_SIZE_MAX
#define ROT_SIZE_MAX UINT32_MAX
#endif

typedef struct psa_invec {
    const void *base;
    size_t len;
} psa_invec;

typedef struct psa_outvec {
    void *base;
    size_t len;
} psa_outvec;

#ifndef PSA_IPC_CALL
#define PSA_IPC_CALL ((int32_t)1)
#endif

#ifndef PSA_CALL_TYPE_MIN
#define PSA_CALL_TYPE_MIN (PSA_IPC_CALL)
#endif
#ifndef PSA_CALL_TYPE_MAX
#define PSA_CALL_TYPE_MAX (PSA_IPC_CALL)
#endif

#ifndef PSA_MAX_IOVEC
#define PSA_MAX_IOVEC 4
#endif

#define IOVEC_LEN(x) (sizeof(x) / sizeof((x)[0]))

psa_handle_t psa_connect(uint32_t sid, uint32_t version);
void psa_close(psa_handle_t handle);
psa_status_t psa_call(psa_handle_t handle, int32_t type,
    const psa_invec *in_vec, size_t in_len,
    psa_outvec *out_vec, size_t out_len);

#endif /* WOLFBOOT_PSA_CLIENT_H_ */
