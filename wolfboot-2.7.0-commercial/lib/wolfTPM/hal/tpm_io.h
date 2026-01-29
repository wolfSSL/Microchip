/* tpm_io.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM_IO_H_
#define _TPM_IO_H_

#include <wolftpm/tpm2.h>

#ifdef __cplusplus
    extern "C" {
#endif

/* TPM2 IO Examples */

/** @defgroup TPM2_IO wolfTPM2 IO HAL Callbacks
 *
 * This module describes the available example TPM 2.0 IO HAL Callbacks in wolfTPM
 *
 * wolfTPM uses a single IO callback function.
 * This allows the TPM 2.0 stack to be highly portable.
 * These IO Callbacks are working examples for various embedded platforms and operating systems.
 *
 * Here is a list of the existing TPM 2.0 IO Callbacks:
 * - ST Micro STM32, through STM32 CubeMX HAL
 * - Native Linux (/dev/tpm0)
 * - Linux through spidev without kernel driver thanks to wolfTPM own TIS layer
 * - Linux through i2c without kernel driver thanks to wolfTPM own TIS layer
 * - Intel MMIO interface
 * - Native Windows
 * - Atmel MCUs
 * - Xilinx Zynq
 * - Barebox
 * - QNX
 * - uboot
 * - Infineon Tri-Core
 * - Microchip MPLAB X Harmony (WOLFTPM_MICROCHIP_HARMONY)
 * Using custom IO Callback is always possible.
 *
 */

#if defined(WOLFTPM_LINUX_DEV) || defined(WOLFTPM_SWTPM) || \
    defined(WOLFTPM_WINAPI)

/* HAL not required, so use NULL */
#define TPM2_IoCb NULL

#else

#ifdef WOLFTPM_EXAMPLE_HAL

#ifdef WOLFTPM_ADV_IO
WOLFTPM_API int TPM2_IoCb(TPM2_CTX* ctx, INT32 isRead, UINT32 addr,
    BYTE* buf, UINT16 size, void* userCtx);
#else
WOLFTPM_API int TPM2_IoCb(TPM2_CTX* ctx, const BYTE* txBuf, BYTE* rxBuf,
    UINT16 xferSz, void* userCtx);
#endif

/* Platform support, in alphabetical order */
#ifdef WOLFTPM_I2C

#if defined(__linux__)
WOLFTPM_LOCAL int TPM2_IoCb_Linux_I2C(TPM2_CTX* ctx, int isRead, word32 addr, byte* buf,
    word16 size, void* userCtx);
#elif defined(WOLFSSL_STM32_CUBEMX)
WOLFTPM_LOCAL int TPM2_IoCb_STCubeMX_I2C(TPM2_CTX* ctx, int isRead, word32 addr,
    byte* buf, word16 size, void* userCtx);
#elif defined(CY_USING_HAL)
WOLFTPM_LOCAL int TPM2_IoCb_Infineon_I2C(TPM2_CTX* ctx, int isRead, word32 addr,
    byte* buf, word16 size, void* userCtx);
#elif defined(WOLFSSL_ESPIDF)
WOLFTPM_LOCAL int TPM2_IoCb_Espressif_I2C(TPM2_CTX* ctx, int isRead, word32 addr,
    byte* buf, word16 size, void* userCtx);
#elif defined(WOLFTPM_MICROCHIP_HARMONY)
WOLFTPM_LOCAL int TPM2_IoCb_MicrochipHarmony_I2C(TPM2_CTX* ctx, int isRead, word32 addr,
    byte* buf, word16 size, void* userCtx);
#elif defined(WOLFSSL_ZEPHYR)
WOLFTPM_LOCAL int TPM2_IoCb_Zephyr_I2C(TPM2_CTX* ctx, int isRead, word32 addr,
    byte* buf, word16 size, void* userCtx);
#endif /* __linux__ */

#else /* SPI */

#if defined(WOLFSSL_ATMEL)
WOLFTPM_LOCAL int TPM2_IoCb_Atmel_SPI(TPM2_CTX* ctx, const byte* txBuf, byte* rxBuf,
    word16 xferSz, void* userCtx);
#elif defined(__BAREBOX__)
WOLFTPM_LOCAL int TPM2_IoCb_Barebox_SPI(TPM2_CTX* ctx, const byte* txBuf,
    byte* rxBuf, word16 xferSz, void* userCtx);
#elif defined(__UBOOT__)
WOLFTPM_LOCAL int TPM2_IoCb_Uboot_SPI(TPM2_CTX* ctx, const byte* txBuf,
    byte* rxBuf, word16 xferSz, void* userCtx);
#elif defined(__linux__)
WOLFTPM_LOCAL int TPM2_IoCb_Linux_SPI(TPM2_CTX* ctx, const byte* txBuf, byte* rxBuf,
    word16 xferSz, void* userCtx);
#elif defined(WOLFSSL_STM32_CUBEMX)
WOLFTPM_LOCAL int TPM2_IoCb_STCubeMX_SPI(TPM2_CTX* ctx, const byte* txBuf, byte* rxBuf,
    word16 xferSz, void* userCtx);
#elif defined(__QNX__) || defined(__QNXTO__)
WOLFTPM_LOCAL int TPM2_IoCb_QNX_SPI(TPM2_CTX* ctx, const byte* txBuf,
    byte* rxBuf, word16 xferSz, void* userCtx);
#elif defined(__XILINX__)
WOLFTPM_LOCAL int TPM2_IoCb_Xilinx_SPI(TPM2_CTX* ctx, const byte* txBuf,
    byte* rxBuf, word16 xferSz, void* userCtx);
#elif defined(CY_USING_HAL)
WOLFTPM_LOCAL int TPM2_IoCb_Infineon_SPI(TPM2_CTX* ctx, const byte* txBuf,
    byte* rxBuf, word16 xferSz, void* userCtx);
#elif defined(WOLFTPM_INFINEON_TRICORE)
WOLFTPM_LOCAL int TPM2_IoCb_Infineon_TriCore_SPI(TPM2_CTX* ctx, const byte* txBuf,
    byte* rxBuf, word16 xferSz, void* userCtx);
#elif defined(WOLFTPM_MICROCHIP_HARMONY)
WOLFTPM_LOCAL int TPM2_IoCb_Microchip_SPI(TPM2_CTX* ctx, const byte* txBuf, byte* rxBuf,
    word16 xferSz, void* userCtx);
#endif

#endif /* WOLFTPM_I2C */

#if defined(WOLFTPM_MMIO)
/* requires WOLFTPM_ADV_IO */
WOLFTPM_LOCAL int TPM2_IoCb_Mmio(TPM2_CTX* ctx, int isRead, word32 addr, byte* buf,
    word16 size, void* userCtx);
#endif

#endif /* WOLFTPM_EXAMPLE_HAL */
#endif /* !(WOLFTPM_LINUX_DEV || WOLFTPM_SWTPM || WOLFTPM_WINAPI) */

#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* _TPM_IO_H_ */
