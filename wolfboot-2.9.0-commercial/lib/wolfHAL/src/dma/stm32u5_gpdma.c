/* stm32u5_gpdma.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef WHAL_CFG_STM32U5_GPDMA_DIRECT_API_MAPPING
#define WHAL_CFG_STM32WBA_GPDMA_DIRECT_API_MAPPING
#endif
#ifdef WHAL_CFG_STM32U5_GPDMA_SINGLE_INSTANCE
#define WHAL_CFG_STM32WBA_GPDMA_SINGLE_INSTANCE
#endif
#include "stm32wba_gpdma.c"
