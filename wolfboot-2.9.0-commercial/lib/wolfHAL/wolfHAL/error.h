/* error.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WHAL_ERROR_H
#define WHAL_ERROR_H


/*
 * @file error.h
 * @brief Shared error codes for wolfHAL APIs.
 */

/* Status code type used by wolfHAL.  Zero is success, non-zero is error. */
typedef int whal_Error;

enum {
    /* Operation completed successfully. */
    WHAL_SUCCESS = 0,
    /* Invalid argument (null pointer, bad configuration). */
    WHAL_EINVAL = 1,
    /* Resource not ready or busy. */
    WHAL_ENOTREADY = 2,
    /* Hardware device error. */
    WHAL_EHARDWARE = 3,
    /* Operation timed out. */
    WHAL_ETIMEOUT = 4,
    /* Operation or argument not supported by the selected driver/hardware
     * (use for requests that are valid in general but this implementation
     * cannot fulfill — e.g., hardware lacks the feature or the specific
     * parameter combination isn't supported). For universally invalid
     * arguments (null pointer, out-of-range enum) return WHAL_EINVAL. */
    WHAL_ENOTSUP = 5,
};

#endif /* WHAL_ERROR_H */
