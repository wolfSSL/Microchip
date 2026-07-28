/* crypto-pqc.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Implements the PSA Certified Crypto API 1.4 PQC extension appendix. */

#ifndef PSA_CRYPTO_PQC_H
#define PSA_CRYPTO_PQC_H

#include "psa/crypto_types.h"

typedef uint8_t psa_slh_dsa_family_t;

/* --- Additional hash algorithm identifiers used by PQC --- */

#define PSA_ALG_SHA_256_192     ((psa_algorithm_t)0x0200000E)
#define PSA_ALG_SHAKE128_256    ((psa_algorithm_t)0x02000016)
#define PSA_ALG_SHAKE256_192    ((psa_algorithm_t)0x02000017)
#define PSA_ALG_SHAKE256_256    ((psa_algorithm_t)0x02000018)

/* --- ML-KEM (CRYSTALS-Kyber) --- */

#define PSA_KEY_TYPE_ML_KEM_KEY_PAIR    ((psa_key_type_t)0x7004)
#define PSA_KEY_TYPE_ML_KEM_PUBLIC_KEY  ((psa_key_type_t)0x4004)
#define PSA_KEY_TYPE_IS_ML_KEM(type) \
    (PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) == 0x4004)
#define PSA_ALG_ML_KEM  ((psa_algorithm_t)0x0c000200)

/* --- ML-DSA (CRYSTALS-Dilithium) --- */

#define PSA_KEY_TYPE_ML_DSA_KEY_PAIR    ((psa_key_type_t)0x7002)
#define PSA_KEY_TYPE_ML_DSA_PUBLIC_KEY  ((psa_key_type_t)0x4002)
#define PSA_KEY_TYPE_IS_ML_DSA(type) \
    (PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) == 0x4002)
#define PSA_ALG_ML_DSA              ((psa_algorithm_t)0x06004400)
#define PSA_ALG_DETERMINISTIC_ML_DSA    ((psa_algorithm_t)0x06004500)
#define PSA_ALG_HASH_ML_DSA(hash_alg) \
    ((psa_algorithm_t)(0x06004600 | ((hash_alg) & 0x000000ff)))
#define PSA_ALG_DETERMINISTIC_HASH_ML_DSA(hash_alg) \
    ((psa_algorithm_t)(0x06004700 | ((hash_alg) & 0x000000ff)))
#define PSA_ALG_IS_ML_DSA(alg) \
    (((alg) & ~0x00000100U) == 0x06004400)
#define PSA_ALG_IS_HASH_ML_DSA(alg) \
    (((alg) & ~0x000001ffU) == 0x06004600)
#define PSA_ALG_IS_DETERMINISTIC_HASH_ML_DSA(alg) \
    (((alg) & ~0x000000ffU) == 0x06004700)
#define PSA_ALG_IS_HEDGED_HASH_ML_DSA(alg) \
    (((alg) & ~0x000000ffU) == 0x06004600)

/* --- SLH-DSA (SPHINCS+) --- */

#define PSA_SLH_DSA_FAMILY_SHA2_S   ((psa_slh_dsa_family_t)0x02)
#define PSA_SLH_DSA_FAMILY_SHA2_F   ((psa_slh_dsa_family_t)0x04)
#define PSA_SLH_DSA_FAMILY_SHAKE_S  ((psa_slh_dsa_family_t)0x0b)
#define PSA_SLH_DSA_FAMILY_SHAKE_F  ((psa_slh_dsa_family_t)0x0d)
#define PSA_KEY_TYPE_SLH_DSA_KEY_PAIR(set) \
    ((psa_key_type_t)(0x7180 | ((set) & 0x007f)))
#define PSA_KEY_TYPE_SLH_DSA_PUBLIC_KEY(set) \
    ((psa_key_type_t)(0x4180 | ((set) & 0x007f)))
#define PSA_KEY_TYPE_IS_SLH_DSA(type) \
    ((PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(type) & 0xff80) == 0x4180)
#define PSA_KEY_TYPE_IS_SLH_DSA_KEY_PAIR(type) \
    (((type) & 0xff80) == 0x7180)
#define PSA_KEY_TYPE_IS_SLH_DSA_PUBLIC_KEY(type) \
    (((type) & 0xff80) == 0x4180)
#define PSA_KEY_TYPE_SLH_DSA_GET_FAMILY(type) \
    ((psa_slh_dsa_family_t)((type) & 0x007f))
#define PSA_ALG_SLH_DSA             ((psa_algorithm_t)0x06004000)
#define PSA_ALG_DETERMINISTIC_SLH_DSA   ((psa_algorithm_t)0x06004100)
#define PSA_ALG_HASH_SLH_DSA(hash_alg) \
    ((psa_algorithm_t)(0x06004200 | ((hash_alg) & 0x000000ff)))
#define PSA_ALG_DETERMINISTIC_HASH_SLH_DSA(hash_alg) \
    ((psa_algorithm_t)(0x06004300 | ((hash_alg) & 0x000000ff)))
#define PSA_ALG_IS_SLH_DSA(alg) \
    (((alg) & ~0x00000100U) == 0x06004000)
#define PSA_ALG_IS_HASH_SLH_DSA(alg) \
    (((alg) & ~0x000001ffU) == 0x06004200)
#define PSA_ALG_IS_DETERMINISTIC_HASH_SLH_DSA(alg) \
    (((alg) & ~0x000000ffU) == 0x06004300)
#define PSA_ALG_IS_HEDGED_HASH_SLH_DSA(alg) \
    (((alg) & ~0x000000ffU) == 0x06004200)

/* --- LMS / HSS --- */

#define PSA_KEY_TYPE_LMS_PUBLIC_KEY ((psa_key_type_t)0x4007)
#define PSA_KEY_TYPE_HSS_PUBLIC_KEY ((psa_key_type_t)0x4008)
#define PSA_ALG_LMS ((psa_algorithm_t)0x06004800)
#define PSA_ALG_HSS ((psa_algorithm_t)0x06004900)

/* --- XMSS / XMSS^MT --- */

#define PSA_KEY_TYPE_XMSS_PUBLIC_KEY    ((psa_key_type_t)0x400B)
#define PSA_KEY_TYPE_XMSS_MT_PUBLIC_KEY ((psa_key_type_t)0x400D)
#define PSA_ALG_XMSS   ((psa_algorithm_t)0x06004A00)
#define PSA_ALG_XMSS_MT    ((psa_algorithm_t)0x06004B00)

#endif /* PSA_CRYPTO_PQC_H */
