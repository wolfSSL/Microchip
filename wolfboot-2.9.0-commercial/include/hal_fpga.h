/* hal_fpga.h
 *
 * FPGA/PL bitstream loading HAL interface.
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Split out from hal.h so the per-target HAL implementations (hal/zynq.c,
 * hal/zynq7000.c, ...) can pull in just the FPGA flag constants and the
 * hal_fpga_load() prototype without including hal.h, which also drags in the
 * external-flash and wolfHSM interfaces. */

#ifndef H_HAL_FPGA_
#define H_HAL_FPGA_

#ifdef WOLFBOOT_FPGA_BITSTREAM

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* FPGA load mode (flags argument to hal_fpga_load) */
#define HAL_FPGA_FULL    0u  /* full bitstream / device image */
#define HAL_FPGA_PARTIAL 1u  /* partial reconfiguration */

/*
 * Program the PL/FPGA fabric from an in-DDR bitstream/PDI image.
 * addr/size describe the staged image buffer; the implementation
 * is responsible for any required cache maintenance before the
 * configuration engine reads it. Returns 0 on success, negative on
 * error. The weak default returns -1 (not implemented).
 */
int hal_fpga_load(uint32_t flags, uintptr_t addr, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* WOLFBOOT_FPGA_BITSTREAM */

#endif /* H_HAL_FPGA_ */
