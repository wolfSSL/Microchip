/*
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * wolfhsm/wh_server_img_mgr.h
 *
 */

#ifndef WOLFHSM_WH_SERVER_IMG_MGR_H_
#define WOLFHSM_WH_SERVER_IMG_MGR_H_

#include "wolfhsm/wh_settings.h"

#ifdef WOLFHSM_CFG_SERVER_IMG_MGR

#include <stdint.h>
#include <stddef.h>

#include "wolfhsm/wh_common.h"
#include "wolfhsm/wh_server.h"

/* wolfBoot header constants */
#define WH_IMG_MGR_WOLFBOOT_MAGIC 0x464C4F57 /* "WOLF" LE */
#define WH_IMG_MGR_WOLFBOOT_HDR_OFFSET 8

/* wolfBoot TLV types */
#define WH_IMG_MGR_WOLFBOOT_HDR_SHA256 0x03
#define WH_IMG_MGR_WOLFBOOT_HDR_IMG_TYPE 0x04
#define WH_IMG_MGR_WOLFBOOT_HDR_PUBKEY 0x10
#define WH_IMG_MGR_WOLFBOOT_HDR_SIGNATURE 0x20
#define WH_IMG_MGR_WOLFBOOT_HDR_CERT_CHAIN 0x23
#define WH_IMG_MGR_WOLFBOOT_HDR_PADDING 0xFF

/* wolfBoot auth key types (from high byte of img_type) */
#define WH_IMG_MGR_WOLFBOOT_AUTH_RSA4096 0x04
#define WH_IMG_MGR_WOLFBOOT_HDR_IMG_TYPE_AUTH_MASK 0xFF00

/* Image type enum controlling how the framework loads keys/signatures */
typedef enum {
    WH_IMG_MGR_IMG_TYPE_RAW = 0,       /* Key from keystore, sig from NVM */
    WH_IMG_MGR_IMG_TYPE_WOLFBOOT,      /* Key from keystore, sig from header */
    WH_IMG_MGR_IMG_TYPE_WOLFBOOT_CERT, /* Root CA from NVM, cert chain + sig
                                          from header */
} whServerImgMgrImgType;

/* Forward declaration for callback function signatures */
typedef struct whServerImgMgrContext_t whServerImgMgrContext;

/* Forward declare so the callbacks can reference the parent struct */
struct whServerImgMgrImg;

/**
 * @brief Image verification method callback
 *
 * This callback performs the actual cryptographic verification of an image.
 * It receives the image metadata, key data, and signature data, and returns
 * the verification result.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure containing verification parameters
 * @param[in] key Key data for verification
 * @param[in] keySz Size of key data
 * @param[in] sig Signature data for verification
 * @param[in] sigSz Size of signature data
 * @return WH_ERROR_OK on successful verification, WH_ERROR_NOTVERIFIED or a
 * specific wolfCrypt error code when verification fails, other negative error
 * codes for other operational failures
 */
typedef int (*whServerImgMgrVerifyMethod)(whServerImgMgrContext* context,
                                          const struct whServerImgMgrImg* img,
                                          const uint8_t* key, size_t keySz,
                                          const uint8_t* sig, size_t sigSz);

/**
 * @brief Image verification action callback
 *
 * This callback is invoked after the verification method completes.
 * It receives the verification result and can perform actions based on
 * whether the verification succeeded or failed.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure containing verification parameters
 * @param[in] verifyResult Result from the verification method
 * @return WH_ERROR_OK on success, negative error code on failure
 */
typedef int (*whServerImgMgrVerifyAction)(whServerImgMgrContext* context,
                                          const struct whServerImgMgrImg* img,
                                          int verifyResult);

/*
 * @brief Image structure for verification
 *
 * This structure defines an image to be verified, including its location,
 * the key and signature identifiers, and the callbacks for verification
 * and post-verification actions.
 */
typedef struct whServerImgMgrImg {
    uintptr_t addr;     /* RAW: image blob. WOLFBOOT: firmware payload */
    size_t    size;     /* RAW: blob size. WOLFBOOT: max payload size, actual
                            size obtained from manifest header */
    uintptr_t hdrAddr;  /* wolfBoot header address (unused for RAW). Must be
                            2-byte aligned for WOLFBOOT/WOLFBOOT_CERT. */
    size_t    hdrSize;  /* wolfBoot header size (unused for RAW) */
    whKeyId   keyId;    /* RAW/WOLFBOOT: verify key ID. WOLFBOOT_CERT: unused */
    whNvmId   sigNvmId; /* RAW: sig NVM ID. WOLFBOOT_CERT: root CA NVM ID */
    whServerImgMgrImgType imgType; /* Controls framework loading behavior */
    whServerImgMgrVerifyMethod verifyMethod; /* Verification callback */
    whServerImgMgrVerifyAction verifyAction; /* Post-verification action */
} whServerImgMgrImg;

