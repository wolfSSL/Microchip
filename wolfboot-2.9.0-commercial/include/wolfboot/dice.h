/* dice.h
 *
 * DICE helpers and PSA attestation token builder.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_DICE_H
#define WOLFBOOT_DICE_H

#include <stddef.h>
#include <stdint.h>

/* Component name used in the DICE claims for the wolfBoot measurement.
 * Shared between dice.c (producer) and HAL (consumer) to keep them in sync. */
#define WOLFBOOT_DICE_COMPONENT_WOLFBOOT  "wolfboot"
#define WOLFBOOT_DICE_COMPONENT_BOOTIMAGE "boot-image"

#ifdef __cplusplus
extern "C" {
#endif

int wolfBoot_dice_get_token(const uint8_t *challenge,
                            size_t challenge_size,
                            uint8_t *token_buf,
                            size_t token_buf_size,
                            size_t *token_size);

int wolfBoot_dice_get_token_size(size_t challenge_size, size_t *token_size);

/* Retrieve the IAK public key as a 65-byte X9.63 uncompressed point
 * (0x04 || X[32] || Y[32]).  Must be called after wolfBoot_dice_get_token().
 * The internal copy is zeroized after this call (read-once).
 * Not available when WOLFBOOT_ATTESTATION_IAK is set (provisioned key is used). */
#ifndef WOLFBOOT_ATTESTATION_IAK
int wolfBoot_dice_get_attest_pubkey(uint8_t *buf, size_t *len);
#endif /* !WOLFBOOT_ATTESTATION_IAK */

#ifdef __cplusplus
}
#endif

#endif /* WOLFBOOT_DICE_H */
