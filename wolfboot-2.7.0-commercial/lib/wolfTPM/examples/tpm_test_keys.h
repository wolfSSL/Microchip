/* tpm_test_keys.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef _TPM_TEST_KEYS_H_
#define _TPM_TEST_KEYS_H_

#ifndef WOLFTPM2_NO_WRAPPER
#include <wolftpm/tpm2.h>
#include <wolftpm/tpm2_wrap.h>

WOLFTPM_LOCAL int readKeyBlob(const char* filename, WOLFTPM2_KEYBLOB* key);
WOLFTPM_LOCAL int writeKeyBlob(const char* filename, WOLFTPM2_KEYBLOB* key);

WOLFTPM_LOCAL int writeBin(const char* filename, const byte *buf, word32 bufSz);
WOLFTPM_LOCAL int readBin(const char* filename, byte *buf, word32* bufSz);

WOLFTPM_LOCAL int readAndLoadKey(WOLFTPM2_DEV* pDev,
                          WOLFTPM2_KEY* key,
                          WOLFTPM2_HANDLE* parent,
                          const char* filename,
                          const byte* auth,
                          int authSz);

WOLFTPM_LOCAL int createAndLoadKey(WOLFTPM2_DEV* pDev,
                WOLFTPM2_KEY* key,
                WOLFTPM2_HANDLE* parent,
                const char* filename,
                const byte* auth,
                int authSz,
                TPMT_PUBLIC* publicTemplate);


WOLFTPM_LOCAL int getPrimaryStoragekey(WOLFTPM2_DEV* pDev,
                                       WOLFTPM2_KEY* pStorageKey,
                                       TPM_ALG_ID alg);

WOLFTPM_LOCAL int getRSAkey(WOLFTPM2_DEV* pDev,
                            WOLFTPM2_KEY* pStorageKey,
                            WOLFTPM2_KEY* key,
                            void* pWolfRsaKey,
                            int tpmDevId,
                            const byte* auth, int authSz,
                            TPMT_PUBLIC* publicTemplate);

WOLFTPM_LOCAL int getECCkey(WOLFTPM2_DEV* pDev,
                            WOLFTPM2_KEY* pStorageKey,
                            WOLFTPM2_KEY* key,
                            void* pWolfEccKey,
                            int tpmDevId,
                            const byte* auth, int authSz,
                            TPMT_PUBLIC* publicTemplate);


/* if *buf != NULL, it will use existing buffer and provided bufLen */
WOLFTPM_LOCAL int loadFile(const char* fname, byte** buf, size_t* bufLen);

WOLFTPM_LOCAL int hexToByte(const char *hex, unsigned char *output, unsigned long sz);
WOLFTPM_LOCAL void printHexString(const unsigned char* bin, unsigned long sz,
    unsigned long maxLine);

#endif /* !WOLFTPM2_NO_WRAPPER */

#endif /* _TPM_TEST_KEYS_H_ */
