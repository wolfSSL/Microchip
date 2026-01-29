/* tpm_io_mmio.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Support for Memory Mapped I/O for accessing TPM */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wolftpm/tpm2.h>
#include <wolftpm/tpm2_tis.h>
#include "tpm_io.h"

/******************************************************************************/
/* --- BEGIN IO Callback Logic -- */
/******************************************************************************/

/* Included via tpm_io.c if WOLFTPM_INCLUDE_IO_FILE is defined */
#ifdef WOLFTPM_INCLUDE_IO_FILE
#ifdef WOLFTPM_MMIO

#ifndef MIMO_BASE_ADDRESS
#define MIMO_BASE_ADDRESS 0xFE000000u
#endif

#ifndef WOLFTPM_ADV_IO
#error "WOLFTPM_MMIO requires WOLFTPM_ADV_IO"
#endif

#ifdef __GNUC__
    /* this will prevent the compiler to re-order memory accesses across
    * sw_barrier() invocation.
    */
    #define sw_barrier() __asm__ __volatile__ ("":::"memory")
#else
    #define sw_barrier()
#endif /* __GNUC__ */

static void TPM2_Mmio_Read32(word32 addr, byte *buf)
{
    volatile word32 *_addr = (volatile word32*)(wordptr)addr;
    word32 v;

    v = *_addr;
    sw_barrier();
    memcpy(buf, (byte*)&v, sizeof(word32));
}

static void TPM2_Mmio_Write32(word32 addr, byte *buf)
{
    volatile word32 *_addr = (volatile word32*)(wordptr)addr;
    word32 v;

    memcpy((uint8_t*)&v, buf, sizeof(word32));
    *_addr = v;
    sw_barrier();
}

static void TPM2_Mmio_Read8(word32 addr, byte *buf)
{
    volatile byte *_addr = (volatile byte*)(wordptr)addr;

    *buf = *_addr;
    sw_barrier();
}

static void TPM2_Mmio_Write8(word32 addr, byte *buf)
{
    volatile byte *_addr = (volatile byte*)(wordptr)addr;

    *_addr = *buf;
    sw_barrier();
}

int TPM2_IoCb_Mmio(TPM2_CTX *ctx, int isRead, word32 addr, byte* buf, word16 size,
    void* userCtx)
{
    size_t i;

    /* IO for 32-bit aligned */
    for (i = 0; ((size_t)size - i) >= sizeof(word32); i += sizeof(word32)) {
        if (isRead)
            TPM2_Mmio_Read32(MIMO_BASE_ADDRESS + addr, buf + i);
        else
            TPM2_Mmio_Write32(MIMO_BASE_ADDRESS + addr, buf + i);
    }

    /* IO for unaligned remainder */
    for (; i < (size_t)size; i++) {
        if (isRead)
            TPM2_Mmio_Read8(MIMO_BASE_ADDRESS + addr, buf + i);
        else
            TPM2_Mmio_Write8(MIMO_BASE_ADDRESS + addr, buf + i);
    }

    (void)ctx;
    (void)userCtx;

    return 0;
}

#undef sw_barrier

#endif /* WOLFTPM_MMIO */
#endif /* WOLFTPM_INCLUDE_IO_FILE */

/******************************************************************************/
/* --- END IO Callback Logic -- */
/******************************************************************************/
