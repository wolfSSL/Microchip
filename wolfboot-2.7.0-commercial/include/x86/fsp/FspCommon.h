/* FspCommon.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef FSPCOMMON_H
#define FSPCOMMON_H

#include <stdint.h>
#include "stdtype_mapping.h"
#include <x86/hob.h>


typedef struct {
  UINT64 Signature;
  UINT8 Revision;
  UINT8 Reserved[23];
} __attribute__((packed)) FSP_UPD_HEADER;

typedef struct {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
} __attribute__((packed)) EFI_GUID;

typedef struct {
  UINT8  Revision;
  UINT8  Reserved[3];
  UINT32 Length;
  UINT32 FspDebugHandler;
  UINT8  Reserved1[20];
} __attribute__((packed)) FSPT_ARCH_UPD;

typedef struct {
    UINT8 Revision;
    UINT8 Reserved[3];
    UINT32 NvsBufferPtr;
    UINT32 StackBase;
    UINT32 StackSize;
    UINT32 BootLoaderTolumSize;
    UINT32 BootMode;
    UINT32 FspEventHandler;
    UINT8 Reserved1[4];
} __attribute__((packed)) FSPM_ARCH_UPD;

struct fsp_info_header {
    uint32_t Signature;
    uint32_t HeaderLength;
    uint8_t Reserved1[2];
    uint8_t SpecVersion;
    uint8_t HeaderRevision;
    uint32_t ImageRevision;
    uint8_t ImageId[8];
    uint32_t ImageSize;
    uint32_t ImageBase;
    uint16_t ImageAttribute;
    uint16_t ComponentAttribute;
    uint32_t CfgRegionOffset;
    uint32_t CfgRegionSize;
    uint32_t Reserved2;
    uint32_t TempRamInitEntryOffset;
    uint32_t Reserved3;
    uint32_t NotifyPhaseEntryOffset;
    uint32_t FspMemoryInitEntryOffset;
    uint32_t TempRamExitEntryOffset;
    uint32_t FspSiliconInitEntryOffset;
    uint32_t FspMultiPhaseSiInitEntryOffset;
    uint16_t ExtendedImageRevision;
    uint16_t Reserved4;
} __attribute__((packed));

typedef enum {
    EnumInitPhaseAfterPciEnumeration= 0x20,
    EnumInitPhaseReadyToBoot = 0x40,
    EnumInitPhaseEndOfFirmware = 0xf0,
} FSP_INIT_PHASE;

typedef struct {
    FSP_INIT_PHASE Phase;
} NOTIFY_PHASE_PARAMS;

#endif /* FSPCOMMON_H */
