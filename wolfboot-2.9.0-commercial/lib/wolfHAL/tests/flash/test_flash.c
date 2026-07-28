/* test_flash.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include <wolfHAL/wolfHAL.h>
#include "board.h"
#include "test.h"
#include "peripheral.h"

static whal_Flash *g_testFlashDev;
static size_t g_testFlashAddr;
static size_t g_testFlashSectorSz;

static void Test_Flash_Api(void)
{
    WHAL_ASSERT_EQ(whal_Flash_Read(g_testFlashDev, 0, NULL, 8), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Flash_Write(g_testFlashDev, 0, NULL, 8), WHAL_EINVAL);
}

static void Test_Flash_WriteReadErase(void)
{
    uint8_t pattern[32] = {
        0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE,
        0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE,
        0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE,
        0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE,
    };
    uint8_t readback[32];
    whal_Error err;

    WHAL_ASSERT_EQ(whal_Flash_Unlock(g_testFlashDev, g_testFlashAddr,
                                      g_testFlashSectorSz), WHAL_SUCCESS);

    WHAL_ASSERT_EQ(whal_Flash_Erase(g_testFlashDev, g_testFlashAddr,
                                     g_testFlashSectorSz), WHAL_SUCCESS);

    WHAL_ASSERT_EQ(whal_Flash_Read(g_testFlashDev, g_testFlashAddr,
                                    readback, sizeof(readback)), WHAL_SUCCESS);
    WHAL_ASSERT_MEM_NEQ(readback, pattern, sizeof(pattern));


    do {
        err = whal_Flash_Write(g_testFlashDev, g_testFlashAddr, pattern,
                               sizeof(pattern));
    } while (err == WHAL_ENOTREADY);
    WHAL_ASSERT_EQ(err, WHAL_SUCCESS);

    WHAL_ASSERT_EQ(whal_Flash_Read(g_testFlashDev, g_testFlashAddr,
                                    readback, sizeof(readback)), WHAL_SUCCESS);
    WHAL_ASSERT_MEM_EQ(pattern, readback, sizeof(pattern));

    WHAL_ASSERT_EQ(whal_Flash_Erase(g_testFlashDev, g_testFlashAddr,
                                     g_testFlashSectorSz), WHAL_SUCCESS);

    WHAL_ASSERT_EQ(whal_Flash_Read(g_testFlashDev, g_testFlashAddr,
                                    readback, sizeof(readback)), WHAL_SUCCESS);
    WHAL_ASSERT_MEM_NEQ(readback, pattern, sizeof(pattern));

    WHAL_ASSERT_EQ(whal_Flash_Lock(g_testFlashDev, g_testFlashAddr,
                                    g_testFlashSectorSz), WHAL_SUCCESS);
}

static void run_flash_tests(const char *name)
{
    WHAL_TEST_SUITE_START("flash");
    if (name)
        whal_Test_Printf("  device: %s\n", name);
    WHAL_TEST(Test_Flash_Api);
    WHAL_TEST(Test_Flash_WriteReadErase);
    WHAL_TEST_SUITE_END();
}

void whal_Test_Flash(void)
{
    /* Test on-chip flash */
    g_testFlashDev = BOARD_FLASH_DEV;
    g_testFlashAddr = BOARD_FLASH_TEST_ADDR;
    g_testFlashSectorSz = BOARD_FLASH_SECTOR_SZ;
    run_flash_tests("on-chip");

    /* Test peripheral flash devices */
    for (size_t i = 0; g_peripheralFlash[i].dev; i++) {
        g_testFlashDev = g_peripheralFlash[i].dev;
        g_testFlashAddr = 0;
        g_testFlashSectorSz = g_peripheralFlash[i].sectorSz;
        run_flash_tests(g_peripheralFlash[i].name);
    }
}
