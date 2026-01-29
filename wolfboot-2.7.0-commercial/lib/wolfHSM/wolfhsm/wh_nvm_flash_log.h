/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef WOLFHSM_WH_NVM_FLASH_LOG_H_
#define WOLFHSM_WH_NVM_FLASH_LOG_H_

#include "wolfhsm/wh_settings.h"

#if defined(WOLFHSM_CFG_SERVER_NVM_FLASH_LOG)

#include "wolfhsm/wh_common.h"
#include "wolfhsm/wh_flash.h"

#ifndef WH_NVM_FLASH_LOG_WRITE_GRANULARITY
#define WH_NVM_FLASH_LOG_WRITE_GRANULARITY 64
#endif

#ifndef WOLFHSM_CFG_NVM_OBJECT_COUNT
#define WOLFHSM_CFG_NVM_OBJECT_COUNT 32
#endif

#ifndef WH_NVM_FLASH_LOG_PARTITION_SIZE
#define WH_NVM_FLASH_LOG_PARTITION_SIZE (4 * 1024)
#endif

typedef struct {
    uint32_t partition_epoch;
    uint32_t size;
    uint8_t  WH_PAD[WH_NVM_FLASH_LOG_WRITE_GRANULARITY - sizeof(uint32_t) * 2];
} whNvmFlashLogPartitionHeader;

/* In-memory representation of a partition */
typedef struct {
    whNvmFlashLogPartitionHeader header;
    uint8_t                      data[WH_NVM_FLASH_LOG_PARTITION_SIZE];
} whNvmFlashLogMemPartition;

/* Flash log backend context structure */
typedef struct {
    const whFlashCb*          flash_cb;  /* Flash callback interface */
    void*                     flash_ctx; /* Flash context */
    uint32_t                  partition_size;
    uint32_t                  active_partition; /* 0 or 1 */
    int                       is_initialized;
    whNvmFlashLogMemPartition directory;
} whNvmFlashLogContext;

/* Flash log backend config structure */
typedef struct {
    const whFlashCb* flash_cb;  /* Flash callback interface */
    void*            flash_ctx; /* Flash context */
    const void*      flash_cfg; /* Config to be passed to cb->Init */
} whNvmFlashLogConfig;

int wh_NvmFlashLog_Init(void* c, const void* cf);
int wh_NvmFlashLog_Cleanup(void* c);
int wh_NvmFlashLog_List(void* c, whNvmAccess access, whNvmFlags flags,
                        whNvmId start_id, whNvmId* out_avail_objects,
                        whNvmId* out_id);
int wh_NvmFlashLog_GetAvailable(void* c, uint32_t* out_avail_size,
                                whNvmId*  out_avail_objects,
                                uint32_t* out_reclaim_size,
                                whNvmId*  out_reclaim_objects);
int wh_NvmFlashLog_GetMetadata(void* c, whNvmId id, whNvmMetadata* meta);
int wh_NvmFlashLog_AddObject(void* c, whNvmMetadata* meta, whNvmSize data_len,
                             const uint8_t* data);
int wh_NvmFlashLog_DestroyObjects(void* c, whNvmId list_count,
                                  const whNvmId* id_list);
int wh_NvmFlashLog_Read(void* c, whNvmId id, whNvmSize offset,
                        whNvmSize data_len, uint8_t* data);

#define WH_NVM_FLASH_LOG_CB                                             \
    {                                                                   \
        .Init = wh_NvmFlashLog_Init, .Cleanup = wh_NvmFlashLog_Cleanup, \
        .List           = wh_NvmFlashLog_List,                          \
        .GetAvailable   = wh_NvmFlashLog_GetAvailable,                  \
        .GetMetadata    = wh_NvmFlashLog_GetMetadata,                   \
        .AddObject      = wh_NvmFlashLog_AddObject,                     \
        .DestroyObjects = wh_NvmFlashLog_DestroyObjects,                \
        .Read           = wh_NvmFlashLog_Read,                          \
    }

#endif /* WOLFHSM_CFG_SERVER_NVM_FLASH_LOG */

#endif /* WOLFHSM_WH_NVM_FLASH_LOG_H_ */
