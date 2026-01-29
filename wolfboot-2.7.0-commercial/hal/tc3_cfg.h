/* tc3_cfg.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef TC3_CFG_H
#define TC3_CFG_H

#if defined(WOLFBOOT_AURIX_TC3XX_HSM)
#define TC3_CFG_HAVE_ARM
#else
#define TC3_CFG_HAVE_TRICORE
#endif

#define TC3_CFG_HAVE_BOARD
#define TC3_BOARD_TC375LITEKIT 1
#define TC3_CFG_HAVE_WOLFBOOT

#endif /* TC3_CFG_H */
