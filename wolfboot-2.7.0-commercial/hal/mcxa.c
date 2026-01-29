/* mcxa.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include <target.h>
#include "image.h"
/* FSL includes */
#include "fsl_common.h"

/* Clock + RAM voltage settings */
#include "fsl_clock.h"
#include "fsl_spc.h"

/* Flash driver */
#include "fsl_romapi.h"

/*!< Core clock frequency: 96000000Hz */
#define BOARD_BOOTCLOCKFRO96M_CORE_CLOCK 96000000UL

static flash_config_t pflash;

uint32_t SystemCoreClock;

extern void BOARD_BootClockFRO96M(void);

#ifdef __WOLFBOOT
/* Assert hook needed by Kinetis SDK */
void __assert_func(const char *a, int b, const char *c, const char *d)
{
    while(1)
        ;
}

#endif /* __WOLFBOOT */

void hal_init(void)
{
#ifdef __WOLFBOOT
    /* Clock setting  */
    BOARD_BootClockFRO96M();

    /* Clear the FLASH configuration structure */
    memset(&pflash, 0, sizeof(pflash));
    /* FLASH driver init */
    FLASH_Init(&pflash);
#endif /* __WOLFBOOT */
}

void hal_prepare_boot(void)
{
}

int RAMFUNCTION hal_flash_write(uint32_t address, const uint8_t *data, int len)
{
    int ret;
    int w = 0;
    const uint8_t empty_qword[16] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };

    while (len > 0) {
        if ((len < 16) || address & 0x0F) {
            uint8_t aligned_qword[16];
            uint32_t address_align = address - (address & 0x0F);
            uint32_t start_off = address - address_align;
            int i;

            memcpy(aligned_qword, (void*)address_align, 16);
            for (i = start_off; ((i < 16) && (i < len + (int)start_off)); i++) {
                aligned_qword[i] = data[w++];
            }
            if (memcmp(aligned_qword, empty_qword, 16) != 0) {
                ret = FLASH_ProgramPhrase(&pflash, address_align, aligned_qword, 16);
                if (ret != kStatus_Success)
                    return -1;
            }
            address += i;
            len -= i;
        }
        else {
            uint32_t len_align = len - (len & 0x0F);
            ret = FLASH_ProgramPhrase(&pflash, address, (uint8_t*)data + w, len_align);
            if (ret != kStatus_Success)
                return -1;
            len -= len_align;
            address += len_align;
        }
    }
    return 0;
}

void RAMFUNCTION hal_flash_unlock(void)
{
}

void RAMFUNCTION hal_flash_lock(void)
{
}


int RAMFUNCTION hal_flash_erase(uint32_t address, int len)
{
    while ((address % 4) != 0)
        address --;
    if (FLASH_EraseSector(&pflash, address, len, kFLASH_ApiEraseKey) != kStatus_Success)
        return -1;
    return 0;
}
