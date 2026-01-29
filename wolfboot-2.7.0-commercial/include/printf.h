/* printf.h
 *
 * The HAL API definitions.
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFBOOT_PRINTF_INCLUDED
#define WOLFBOOT_PRINTF_INCLUDED

#if defined(DEBUG_ZYNQ) && !defined(PRINTF_ENABLED)
#   define PRINTF_ENABLED
#endif
#if defined(WOLFBOOT_DEBUG_EFI) && !defined(PRINTF_ENABLED)
#   define PRINTF_ENABLED
#endif
#if (defined(ARCH_SIM) || defined(__linux__)) && !defined(PRINTF_ENABLED)
#   define PRINTF_ENABLED
#endif

#if defined(DEBUG_UART)
    #if !defined(UART_FLASH) && !defined(WOLFBOOT_FSP)
        void uart_init(void);
    #endif
    void uart_write(const char* buf, unsigned int sz);

    /* turn on small printf support in string.c */
    #if !defined(PRINTF_ENABLED) && !defined(NO_PRINTF_UART)
        #define PRINTF_ENABLED
    #endif
#endif

/* support for wolfBoot_printf logging */
#if defined(PRINTF_ENABLED) && !defined(WOLFBOOT_NO_PRINTF)
#   include <stdio.h>
#   if defined(DEBUG_ZYNQ) && !defined(USE_QNX) && !defined(DEBUG_UART)
#       include "xil_printf.h"
#       define wolfBoot_printf(_f_, ...) xil_printf(_f_, ##__VA_ARGS__)
#   elif defined(WOLFBOOT_DEBUG_EFI)
#       include "efi/efi.h"
#       include "efi/efilib.h"
        /* NOTE: %s arguments will not work as EFI uses widechar string */
#       define wolfBoot_printf(_f_, ...) Print(L##_f_, ##__VA_ARGS__)
#   elif defined(DEBUG_UART)
        /* use minimal printf support in string.h */
        void uart_printf(const char* fmt, ...);
#       define wolfBoot_printf(_f_, ...) uart_printf(_f_, ##__VA_ARGS__)
#   elif defined(__CCRX__)
#       define wolfBoot_printf printf
#   elif defined(WOLFBOOT_LOG_PRINTF)
        /* allow output to stdout */
#       define wolfBoot_printf(_f_, ...) printf(_f_, ##__VA_ARGS__)
#   else
        /* use stderr by default */
#       define wolfBoot_printf(_f_, ...) fprintf(stderr, _f_, ##__VA_ARGS__)
#   endif
#else
#   define wolfBoot_printf(_f_, ...) do{}while(0)
#endif

#endif /* !WOLFBOOT_PRINTF_INCLUDED */
