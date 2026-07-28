/* arm_tee_veneers.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_ARM_TEE_VENEERS_H_
#define WOLFBOOT_ARM_TEE_VENEERS_H_

#include <stdint.h>
#include "psa/client.h"
#include <wolfboot/arm_tee_api.h>

#ifdef __cplusplus
extern "C" {
#endif

/* wolfBoot CMSE veneers (ARM TEE compatible names). */
uint32_t arm_tee_psa_framework_version_veneer(void);
uint32_t arm_tee_psa_version_veneer(uint32_t sid);
psa_handle_t arm_tee_psa_connect_veneer(uint32_t sid, uint32_t version);
psa_status_t arm_tee_psa_call_veneer(psa_handle_t handle,
				 uint32_t ctrl_param,
				 const psa_invec *in_vec,
				 psa_outvec *out_vec);
void arm_tee_psa_close_veneer(psa_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* WOLFBOOT_ARM_TEE_VENEERS_H_ */
