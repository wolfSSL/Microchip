/* psa_store.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFPSA_STORE_H
#define WOLFPSA_STORE_H

#include <stddef.h>

#define WOLFPSA_STORE_KEY            0x00

/*
 * Opens access to location to read/write PSA data.
 *
 * @param [in]   type   Type of data to be stored. See WOLFPSA_STORE_* above.
 * @param [in]   id1    Numeric identifier 1.
 * @param [in]   id2    Numeric identifier 2.
 * @param [in]   read   1 when opening for read and 0 for write.
 * @param [out]  store  Return pointer to context data.
 * @return  0 on success.
 * @return  -4 when data not available.
 * @return  Other value to indicate failure.
 */
int wolfPSA_Store_Open(int type, unsigned long id1, unsigned long id2, int read,
    void** store);

/*
 * Opens access to location to read/write PSA data with extra size hint.
 *
 * @param [in]   type        Type of data to be stored. See WOLFPSA_STORE_* above.
 * @param [in]   id1         Numeric identifier 1.
 * @param [in]   id2         Numeric identifier 2.
 * @param [in]   read        1 when opening for read and 0 for write.
 * @param [in]   variableSz  Additional size needed for type (needed on write).
 * @param [out]  store       Return pointer to context data.
 * @return  0 on success.
 * @return  -4 when data not available.
 * @return  Other value to indicate failure.
 */
int wolfPSA_Store_OpenSz(int type, unsigned long id1, unsigned long id2, int read,
    int variableSz, void** store);

/*
 * Removes stored data from the specified location.
 *
 * @param [in]  type   Type of data to be removed. See WOLFPSA_STORE_* above.
 * @param [in]  id1    Numeric identifier 1.
 * @param [in]  id2    Numeric identifier 2.
 * @return  0 on success.
 * @return  -4 when data not available.
 * @return  Other value to indicate failure.
 */
int wolfPSA_Store_Remove(int type, unsigned long id1, unsigned long id2);

/*
 * Closes access to location being read or written.
 *
 * @param [in]  store  Context for operation.
 */
void wolfPSA_Store_Close(void* store);

/*
 * Reads a specific number of bytes into buffer.
 *
 * @param [in]       store   Context for operation.
 * @param [in, out]  buffer  Buffer to hold data read.
 * @param [in]       len     Length of data required.
 * @return  Length of data read into buffer.
 * @return  -ve to indicate failure.
 */
int wolfPSA_Store_Read(void* store, unsigned char* buffer, int len);

/*
 * Writes a specific number of bytes from buffer.
 *
 * @param [in]  store   Context for operation.
 * @param [in]  buffer  Data to write.
 * @param [in]  len     Length of data to write.
 * @return  Length of data written into buffer.
 * @return  -ve to indicate failure.
 */
int wolfPSA_Store_Write(void* store, unsigned char* buffer, int len);

#endif /* WOLFPSA_STORE_H */
