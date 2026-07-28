/*
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfHSM.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * src/wh_message_customcb.c
 *
 */

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_comm.h"

#include "wolfhsm/wh_message_customcb.h"

static void _translateCustomData(uint16_t magic, uint32_t translatedType,
                                 const whMessageCustomCb_Data* src,
                                 whMessageCustomCb_Data*       dst)
{
    if (translatedType < WH_MESSAGE_CUSTOM_CB_TYPE_USER_DEFINED_START) {
        switch (translatedType) {
            case WH_MESSAGE_CUSTOM_CB_TYPE_QUERY: {
                /* right now, no further translations required */
            } break;
            case WH_MESSAGE_CUSTOM_CB_TYPE_DMA32: {
                WH_T32(magic, dst, src, dma32.client_addr);
                WH_T32(magic, dst, src, dma32.client_sz);
                WH_T32(magic, dst, src, dma32.server_addr);
                WH_T32(magic, dst, src, dma32.server_sz);
            } break;
            case WH_MESSAGE_CUSTOM_CB_TYPE_DMA64: {
                WH_T64(magic, dst, src, dma64.client_addr);
                WH_T64(magic, dst, src, dma64.client_sz);
                WH_T64(magic, dst, src, dma64.server_addr);
                WH_T64(magic, dst, src, dma64.server_sz);
            } break;
            default: {
                /* reserved message types - no translation for now */
            } break;
        }
    }
    else {
        /* use memmove in case data is translated "in place" */
        memmove(dst->buffer.data, src->buffer.data, sizeof(dst->buffer.data));
    }
}


int wh_MessageCustomCb_TranslateRequest(uint16_t                         magic,
                                        const whMessageCustomCb_Request* src,
                                        whMessageCustomCb_Request*       dst)
{
    if ((src == NULL) || (dst == NULL)) {
        return WH_ERROR_BADARGS;
    }

    WH_T32(magic, dst, src, id);
    WH_T32(magic, dst, src, type);
    _translateCustomData(magic, dst->type, &src->data, &dst->data);

    return WH_ERROR_OK;
}


int wh_MessageCustomCb_TranslateResponse(uint16_t magic,
                                         const whMessageCustomCb_Response* src,
                                         whMessageCustomCb_Response*       dst)
{
    if ((src == NULL) || (dst == NULL)) {
        return WH_ERROR_BADARGS;
    }
    WH_T32(magic, dst, src, rc);
    WH_T32(magic, dst, src, err);

    /* TODO: should we continue to translate responses for err != 0?
     * Probably still should...*/
    WH_T32(magic, dst, src, id);
    WH_T32(magic, dst, src, type);
    _translateCustomData(magic, dst->type, &src->data, &dst->data);

    return WH_ERROR_OK;
}
