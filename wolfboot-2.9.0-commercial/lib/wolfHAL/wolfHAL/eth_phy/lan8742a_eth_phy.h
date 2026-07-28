/* lan8742a_eth_phy.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_LAN8742A_H
#define WHAL_LAN8742A_H

#include <wolfHAL/eth_phy/eth_phy.h>
#include <wolfHAL/timeout.h>

/*
 * @file lan8742a.h
 * @brief LAN8742A Ethernet PHY driver.
 *
 * The LAN8742A is a 10/100 Ethernet PHY from Microchip (formerly SMSC)
 * commonly found on STM32 Nucleo-144 boards. It connects to the MAC
 * via RMII and is configured over the MDIO bus.
 */

/*
 * @brief LAN8742A PHY configuration.
 */
typedef struct whal_Lan8742a_Cfg {
    whal_Timeout *timeout;
} whal_Lan8742a_Cfg;

/*
 * @brief Platform-owned LAN8742A PHY device singleton. Defined in the
 * driver TU from the WHAL_CFG_LAN8742A_DEV initializer in board.h.
 */
extern const whal_EthPhy whal_Lan8742a_Dev;

#ifndef WHAL_CFG_LAN8742A_ETH_PHY_DIRECT_API_MAPPING
/*
 * @brief Driver instance for LAN8742A PHY.
 */
extern const whal_EthPhyDriver whal_Lan8742a_Driver;

/*
 * @brief Initialize the LAN8742A PHY.
 *
 * Resets the PHY, configures autonegotiation, and waits for link.
 *
 * @param phyDev PHY device instance.
 *
 * @retval WHAL_SUCCESS   PHY initialized.
 * @retval WHAL_EINVAL    Invalid arguments.
 * @retval WHAL_ETIMEOUT  Link did not come up.
 */
whal_Error whal_Lan8742a_Init(whal_EthPhy *phyDev);

/*
 * @brief Deinitialize the LAN8742A PHY.
 *
 * Powers down the PHY.
 *
 * @param phyDev PHY device instance.
 *
 * @retval WHAL_SUCCESS Deinit completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Lan8742a_Deinit(whal_EthPhy *phyDev);

/*
 * @brief Get the LAN8742A link state.
 *
 * @param phyDev PHY device instance.
 * @param up     Output: 1 if link is up, 0 if down.
 * @param speed  Output: negotiated speed (10 or 100).
 *
 * @retval WHAL_SUCCESS Link state read.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Lan8742a_GetLinkState(whal_EthPhy *phyDev, uint8_t *up,
                                       uint8_t *speed, uint8_t *duplex);
#endif /* !WHAL_CFG_LAN8742A_ETH_PHY_DIRECT_API_MAPPING */

#endif /* WHAL_LAN8742A_H */
