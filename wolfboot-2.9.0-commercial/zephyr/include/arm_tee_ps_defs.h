/* arm_tee_ps_defs.h
 *
 * ARM TEE protected storage message IDs.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_ARM_TEE_PS_DEFS_H_
#define WOLFBOOT_ARM_TEE_PS_DEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Protected Storage message types that distinguish PS services. */
#define ARM_TEE_PS_SET                1001
#define ARM_TEE_PS_GET                1002
#define ARM_TEE_PS_GET_INFO           1003
#define ARM_TEE_PS_REMOVE             1004
#define ARM_TEE_PS_GET_SUPPORT        1005

#ifdef __cplusplus
}
#endif

#endif /* WOLFBOOT_ARM_TEE_PS_DEFS_H_ */
