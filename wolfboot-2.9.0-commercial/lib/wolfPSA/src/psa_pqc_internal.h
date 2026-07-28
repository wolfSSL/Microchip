/* psa_pqc_internal.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Internal interfaces between the PQC backends (psa_mldsa.c, psa_mlkem.c,
 * psa_lms_xmss.c) and the PSA front-end dispatch (psa_asymmetric_api.c,
 * psa_key_storage.c, psa_kem.c). Not part of the public API.
 *
 * Key material conventions (PSA Crypto API 1.4 PQC extension):
 *  - ML-DSA key pair  = 32-byte seed xi (FIPS 204 ML-DSA.KeyGen_internal),
 *    bits in {128, 192, 256} for ML-DSA-44/65/87.
 *  - ML-DSA public key = raw FIPS 204 pk bytes (1312/1952/2592).
 *  - ML-KEM key pair  = 64-byte seed d||z (FIPS 203 ML-KEM.KeyGen_internal),
 *    bits in {512, 768, 1024}.
 *  - ML-KEM public key = raw FIPS 203 ek bytes (800/1184/1568).
 *  - LMS/HSS and XMSS/XMSS^MT: raw public keys, verify only.
 */

#ifndef PSA_PQC_INTERNAL_H
#define PSA_PQC_INTERNAL_H

#include <psa/crypto.h>

#define WOLFPSA_MLDSA_SEED_SIZE 32
#define WOLFPSA_MLKEM_SEED_SIZE 64
#define WOLFPSA_MLKEM_SS_SIZE   32

/* psa_mldsa.c -- bits in {128, 192, 256} */
psa_status_t wolfpsa_mldsa_generate_seed(size_t bits, uint8_t *seed);
psa_status_t wolfpsa_mldsa_export_public(size_t bits, const uint8_t *seed,
        uint8_t *out, size_t out_size, size_t *out_length);
psa_status_t wolfpsa_mldsa_sign(size_t bits, const uint8_t *key_data,
        size_t key_data_length, psa_algorithm_t alg,
        const uint8_t *context, size_t context_length,
        const uint8_t *input, size_t input_length, int input_is_hash,
        uint8_t *signature, size_t signature_size, size_t *signature_length);
psa_status_t wolfpsa_mldsa_verify(size_t bits, psa_key_type_t key_type,
        const uint8_t *key_data, size_t key_data_length, psa_algorithm_t alg,
        const uint8_t *context, size_t context_length,
        const uint8_t *input, size_t input_length, int input_is_hash,
        const uint8_t *signature, size_t signature_length);

/* psa_mlkem.c -- bits in {512, 768, 1024} */
psa_status_t wolfpsa_mlkem_generate_seed(size_t bits, uint8_t *seed);
psa_status_t wolfpsa_mlkem_export_public(size_t bits, const uint8_t *seed,
        uint8_t *out, size_t out_size, size_t *out_length);
psa_status_t wolfpsa_mlkem_encapsulate(size_t bits, psa_key_type_t key_type,
        const uint8_t *key_data, size_t key_data_length,
        uint8_t *ciphertext, size_t ciphertext_size, size_t *ciphertext_length,
        uint8_t *shared_secret);
psa_status_t wolfpsa_mlkem_decapsulate(size_t bits, const uint8_t *seed,
        const uint8_t *ciphertext, size_t ciphertext_length,
        uint8_t *shared_secret);

/* psa_lms_xmss.c -- verify only, raw public keys */
psa_status_t wolfpsa_lms_verify(const uint8_t *pub, size_t pub_len,
        const uint8_t *msg, size_t msg_len, const uint8_t *sig, size_t sig_len);
psa_status_t wolfpsa_xmss_verify(const uint8_t *pub, size_t pub_len,
        const uint8_t *msg, size_t msg_len, const uint8_t *sig, size_t sig_len);

#endif /* PSA_PQC_INTERNAL_H */
