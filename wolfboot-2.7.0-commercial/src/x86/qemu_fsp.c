/* qemu_fsp.c
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include <x86/hob.h>
#include <uart_drv.h>
#include <x86/ahci.h>
#include <stage2_params.h>

#define FSPM_UPD_SIGNATURE 0x4D5F4450554D4551 /* 'QEMUPD_M' */
#define FSPT_UPD_SIGNATURE 0x545F4450554D4551 /* 'QEMUPD_T' */

struct fsp_upd_header {
    uint64_t Signature;
    uint8_t Revision;
    uint8_t Reserved[23];
} __attribute__((packed));

struct fspt_common_upd {
    uint8_t Revision;
    uint8_t Reserved[3];
    uint32_t MicrocodeRegionBase;
    uint32_t MicrocodeRegionLength;
    uint32_t CodeRegionBase;
    uint32_t CodeRegionLength;
    uint8_t Reserved1[12];
} __attribute__((packed));

struct fspt_upd {
    struct fsp_upd_header FspUpdHeader;
    struct fspt_common_upd FsptCommonUpd;
    uint8_t ReservedFsptUpd1[32];
    uint8_t UnusedUpdSpace0[48];
    uint16_t UpdTerminator;
} __attribute__((packed));

struct fspm_arch_upd {
    uint8_t Revision;
    uint8_t Reserved[3];
    uint32_t NvsBufferPtr;
    uint32_t StackBase;
    uint32_t StackSize;
    uint32_t BootLoaderTolumSize;
    uint32_t BootMode;
    uint32_t FspEventHandler;
    uint8_t Reserved1[4];
} __attribute__((packed));

struct fsp_m_config {
    uint32_t SerialDebugPortAddress;
    uint8_t SerialDebugPortType;
    uint8_t SerialDebugPortDevice;
    uint8_t SerialDebugPortStrideSize;
    uint8_t UnusedUpdSpace0[49];
    uint8_t ReservedFspmUpd[4];
} __attribute__((packed));

struct fspm_upd {
    struct fsp_upd_header FspUpdHeader;
    struct fspm_arch_upd FspmArchUpd;
    struct fsp_m_config FspmConfig;
    uint8_t UnusedUpdSpace1[2];
    uint16_t UpdTerminator;
} __attribute__((packed));

const
struct fspt_upd TempRamInitParams = {
    .FspUpdHeader = {
        .Signature = FSPT_UPD_SIGNATURE,
        .Revision  = 1,
        .Reserved  = {0},
    },
    .FsptCommonUpd = {
        .Revision              = 1,
        .MicrocodeRegionBase   = 0,
        .MicrocodeRegionLength = 0,
        .CodeRegionBase        = 0xFF000000,
        .CodeRegionLength      = 0x00000000,
    },
    .UpdTerminator = 0x55AA,
};

int fsp_machine_update_s_parameters(uint8_t *default_s_params)
{
    (void)default_s_params;
    return 0;
}

int post_temp_ram_init_cb(void)
{
    uart_init(115200, 8, 'N', 0);
    return 0;
}

int fsp_machine_update_m_parameters(uint8_t *default_m_params,
                                    uint32_t mem_base,
                                    uint32_t mem_size)
{
    struct stage2_parameter *params;
    struct fspm_upd *new_udp;

    new_udp = (struct fspm_upd*)default_m_params;
    new_udp->FspmArchUpd.BootLoaderTolumSize = 0;
    new_udp->FspmArchUpd.BootMode = BOOT_WITH_FULL_CONFIGURATION;

    /* TODO: support permanent flash area to store NVS*/
    new_udp->FspmArchUpd.NvsBufferPtr        = 0;
    new_udp->FspmArchUpd.StackBase = mem_base;
    new_udp->FspmArchUpd.StackSize = mem_size;

    return 0;
}

int fsp_pre_mem_init_cb(void)
{
    return 0;
}

int fsp_pre_silicon_init_cb(void)
{
    return 0;
}
