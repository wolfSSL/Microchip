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
 * wolfhsm/wh_message_keystore.c
 *
 * Message translation functions for keystore operations.
 */

#include "wolfhsm/wh_message_keystore.h"
#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_comm.h"
#include <string.h>

/* Key Cache Request translation */
int wh_MessageKeystore_TranslateCacheRequest(
    uint16_t magic, const whMessageKeystore_CacheRequest* src,
    whMessageKeystore_CacheRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, flags);
    WH_T32(magic, dest, src, sz);
    WH_T32(magic, dest, src, labelSz);
    WH_T16(magic, dest, src, id);
    /* Label is just a byte array, no translation needed */
    if (src != dest) {
        memcpy(dest->label, src->label, WH_NVM_LABEL_LEN);
    }
    return 0;
}

/* Key Cache Response translation */
int wh_MessageKeystore_TranslateCacheResponse(
    uint16_t magic, const whMessageKeystore_CacheResponse* src,
    whMessageKeystore_CacheResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T16(magic, dest, src, id);
    return 0;
}

/* Key Evict Request translation */
int wh_MessageKeystore_TranslateEvictRequest(
    uint16_t magic, const whMessageKeystore_EvictRequest* src,
    whMessageKeystore_EvictRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, id);
    return 0;
}

/* Key Evict Response translation */
int wh_MessageKeystore_TranslateEvictResponse(
    uint16_t magic, const whMessageKeystore_EvictResponse* src,
    whMessageKeystore_EvictResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, ok);
    return 0;
}

/* Key Commit Request translation */
int wh_MessageKeystore_TranslateCommitRequest(
    uint16_t magic, const whMessageKeystore_CommitRequest* src,
    whMessageKeystore_CommitRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, id);
    return 0;
}

/* Key Commit Response translation */
int wh_MessageKeystore_TranslateCommitResponse(
    uint16_t magic, const whMessageKeystore_CommitResponse* src,
    whMessageKeystore_CommitResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, ok);
    return 0;
}

/* Key Export Request translation */
int wh_MessageKeystore_TranslateExportRequest(
    uint16_t magic, const whMessageKeystore_ExportRequest* src,
    whMessageKeystore_ExportRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, id);
    return 0;
}

/* Key Export Response translation */
int wh_MessageKeystore_TranslateExportResponse(
    uint16_t magic, const whMessageKeystore_ExportResponse* src,
    whMessageKeystore_ExportResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, len);
    /* Label is just a byte array, no translation needed */
    if (src != dest) {
        memcpy(dest->label, src->label, WH_NVM_LABEL_LEN);
    }
    return 0;
}

/* Key Erase Request translation */
int wh_MessageKeystore_TranslateEraseRequest(
    uint16_t magic, const whMessageKeystore_EraseRequest* src,
    whMessageKeystore_EraseRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, id);
    return 0;
}

/* Key Erase Response translation */
int wh_MessageKeystore_TranslateEraseResponse(
    uint16_t magic, const whMessageKeystore_EraseResponse* src,
    whMessageKeystore_EraseResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, ok);
    return 0;
}

#ifdef WOLFHSM_CFG_DMA
/*
 * DMA-based keystore operations
 */

/* Key Cache DMA Request translation */
int wh_MessageKeystore_TranslateCacheDmaRequest(
    uint16_t magic, const whMessageKeystore_CacheDmaRequest* src,
    whMessageKeystore_CacheDmaRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T64(magic, dest, src, key.addr);
    WH_T64(magic, dest, src, key.sz);
    WH_T32(magic, dest, src, flags);
    WH_T32(magic, dest, src, labelSz);
    WH_T16(magic, dest, src, id);
    /* Label is just a byte array, no translation needed */
    if (src != dest) {
        memcpy(dest->label, src->label, WH_NVM_LABEL_LEN);
    }
    return 0;
}

/* Key Cache DMA Response translation */
int wh_MessageKeystore_TranslateCacheDmaResponse(
    uint16_t magic, const whMessageKeystore_CacheDmaResponse* src,
    whMessageKeystore_CacheDmaResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T64(magic, dest, src, dmaAddrStatus.badAddr.addr);
    WH_T64(magic, dest, src, dmaAddrStatus.badAddr.sz);
    WH_T16(magic, dest, src, id);
    return 0;
}

