/* keystore.h
 *
 * API's for key store
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

#ifndef KEYSTORE_H
#define KEYSTORE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef KEYSTORE_PUBKEY_SIZE
    /* allow building version for external API use */
    #define KEYSTORE_ANY
#ifdef WOLFBOOT_SIGN_ML_DSA
    #define KEYSTORE_PUBKEY_SIZE KEYSTORE_PUBKEY_SIZE_ML_DSA
#else
    #define KEYSTORE_PUBKEY_SIZE KEYSTORE_PUBKEY_SIZE_RSA4096
#endif
#endif


struct keystore_slot {
    uint32_t slot_id;
    uint32_t key_type;
    uint32_t part_id_mask;
    uint32_t pubkey_size;
    uint8_t  pubkey[KEYSTORE_PUBKEY_SIZE];
};

#define KEYSTORE_HDR_SIZE 16
#define SIZEOF_KEYSTORE_SLOT (KEYSTORE_HDR_SIZE + KEYSTORE_PUBKEY_SIZE)

/* KeyStore API */
int keystore_num_pubkeys(void);
uint8_t *keystore_get_buffer(int id);
int keystore_get_size(int id);
uint32_t keystore_get_key_type(int id);
uint32_t keystore_get_mask(int id);


#ifdef __cplusplus
}
#endif

#endif /* KEYSTORE_H */
