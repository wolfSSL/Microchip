/* Flash_sections.s
 *
 * Custom configuration for wolfCrypt/wolfSSL.
 * Enabled via WOLFSSL_USER_SETTINGS.
 *
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/* This file is used to include the application image into the loader project.*/

.section .IMAGE_APP_FLASH_section, "ax", %progbits
.incbin "../../app_RZ/Debug/app_RZ_v1.0_signed.bin"
