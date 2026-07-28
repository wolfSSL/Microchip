/* eth_phy.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_ETH_PHY_H
#define WHAL_ETH_PHY_H

#include <wolfHAL/error.h>
#include <wolfHAL/eth/eth.h>
#include <stdint.h>

/*
 * @file eth_phy.h
 * @brief Generic Ethernet PHY abstraction and driver interface.
 *
 * The PHY driver handles link negotiation and status for an Ethernet
 * PHY device connected to a MAC via the MDIO bus. Different PHY chips
 * (e.g. LAN8742A, DP83848) have different init sequences but share
 * the same API.
 */

typedef struct whal_EthPhy whal_EthPhy;

/*
 * @brief Driver vtable for Ethernet PHY devices.
 */
typedef struct {
    /* Reset PHY, configure autonegotiation, and wait for link. */
    whal_Error (*Init)(whal_EthPhy *phyDev);
    /* Power down the PHY. */
    whal_Error (*Deinit)(whal_EthPhy *phyDev);
    /* Read current link state: up/down, negotiated speed, and duplex. */
    whal_Error (*GetLinkState)(whal_EthPhy *phyDev, uint8_t *up,
                               uint8_t *speed, uint8_t *duplex);
} whal_EthPhyDriver;

/*
 * @brief Ethernet PHY device instance.
 *
 * The PHY is not memory-mapped. It accesses registers through the
 * parent MAC's MDIO bus via whal_Eth_MdioRead/MdioWrite.
 */
struct whal_EthPhy {
    whal_Eth *eth;                    /* MAC whose MDIO bus this PHY is on */
    uint8_t addr;                     /* PHY address on MDIO bus (0-31) */
    const whal_EthPhyDriver *driver;
    void *cfg;
};

/*
 * @brief Initialize an Ethernet PHY.
 *
 * @param phyDev PHY device instance.
 *
 * @retval WHAL_SUCCESS   PHY initialized and link established.
 * @retval WHAL_EINVAL    Invalid arguments.
 * @retval WHAL_ETIMEOUT  Link did not come up within timeout.
 */
whal_Error whal_EthPhy_Init(whal_EthPhy *phyDev);
/*
 * @brief Deinitialize an Ethernet PHY.
 *
 * @param phyDev PHY device instance.
 *
 * @retval WHAL_SUCCESS Deinit completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_EthPhy_Deinit(whal_EthPhy *phyDev);
/*
 * @brief Get the current link state.
 *
 * @param phyDev PHY device instance.
 * @param up     Output: 1 if link is up, 0 if down.
 * @param speed  Output: negotiated speed (WHAL_ETH_SPEED_10/100).
 * @param duplex Output: duplex mode (WHAL_ETH_DUPLEX_HALF/FULL).
 *
 * @retval WHAL_SUCCESS   Link state read.
 * @retval WHAL_EINVAL    Invalid arguments.
 */
whal_Error whal_EthPhy_GetLinkState(whal_EthPhy *phyDev, uint8_t *up,
                                     uint8_t *speed, uint8_t *duplex);

#endif /* WHAL_ETH_PHY_H */
