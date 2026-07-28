/* psa_key_storage.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/**
 * Platform Security Architecture (PSA) Key Storage API header
 *
 * If WOLFSSL_PSA_ENGINE is defined, wolfSSL provides an implementation of the
 * PSA Crypto API for key storage that calls wolfCrypt APIs.
 *
 */

#ifndef WOLFSSL_PSA_KEY_STORAGE_H
#define WOLFSSL_PSA_KEY_STORAGE_H

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#if defined(WOLFSSL_PSA_ENGINE)

#include <psa/crypto.h>
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Key storage callback function types */
typedef int (*wc_KeyVault_Open_cb)(void** context);
typedef int (*wc_KeyVault_Close_cb)(void* context);
typedef int (*wc_KeyVault_Read_cb)(void* context, psa_key_id_t key_id, 
                                  uint8_t* data, size_t data_size, 
                                  size_t* data_length);
typedef int (*wc_KeyVault_Write_cb)(void* context, psa_key_id_t key_id, 
                                   const uint8_t* data, size_t data_length);
typedef int (*wc_KeyVault_Remove_cb)(void* context, psa_key_id_t key_id);
typedef int (*wc_KeyVault_GetInfo_cb)(void* context, psa_key_id_t key_id, 
                                     psa_key_attributes_t* attributes);

/* Key storage callback structure */
typedef struct {
    wc_KeyVault_Open_cb    open;
    wc_KeyVault_Close_cb   close;
    wc_KeyVault_Read_cb    read;
    wc_KeyVault_Write_cb   write;
    wc_KeyVault_Remove_cb  remove;
    wc_KeyVault_GetInfo_cb get_info;
} wc_KeyVault_Callbacks;

/* PSA Key Storage API Functions */
WOLFSSL_API psa_status_t psa_key_storage_init(const wc_KeyVault_Callbacks* callbacks);
WOLFSSL_API void psa_key_storage_cleanup(void);
WOLFSSL_API psa_status_t psa_import_key(const psa_key_attributes_t* attributes,
                                       const uint8_t* data,
                                       size_t data_length,
                                       psa_key_id_t* key_id);
WOLFSSL_API psa_status_t psa_generate_key(const psa_key_attributes_t* attributes,
                                         psa_key_id_t* key_id);
WOLFSSL_API psa_status_t psa_destroy_key(psa_key_id_t key_id);
WOLFSSL_API psa_status_t psa_export_key(psa_key_id_t key_id,
                                       uint8_t* data,
                                       size_t data_size,
                                       size_t* data_length);
WOLFSSL_API psa_status_t psa_export_public_key(psa_key_id_t key_id,
                                              uint8_t* data,
                                              size_t data_size,
                                              size_t* data_length);
WOLFSSL_API psa_status_t psa_get_key_attributes(psa_key_id_t key_id,
                                               psa_key_attributes_t* attributes);
WOLFSSL_API psa_status_t psa_copy_key(psa_key_id_t source_key,
                                     const psa_key_attributes_t* attributes,
                                     psa_key_id_t* target_key);

/* Internal helper to fetch raw key material from storage */
WOLFSSL_API psa_status_t wolfpsa_get_key_data(psa_key_id_t key_id,
                                             psa_key_attributes_t* attributes,
                                             uint8_t** key_data,
                                             size_t* key_data_length);
WOLFSSL_API void wolfpsa_forcezero_free_key_data(uint8_t* key_data,
                                                size_t key_data_length);

#ifdef __cplusplus
}
#endif

#endif /* WOLFSSL_PSA_ENGINE */
#endif /* WOLFSSL_PSA_KEY_STORAGE_H */
