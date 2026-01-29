/* app_renesasRx01.c
 *
 * Test bare-metal application.
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hal.h"
#include "wolfboot/wolfboot.h"

static const char* state2str(uint8_t s)
{
    switch(s) {
        case IMG_STATE_NEW: return "New";
        case IMG_STATE_UPDATING: return "Updating";
        case IMG_STATE_TESTING: return "Testing";
        case IMG_STATE_SUCCESS: return "Success";
        default: return "Unknown";
    }
}

static void printPart(uint8_t *part)
{
#ifdef WOLFBOOT_DEBUG_PARTION
    uint32_t *v;
    int i;
#endif
    uint8_t  *magic;
    uint8_t  state;
    uint32_t ver;

    magic = part;
    printf("Magic:    %c%c%c%c\n", magic[0], magic[1], magic[2], magic[3]);
    ver = wolfBoot_get_blob_version(part);
    printf("Version:  %02x\n", ver);
    state = *(part + WOLFBOOT_PARTITION_SIZE - sizeof(uint32_t) - 1);
    printf("Status:   %02x (%s)\n", state,state2str(state));
    magic = part + WOLFBOOT_PARTITION_SIZE - sizeof(uint32_t);
    printf("Trailer Mgc: %c%c%c%c\n", magic[0], magic[1], magic[2], magic[3]);

#ifdef WOLFBOOT_DEBUG_PARTION
    v = (uint32_t *)part;
    for(i = 0; i < 0x100/4; i++) {
        if(i % 4 == 0)
            print("\n%08x: ", (uint32_t)v+i*4);
        print("%08x ", v[i]);
    }
#endif

}


static void printPartitions(void)
{
    printf("\n=== Boot Partition[%08x] ===\n", WOLFBOOT_PARTITION_BOOT_ADDRESS);
    printPart((uint8_t*)WOLFBOOT_PARTITION_BOOT_ADDRESS);
    printf("\n=== Update Partition[%08x] ===\n", WOLFBOOT_PARTITION_UPDATE_ADDRESS);
    printPart((uint8_t*)WOLFBOOT_PARTITION_UPDATE_ADDRESS);
}

void main(void)
{
    uint8_t firmware_version = 0;

#if !defined(WOLFBOOT_RENESAS_TSIP)
    printf("| ------------------------------------------------------------------- |\n");
    printf("| Renesas RX User Application in BOOT partition started by wolfBoot   |\n");
    printf("| ------------------------------------------------------------------- |\n\n");
#elif defined(WOLFBOOT_RENESAS_TSIP_SRCVERSION)
    printf("| ------------------------------------------------------------------------------- |\n");
    printf("| Renesas RX w/ TSIP(SRC) User Application in BOOT partition started by wolfBoot  |\n");
    printf("| ------------------------------------------------------------------------------- |\n\n");
#else
    printf("| ------------------------------------------------------------------------------- |\n");
    printf("| Renesas RX w/ TSIP(LIB) User Application in BOOT partition started by wolfBoot  |\n");
    printf("| ------------------------------------------------------------------------------- |\n\n");
#endif

    hal_init();

    printPartitions();

    /* The same as: wolfBoot_get_image_version(PART_BOOT); */
    firmware_version = wolfBoot_current_firmware_version();

    printf("\nCurrent Firmware Version: %d\n", firmware_version);

    if (firmware_version >= 1) {
        if (firmware_version == 1) {
            printf("Hit any key to call wolfBoot_success the firmware.\n");
            getchar();

            wolfBoot_success();
            printPartitions();

            printf("\nHit any key to update the firmware.\n");
            getchar();

            wolfBoot_update_trigger();
            printf("Firmware Update is triggered\n");
            printPartitions();

        } else if (firmware_version == 2) {
            printf("Hit any key to call wolfBoot_success the firmware.\n");
            getchar();

            wolfBoot_success();
            printPartitions();
        }
    } else {
        printf("Invalid Firmware Version\n");
        goto busy_idle;
    }

    /* busy wait */
busy_idle:
    while (1)
        ;
}
