/* eth.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_ETH_H
#define WHAL_ETH_H

#include <wolfHAL/error.h>
#include <stddef.h>
#include <stdint.h>

/*
 * @file eth.h
 * @brief Generic Ethernet MAC abstraction and driver interface.
 */

typedef struct whal_Eth whal_Eth;

/*
 * @brief Ethernet link speed.
 */
#define WHAL_ETH_SPEED_10   10
#define WHAL_ETH_SPEED_100  100

/*
 * @brief Ethernet duplex mode.
 */
#define WHAL_ETH_DUPLEX_HALF 0
#define WHAL_ETH_DUPLEX_FULL 1

/*
 * @brief Driver vtable for Ethernet MAC devices.
 */
typedef struct {
    /* Initialize the Ethernet MAC, DMA descriptors, and MAC address. */
    whal_Error (*Init)(whal_Eth *ethDev);
    /* Deinitialize the Ethernet MAC hardware. */
    whal_Error (*Deinit)(whal_Eth *ethDev);
    /* Configure link speed/duplex, enable MAC TX/RX, start DMA engines. */
    whal_Error (*Start)(whal_Eth *ethDev, uint8_t speed, uint8_t duplex);
    /* Disable MAC TX/RX and stop DMA engines. */
    whal_Error (*Stop)(whal_Eth *ethDev);
    /* Transmit an Ethernet frame. */
    whal_Error (*Send)(whal_Eth *ethDev, const void *frame, size_t len);
    /* Receive an Ethernet frame. */
    whal_Error (*Recv)(whal_Eth *ethDev, void *frame, size_t *len);
    /* Read a PHY register via MDIO. */
    whal_Error (*MdioRead)(whal_Eth *ethDev, uint8_t phyAddr, uint8_t reg,
                           uint16_t *val);
    /* Write a PHY register via MDIO. */
    whal_Error (*MdioWrite)(whal_Eth *ethDev, uint8_t phyAddr, uint8_t reg,
                            uint16_t val);
} whal_EthDriver;

/*
 * @brief Ethernet device instance with a base address, driver vtable, and platform-specific cfg.
 */
struct whal_Eth {
    const size_t base;
    const whal_EthDriver *driver;
    void *cfg;
    uint8_t macAddr[6];
};

/*
 * @brief Initialize an Ethernet device and its driver.
 *
 * @param ethDev Ethernet device instance.
 *
 * @retval WHAL_SUCCESS Initialization completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Eth_Init(whal_Eth *ethDev);
/*
 * @brief Deinitialize an Ethernet device.
 *
 * @param ethDev Ethernet device instance.
 *
 * @retval WHAL_SUCCESS Deinit completed.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Eth_Deinit(whal_Eth *ethDev);
/*
 * @brief Start the Ethernet MAC.
 *
 * Configures MAC speed and duplex to match the PHY, enables TX/RX,
 * and starts the DMA engines.
 *
 * @param ethDev Ethernet device instance.
 * @param speed  Link speed: WHAL_ETH_SPEED_10 or WHAL_ETH_SPEED_100.
 * @param duplex Duplex mode: WHAL_ETH_DUPLEX_HALF or WHAL_ETH_DUPLEX_FULL.
 *
 * @retval WHAL_SUCCESS MAC started.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Eth_Start(whal_Eth *ethDev, uint8_t speed, uint8_t duplex);
/*
 * @brief Stop the Ethernet MAC.
 *
 * Disables TX/RX and stops the DMA engines.
 *
 * @param ethDev Ethernet device instance.
 *
 * @retval WHAL_SUCCESS MAC stopped.
 * @retval WHAL_EINVAL  Invalid arguments.
 */
whal_Error whal_Eth_Stop(whal_Eth *ethDev);
/*
 * @brief Transmit an Ethernet frame.
 *
 * @param ethDev Ethernet device instance.
 * @param frame  Frame data to transmit.
 * @param len    Length of the frame in bytes.
 *
 * @retval WHAL_SUCCESS   Frame queued for transmission.
 * @retval WHAL_EINVAL    Invalid arguments.
 * @retval WHAL_ENOTREADY No TX descriptor available.
 */
whal_Error whal_Eth_Send(whal_Eth *ethDev, const void *frame, size_t len);
/*
 * @brief Receive an Ethernet frame.
 *
 * @param ethDev Ethernet device instance.
 * @param frame  Buffer to receive frame data into.
 * @param len    On entry, size of the buffer. On exit, length of received frame.
 *
 * @retval WHAL_SUCCESS   Frame received.
 * @retval WHAL_EINVAL    Invalid arguments.
 * @retval WHAL_ENOTREADY No frame available.
 */
whal_Error whal_Eth_Recv(whal_Eth *ethDev, void *frame, size_t *len);
/*
 * @brief Read a PHY register via the MDIO bus.
 *
 * @param ethDev  Ethernet device instance (MDIO master).
 * @param phyAddr PHY address on the MDIO bus (0-31).
 * @param reg     PHY register address (0-31).
 * @param val     Output for the 16-bit register value.
 *
 * @retval WHAL_SUCCESS   Register read completed.
 * @retval WHAL_EINVAL    Invalid arguments.
 * @retval WHAL_ETIMEOUT  MDIO bus busy timeout.
 */
whal_Error whal_Eth_MdioRead(whal_Eth *ethDev, uint8_t phyAddr, uint8_t reg,
                              uint16_t *val);
/*
 * @brief Write a PHY register via the MDIO bus.
 *
 * @param ethDev  Ethernet device instance (MDIO master).
 * @param phyAddr PHY address on the MDIO bus (0-31).
 * @param reg     PHY register address (0-31).
 * @param val     16-bit value to write.
 *
 * @retval WHAL_SUCCESS   Register write completed.
 * @retval WHAL_EINVAL    Invalid arguments.
 * @retval WHAL_ETIMEOUT  MDIO bus busy timeout.
 */
whal_Error whal_Eth_MdioWrite(whal_Eth *ethDev, uint8_t phyAddr, uint8_t reg,
                               uint16_t val);

#endif /* WHAL_ETH_H */
