/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * wolfhsm/wh_server_cert.h
 */

#ifndef WOLFHSM_WH_SERVER_CERT_H_
#define WOLFHSM_WH_SERVER_CERT_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

#include "wolfhsm/wh_server.h"
#include "wolfhsm/wh_nvm.h"

/**
 * @brief Initialize the certificate manager
 * @param server The server context
 * @return WH_ERROR_OK on success, error code on failure
 */
int wh_Server_CertInit(whServerContext* server);

/**
 * @brief Add a trusted certificate to NVM storage
 * @param server The server context
 * @param id The NVM ID to store the certificate under
 * @param cert The certificate data buffer
 * @param cert_len Length of the certificate data
 * @param flags NVM flags for the certificate storage
 * @return WH_ERROR_OK on success, error code on failure
 */
int wh_Server_CertAddTrusted(whServerContext* server, whNvmId id,
                             whNvmAccess access, whNvmFlags flags,
                             const uint8_t* label, whNvmSize label_len,
                             const uint8_t* cert, uint32_t cert_len);

/**
 * @brief Delete a trusted certificate from NVM storage
 * @param server The server context
 * @param id The NVM ID of the certificate to delete
 * @return WH_ERROR_OK on success, error code on failure
 */
int wh_Server_CertEraseTrusted(whServerContext* server, whNvmId id);

/**
 * @brief Get a trusted certificate from NVM storage
 * @param server The server context
 * @param id The NVM ID of the certificate to read
 * @param cert Buffer to store the certificate data
 * @param inout_cert_len On input, size of cert buffer. On output, actual cert
 * size
 * @return WH_ERROR_OK on success, error code on failure. If certificate is too
 * large for the buffer, WH_ERROR_BUFFER_SIZE will be returned and
 * inout_cert_len will be updated to the actual certificate size.
 */
int wh_Server_CertReadTrusted(whServerContext* server, whNvmId id,
                              uint8_t* cert, uint32_t* inout_cert_len);

/**
 * @brief Verify a certificate against trusted certificates
 * @param server The server context
 * @param cert The certificate data to verify
 * @param cert_len Length of the certificate data
 * @param trustedRootNvmId NVM ID of the trusted root certificate
 * @param flags Flags for the certificate verification (see WH_CERT_FLAGS_* in
 * wh_common.h)
 * @param cachedKeyFlags NVM usage flags to apply when caching the leaf public
 * key (only used if WH_CERT_FLAGS_CACHE_LEAF_PUBKEY is set)
 * @param inout_keyId Only valid if WH_CERT_FLAGS_CACHE_LEAF_PUBKEY is set. On
 * input, set to the keyId to use when caching the leaf public key. If set to
 * WH_KEYID_ERASED then a new unique keyId will be generated. On output, holds
 * the keyId used for the leaf certificate.
 * @return WH_ERROR_OK on success, error code on failure
 */
int wh_Server_CertVerify(whServerContext* server, const uint8_t* cert,
                         uint32_t cert_len, whNvmId trustedRootNvmId,
                         whCertFlags flags, whNvmFlags cachedKeyFlags,
                         whKeyId* inout_keyId);

#if defined(WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT)
/**
 * @brief Verifies an attribute certificate against a trusted root certificate
 *
 * This function retrieves a trusted root certificate from NVM using the
 * specified NVM ID and verifies the provided attribute certificate against it.
 *
 * @param[in] server Pointer to the server context
 * @param[in] cert Pointer to the attribute certificate data to verify
 * @param[in] cert_len Length of the certificate data in bytes
 * @param[in] trustedRootNvmId NVM ID of the trusted root certificate to verify
 * against
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int wh_Server_CertVerifyAcert(whServerContext* server, const uint8_t* cert,
                              uint32_t cert_len, whNvmId trustedRootNvmId);
#endif

/**
 * @brief Handle a certificate request and generate a response
 * @param server The server context
 * @param magic Magic number for message validation
 * @param action The certificate action to perform
 * @param seq Sequence number for the request
 * @param req_size Size of the request packet
 * @param req_packet The request packet data
 * @param out_resp_size Size of the response packet
 * @param resp_packet Buffer to store the response packet
 * @return WH_ERROR_OK on success, error code on failure
 */
int wh_Server_HandleCertRequest(whServerContext* server, uint16_t magic,
                                uint16_t action, uint16_t seq,
                                uint16_t req_size, const void* req_packet,
                                uint16_t* out_resp_size, void* resp_packet);

#endif /* !WOLFHSM_WH_SERVER_CERT_H_ */