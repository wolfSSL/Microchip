/* endorsement.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _WOLFTPM_ENDORSEMENT_H_
#define _WOLFTPM_ENDORSEMENT_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_EndorsementCert_Example(void* userCtx, int argc, char *argv[]);
int TPM2_EndorsementCertVerify_Example(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _WOLFTPM_ENDORSEMENT_H_ */
