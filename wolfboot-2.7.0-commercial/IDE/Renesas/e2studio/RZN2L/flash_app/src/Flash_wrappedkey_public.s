/* Flash_wrappedkey_public.s
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/* This file is used to include the application update image into
the loader project. */

.section .WRAPPED_KEY_FLASH_PUB, "ax", %progbits
/* To download the encrypted rsip key, please enable the line below.  */
/* .incbin "../rsa_pub2048.bin" */