/*
 * @brief Image manager configuration structure
 *
 * Configuration structure passed to the image manager during initialization.
 * Contains the list of images to manage and their count.
 */
typedef struct whServerImgMgrConfig {
    whServerImgMgrImg* images;     /* Pointer to array of images */
    size_t             imageCount; /* Number of images in array */
    whServerContext*   server;     /* Server context for NVM/DMA access */
} whServerImgMgrConfig;

/*
 * @brief Image verification result structure
 *
 * Structure containing detailed results from image verification operations.
 * Provides separate access to verification method and action results.
 */
typedef struct whServerImgMgrVerifyResult {
    int verifyMethodResult; /* Result from the verification method callback */
    int verifyActionResult; /* Result from the verification action callback */
} whServerImgMgrVerifyResult;

/*
 * @brief Image manager context structure
 *
 * Context structure that maintains the state of the image manager.
 * This is embedded in the main server context.
 */
struct whServerImgMgrContext_t {
    whServerImgMgrImg images[WOLFHSM_CFG_SERVER_IMG_MGR_MAX_IMG_COUNT];
    size_t            imageCount;
    whServerContext*  server; /* Server context for NVM/DMA access */
};

/**
 * @brief Initialize the image manager
 *
 * Initializes the image manager context with the provided configuration.
 * Registers the list of images to be managed.
 *
 * @param[in] context Image manager context to initialize
 * @param[in] config Configuration containing image list
 * @return WH_ERROR_OK on success, negative error code on failure
 */
int wh_Server_ImgMgrInit(whServerImgMgrContext*      context,
                         const whServerImgMgrConfig* config);

/**
 * @brief Verify all registered images
 *
 * Iterates through all registered images and verifies each one.
 * Calls the verification method and action callbacks for each image.
 * Populates detailed verification results for each image.
 *
 * @param[in] context Image manager context
 * @param[out] outResults Array to store verification results for each image
 * @param[in] outResultsCount Number of result slots in the results array (must
 * be == context->imageCount)
 * @param[out] outErrorIdx Holds the index of the image whose verification
 * returned an error (indicated via this function's return value).  Only valid
 * if return value is not WH_ERROR_OK.  If no error occurred, this value is not
 * updated.
 *
 * @return WH_ERROR_OK on success, negative error code on failure.
 */
int wh_Server_ImgMgrVerifyAll(whServerImgMgrContext*      context,
                              whServerImgMgrVerifyResult* outResults,
                              size_t outResultsCount, size_t* outErrorIdx);

/**
 * @brief Verify an image by reference
 *
 * Verifies a specific image by direct reference to its structure.
 * Performs DMA operations, key loading, and signature verification.
 * Populates detailed verification results.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure to verify
 * @param[out] outResult Verification result. Only valid when function returns
 * WH_ERROR_OK.
 * @return WH_ERROR_OK on success, negative error code on failure
 */
int wh_Server_ImgMgrVerifyImg(whServerImgMgrContext*      context,
                              const whServerImgMgrImg*    img,
                              whServerImgMgrVerifyResult* outResult);

/**
 * @brief Verify an image by index
 *
 * Verifies a specific image by its index in the registered image array.
 * Populates detailed verification results.
 *
 * @param[in] context Image manager context
 * @param[in] imgIdx Index of image to verify
 * @param[out] outResult Verification result. Only valid when function returns
 * WH_ERROR_OK.
 * @return WH_ERROR_OK on success, negative error code on failure
 */
int wh_Server_ImgMgrVerifyImgIdx(whServerImgMgrContext* context, size_t imgIdx,
                                 whServerImgMgrVerifyResult* outResult);

/* Built-in verification method callbacks */

/**
 * @brief Default ECC P256 verification method
 *
 * Default implementation of image verification using ECC P256 signatures.
 * Uses wolfCrypt to hash the image data and verify the signature.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure containing verification parameters
 * @param[in] key ECC public key data
 * @param[in] keySz Size of key data
 * @param[in] sig Signature data
 * @param[in] sigSz Size of signature data
 * @return WH_ERROR_OK on successful verification, negative error code on
 * failure
 */
