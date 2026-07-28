/* main.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/port/psa/psa.h>
#include <wolfcrypt/benchmark/benchmark.h>

static void* load_wolfpsa(void)
{
    const char* lib = getenv("WOLFPSA_LIB");
    void* handle;

    if (lib == NULL || lib[0] == '\0')
        lib = "libwolfpsa.so";

    handle = dlopen(lib, RTLD_NOW | RTLD_GLOBAL);
    if (handle == NULL) {
        fprintf(stderr, "wolfpsa: dlopen(%s) failed: %s\n", lib, dlerror());
        return NULL;
    }

    return handle;
}

int main(int argc, char** argv)
{
    void* wolfpsa_handle;
    int ret;

#if !defined(WOLFSSL_HAVE_PSA)
    fprintf(stderr, "ERROR: WOLFSSL_HAVE_PSA is not enabled in this build.\n");
    return EXIT_FAILURE;
#endif

    wolfpsa_handle = load_wolfpsa();
    if (wolfpsa_handle == NULL)
        return EXIT_FAILURE;

    /* Initialize wolfCrypt/PSA once so we can register the PSA CryptoCb. */
    ret = wolfCrypt_Init();
    if (ret != 0) {
        fprintf(stderr, "wolfCrypt_Init failed: %d\n", ret);
        dlclose(wolfpsa_handle);
        return EXIT_FAILURE;
    }

    ret = wolfcrypt_benchmark_main(argc, argv);

    wolfCrypt_Cleanup();
    dlclose(wolfpsa_handle);

    return ret;
}
