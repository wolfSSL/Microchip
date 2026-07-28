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

int wh_She_Label2Meta(const uint8_t* label, uint32_t *out_count,
        uint32_t *out_flags)
{
    uint32_t tmp;

    if (label == NULL) {
        return WH_ERROR_BADARGS;
    }

    if (out_count != NULL) {
        memcpy(&tmp, label, sizeof(uint32_t));
        *out_count = wh_Utils_ntohl(tmp);
    }
    if (out_flags != NULL) {
        memcpy(&tmp, label + sizeof(uint32_t), sizeof(uint32_t));
        *out_flags = wh_Utils_ntohl(tmp);
    }
    return 0;
}

int wh_She_Meta2Label(uint32_t count, uint32_t flags, uint8_t* label)
{
    uint32_t tmp;

    if (label == NULL) {
        return WH_ERROR_BADARGS;
    }

    tmp = wh_Utils_htonl(count);
    memcpy(label, &tmp, sizeof(uint32_t));
    tmp = wh_Utils_htonl(flags);
    memcpy(label + sizeof(uint32_t), &tmp, sizeof(uint32_t));

    return 0;
}

#endif /* WOLFHSM_CFG_SHE_EXTENSION */

