/* psa_size.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFPSA_SIZE_H
#define WOLFPSA_SIZE_H

#include <stdint.h>

#include <psa/crypto.h>

static inline psa_status_t wolfpsa_check_word32_length(size_t length)
{
    if (length > UINT32_MAX) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    return PSA_SUCCESS;
}

#endif /* WOLFPSA_SIZE_H */
