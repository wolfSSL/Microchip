/* lan8742a_eth_phy.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "board.h"  /* provides WHAL_CFG_LAN8742A_DEV initializer */
#include <wolfHAL/eth_phy/lan8742a_eth_phy.h>
#include <wolfHAL/eth/eth.h>
#include <wolfHAL/error.h>

const whal_EthPhy whal_Lan8742a_Dev = WHAL_CFG_LAN8742A_DEV;

/*
 * LAN8742A PHY Register Definitions (IEEE 802.3 standard + vendor)
 */

#define PHY_BCR       0x00  /* Basic Control Register */
#define PHY_BCR_RESET (1UL << 15)
#define PHY_BCR_ANEN  (1UL << 12)

#define PHY_BSR       0x01  /* Basic Status Register */
#define PHY_BSR_LINK  (1UL << 2)
#define PHY_BSR_ANEG_COMPLETE (1UL << 5)

#define PHY_PHYSCSR   0x1F  /* PHY Special Control/Status Register */
#define PHY_PHYSCSR_SPEED_Msk  (7UL << 2)
#define PHY_PHYSCSR_10HD   (1UL << 2)
#define PHY_PHYSCSR_10FD   (5UL << 2)
#define PHY_PHYSCSR_100HD  (2UL << 2)
#define PHY_PHYSCSR_100FD  (6UL << 2)

#ifdef WHAL_CFG_LAN8742A_ETH_PHY_DIRECT_API_MAPPING
#define whal_Lan8742a_Init         whal_EthPhy_Init
#define whal_Lan8742a_Deinit       whal_EthPhy_Deinit
#define whal_Lan8742a_GetLinkState whal_EthPhy_GetLinkState
#endif /* WHAL_CFG_LAN8742A_ETH_PHY_DIRECT_API_MAPPING */

whal_Error whal_Lan8742a_Init(whal_EthPhy *phyDev)
{
    const whal_Lan8742a_Cfg *cfg =
        (const whal_Lan8742a_Cfg *)whal_Lan8742a_Dev.cfg;
    uint8_t addr = whal_Lan8742a_Dev.addr;
    whal_Error err;
    uint16_t val;
    (void)phyDev;
#ifdef WHAL_CFG_NO_TIMEOUT
    (void)cfg;
#endif

    /* Software reset */
    err = whal_Eth_MdioWrite(NULL, addr, PHY_BCR, PHY_BCR_RESET);
    if (err)
        return err;

    /* Wait for reset to complete (bit self-clears) */
    WHAL_TIMEOUT_START(cfg->timeout);
    do {
        if (WHAL_TIMEOUT_EXPIRED(cfg->timeout))
            return WHAL_ETIMEOUT;
        err = whal_Eth_MdioRead(NULL, addr, PHY_BCR, &val);
        if (err)
            return err;
    } while (val & PHY_BCR_RESET);

    /* Enable autonegotiation */
    err = whal_Eth_MdioRead(NULL, addr, PHY_BCR, &val);
    if (err)
        return err;
    val |= PHY_BCR_ANEN;
    err = whal_Eth_MdioWrite(NULL, addr, PHY_BCR, val);
    if (err)
        return err;

    return WHAL_SUCCESS;
}

whal_Error whal_Lan8742a_Deinit(whal_EthPhy *phyDev)
{
    (void)phyDev;
    return WHAL_SUCCESS;
}

whal_Error whal_Lan8742a_GetLinkState(whal_EthPhy *phyDev, uint8_t *up,
                                       uint8_t *speed, uint8_t *duplex)
{
    uint8_t addr = whal_Lan8742a_Dev.addr;
    whal_Error err;
    uint16_t bsr;
    uint16_t scsr;
    (void)phyDev;

    if (!up || !speed || !duplex)
        return WHAL_EINVAL;

    /*
     * BSR link bit is latching-low (IEEE 802.3). First read clears a
     * stale link-down event; second read gives current status.
     */
    err = whal_Eth_MdioRead(NULL, addr, PHY_BSR, &bsr);
    if (err)
        return err;
    err = whal_Eth_MdioRead(NULL, addr, PHY_BSR, &bsr);
    if (err)
        return err;

    *up = (bsr & PHY_BSR_LINK) ? 1 : 0;

    if (*up) {
        err = whal_Eth_MdioRead(NULL, addr, PHY_PHYSCSR, &scsr);
        if (err)
            return err;
        uint16_t spd = scsr & PHY_PHYSCSR_SPEED_Msk;
        if (spd == PHY_PHYSCSR_100FD) {
            *speed = 100;
            *duplex = 1;
        } else if (spd == PHY_PHYSCSR_100HD) {
            *speed = 100;
            *duplex = 0;
        } else if (spd == PHY_PHYSCSR_10FD) {
            *speed = 10;
            *duplex = 1;
        } else {
            *speed = 10;
            *duplex = 0;
        }
    } else {
        *speed = 0;
        *duplex = 0;
    }

    return WHAL_SUCCESS;
}

#ifndef WHAL_CFG_LAN8742A_ETH_PHY_DIRECT_API_MAPPING
const whal_EthPhyDriver whal_Lan8742a_Driver = {
    .Init = whal_Lan8742a_Init,
    .Deinit = whal_Lan8742a_Deinit,
    .GetLinkState = whal_Lan8742a_GetLinkState,
};
#endif /* !WHAL_CFG_LAN8742A_ETH_PHY_DIRECT_API_MAPPING */
