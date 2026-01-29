/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "wh_bench_data.h"

#if defined(WOLFHSM_CFG_BENCH_ENABLE)

#if !defined(WOLFHSM_CFG_BENCH_CUSTOM_DATA_BUFFERS)
uint8_t wh_bench_data_in_buffer[WOLFHSM_CFG_BENCH_DATA_BUFFER_SIZE]  = {0};
uint8_t wh_bench_data_out_buffer[WOLFHSM_CFG_BENCH_DATA_BUFFER_SIZE] = {0};
#endif

#if defined(WOLFHSM_CFG_DMA) && !defined(WOLFHSM_CFG_BENCH_CUSTOM_DMA_BUFFER)
/* Define the DMA buffer if using built-in buffer */
uint8_t wh_bench_data_dma_buffer[WOLFHSM_CFG_BENCH_DMA_BUFFER_SIZE] = {0};
#endif

#endif /* WOLFHSM_CFG_BENCH_ENABLE */