/* wcs_fwtpm.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_WCS_FWTPM_H
#define WOLFBOOT_WCS_FWTPM_H

#include <stdint.h>
#include "wolfboot/wc_secure.h"

#ifdef WOLFBOOT_TZ_FWTPM

#ifndef WCS_FWTPM_MAX_COMMAND_SIZE
#define WCS_FWTPM_MAX_COMMAND_SIZE 4096U
#endif

int CSME_NSE_API wcs_fwtpm_transmit(const uint8_t *cmd, uint32_t cmdSz,
        uint8_t *rsp, uint32_t *rspSz);

void wcs_fwtpm_init(void);

#endif /* WOLFBOOT_TZ_FWTPM */

#endif /* WOLFBOOT_WCS_FWTPM_H */
