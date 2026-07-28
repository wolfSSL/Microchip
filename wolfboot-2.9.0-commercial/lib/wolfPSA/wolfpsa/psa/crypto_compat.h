/* crypto_compat.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef PSA_CRYPTO_COMPAT_H
#define PSA_CRYPTO_COMPAT_H
#include "psa/crypto_types.h"
int psa_can_do_hash(psa_algorithm_t hash_alg);
#define PSA_KEY_TYPE_DES ((psa_key_type_t) 0x2301)
#define PSA_ALG_JPAKE_BETA PSA_ALG_JPAKE_BASE
#endif 
