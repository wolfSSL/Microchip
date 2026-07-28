/* quickassist_mem.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _QUICKASSIST_MEM_H_
#define _QUICKASSIST_MEM_H_

#ifdef HAVE_INTEL_QA

#include <wolfssl/wolfcrypt/port/intel/quickassist.h>

CpaStatus qaeMemInit(void);
void qaeMemDestroy(void);

#ifndef QAT_V2
    #define QAE_PHYS_ADDR  CpaPhysicalAddr
    WOLFSSL_LOCAL QAE_PHYS_ADDR qaeVirtToPhysNUMA(void* pVirtAddress);
#endif


#ifdef WOLFSSL_TRACK_MEMORY
    WOLFSSL_API int InitMemoryTracker(void);
    WOLFSSL_API void ShowMemoryTracker(void);
#endif


WOLFSSL_API void* IntelQaMalloc(size_t size, void* heap, int type
#ifdef WOLFSSL_DEBUG_MEMORY
    , const char* func, unsigned int line
#endif
);

WOLFSSL_API void IntelQaFree(void *ptr, void* heap, int type
#ifdef WOLFSSL_DEBUG_MEMORY
    , const char* func, unsigned int line
#endif
);

WOLFSSL_API void* IntelQaRealloc(void *ptr, size_t size, void* heap, int type
#ifdef WOLFSSL_DEBUG_MEMORY
    , const char* func, unsigned int line
#endif
);

#endif /* HAVE_INTEL_QA */

#endif /* _QUICKASSIST_MEM_H_ */
