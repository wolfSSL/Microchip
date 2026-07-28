/**
 * RISC-V bootup
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "hal/riscv.h"

#if __riscv_xlen == 64

.macro trap_entry
    addi sp, sp, -128
    sd x1,   0(sp)
    sd x5,   8(sp)
    sd x6,  16(sp)
    sd x7,  24(sp)
    sd x10, 32(sp)
    sd x11, 40(sp)
    sd x12, 48(sp)
    sd x13, 56(sp)
    sd x14, 64(sp)
    sd x15, 72(sp)
    sd x16, 80(sp)
    sd x17, 88(sp)
    sd x28, 96(sp)
    sd x29, 104(sp)
    sd x30, 112(sp)
    sd x31, 120(sp)
.endm

.macro trap_exit
    ld x1,   0(sp)
    ld x5,   8(sp)
    ld x6,  16(sp)
    ld x7,  24(sp)
    ld x10, 32(sp)
    ld x11, 40(sp)
    ld x12, 48(sp)
    ld x13, 56(sp)
    ld x14, 64(sp)
    ld x15, 72(sp)
    ld x16, 80(sp)
    ld x17, 88(sp)
    ld x28, 96(sp)
    ld x29, 104(sp)
    ld x30, 112(sp)
    ld x31, 120(sp)
    addi sp, sp, 128
    MODE_PREFIX(ret)
.endm

#else /* __riscv_xlen == 32 */

.macro trap_entry
    addi sp, sp, -64
    sw x1,  0(sp)
    sw x5,  4(sp)
    sw x6,  8(sp)
    sw x7,  12(sp)
    sw x10, 16(sp)
    sw x11, 20(sp)
    sw x12, 24(sp)
    sw x13, 28(sp)
    sw x14, 32(sp)
    sw x15, 36(sp)
    sw x16, 40(sp)
    sw x17, 44(sp)
    sw x28, 48(sp)
    sw x29, 52(sp)
    sw x30, 56(sp)
    sw x31, 60(sp)
.endm


.macro trap_exit
  lw x1,  0(sp)
  lw x5,  4(sp)
  lw x6,  8(sp)
  lw x7,  12(sp)
  lw x10, 16(sp)
  lw x11, 20(sp)
  lw x12, 24(sp)
  lw x13, 28(sp)
  lw x14, 32(sp)
  lw x15, 36(sp)
  lw x16, 40(sp)
  lw x17, 44(sp)
  lw x28, 48(sp)
  lw x29, 52(sp)
  lw x30, 56(sp)
  lw x31, 60(sp)
  addi sp, sp, 64
  MODE_PREFIX(ret)
.endm

#endif /* __riscv_xlen */

.section .isr_vector
.align 8

.global IV

IV:
    j _synctrap
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2
    j trap_empty
    .align 2

_synctrap:
  trap_entry
  jal isr_synctrap
  trap_exit

trap_empty:
    nop