/* Key Export DMA Request translation */
int wh_MessageKeystore_TranslateExportDmaRequest(
    uint16_t magic, const whMessageKeystore_ExportDmaRequest* src,
    whMessageKeystore_ExportDmaRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T64(magic, dest, src, key.addr);
    WH_T64(magic, dest, src, key.sz);
    WH_T16(magic, dest, src, id);
    return 0;
}

/* Key Export DMA Response translation */
int wh_MessageKeystore_TranslateExportDmaResponse(
    uint16_t magic, const whMessageKeystore_ExportDmaResponse* src,
    whMessageKeystore_ExportDmaResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T64(magic, dest, src, dmaAddrStatus.badAddr.addr);
    WH_T64(magic, dest, src, dmaAddrStatus.badAddr.sz);
    WH_T32(magic, dest, src, len);
    /* Label is just a byte array, no translation needed */
    if (src != dest) {
        memcpy(dest->label, src->label, WH_NVM_LABEL_LEN);
    }
    return 0;
}

#endif /* WOLFHSM_CFG_DMA */

/* Key Wrap Request translation */
int wh_MessageKeystore_TranslateKeyWrapRequest(
    uint16_t magic, const whMessageKeystore_KeyWrapRequest* src,
    whMessageKeystore_KeyWrapRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, keySz);
    WH_T16(magic, dest, src, serverKeyId);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Key Wrap Response translation */
int wh_MessageKeystore_TranslateKeyWrapResponse(
    uint16_t magic, const whMessageKeystore_KeyWrapResponse* src,
    whMessageKeystore_KeyWrapResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T16(magic, dest, src, wrappedKeySz);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Key Unwrap Request translation */
int wh_MessageKeystore_TranslateKeyUnwrapAndExportRequest(
    uint16_t magic, const whMessageKeystore_KeyUnwrapAndExportRequest* src,
    whMessageKeystore_KeyUnwrapAndExportRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, wrappedKeySz);
    WH_T16(magic, dest, src, serverKeyId);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Key Unwrap Response translation */
int wh_MessageKeystore_TranslateKeyUnwrapAndExportResponse(
    uint16_t magic, const whMessageKeystore_KeyUnwrapAndExportResponse* src,
    whMessageKeystore_KeyUnwrapAndExportResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T16(magic, dest, src, keySz);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Wrapped Key Cache Request translation */
int wh_MessageKeystore_TranslateKeyUnwrapAndCacheRequest(
    uint16_t magic, const whMessageKeystore_KeyUnwrapAndCacheRequest* src,
    whMessageKeystore_KeyUnwrapAndCacheRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, wrappedKeySz);
    WH_T16(magic, dest, src, serverKeyId);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Key Cache Response translation */
int wh_MessageKeystore_TranslateKeyUnwrapAndCacheResponse(
    uint16_t magic, const whMessageKeystore_KeyUnwrapAndCacheResponse* src,
    whMessageKeystore_KeyUnwrapAndCacheResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T16(magic, dest, src, keyId);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Data Wrap Request translation */
int wh_MessageKeystore_TranslateDataWrapRequest(
    uint16_t magic, const whMessageKeystore_DataWrapRequest* src,
    whMessageKeystore_DataWrapRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, dataSz);
    WH_T16(magic, dest, src, serverKeyId);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Data Wrap Response translation */
int wh_MessageKeystore_TranslateDataWrapResponse(
    uint16_t magic, const whMessageKeystore_DataWrapResponse* src,
    whMessageKeystore_DataWrapResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, wrappedDataSz);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Data Unwrap Request translation */
int wh_MessageKeystore_TranslateDataUnwrapRequest(
    uint16_t magic, const whMessageKeystore_DataUnwrapRequest* src,
    whMessageKeystore_DataUnwrapRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, wrappedDataSz);
    WH_T16(magic, dest, src, serverKeyId);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}

/* Data Unwrap Response translation */
int wh_MessageKeystore_TranslateDataUnwrapResponse(
    uint16_t magic, const whMessageKeystore_DataUnwrapResponse* src,
    whMessageKeystore_DataUnwrapResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, dataSz);
    WH_T16(magic, dest, src, cipherType);
    return 0;
}
