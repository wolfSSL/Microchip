/* test_dispatch.c
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
#include <wolfHAL/timer/timer.h>
#include <wolfHAL/rng/rng.h>
#include "../test.h"

/*
 * Mock drivers that return SUCCESS for all operations.
 * Used to verify the generic dispatch layer.
 *
 * Clock and power are board-level drivers — they have no generic
 * whal_<Type>_* API or vtable, so they are not exercised here.
 */

static whal_Error MockGpioInit(whal_Gpio *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockGpioDeinit(whal_Gpio *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockGpioGet(whal_Gpio *d, size_t p, size_t *v) { (void)d; (void)p; *v = 1; return WHAL_SUCCESS; }
static whal_Error MockGpioSet(whal_Gpio *d, size_t p, size_t v) { (void)d; (void)p; (void)v; return WHAL_SUCCESS; }

static const whal_GpioDriver mockGpioDriver = {
    .Init = MockGpioInit,
    .Deinit = MockGpioDeinit,
    .Get = MockGpioGet,
    .Set = MockGpioSet,
};

static whal_Error MockUartInit(whal_Uart *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockUartDeinit(whal_Uart *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockUartSend(whal_Uart *d, const void *data, size_t sz) { (void)d; (void)data; (void)sz; return WHAL_SUCCESS; }
static whal_Error MockUartRecv(whal_Uart *d, void *data, size_t sz) { (void)d; (void)data; (void)sz; return WHAL_SUCCESS; }

static whal_Error MockUartSendAsync(whal_Uart *d, const void *data, size_t sz) { (void)d; (void)data; (void)sz; return WHAL_SUCCESS; }
static whal_Error MockUartRecvAsync(whal_Uart *d, void *data, size_t sz) { (void)d; (void)data; (void)sz; return WHAL_SUCCESS; }

static const whal_UartDriver mockUartDriver = {
    .Init = MockUartInit,
    .Deinit = MockUartDeinit,
    .Send = MockUartSend,
    .Recv = MockUartRecv,
};

static const whal_UartDriver mockUartAsyncDriver = {
    .Init = MockUartInit,
    .Deinit = MockUartDeinit,
    .Send = MockUartSend,
    .Recv = MockUartRecv,
    .SendAsync = MockUartSendAsync,
    .RecvAsync = MockUartRecvAsync,
};

static whal_Error MockFlashInit(whal_Flash *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockFlashDeinit(whal_Flash *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockFlashLock(whal_Flash *d, size_t a, size_t l) { (void)d; (void)a; (void)l; return WHAL_SUCCESS; }
static whal_Error MockFlashUnlock(whal_Flash *d, size_t a, size_t l) { (void)d; (void)a; (void)l; return WHAL_SUCCESS; }
static whal_Error MockFlashRead(whal_Flash *d, size_t a, void *data, size_t sz) { (void)d; (void)a; (void)data; (void)sz; return WHAL_SUCCESS; }
static whal_Error MockFlashWrite(whal_Flash *d, size_t a, const void *data, size_t sz) { (void)d; (void)a; (void)data; (void)sz; return WHAL_SUCCESS; }
static whal_Error MockFlashErase(whal_Flash *d, size_t a, size_t sz) { (void)d; (void)a; (void)sz; return WHAL_SUCCESS; }

static const whal_FlashDriver mockFlashDriver = {
    .Init = MockFlashInit,
    .Deinit = MockFlashDeinit,
    .Lock = MockFlashLock,
    .Unlock = MockFlashUnlock,
    .Read = MockFlashRead,
    .Write = MockFlashWrite,
    .Erase = MockFlashErase,
};

static whal_Error MockTimerInit(whal_Timer *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockTimerDeinit(whal_Timer *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockTimerStart(whal_Timer *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockTimerStop(whal_Timer *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockTimerReset(whal_Timer *d) { (void)d; return WHAL_SUCCESS; }

static const whal_TimerDriver mockTimerDriver = {
    .Init = MockTimerInit,
    .Deinit = MockTimerDeinit,
    .Start = MockTimerStart,
    .Stop = MockTimerStop,
    .Reset = MockTimerReset,
};

static whal_Error MockRngInit(whal_Rng *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockRngDeinit(whal_Rng *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockRngGenerate(whal_Rng *d, void *data, size_t sz) { (void)d; (void)data; (void)sz; return WHAL_SUCCESS; }

static const whal_RngDriver mockRngDriver = {
    .Init = MockRngInit,
    .Deinit = MockRngDeinit,
    .Generate = MockRngGenerate,
};


/* --- GPIO dispatch tests --- */

static void Test_Gpio_NullDev(void)
{
    WHAL_ASSERT_EQ(whal_Gpio_Init(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Gpio_Set(NULL, 0, 0), WHAL_EINVAL);
    size_t val;
    WHAL_ASSERT_EQ(whal_Gpio_Get(NULL, 0, &val), WHAL_EINVAL);
}

static void Test_Gpio_NullDriver(void)
{
    whal_Gpio dev = { .driver = NULL };
    WHAL_ASSERT_EQ(whal_Gpio_Init(&dev), WHAL_ENOTSUP);
}

static void Test_Gpio_ValidDispatch(void)
{
    whal_Gpio dev = { .driver = &mockGpioDriver };
    WHAL_ASSERT_EQ(whal_Gpio_Init(&dev), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Gpio_Set(&dev, 0, 1), WHAL_SUCCESS);
    size_t val;
    WHAL_ASSERT_EQ(whal_Gpio_Get(&dev, 0, &val), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(val, 1);
}

/* --- UART dispatch tests --- */

static void Test_Uart_NullDev(void)
{
    WHAL_ASSERT_EQ(whal_Uart_Init(NULL), WHAL_EINVAL);
    uint8_t buf[1];
    WHAL_ASSERT_EQ(whal_Uart_Send(NULL, buf, 1), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Uart_Recv(NULL, buf, 1), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Uart_SendAsync(NULL, buf, 1), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Uart_RecvAsync(NULL, buf, 1), WHAL_EINVAL);
}

static void Test_Uart_NullDriver(void)
{
    whal_Uart dev = { .driver = NULL };
    WHAL_ASSERT_EQ(whal_Uart_Init(&dev), WHAL_ENOTSUP);
}

static void Test_Uart_NullAsyncVtable(void)
{
    whal_Uart dev = { .driver = &mockUartDriver };
    uint8_t buf[1] = {0};
    WHAL_ASSERT_EQ(whal_Uart_SendAsync(&dev, buf, 1), WHAL_ENOTSUP);
    WHAL_ASSERT_EQ(whal_Uart_RecvAsync(&dev, buf, 1), WHAL_ENOTSUP);
}

static void Test_Uart_ValidDispatch(void)
{
    whal_Uart dev = { .driver = &mockUartDriver };
    WHAL_ASSERT_EQ(whal_Uart_Init(&dev), WHAL_SUCCESS);
    uint8_t buf[4] = {0};
    WHAL_ASSERT_EQ(whal_Uart_Send(&dev, buf, sizeof(buf)), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Uart_Recv(&dev, buf, sizeof(buf)), WHAL_SUCCESS);

    whal_Uart asyncDev = { .driver = &mockUartAsyncDriver };
    WHAL_ASSERT_EQ(whal_Uart_SendAsync(&asyncDev, buf, sizeof(buf)), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Uart_RecvAsync(&asyncDev, buf, sizeof(buf)), WHAL_SUCCESS);
}

/* --- Flash dispatch tests --- */

static void Test_Flash_NullDev(void)
{
    WHAL_ASSERT_EQ(whal_Flash_Init(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Flash_Lock(NULL, 0, 0), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Flash_Unlock(NULL, 0, 0), WHAL_EINVAL);
    uint8_t buf[1];
    WHAL_ASSERT_EQ(whal_Flash_Read(NULL, 0, buf, 1), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Flash_Write(NULL, 0, buf, 1), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Flash_Erase(NULL, 0, 1), WHAL_EINVAL);
}

static void Test_Flash_NullDriver(void)
{
    whal_Flash dev = { .driver = NULL };
    WHAL_ASSERT_EQ(whal_Flash_Init(&dev), WHAL_ENOTSUP);
}

static void Test_Flash_ValidDispatch(void)
{
    whal_Flash dev = { .driver = &mockFlashDriver };
    WHAL_ASSERT_EQ(whal_Flash_Init(&dev), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Flash_Lock(&dev, 0, 0), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Flash_Unlock(&dev, 0, 0), WHAL_SUCCESS);
    uint8_t buf[4] = {0};
    WHAL_ASSERT_EQ(whal_Flash_Read(&dev, 0, buf, sizeof(buf)), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Flash_Write(&dev, 0, buf, sizeof(buf)), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Flash_Erase(&dev, 0, sizeof(buf)), WHAL_SUCCESS);
}

/* --- Timer dispatch tests --- */

static void Test_Timer_NullDev(void)
{
    WHAL_ASSERT_EQ(whal_Timer_Init(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Timer_Start(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Timer_Stop(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Timer_Reset(NULL), WHAL_EINVAL);
}

static void Test_Timer_NullDriver(void)
{
    whal_Timer dev = { .driver = NULL };
    WHAL_ASSERT_EQ(whal_Timer_Init(&dev), WHAL_ENOTSUP);
}

static void Test_Timer_ValidDispatch(void)
{
    whal_Timer dev = { .driver = &mockTimerDriver };
    WHAL_ASSERT_EQ(whal_Timer_Init(&dev), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Timer_Start(&dev), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Timer_Stop(&dev), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Timer_Reset(&dev), WHAL_SUCCESS);
}

/* --- RNG dispatch tests --- */

static void Test_Rng_NullDev(void)
{
    uint8_t buf[1];
    WHAL_ASSERT_EQ(whal_Rng_Init(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Rng_Deinit(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Rng_Generate(NULL, buf, 1), WHAL_EINVAL);
}

static void Test_Rng_NullDriver(void)
{
    whal_Rng dev = { .driver = NULL };
    WHAL_ASSERT_EQ(whal_Rng_Init(&dev), WHAL_ENOTSUP);
}

static void Test_Rng_ValidDispatch(void)
{
    whal_Rng dev = { .driver = &mockRngDriver };
    WHAL_ASSERT_EQ(whal_Rng_Init(&dev), WHAL_SUCCESS);
    uint8_t buf[4] = {0};
    WHAL_ASSERT_EQ(whal_Rng_Generate(&dev, buf, sizeof(buf)), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Rng_Deinit(&dev), WHAL_SUCCESS);
}

/* --- SPI dispatch tests --- */

static whal_Error MockSpiInit(whal_Spi *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockSpiDeinit(whal_Spi *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockSpiStartCom(whal_Spi *d, whal_Spi_ComCfg *c) { (void)d; (void)c; return WHAL_SUCCESS; }
static whal_Error MockSpiEndCom(whal_Spi *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockSpiSendRecv(whal_Spi *d, const void *tx, size_t txLen, void *rx, size_t rxLen) { (void)d; (void)tx; (void)txLen; (void)rx; (void)rxLen; return WHAL_SUCCESS; }

static const whal_SpiDriver mockSpiDriver = {
    .Init = MockSpiInit,
    .Deinit = MockSpiDeinit,
    .StartCom = MockSpiStartCom,
    .EndCom = MockSpiEndCom,
    .SendRecv = MockSpiSendRecv,
};

static void Test_Spi_NullDev(void)
{
    whal_Spi_ComCfg comCfg = {0};
    uint8_t buf[1];
    WHAL_ASSERT_EQ(whal_Spi_Init(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Spi_Deinit(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Spi_StartCom(NULL, &comCfg), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Spi_EndCom(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Spi_SendRecv(NULL, buf, 1, buf, 1), WHAL_EINVAL);
}

static void Test_Spi_NullDriver(void)
{
    whal_Spi dev = { .driver = NULL };
    WHAL_ASSERT_EQ(whal_Spi_Init(&dev), WHAL_ENOTSUP);
}

static void Test_Spi_ValidDispatch(void)
{
    whal_Spi dev = { .driver = &mockSpiDriver };
    whal_Spi_ComCfg comCfg = {0};
    uint8_t buf[4] = {0};
    WHAL_ASSERT_EQ(whal_Spi_Init(&dev), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Spi_StartCom(&dev, &comCfg), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Spi_SendRecv(&dev, buf, sizeof(buf), buf, sizeof(buf)), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Spi_EndCom(&dev), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Spi_Deinit(&dev), WHAL_SUCCESS);
}

/* --- Block dispatch tests --- */

static whal_Error MockBlockInit(whal_Block *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockBlockDeinit(whal_Block *d) { (void)d; return WHAL_SUCCESS; }
static whal_Error MockBlockRead(whal_Block *d, uint32_t b, void *data, uint32_t c) { (void)d; (void)b; (void)data; (void)c; return WHAL_SUCCESS; }
static whal_Error MockBlockWrite(whal_Block *d, uint32_t b, const void *data, uint32_t c) { (void)d; (void)b; (void)data; (void)c; return WHAL_SUCCESS; }
static whal_Error MockBlockErase(whal_Block *d, uint32_t b, uint32_t c) { (void)d; (void)b; (void)c; return WHAL_SUCCESS; }

static const whal_BlockDriver mockBlockDriver = {
    .Init = MockBlockInit,
    .Deinit = MockBlockDeinit,
    .Read = MockBlockRead,
    .Write = MockBlockWrite,
    .Erase = MockBlockErase,
};

static void Test_Block_NullDev(void)
{
    WHAL_ASSERT_EQ(whal_Block_Init(NULL), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Block_Deinit(NULL), WHAL_EINVAL);
    uint8_t buf[1];
    WHAL_ASSERT_EQ(whal_Block_Read(NULL, 0, buf, 1), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Block_Write(NULL, 0, buf, 1), WHAL_EINVAL);
    WHAL_ASSERT_EQ(whal_Block_Erase(NULL, 0, 1), WHAL_EINVAL);
}

static void Test_Block_NullDriver(void)
{
    whal_Block dev = { .driver = NULL };
    WHAL_ASSERT_EQ(whal_Block_Init(&dev), WHAL_ENOTSUP);
}

static void Test_Block_ValidDispatch(void)
{
    whal_Block dev = { .driver = &mockBlockDriver };
    WHAL_ASSERT_EQ(whal_Block_Init(&dev), WHAL_SUCCESS);
    uint8_t buf[4] = {0};
    WHAL_ASSERT_EQ(whal_Block_Read(&dev, 0, buf, 1), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Block_Write(&dev, 0, buf, 1), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Block_Erase(&dev, 0, 1), WHAL_SUCCESS);
    WHAL_ASSERT_EQ(whal_Block_Deinit(&dev), WHAL_SUCCESS);
}

void whal_Test_Dispatch(void)
{
    WHAL_TEST_SUITE_START("dispatch");
    WHAL_TEST(Test_Gpio_NullDev);
    WHAL_TEST(Test_Gpio_NullDriver);
    WHAL_TEST(Test_Gpio_ValidDispatch);
    WHAL_TEST(Test_Uart_NullDev);
    WHAL_TEST(Test_Uart_NullDriver);
    WHAL_TEST(Test_Uart_NullAsyncVtable);
    WHAL_TEST(Test_Uart_ValidDispatch);
    WHAL_TEST(Test_Flash_NullDev);
    WHAL_TEST(Test_Flash_NullDriver);
    WHAL_TEST(Test_Flash_ValidDispatch);
    WHAL_TEST(Test_Timer_NullDev);
    WHAL_TEST(Test_Timer_NullDriver);
    WHAL_TEST(Test_Timer_ValidDispatch);
    WHAL_TEST(Test_Rng_NullDev);
    WHAL_TEST(Test_Rng_NullDriver);
    WHAL_TEST(Test_Rng_ValidDispatch);
    WHAL_TEST(Test_Spi_NullDev);
    WHAL_TEST(Test_Spi_NullDriver);
    WHAL_TEST(Test_Spi_ValidDispatch);
    WHAL_TEST(Test_Block_NullDev);
    WHAL_TEST(Test_Block_NullDriver);
    WHAL_TEST(Test_Block_ValidDispatch);
    WHAL_TEST_SUITE_END();
}
