/* visibility.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSH.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


/*
 * The visibility header handles the visibility of function prototypes
 * between the local (used between modules in the library) and public
 * (exported for the library user) APIs.
 */


#ifndef _WOLFSSH_VISIBILITY_H_
#define _WOLFSSH_VISIBILITY_H_


#ifdef __cplusplus
extern "C" {
#endif

/* WOLFSSH_API is used for the public API symbols.
        It either imports or exports (or does nothing for static builds)

   WOLFSSH_LOCAL is used for non-API symbols (private).
*/

#if defined(BUILDING_WOLFSSH)
    #if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__)
        #ifdef WOLFSSH_DLL
            #define WOLFSSH_API extern __declspec(dllexport)
        #else
            #define WOLFSSH_API
        #endif
        #define WOLFSSH_LOCAL
    #elif defined(HAVE_VISIBILITY) && HAVE_VISIBILITY
        #define WOLFSSH_API   __attribute__ ((visibility("default")))
        #define WOLFSSH_LOCAL __attribute__ ((visibility("hidden")))
    #elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)
        #define WOLFSSH_API   __global
        #define WOLFSSH_LOCAL __hidden
    #else
        #define WOLFSSH_API
        #define WOLFSSH_LOCAL
    #endif /* HAVE_VISIBILITY */
#else /* BUILDING_WOLFSSH */
    #if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__)
        #ifdef WOLFSSH_DLL
            #define WOLFSSH_API extern __declspec(dllimport)
        #else
            #define WOLFSSH_API
        #endif
        #define WOLFSSH_LOCAL
    #else
        #define WOLFSSH_API
        #define WOLFSSH_LOCAL
    #endif
#endif /* BUILDING_WOLFSSH */


/* Do nothing tag to flag an API as deprecated. */
#define DEPRECATED


#ifdef __cplusplus
}
#endif

#endif /* _WOLFSSH_VISIBILITY_H_ */

