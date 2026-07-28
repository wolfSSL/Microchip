/ * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* This file maps the MT3620 reference development board (RDB)
 * to the 'template appliance' abstraction used by the templates.
 * Some peripherals are on-board, while other peripherals must be
 * attached externally (conditionally).
 * See https://aka.ms/AzureSphereHardwareDefinitions for more
 * information on how to use hardware abstractions .
 */

#pragma once
#include "mt3620_rdb.h"

/* MT3620 SK: wolfssl azsphere CI app */
#define WOLF_AZSPHERE MT3620_RDB_LED1_RED

