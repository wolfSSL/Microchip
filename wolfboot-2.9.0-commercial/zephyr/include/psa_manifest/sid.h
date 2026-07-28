/* sid.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef PSA_MANIFEST_SID_H_
#define PSA_MANIFEST_SID_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Service IDs and handles aligned with ARM TEE defaults. */
#define ARM_TEE_ATTESTATION_SERVICE_SID                 (0x00000020U)
#define ARM_TEE_ATTESTATION_SERVICE_VERSION             (1U)
#define ARM_TEE_ATTESTATION_SERVICE_HANDLE              (4U)

#define ARM_TEE_PLATFORM_SERVICE_SID                    (0x00000040U)
#define ARM_TEE_PLATFORM_SERVICE_VERSION                (1U)
#define ARM_TEE_PLATFORM_SERVICE_HANDLE                 (6U)

#define ARM_TEE_PROTECTED_STORAGE_SERVICE_SID           (0x00000060U)
#define ARM_TEE_PROTECTED_STORAGE_SERVICE_VERSION       (1U)
#define ARM_TEE_PROTECTED_STORAGE_SERVICE_HANDLE        (2U)

#define ARM_TEE_INTERNAL_TRUSTED_STORAGE_SERVICE_SID    (0x00000070U)
#define ARM_TEE_INTERNAL_TRUSTED_STORAGE_SERVICE_VERSION (1U)
#define ARM_TEE_INTERNAL_TRUSTED_STORAGE_SERVICE_HANDLE (3U)

#define ARM_TEE_CRYPTO_SID                              (0x00000080U)
#define ARM_TEE_CRYPTO_VERSION                          (1U)
#define ARM_TEE_CRYPTO_HANDLE                           (1U)

#ifdef __cplusplus
}
#endif

#endif /* PSA_MANIFEST_SID_H_ */
