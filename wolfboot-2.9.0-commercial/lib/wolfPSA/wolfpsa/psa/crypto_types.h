/* crypto_types.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef PSA_CRYPTO_TYPES_H
#define PSA_CRYPTO_TYPES_H

#include <stddef.h>
#include <stdint.h>


#ifndef PSA_SUCCESS
typedef int32_t psa_status_t;
#endif

typedef uint16_t psa_key_type_t;
typedef uint8_t psa_ecc_family_t;
typedef uint8_t psa_dh_family_t;
typedef uint32_t psa_algorithm_t;
typedef uint32_t psa_key_lifetime_t;
typedef uint8_t psa_key_persistence_t;
typedef uint32_t psa_key_location_t;
typedef uint32_t psa_key_id_t;
typedef uint32_t psa_key_usage_t;
typedef uint16_t psa_key_derivation_step_t;
typedef uint32_t psa_pake_primitive_t;
typedef uint8_t psa_pake_primitive_type_t;
typedef uint8_t psa_pake_family_t;
typedef uint8_t psa_pake_role_t;
typedef uint8_t psa_pake_step_t;

typedef struct psa_key_attributes_s psa_key_attributes_t;
typedef struct psa_custom_key_parameters_s psa_custom_key_parameters_t;
typedef struct psa_pake_cipher_suite_s psa_pake_cipher_suite_t;
typedef struct psa_pake_operation_s psa_pake_operation_t;

#endif 
