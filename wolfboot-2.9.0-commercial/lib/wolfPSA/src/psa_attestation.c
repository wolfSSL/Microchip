/* psa_attestation.c
 *
 * Stub PSA initial attestation APIs.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stddef.h>
#include <stdint.h>

#include "psa/initial_attestation.h"

psa_status_t psa_initial_attest_get_token(const uint8_t *auth_challenge,
					  size_t challenge_size,
					  uint8_t *token_buf,
					  size_t token_buf_size,
					  size_t *token_size)
{
	(void)auth_challenge;
	(void)challenge_size;
	(void)token_buf;
	(void)token_buf_size;
	if (token_size != NULL) {
		*token_size = 0;
	}
	return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t psa_initial_attest_get_token_size(size_t challenge_size,
					       size_t *token_size)
{
	(void)challenge_size;
	if (token_size != NULL) {
		*token_size = 0;
	}
	return PSA_ERROR_NOT_SUPPORTED;
}
