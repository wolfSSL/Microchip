
/* clang_sections.S
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Force clang to emit .data and .bss sections, even if empty, to prevent the
 * linker from mishandling ld scripts and creating sparse binaries by putting
 * .data in RAM. */
.section .data
.section .bss
