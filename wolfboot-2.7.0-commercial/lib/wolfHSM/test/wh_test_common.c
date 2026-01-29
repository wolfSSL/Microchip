/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <string.h>

#include <wolfhsm/wh_nvm.h>
#include <wolfhsm/wh_nvm_flash.h>
#include <wolfhsm/wh_nvm_flash_log.h>
#include <wolfhsm/wh_flash_ramsim.h>
#include <wolfhsm/wh_error.h>

#include "wh_test_common.h"


/**
 * Helper function to configure and select an NVM backend for testing.
 *
 * @param type      The type of NVM backend to configure (see
 * NvmTestBackendType).
 * @param nvmSetup  Pointer to a union of NVM backend setup structures (output).
 * @param nvmCfg    Pointer to the NVM configuration structure to populate
 * (output).
 * @param fCfg      Pointer to the RamSim flash configuration structure.
 * @param fCtx      Pointer to the RamSim flash context structure.
 * @param fCb       Pointer to the RamSim flash callback structure.
 *
 * @return WH_ERROR_OK on success, or WH_ERROR_BADARGS on failure.
 */
int whTest_NvmCfgBackend(whTestNvmBackendType   type,
                         whTestNvmBackendUnion* nvmSetup, whNvmConfig* nvmCfg,
                         whFlashRamsimCfg* fCfg, whFlashRamsimCtx* fCtx,
                         const whFlashCb* fCb)
{

    WH_TEST_ASSERT(nvmSetup != NULL);
    WH_TEST_ASSERT(nvmCfg != NULL);
    WH_TEST_ASSERT(fCfg != NULL);

    switch (type) {
#if defined(WOLFHSM_CFG_SERVER_NVM_FLASH_LOG)
        case WH_NVM_TEST_BACKEND_FLASH_LOG:
            nvmSetup->nvmFlashLogCfg.flash_cb = fCb;
            /* restrict simulated flash partition to nvm_flash_log_partition */
            WH_TEST_ASSERT(fCfg->size >= WH_NVM_FLASH_LOG_PARTITION_SIZE * 2);
            fCfg->sectorSize = WH_NVM_FLASH_LOG_PARTITION_SIZE;
            nvmSetup->nvmFlashLogCfg.flash_cfg = fCfg;
            nvmSetup->nvmFlashLogCfg.flash_ctx = fCtx;
            memset(&nvmSetup->nvmFlashLogCtx, 0,
                   sizeof(nvmSetup->nvmFlashLogCtx));
            static whNvmCb nflcb[1] = {WH_NVM_FLASH_LOG_CB};

            nvmCfg->cb      = nflcb;
            nvmCfg->context = &nvmSetup->nvmFlashLogCtx;
            nvmCfg->config  = &nvmSetup->nvmFlashLogCfg;
            break;
#endif
        case WH_NVM_TEST_BACKEND_FLASH:
            /* NVM Flash Configuration using RamSim HAL Flash */
            nvmSetup->nvmFlashCfg.cb      = fCb;
            nvmSetup->nvmFlashCfg.context = fCtx;
            nvmSetup->nvmFlashCfg.config  = fCfg;

            memset(&nvmSetup->nvmFlashCtx, 0, sizeof(nvmSetup->nvmFlashCtx));
            static whNvmCb nfcb[1] = {WH_NVM_FLASH_CB};

            nvmCfg->cb      = nfcb;
            nvmCfg->context = &nvmSetup->nvmFlashCtx;
            nvmCfg->config  = &nvmSetup->nvmFlashCfg;
            break;

        default:
            return WH_ERROR_BADARGS;
    }

    return 0;
}
