/* arm_tee_attest_api.c
 *
 * ARM TEE attestation NS API wrappers.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdio.h>

#include "psa/initial_attestation.h"
#include "psa/client.h"
#include "psa_manifest/sid.h"
#include "arm_tee_attest_defs.h"

psa_status_t
psa_initial_attest_get_token(const uint8_t *auth_challenge,
                             size_t challenge_size,
                             uint8_t *token_buf,
                             size_t token_buf_size,
                             size_t *token_size)
{
    psa_status_t status;

    psa_invec in_vec[] = {
        { auth_challenge, challenge_size }
    };
    psa_outvec out_vec[] = {
        { token_buf, token_buf_size }
    };

    printf("[ATTEST-NS] get_token: chal=%u buf=%u\r\n",
           (unsigned)challenge_size, (unsigned)token_buf_size);
    status = psa_call(ARM_TEE_ATTESTATION_SERVICE_HANDLE,
                      ARM_TEE_ATTEST_GET_TOKEN,
                      in_vec, IOVEC_LEN(in_vec),
                      out_vec, IOVEC_LEN(out_vec));
    printf("[ATTEST-NS] get_token: status=%ld len=%u\r\n",
           (long)status, (unsigned)out_vec[0].len);

    if (status == PSA_SUCCESS && token_size != NULL) {
        *token_size = out_vec[0].len;
    }

    return status;
}

psa_status_t
psa_initial_attest_get_token_size(size_t challenge_size,
                                  size_t *token_size)
{
    psa_status_t status;
    rot_size_t challenge_size_param;
    rot_size_t token_size_param = 0;

    psa_invec in_vec[] = {
        { &challenge_size_param, sizeof(challenge_size_param) }
    };
    psa_outvec out_vec[] = {
        { &token_size_param, sizeof(token_size_param) }
    };

    if (challenge_size > ROT_SIZE_MAX) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    challenge_size_param = (rot_size_t)challenge_size;

    if (token_size == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    printf("[ATTEST-NS] get_token_size: chal=%u\r\n",
           (unsigned)challenge_size);
    status = psa_call(ARM_TEE_ATTESTATION_SERVICE_HANDLE,
                      ARM_TEE_ATTEST_GET_TOKEN_SIZE,
                      in_vec, IOVEC_LEN(in_vec),
                      out_vec, IOVEC_LEN(out_vec));
    printf("[ATTEST-NS] get_token_size: status=%ld size=%u\r\n",
           (long)status, (unsigned)token_size_param);

    *token_size = token_size_param;

    return status;
}

#ifndef WOLFBOOT_ATTESTATION_IAK
psa_status_t
psa_initial_attest_get_iak_pubkey(uint8_t *buf,
                                  size_t buf_size,
                                  size_t *key_len)
{
    psa_status_t status;

    if (buf == NULL || key_len == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (buf_size < 65) { /* 65 bytes for uncompressed ECC P-256 public key */
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }
    psa_outvec out_vec[] = {
        { buf, buf_size }
    };

    printf("[ATTEST-NS] get_iak_pubkey: buf_size=%u\r\n", (unsigned)buf_size);
    status = psa_call(ARM_TEE_ATTESTATION_SERVICE_HANDLE,
                      ARM_TEE_ATTEST_GET_IAK_PUBKEY,
                      NULL, 0,
                      out_vec, IOVEC_LEN(out_vec));
    printf("[ATTEST-NS] get_iak_pubkey: status=%ld key_len=%u\r\n",
           (long)status, (unsigned)out_vec[0].len);
    if (status == PSA_SUCCESS) {
        *key_len = out_vec[0].len;
    }
    return status;
}
#endif /* !WOLFBOOT_ATTESTATION_IAK */
