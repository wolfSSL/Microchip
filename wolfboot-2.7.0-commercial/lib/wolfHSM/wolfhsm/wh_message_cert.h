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
 * wolfhsm/wh_message_cert.h
 */

#ifndef WOLFHSM_WH_MESSAGE_CERT_H_
#define WOLFHSM_WH_MESSAGE_CERT_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

#include "wolfhsm/wh_common.h"
#include "wolfhsm/wh_comm.h"
#include "wolfhsm/wh_message.h"
#include "wolfhsm/wh_nvm.h"

enum WH_MESSAGE_CERT_ACTION_ENUM {
    WH_MESSAGE_CERT_ACTION_INIT             = 0x1,
    WH_MESSAGE_CERT_ACTION_ADDTRUSTED       = 0x2,
    WH_MESSAGE_CERT_ACTION_ERASETRUSTED     = 0x3,
    WH_MESSAGE_CERT_ACTION_READTRUSTED      = 0x4,
    WH_MESSAGE_CERT_ACTION_VERIFY           = 0x5,
    WH_MESSAGE_CERT_ACTION_ADDTRUSTED_DMA   = 0x22,
    WH_MESSAGE_CERT_ACTION_READTRUSTED_DMA  = 0x24,
    WH_MESSAGE_CERT_ACTION_VERIFY_DMA       = 0x25,
    WH_MESSAGE_CERT_ACTION_VERIFY_ACERT     = 0x26,
    WH_MESSAGE_CERT_ACTION_VERIFY_ACERT_DMA = 0x27,
};

/* Simple reusable response message */
typedef struct {
    int32_t rc;
    uint8_t WH_PAD[4];
} whMessageCert_SimpleResponse;

int wh_MessageCert_TranslateSimpleResponse(
    uint16_t magic, const whMessageCert_SimpleResponse* src,
    whMessageCert_SimpleResponse* dest);

/* Init Request/Response */
/* Empty request message */
/* Use SimpleResponse */

/* AddTrusted Request */
typedef struct {
    uint32_t    cert_len;
    whNvmId     id;
    whNvmAccess access;
    whNvmFlags  flags;
    uint8_t     label[WH_NVM_LABEL_LEN];
    uint8_t     WH_PAD[2];
    /* Certificate data follows */
} whMessageCert_AddTrustedRequest;

int wh_MessageCert_TranslateAddTrustedRequest(
    uint16_t magic, const whMessageCert_AddTrustedRequest* src,
    whMessageCert_AddTrustedRequest* dest);

/* AddTrusted Response */
/* Use SimpleResponse */

/* EraseTrusted Request */
typedef struct {
    whNvmId id;
    uint8_t WH_PAD[6];
} whMessageCert_EraseTrustedRequest;

int wh_MessageCert_TranslateEraseTrustedRequest(
    uint16_t magic, const whMessageCert_EraseTrustedRequest* src,
    whMessageCert_EraseTrustedRequest* dest);

/* EraseTrusted Response */
/* Use SimpleResponse */

/* ReadTrusted Request */
typedef struct {
    whNvmId id;
    uint8_t WH_PAD[6];
} whMessageCert_ReadTrustedRequest;

int wh_MessageCert_TranslateReadTrustedRequest(
    uint16_t magic, const whMessageCert_ReadTrustedRequest* src,
    whMessageCert_ReadTrustedRequest* dest);

/* ReadTrusted Response */
typedef struct {
    int32_t  rc;
    uint32_t cert_len;
    /* Certificate data follows */
} whMessageCert_ReadTrustedResponse;

int wh_MessageCert_TranslateReadTrustedResponse(
    uint16_t magic, const whMessageCert_ReadTrustedResponse* src,
    whMessageCert_ReadTrustedResponse* dest);

/* Verify Request */
typedef struct {
    uint32_t   cert_len;
    whNvmId    trustedRootNvmId;
    uint16_t   flags;
    whNvmFlags cachedKeyFlags;
    whKeyId    keyId;
    /* Certificate data follows */
} whMessageCert_VerifyRequest;

/* Verify Response */
typedef struct {
    int32_t rc;
    whKeyId keyId;
    uint8_t WH_PAD[2];
} whMessageCert_VerifyResponse;

int wh_MessageCert_TranslateVerifyRequest(
    uint16_t magic, const whMessageCert_VerifyRequest* src,
    whMessageCert_VerifyRequest* dest);

int wh_MessageCert_TranslateVerifyResponse(
    uint16_t magic, const whMessageCert_VerifyResponse* src,
    whMessageCert_VerifyResponse* dest);

#ifdef WOLFHSM_CFG_DMA

/* AddTrusted DMA Request */
typedef struct {
    uint64_t    cert_addr;
    uint32_t    cert_len;
    whNvmId     id;
    whNvmAccess access;
    whNvmFlags  flags;
    uint8_t     label[WH_NVM_LABEL_LEN];
    uint8_t     WH_PAD[6];
} whMessageCert_AddTrustedDmaRequest;

int wh_MessageCert_TranslateAddTrustedDmaRequest(
    uint16_t magic, const whMessageCert_AddTrustedDmaRequest* src,
    whMessageCert_AddTrustedDmaRequest* dest);

/* ReadTrusted DMA Request */
typedef struct {
    uint64_t cert_addr;
    uint32_t cert_len;
    whNvmId  id;
    uint8_t  WH_PAD[2];
} whMessageCert_ReadTrustedDmaRequest;

int wh_MessageCert_TranslateReadTrustedDmaRequest(
    uint16_t magic, const whMessageCert_ReadTrustedDmaRequest* src,
    whMessageCert_ReadTrustedDmaRequest* dest);

/* Verify DMA Request */
typedef struct {
    uint64_t   cert_addr;
    uint32_t   cert_len;
    whNvmId    trustedRootNvmId;
    uint16_t   flags;
    whNvmFlags cachedKeyFlags;
    whKeyId    keyId;
    uint8_t    WH_PAD[4];
} whMessageCert_VerifyDmaRequest;

/* Verify DMA Response */
typedef struct {
    int32_t rc;
    whKeyId keyId;
    uint8_t WH_PAD[2];
} whMessageCert_VerifyDmaResponse;

int wh_MessageCert_TranslateVerifyDmaRequest(
    uint16_t magic, const whMessageCert_VerifyDmaRequest* src,
    whMessageCert_VerifyDmaRequest* dest);

int wh_MessageCert_TranslateVerifyDmaResponse(
    uint16_t magic, const whMessageCert_VerifyDmaResponse* src,
    whMessageCert_VerifyDmaResponse* dest);

#endif /* WOLFHSM_CFG_DMA */

#ifdef WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT
/* Verify ACERT Request */
typedef struct {
    uint32_t cert_len;
    whNvmId  trustedRootNvmId;
    uint8_t  WH_PAD[2];
    /* Attribute Certificate data follows */
} whMessageCert_VerifyAcertRequest;

int wh_MessageCert_TranslateVerifyAcertRequest(
    uint16_t magic, const whMessageCert_VerifyAcertRequest* src,
    whMessageCert_VerifyAcertRequest* dest);

/* Verify ACERT Response */
/* Use SimpleResponse */

#endif /* WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT */


#endif /* !WOLFHSM_WH_MESSAGE_CERT_H_ */