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
 * wolfhsm/wh_message_counter.h
 *
 * Message structures and translation functions for counter operations.
 */

#ifndef WOLFHSM_WH_MESSAGE_COUNTER_H_
#define WOLFHSM_WH_MESSAGE_COUNTER_H_

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stdint.h>

#include "wolfhsm/wh_common.h"

/* Counter Init Request */
typedef struct {
    uint32_t counter;
    uint16_t counterId;
    uint8_t  WH_PAD[2];
} whMessageCounter_InitRequest;

/* Counter Init Response */
typedef struct {
    int32_t  rc;
    uint32_t counter;
} whMessageCounter_InitResponse;

/* Counter Init translation functions */
int wh_MessageCounter_TranslateInitRequest(
    uint16_t magic, const whMessageCounter_InitRequest* src,
    whMessageCounter_InitRequest* dest);

int wh_MessageCounter_TranslateInitResponse(
    uint16_t magic, const whMessageCounter_InitResponse* src,
    whMessageCounter_InitResponse* dest);

/* Counter Increment Request */
typedef struct {
    uint16_t counterId;
    uint8_t  WH_PAD[6];
} whMessageCounter_IncrementRequest;

/* Counter Increment Response */
typedef struct {
    int32_t  rc;
    uint32_t counter;
} whMessageCounter_IncrementResponse;

/* Counter Increment translation functions */
int wh_MessageCounter_TranslateIncrementRequest(
    uint16_t magic, const whMessageCounter_IncrementRequest* src,
    whMessageCounter_IncrementRequest* dest);

int wh_MessageCounter_TranslateIncrementResponse(
    uint16_t magic, const whMessageCounter_IncrementResponse* src,
    whMessageCounter_IncrementResponse* dest);

/* Counter Read Request */
typedef struct {
    uint16_t counterId;
    uint8_t  WH_PAD[6];
} whMessageCounter_ReadRequest;

/* Counter Read Response */
typedef struct {
    int32_t  rc;
    uint32_t counter;
} whMessageCounter_ReadResponse;

/* Counter Read translation functions */
int wh_MessageCounter_TranslateReadRequest(
    uint16_t magic, const whMessageCounter_ReadRequest* src,
    whMessageCounter_ReadRequest* dest);

int wh_MessageCounter_TranslateReadResponse(
    uint16_t magic, const whMessageCounter_ReadResponse* src,
    whMessageCounter_ReadResponse* dest);

/* Counter Destroy Request */
typedef struct {
    uint16_t counterId;
    uint8_t  WH_PAD[6];
} whMessageCounter_DestroyRequest;

/* Counter Destroy Response */
typedef struct {
    int32_t  rc;
    uint8_t  WH_PAD[4];
} whMessageCounter_DestroyResponse;

/* Counter Destroy translation functions */
int wh_MessageCounter_TranslateDestroyRequest(
    uint16_t magic, const whMessageCounter_DestroyRequest* src,
    whMessageCounter_DestroyRequest* dest);

int wh_MessageCounter_TranslateDestroyResponse(
    uint16_t magic, const whMessageCounter_DestroyResponse* src,
    whMessageCounter_DestroyResponse* dest);

#endif /* !WOLFHSM_WH_MESSAGE_COUNTER_H_ */