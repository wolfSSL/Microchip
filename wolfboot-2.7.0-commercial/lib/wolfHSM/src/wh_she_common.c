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
 * src/wh_she_common.c
 *
 */
/* System libraries */

/* Pick up compile-time configuration */
#include "wolfhsm/wh_settings.h"

#ifdef WOLFHSM_CFG_SHE_EXTENSION

#include <stdint.h>
#include <stddef.h>  /* For NULL */
#include <string.h>  /* For memset, memcpy */

#include "wolfhsm/wh_common.h"
#include "wolfhsm/wh_error.h"
#include "wolfhsm/wh_utils.h"

#include "wolfhsm/wh_she_common.h"

typedef struct {
    uint32_t count;
    uint32_t flags;
} whSheMetadata;

int wh_She_Label2Meta(const uint8_t* label, uint32_t *out_count,
        uint32_t *out_flags)
{
    whSheMetadata* meta = (whSheMetadata*)label;

    if (label == NULL) {
        return WH_ERROR_BADARGS;
    }

    if (out_count != NULL) {
        *out_count = wh_Utils_ntohl(meta->count);
    }
    if (out_flags != NULL) {
        *out_flags = wh_Utils_ntohl(meta->flags);
    }
    return 0;
}

int wh_She_Meta2Label(uint32_t count, uint32_t flags, uint8_t* label)
{
    whSheMetadata* meta = (whSheMetadata*)label;
    if (label == NULL) {
        return WH_ERROR_BADARGS;
    }

    meta->count = wh_Utils_htonl(count);
    meta->flags = wh_Utils_htonl(flags);

    return 0;
}

#endif /* WOLFHSM_CFG_SHE_EXTENSION */

