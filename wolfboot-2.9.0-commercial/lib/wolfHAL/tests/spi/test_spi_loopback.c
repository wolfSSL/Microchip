/* test_spi_loopback.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/wolfHAL.h>
#include "board.h"
#include "test.h"

/*
 * Generic SPI loopback test.
 *
 * Requires MOSI wired to MISO so transmitted data is received back.
 * The board must provide g_whalSpi.
 */

static whal_Spi_ComCfg loopbackComCfg = {
    .freq = 1000000,
    .mode = WHAL_SPI_MODE_0,
    .wordSz = 8,
    .dataLines = 1,
};

static void Test_SpiLoopback_SendRecv(void)
{
    uint8_t tx[] = {0xDE, 0xAD, 0xBE, 0xEF};
    uint8_t rx[4] = {0};

    WHAL_ASSERT_EQ(whal_Spi_StartCom(BOARD_SPI_DEV, &loopbackComCfg),
                   WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Spi_SendRecv(BOARD_SPI_DEV,
                                      tx, sizeof(tx), rx, sizeof(rx)),
                   WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Spi_EndCom(BOARD_SPI_DEV), WHAL_SUCCESS);
    WHAL_ASSERT_MEM_EQ(rx, tx, sizeof(tx));
}

static void Test_SpiLoopback_NullBufWithLen(void)
{
    uint8_t buf[1] = {0};

    WHAL_ASSERT_EQ(whal_Spi_StartCom(BOARD_SPI_DEV, &loopbackComCfg),
                   WHAL_SUCCESS);

    /* NULL tx with nonzero txLen */
    WHAL_ASSERT_EQ(whal_Spi_SendRecv(BOARD_SPI_DEV, NULL, 1, buf, 1),
                   WHAL_EINVAL);

    /* NULL rx with nonzero rxLen */
    WHAL_ASSERT_EQ(whal_Spi_SendRecv(BOARD_SPI_DEV, buf, 1, NULL, 1),
                   WHAL_EINVAL);

    WHAL_ASSERT_EQ(whal_Spi_EndCom(BOARD_SPI_DEV), WHAL_SUCCESS);
}

static void Test_SpiLoopback_SendRecvDrain(void)
{
    uint8_t tx[] = {0xDE, 0xAD, 0xBE, 0xEF};
    uint8_t rx[4] = {0};
    uint8_t expected[4] = {0xFF, 0xFF, 0xFF, 0xFF};

    WHAL_ASSERT_EQ(whal_Spi_StartCom(BOARD_SPI_DEV, &loopbackComCfg),
                   WHAL_SUCCESS);

    /* Send-only: driver must drain RX FIFO internally */
    WHAL_ASSERT_EQ(whal_Spi_SendRecv(BOARD_SPI_DEV, tx, sizeof(tx), NULL, 0),
                   WHAL_SUCCESS);

    /* Receive-only: loopback returns 0xFF (the dummy TX byte) */
    WHAL_ASSERT_EQ(whal_Spi_SendRecv(BOARD_SPI_DEV, NULL, 0, rx, sizeof(rx)),
                   WHAL_SUCCESS);

    WHAL_ASSERT_EQ(whal_Spi_EndCom(BOARD_SPI_DEV), WHAL_SUCCESS);

    /* If RX wasn't drained, stale 0xDE/0xAD/0xBE/0xEF leaks here */
    WHAL_ASSERT_MEM_EQ(rx, expected, sizeof(expected));
}

static void Test_Spi_Api(void)
{
    uint8_t buf[4];
    whal_Spi_ComCfg cfg = { .freq = 1000000, .mode = 0, .wordSz = 8 };

    WHAL_ASSERT_EQ(whal_Spi_StartCom(BOARD_SPI_DEV, NULL), WHAL_EINVAL);
}

void whal_Test_Spi_Loopback(void)
{
    WHAL_TEST_SUITE_START("spi_loopback");
    WHAL_TEST(Test_Spi_Api);
    WHAL_TEST(Test_SpiLoopback_SendRecv);
    WHAL_TEST(Test_SpiLoopback_NullBufWithLen);
    WHAL_TEST(Test_SpiLoopback_SendRecvDrain);
    WHAL_TEST_SUITE_END();
}
