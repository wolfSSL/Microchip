/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WH_BENCH_DATA_H_
#define WH_BENCH_DATA_H_
#include <stdint.h>
#include "wolfhsm/wh_settings.h"

/* default size of the data buffer */
#ifndef WOLFHSM_CFG_BENCH_DATA_BUFFER_SIZE
#define WOLFHSM_CFG_BENCH_DATA_BUFFER_SIZE 0x400 /* 1024 bytes */
#endif

#if defined(WOLFHSM_CFG_BENCH_CUSTOM_DATA_BUFFERS)
#define WH_BENCH_DATA_IN_BUFFER ((void*)WOLFHSM_CFG_BENCH_CUSTOM_DATA_IN_BUFFER)
#define WH_BENCH_DATA_OUT_BUFFER \
    ((void*)WOLFHSM_CFG_BENCH_CUSTOM_DATA_OUT_BUFFER)
#else
extern uint8_t wh_bench_data_in_buffer[WOLFHSM_CFG_BENCH_DATA_BUFFER_SIZE];
extern uint8_t wh_bench_data_out_buffer[WOLFHSM_CFG_BENCH_DATA_BUFFER_SIZE];
#define WH_BENCH_DATA_IN_BUFFER (void*)wh_bench_data_in_buffer
#define WH_BENCH_DATA_OUT_BUFFER (void*)wh_bench_data_out_buffer
#endif

#if defined(WOLFHSM_CFG_DMA)

/* default size of the DMA buffer */
#ifndef WOLFHSM_CFG_BENCH_DMA_BUFFER_SIZE
#define WOLFHSM_CFG_BENCH_DMA_BUFFER_SIZE 0x8000
#endif

/* Allow the user to define a custom DMA buffer of size
 * WOLFHSM_CFG_BENCH_DMA_BUFFER_SIZE */
#if defined(WOLFHSM_CFG_BENCH_CUSTOM_DMA_BUFFER)
#define WH_BENCH_DMA_BUFFER ((void*)WOLFHSM_CFG_BENCH_CUSTOM_DMA_BUFFER)
#else
/* built-in buffer for DMA operations */
extern uint8_t wh_bench_data_dma_buffer[WOLFHSM_CFG_BENCH_DMA_BUFFER_SIZE];
#define WH_BENCH_DMA_BUFFER wh_bench_data_dma_buffer
#endif

#endif /* WOLFHSM_CFG_DMA */

#endif /* WH_BENCH_DATA_H_ */
