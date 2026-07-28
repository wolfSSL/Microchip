/* initial_attestation.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef PSA_INITIAL_ATTESTATION_H
#define PSA_INITIAL_ATTESTATION_H

#include <stddef.h>
#include <stdint.h>

#include "psa/error.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PSA_INITIAL_ATTEST_API_VERSION_MAJOR (1)
#define PSA_INITIAL_ATTEST_API_VERSION_MINOR (0)

#define PSA_INITIAL_ATTEST_CHALLENGE_SIZE_32 (32u)
#define PSA_INITIAL_ATTEST_CHALLENGE_SIZE_48 (48u)
#define PSA_INITIAL_ATTEST_CHALLENGE_SIZE_64 (64u)

psa_status_t psa_initial_attest_get_token(const uint8_t *auth_challenge,
					  size_t challenge_size,
					  uint8_t *token_buf,
					  size_t token_buf_size,
					  size_t *token_size);

psa_status_t psa_initial_attest_get_token_size(size_t challenge_size,
					       size_t *token_size);

#ifdef __cplusplus
}
#endif

#endif /* PSA_INITIAL_ATTESTATION_H */
