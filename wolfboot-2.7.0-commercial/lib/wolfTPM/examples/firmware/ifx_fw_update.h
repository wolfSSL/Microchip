/* ifx_firmware_update.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _IFX_FIRMWARE_H_
#define _IFX_FIRMWARE_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_IFX_Firmware_Update(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _IFX_FIRMWARE_H_ */
