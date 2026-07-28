/* test_stm32wb_flash.c
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
#include <wolfHAL/flash/stm32wb_flash.h>
#include <wolfHAL/bitops.h>
#include "board.h"
#include "test.h"

/* Flash CR register offset and LOCK bit */
#define FLASH_CR_REG  0x14
#define FLASH_CR_LOCK_Pos 31
#define FLASH_CR_LOCK_Msk (1UL << FLASH_CR_LOCK_Pos)

static void Test_Flash_LockReadback(void)
{
    /* After locking, the CR.LOCK bit should be set */
    WHAL_ASSERT_EQ(whal_Flash_Lock(BOARD_FLASH_DEV, 0, 0), WHAL_SUCCESS);

    size_t val = 0;
    whal_Reg_Get(whal_Stm32wb_Flash_Dev.base, FLASH_CR_REG,
                 FLASH_CR_LOCK_Msk, FLASH_CR_LOCK_Pos, &val);
    WHAL_ASSERT_EQ(val, 1);
}

void whal_Test_Flash_Platform(void)
{
    WHAL_TEST(Test_Flash_LockReadback);
}
