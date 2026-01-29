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
 * wolfhsm/wh_message_counter.c
 *
 * Message translation functions for counter operations.
 */

#include "wolfhsm/wh_message_counter.h"
#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_comm.h"
#include <string.h>

/* Counter Init Request translation */
int wh_MessageCounter_TranslateInitRequest(
    uint16_t magic, const whMessageCounter_InitRequest* src,
    whMessageCounter_InitRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, counter);
    WH_T16(magic, dest, src, counterId);
    return 0;
}

/* Counter Init Response translation */
int wh_MessageCounter_TranslateInitResponse(
    uint16_t magic, const whMessageCounter_InitResponse* src,
    whMessageCounter_InitResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, counter);
    return 0;
}

/* Counter Increment Request translation */
int wh_MessageCounter_TranslateIncrementRequest(
    uint16_t magic, const whMessageCounter_IncrementRequest* src,
    whMessageCounter_IncrementRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, counterId);
    return 0;
}

/* Counter Increment Response translation */
int wh_MessageCounter_TranslateIncrementResponse(
    uint16_t magic, const whMessageCounter_IncrementResponse* src,
    whMessageCounter_IncrementResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, counter);
    return 0;
}

/* Counter Read Request translation */
int wh_MessageCounter_TranslateReadRequest(
    uint16_t magic, const whMessageCounter_ReadRequest* src,
    whMessageCounter_ReadRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, counterId);
    return 0;
}

/* Counter Read Response translation */
int wh_MessageCounter_TranslateReadResponse(
    uint16_t magic, const whMessageCounter_ReadResponse* src,
    whMessageCounter_ReadResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    WH_T32(magic, dest, src, counter);
    return 0;
}

/* Counter Destroy Request translation */
int wh_MessageCounter_TranslateDestroyRequest(
    uint16_t magic, const whMessageCounter_DestroyRequest* src,
    whMessageCounter_DestroyRequest* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T16(magic, dest, src, counterId);
    return 0;
}

/* Counter Destroy Response translation */
int wh_MessageCounter_TranslateDestroyResponse(
    uint16_t magic, const whMessageCounter_DestroyResponse* src,
    whMessageCounter_DestroyResponse* dest)
{
    if ((src == NULL) || (dest == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dest, src, rc);
    return 0;
}