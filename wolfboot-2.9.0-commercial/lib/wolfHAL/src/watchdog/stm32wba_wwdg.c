/* stm32wba_wwdg.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Forward STM32WBA WWDG direct API mapping flag to STM32WB */
#ifdef WHAL_CFG_STM32WBA_WWDG_DIRECT_API_MAPPING
#define WHAL_CFG_STM32WB_WWDG_DIRECT_API_MAPPING
#endif

#include "stm32wb_wwdg.c"
