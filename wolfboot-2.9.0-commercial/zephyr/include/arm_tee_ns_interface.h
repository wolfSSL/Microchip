/* arm_tee_ns_interface.h
 *
 * ARM TEE NS interface helpers for PSA client dispatch.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_ARM_TEE_NS_INTERFACE_H_
#define WOLFBOOT_ARM_TEE_NS_INTERFACE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t (*arm_tee_veneer_fn)(uint32_t arg0, uint32_t arg1,
    uint32_t arg2, uint32_t arg3);

int32_t arm_tee_ns_interface_dispatch(arm_tee_veneer_fn fn,
    uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3);

uint32_t arm_tee_ns_interface_init(void);

#ifdef __cplusplus
}
#endif

#endif /* WOLFBOOT_ARM_TEE_NS_INTERFACE_H_ */