int wh_Server_ImgMgrVerifyMethodEccWithSha256(whServerImgMgrContext*   context,
                                              const whServerImgMgrImg* img,
                                              const uint8_t* key, size_t keySz,
                                              const uint8_t* sig, size_t sigSz);

/**
 * @brief AES128 CMAC verification method
 *
 * Implementation of image verification using AES128 CMAC.
 * Uses wolfCrypt to compute CMAC of the image data and compare with signature.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure containing verification parameters
 * @param[in] key AES128 key data (16 bytes)
 * @param[in] keySz Size of key data (must be 16)
 * @param[in] sig CMAC signature data (16 bytes)
 * @param[in] sigSz Size of signature data (must be 16)
 * @return WH_ERROR_OK on successful verification, negative error code on
 * failure
 */
int wh_Server_ImgMgrVerifyMethodAesCmac(whServerImgMgrContext*   context,
                                        const whServerImgMgrImg* img,
                                        const uint8_t* key, size_t keySz,
                                        const uint8_t* sig, size_t sigSz);

/**
 * @brief RSA2048 signature verification method
 *
 * Implementation of image verification using RSA2048 signatures.
 * Uses wolfCrypt wc_RsaSSL_Verify to verify RSA signatures against SHA256 hash.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure containing verification parameters
 * @param[in] key RSA public key data (DER format)
 * @param[in] keySz Size of key data
 * @param[in] sig RSA signature data
 * @param[in] sigSz Size of signature data
 * @return WH_ERROR_OK on successful verification, negative error code on
 * failure
 */
int wh_Server_ImgMgrVerifyMethodRsaSslWithSha256(
    whServerImgMgrContext* context, const whServerImgMgrImg* img,
    const uint8_t* key, size_t keySz, const uint8_t* sig, size_t sigSz);

/**
 * @brief wolfBoot RSA4096+SHA256 verification method
 *
 * Verifies a wolfBoot image using RSA4096 signature with SHA256 hash.
 * The public key is provided by the framework (loaded from keystore).
 * The signature is extracted from the wolfBoot header at img->hdrAddr.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure with hdrAddr pointing to wolfBoot header
 *                (must be 2-byte aligned) and addr pointing to firmware payload
 * @param[in] key RSA4096 public key data (DER format)
 * @param[in] keySz Size of key data
 * @param[in] sig Unused (NULL), signature is read from wolfBoot header
 * @param[in] sigSz Unused (0)
 * @return WH_ERROR_OK on successful verification, negative error code on
 * failure
 */
int wh_Server_ImgMgrVerifyMethodWolfBootRsa4096WithSha256(
    whServerImgMgrContext* context, const whServerImgMgrImg* img,
    const uint8_t* key, size_t keySz, const uint8_t* sig, size_t sigSz);

/**
 * @brief wolfBoot RSA4096+SHA256 cert chain verification method
 *
 * Verifies a wolfBoot image using RSA4096 signature with SHA256 hash,
 * where the signing key is validated through a certificate chain.
 * The root CA cert NVM ID is read from img->sigNvmId.
 * The cert chain and signature are extracted from the wolfBoot header.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure with hdrAddr pointing to wolfBoot header
 *                (must be 2-byte aligned) and addr pointing to firmware payload
 * @param[in] key Unused (NULL), leaf key is extracted from cert chain
 * @param[in] keySz Unused (0)
 * @param[in] sig Unused (NULL), signature is read from wolfBoot header
 * @param[in] sigSz Unused (0)
 * @return WH_ERROR_OK on successful verification, negative error code on
 * failure
 */
int wh_Server_ImgMgrVerifyMethodWolfBootCertChainRsa4096WithSha256(
    whServerImgMgrContext* context, const whServerImgMgrImg* img,
    const uint8_t* key, size_t keySz, const uint8_t* sig, size_t sigSz);

/**
 * @brief Default verification action callback
 *
 * Default implementation of post-verification action. Simply returns
 * the verification result without performing additional actions.
 *
 * @param[in] context Image manager context
 * @param[in] img Image structure containing verification parameters
 * @param[in] verifyResult Result from the verification method
 * @return verifyResult (passes through the verification result)
 */
int wh_Server_ImgMgrVerifyActionDefault(whServerImgMgrContext*   context,
                                        const whServerImgMgrImg* img,
                                        int                      verifyResult);

#endif /* WOLFHSM_CFG_SERVER_IMG_MGR */

#endif /* !WOLFHSM_WH_SERVER_IMG_MGR_H_ */
