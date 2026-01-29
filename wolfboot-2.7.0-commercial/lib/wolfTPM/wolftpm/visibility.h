/* visibility.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Visibility control macros */

#ifndef WOLFTPM_VISIBILITY_H
#define WOLFTPM_VISIBILITY_H

/* WOLFTPM_API is used for the public API symbols.
        It either imports or exports (or does nothing for static builds)

   WOLFTPM_LOCAL is used for non-API symbols (private).
*/

#if defined(BUILDING_WOLFTPM)
    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__) || \
        defined(_WIN32_WCE)
        #ifdef WOLFTPM_DLL
            #define WOLFTPM_API __declspec(dllexport)
        #else
            #define WOLFTPM_API
        #endif
        #define WOLFTPM_LOCAL
    #elif defined(HAVE_VISIBILITY) && HAVE_VISIBILITY
        #define WOLFTPM_API   __attribute__ ((visibility("default")))
        #define WOLFTPM_LOCAL __attribute__ ((visibility("hidden")))
    #elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)
        #define WOLFTPM_API   __global
        #define WOLFTPM_LOCAL __hidden
    #else
        #define WOLFTPM_API
        #define WOLFTPM_LOCAL
    #endif /* HAVE_VISIBILITY */
#else /* BUILDING_WOLFTPM */
    #if defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__) || \
        defined(_WIN32_WCE)
        #ifdef WOLFTPM_DLL
            #define WOLFTPM_API __declspec(dllimport)
        #else
            #define WOLFTPM_API
        #endif
        #define WOLFTPM_LOCAL
    #else
        #define WOLFTPM_API
        #define WOLFTPM_LOCAL
    #endif
#endif /* BUILDING_WOLFTPM */

#endif /* WOLFTPM_VISIBILITY_H */
