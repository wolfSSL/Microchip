/* template_appliance.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* This file maps the Seeed MT3620 Mini Development Board (MDB)
 * to the 'template appliance' abstraction used by the templates.
 * Some peripherals are on-board, while other peripherals must be
 * attached externally (conditionally).
 * See https://aka.ms/AzureSphereHardwareDefinitions for more
 * information on how to use hardware abstractions .
 */

#pragma once
#include "seeed_mt3620_mdb.h"

/* MT3620 SK: wolfssl azsphere CI app */
#define WOLF_AZSPHERE SEEED_MT3620_MDB_USER_LED

