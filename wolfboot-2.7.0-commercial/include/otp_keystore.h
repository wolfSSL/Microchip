/* otp_keystore.h
 *
 * Helper for storing/retrieving Trust Anchor to/from OTP flash
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


#ifndef OTP_KEYSTORE_H
#define OTP_KEYSTORE_H

#if defined(FLASH_OTP_KEYSTORE) && !defined(WOLFBOOT_NO_SIGN)
/* Specific includes for supported targets
 * (needed for OTP_SIZE)
 */
#ifdef TARGET_stm32h7
    #include "hal/stm32h7.h"
#elif defined TARGET_stm32h5
    #include "hal/stm32h5.h"
#endif

#include "keystore.h"

#define OTP_HDR_SIZE 16

#if (defined(__IAR_SYSTEMS_ICC__) && (__IAR_SYSTEMS_ICC__ > 8)) || \
        defined(__GNUC__)
    #define KEYSTORE_HDR_PACKED __attribute__((packed))
#else
    #define KEYSTORE_HDR_PACKED
#endif

struct KEYSTORE_HDR_PACKED wolfBoot_otp_hdr {
    char keystore_hdr_magic[8];
    uint16_t item_count;
    uint16_t flags;
    uint32_t version;
};

static const char KEYSTORE_HDR_MAGIC[8] = "WOLFBOOT";

#define KEYSTORE_MAX_PUBKEYS ((OTP_SIZE - OTP_HDR_SIZE) / SIZEOF_KEYSTORE_SLOT)

#if (OTP_SIZE == 0)
#error WRONG OTP SIZE
#endif

#if (KEYSTORE_MAX_PUBKEYS < 1)
    #error "No space for any keystores in OTP with current algorithm"
#endif

#endif /* FLASH_OTP_KEYSTORE */ 

#endif /* OTP_KEYSTORE_H */
