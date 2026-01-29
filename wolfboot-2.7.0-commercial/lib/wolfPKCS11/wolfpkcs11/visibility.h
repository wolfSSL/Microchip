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

#ifndef WOLFPKCS11_VISIBILITY_H
#define WOLFPKCS11_VISIBILITY_H


/* WP11_API is used for the public API symbols.
        It either imports or exports (or does nothing for static builds)

   WP11_LOCAL is used for non-API symbols (private).
*/

#if defined(BUILDING_WOLFPKCS11)
    #if defined(HAVE_VISIBILITY) && HAVE_VISIBILITY
        #define WP11_API   __attribute__ ((visibility("default")))
        #define WP11_LOCAL __attribute__ ((visibility("hidden")))
    #elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)
        #define WP11_API   __global
        #define WP11_LOCAL __hidden
    #elif defined(_MSC_VER) || defined(__MINGW32__)
        #if defined(WP11_DLL)
            #define WP11_API __declspec(dllexport)
        #else
            #define WP11_API
        #endif
        #define WP11_LOCAL
    #else
        #define WP11_API
        #define WP11_LOCAL
    #endif /* HAVE_VISIBILITY */
#else /* BUILDING_WOLFPKCS11 */
    #if defined(_MSC_VER) || defined(__MINGW32__)
        #if defined(WP11_DLL)
            #define WP11_API __declspec(dllimport)
        #else
            #define WP11_API
        #endif
        #define WP11_LOCAL
    #else
        #define WP11_API
        #define WP11_LOCAL
    #endif
#endif /* BUILDING_WOLFPKCS11 */

#endif /* WOLFPKCS11_VISIBILITY_H */

