/* boot_arm64_start.S
 *
 * AArch64 (64-bit ARM) boot startup code for test applications
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

.section .text.startup, "ax"
.global _start
.type _start, @function

_start:
    /* Set up stack pointer */
    ldr x0, =__stack
    mov sp, x0

    /* Copy data section from flash to RAM if needed */
    ldr x0, =_stored_data
    ldr x1, =_start_data
    ldr x2, =_end_data
    cmp x1, x2
    b.ge 2f
    cmp x0, x1
    b.eq 2f  /* Skip if data already in place */
1:
    ldr x3, [x0], #8
    str x3, [x1], #8
    cmp x1, x2
    b.lt 1b
2:

    /* Clear BSS */
    ldr x0, =__bss_start__
    ldr x1, =__bss_end__
    cmp x0, x1
    b.ge 4f
3:
    str xzr, [x0], #8
    cmp x0, x1
    b.lt 3b
4:

    /* Jump to main - never returns */
    bl main

    /* If main returns, loop forever */
5:
    wfi
    b 5b

.size _start, . - _start

/* Provide _exit stub for bare-metal builds (required by some standard library code) */
.section .text, "ax"
.global _exit
.type _exit, @function

_exit:
    /* Loop forever - bare-metal applications don't exit */
6:
    wfi
    b 6b

.size _exit, . - _exit
