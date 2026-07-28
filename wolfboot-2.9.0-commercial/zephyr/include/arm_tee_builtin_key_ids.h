/* arm_tee_builtin_key_ids.h
 *
 * ARM TEE builtin key identifiers.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_ARM_TEE_BUILTIN_KEY_IDS_H_
#define WOLFBOOT_ARM_TEE_BUILTIN_KEY_IDS_H_

/**
 * \brief The persistent key identifiers for builtin keys.
 */
enum arm_tee_builtin_key_id_t {
    ARM_TEE_BUILTIN_KEY_ID_MIN = 0x7FFF815Bu,
    ARM_TEE_BUILTIN_KEY_ID_HUK,
    ARM_TEE_BUILTIN_KEY_ID_IAK,
#ifdef ARM_TEE_PARTITION_DELEGATED_ATTESTATION
    ARM_TEE_BUILTIN_KEY_ID_DAK_SEED,
#endif
    ARM_TEE_BUILTIN_KEY_ID_PLAT_SPECIFIC_MIN = 0x7FFF816Bu,
    ARM_TEE_BUILTIN_KEY_ID_MAX = 0x7FFF817Bu,
};

#endif /* WOLFBOOT_ARM_TEE_BUILTIN_KEY_IDS_H_ */
