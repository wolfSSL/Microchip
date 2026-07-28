/* arm_tee_attest_defs.h
 *
 * ARM TEE attestation message IDs.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_ARM_TEE_ATTEST_DEFS_H_
#define WOLFBOOT_ARM_TEE_ATTEST_DEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Initial Attestation message types that distinguish Attest services. */
#define ARM_TEE_ATTEST_GET_TOKEN       1001
#define ARM_TEE_ATTEST_GET_TOKEN_SIZE  1002
#define ARM_TEE_ATTEST_GET_IAK_PUBKEY  1003

#ifdef __cplusplus
}
#endif

#endif /* WOLFBOOT_ARM_TEE_ATTEST_DEFS_H_ */
