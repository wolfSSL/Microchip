/* gpio.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#ifdef __cplusplus
    extern "C" {
#endif

int TPM2_GPIO_Config_Example(void* userCtx, int argc, char *argv[]);
int TPM2_GPIO_Read_Example(void* userCtx, int argc, char *argv[]);
int TPM2_GPIO_Set_Example(void* userCtx, int argc, char *argv[]);

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _GPIO_H_ */
