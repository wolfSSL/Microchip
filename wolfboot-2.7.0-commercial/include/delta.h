/* delta.h
 *
 * Implementation of wolfBoot diff/patch functions,
 *
 * The format of the patch is based on the mechanism suggested
 * by Bentley/McIlroy, which is particularly effective
 * to generate small binary patches.
 *
 *
 * Compile with DELTA_UPDATES=1
 *
 * Use tools/sign.py or tool/sign.c on the host to provide small
 * secure update packages containing only binary difference, using the
 * --delta option.
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
#ifndef WOLFBOOT_DELTA_H
#define WOLFBOOT_DELTA_H

#include <stdint.h>

#ifndef DELTA_PATCH_BLOCK_SIZE
#define DELTA_PATCH_BLOCK_SIZE 1024
#endif

struct wb_patch_ctx {
    uint8_t *src_base;
    uint32_t src_size;
    uint8_t *patch_base;
    uint32_t patch_size;
    uint32_t p_off;
    int matching;
    uint32_t blk_sz;
    uint32_t blk_off;
#ifdef EXT_FLASH
    uint8_t patch_cache[DELTA_PATCH_BLOCK_SIZE];
    uint32_t patch_cache_start;
#endif
};

struct wb_diff_ctx {
    uint8_t *src_a;
    uint8_t *src_b;
    uint32_t size_a, size_b, off_b;
};


typedef struct wb_patch_ctx WB_PATCH_CTX;
typedef struct wb_diff_ctx WB_DIFF_CTX;

int wb_diff_init(WB_DIFF_CTX *ctx, uint8_t *src_a, uint32_t len_a, uint8_t *src_b, uint32_t len_b);
int wb_diff(WB_DIFF_CTX *ctx, uint8_t *patch, uint32_t len);
int wb_patch_init(WB_PATCH_CTX *bm, uint8_t *src, uint32_t ssz, uint8_t *patch, uint32_t psz);
int wb_patch(WB_PATCH_CTX *ctx, uint8_t *dst, uint32_t len);
int wolfBoot_get_delta_info(uint8_t part, int inverse, uint32_t **img_offset,
    uint32_t **img_size, uint8_t **base_hash, uint16_t *base_hash_size);
int wb_diff_get_sector_size(void);

#endif

