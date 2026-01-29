/* otp-keystore-primer.c
 *
 * Primer app to provision public keys into OTP flash
 *
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#include <stdint.h>
#include <string.h>
#include "wolfboot/wolfboot.h"
#include "hal.h"
#include "otp_keystore.h"

extern struct keystore_slot PubKeys[];

void main(void)
{
    int n_keys = keystore_num_pubkeys();
    int i;
    struct wolfBoot_otp_hdr hdr;
    uint32_t tot_len;

    hal_init();

    memcpy(hdr.keystore_hdr_magic, KEYSTORE_HDR_MAGIC, 8);
    hdr.item_count = n_keys;
    hdr.flags = 0;
    hdr.version = WOLFBOOT_VERSION;

    /* Sanity check to avoid writing an empty keystore */
    if (n_keys < 1) {
        while(1)
            ;
    }

    /* Write the header to the beginning of the OTP memory */
    hal_flash_otp_write(FLASH_OTP_BASE, (uint16_t *)&hdr, sizeof(hdr));

    for (i = 0; i < n_keys; i++) {
        /* Write each public key to its slot in OTP */
        hal_flash_otp_write(FLASH_OTP_BASE +
                OTP_HDR_SIZE + i * SIZEOF_KEYSTORE_SLOT, (uint16_t *)&PubKeys[i],
                sizeof(struct keystore_slot));
    }

    tot_len = OTP_HDR_SIZE + n_keys * SIZEOF_KEYSTORE_SLOT;

#ifdef ENABLE_OTP_WP
    /* Protect the OTP area just written */
    hal_flash_otp_set_readonly(FLASH_OTP_BASE, tot_len);
#endif
    (void)tot_len;

    /* Done! */
    while(1)
        ;

}
