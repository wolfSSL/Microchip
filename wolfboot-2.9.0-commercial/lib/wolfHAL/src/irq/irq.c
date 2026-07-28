/* irq.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfHAL/irq/irq.h>

inline whal_Error whal_Irq_Init(whal_Irq *irqDev)
{
    if (!irqDev || !irqDev->driver || !irqDev->driver->Init) {
        return WHAL_EINVAL;
    }

    return irqDev->driver->Init(irqDev);
}

inline whal_Error whal_Irq_Deinit(whal_Irq *irqDev)
{
    if (!irqDev || !irqDev->driver || !irqDev->driver->Deinit) {
        return WHAL_EINVAL;
    }

    return irqDev->driver->Deinit(irqDev);
}

inline whal_Error whal_Irq_Enable(whal_Irq *irqDev, size_t irq,
                                   const void *irqCfg)
{
    if (!irqDev || !irqDev->driver || !irqDev->driver->Enable) {
        return WHAL_EINVAL;
    }

    return irqDev->driver->Enable(irqDev, irq, irqCfg);
}

inline whal_Error whal_Irq_Disable(whal_Irq *irqDev, size_t irq)
{
    if (!irqDev || !irqDev->driver || !irqDev->driver->Disable) {
        return WHAL_EINVAL;
    }

    return irqDev->driver->Disable(irqDev, irq);
}
