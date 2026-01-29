/* store.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFPKCS11_STORE
#define WOLFPKCS11_STORE

#include <wolfpkcs11/pkcs11.h>

#define WOLFPKCS11_STORE_TOKEN          0x00
#define WOLFPKCS11_STORE_OBJECT         0x01
#define WOLFPKCS11_STORE_SYMMKEY        0x02
#define WOLFPKCS11_STORE_RSAKEY_PRIV    0x03
#define WOLFPKCS11_STORE_RSAKEY_PUB     0x04
#define WOLFPKCS11_STORE_ECCKEY_PRIV    0x05
#define WOLFPKCS11_STORE_ECCKEY_PUB     0x06
#define WOLFPKCS11_STORE_DHKEY_PRIV     0x07
#define WOLFPKCS11_STORE_DHKEY_PUB      0x08
#define WOLFPKCS11_STORE_CERT           0x09
#define WOLFPKCS11_STORE_TRUST          0x0A
#define WOLFPKCS11_STORE_DATA           0x0B

/*
 * Opens access to location to read/write token data.
 *
 * @param [in]   type   Type of data to be stored. See WOLFPKCS11_STORE_* above.
 * @param [in]   id1    Numeric identifier 1.
 * @param [in]   id2    Numeric identifier 2.
 * @param [in]   read   1 when opening for read and 0 for write.
 * @param [out]  store  Return pointer to context data.
 * @return  0 on success.
 * @return  -4 when data not available.
 * @return  Other value to indicate failure.
 */
WP11_LOCAL int wolfPKCS11_Store_Open(int type, CK_ULONG id1, CK_ULONG id2, int read,
    void** store);


/*
 * Removes stored data from the specified location.
 *
 * @param [in]  type   Type of data to be removed. See WOLFPKCS11_STORE_* above.
 * @param [in]  id1    Numeric identifier 1.
 * @param [in]  id2    Numeric identifier 2.
 * @return  0 on success.
 * @return  -4 when data not available.
 * @return  Other value to indicate failure.
 */
WP11_LOCAL int wolfPKCS11_Store_Remove(int type, CK_ULONG id1, CK_ULONG id2);

/*
 * Opens access to location to read/write token data.
 *
 * @param [in]   type   Type of data to be stored. See WOLFPKCS11_STORE_* above.
 * @param [in]   id1    Numeric identifier 1.
 * @param [in]   id2    Numeric identifier 2.
 * @param [in]   read   1 when opening for read and 0 for write.
 * @param [in]   variableSz additional size needed for type (needed on write)
 * @param [out]  store  Return pointer to context data.
 * @return  0 on success.
 * @return  -4 when data not available.
 * @return  Other value to indicate failure.
 */
WP11_LOCAL int wolfPKCS11_Store_OpenSz(int type, CK_ULONG id1, CK_ULONG id2, int read,
    int variableSz, void** store);

/*
 * Closes access to location being read or written.
 * Any dynamic memory associated with the store is freed here.
 *
 * @param [in]  store  Context for operation.
 */
WP11_LOCAL void wolfPKCS11_Store_Close(void* store);

/*
 * Reads a specific number of bytes into buffer.
 *
 * @param [in]       store   Context for operation.
 * @param [in, out]  buffer  Buffer to hold data read.
 * @param [in]       len     Length of data required.
 * @return  Length of data read into buffer.
 * @return  -ve to indicate failure.
 */
WP11_LOCAL int wolfPKCS11_Store_Read(void* store, unsigned char* buffer, int len);

/*
 * Writes a specific number of bytes from buffer.
 *
 * @param [in]  store   Context for operation.
 * @param [in]  buffer  Data to write.
 * @param [in]  len     Length of data to write.
 * @return  Length of data written into buffer.
 * @return  -ve to indicate failure.
 */
WP11_LOCAL int wolfPKCS11_Store_Write(void* store, unsigned char* buffer, int len);

#endif /* WOLFPKCS11_STORE */
