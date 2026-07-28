/* arm_tee_psa_call_pack.h
 *
 * Packing helper for PSA call parameters.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_ARM_TEE_PSA_CALL_PACK_H_
#define WOLFBOOT_ARM_TEE_PSA_CALL_PACK_H_

#include <wolfboot/arm_tee_api.h>

#define PARAM_PACK(type, in_len, out_len) \
    WOLFBOOT_ARM_TEE_PARAM_PACK(type, in_len, out_len)

#endif /* WOLFBOOT_ARM_TEE_PSA_CALL_PACK_H_ */
