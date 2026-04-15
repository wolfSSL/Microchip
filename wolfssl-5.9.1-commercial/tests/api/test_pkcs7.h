/* test_pkcs7.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_PKCS7_H
#define WOLFCRYPT_TEST_PKCS7_H

#include <tests/api/api_decl.h>

int test_wc_PKCS7_New(void);
int test_wc_PKCS7_Init(void);
int test_wc_PKCS7_InitWithCert(void);
int test_wc_PKCS7_EncodeData(void);
int test_wc_PKCS7_EncodeSignedData(void);
#if defined(HAVE_PKCS7) && defined(WC_RSA_PSS) && !defined(NO_RSA) && \
    !defined(NO_FILESYSTEM) && !defined(NO_SHA256)
int test_wc_PKCS7_EncodeSignedData_RSA_PSS(void);
#endif
#if defined(HAVE_PKCS7) && defined(WC_RSA_PSS) && !defined(NO_RSA) && \
    !defined(NO_FILESYSTEM) && !defined(NO_SHA256) && \
    !defined(NO_AES) && defined(HAVE_AES_CBC) && defined(WOLFSSL_AES_256)
int test_wc_PKCS7_EnvelopedData_KTRI_RSA_PSS(void);
#endif
int test_wc_PKCS7_EncodeSignedData_ex(void);
int test_wc_PKCS7_VerifySignedData_RSA(void);
int test_wc_PKCS7_VerifySignedData_ECC(void);
int test_wc_PKCS7_DecodeEnvelopedData_stream(void);
int test_wc_PKCS7_EncodeDecodeEnvelopedData(void);
int test_wc_PKCS7_SetAESKeyWrapUnwrapCb(void);
int test_wc_PKCS7_GetEnvelopedDataKariRid(void);
int test_wc_PKCS7_EncodeEncryptedData(void);
int test_wc_PKCS7_DecodeEncryptedKeyPackage(void);
int test_wc_PKCS7_DecodeSymmetricKeyPackage(void);
int test_wc_PKCS7_DecodeOneSymmetricKey(void);
int test_wc_PKCS7_Degenerate(void);
int test_wc_PKCS7_BER(void);
int test_wc_PKCS7_signed_enveloped(void);
int test_wc_PKCS7_NoDefaultSignedAttribs(void);
int test_wc_PKCS7_SetOriEncryptCtx(void);
int test_wc_PKCS7_SetOriDecryptCtx(void);
int test_wc_PKCS7_DecodeCompressedData(void);
int test_wc_PKCS7_DecodeEnvelopedData_multiple_recipients(void);
int test_wc_PKCS7_VerifySignedData_PKCS7ContentSeq(void);
int test_wc_PKCS7_VerifySignedData_IndefLenOOB(void);


#define TEST_PKCS7_DECLS                                        \
    TEST_DECL_GROUP("pkcs7", test_wc_PKCS7_New),                \
    TEST_DECL_GROUP("pkcs7", test_wc_PKCS7_Init)

#if defined(HAVE_PKCS7) && defined(WC_RSA_PSS) && !defined(NO_RSA) && \
    !defined(NO_FILESYSTEM) && !defined(NO_SHA256)
#define TEST_PKCS7_RSA_PSS_SD_DECL \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_EncodeSignedData_RSA_PSS),
#else
#define TEST_PKCS7_RSA_PSS_SD_DECL
#endif

#if defined(HAVE_PKCS7) && defined(WC_RSA_PSS) && !defined(NO_RSA) && \
    !defined(NO_FILESYSTEM) && !defined(NO_SHA256) && \
    !defined(NO_AES) && defined(HAVE_AES_CBC) && defined(WOLFSSL_AES_256)
#define TEST_PKCS7_RSA_PSS_ED_DECL \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_EnvelopedData_KTRI_RSA_PSS),
#else
#define TEST_PKCS7_RSA_PSS_ED_DECL
#endif

#define TEST_PKCS7_SIGNED_DATA_DECLS                                    \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_InitWithCert),            \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_EncodeData),              \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_EncodeSignedData),        \
    TEST_PKCS7_RSA_PSS_SD_DECL                                           \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_EncodeSignedData_ex),     \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_VerifySignedData_RSA),    \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_VerifySignedData_ECC),    \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_Degenerate),              \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_BER),                     \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_NoDefaultSignedAttribs),  \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_VerifySignedData_PKCS7ContentSeq), \
    TEST_DECL_GROUP("pkcs7_sd", test_wc_PKCS7_VerifySignedData_IndefLenOOB)

#define TEST_PKCS7_ENCRYPTED_DATA_DECLS                                     \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_DecodeEnvelopedData_stream),  \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_EncodeDecodeEnvelopedData),   \
    TEST_PKCS7_RSA_PSS_ED_DECL                                              \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_SetAESKeyWrapUnwrapCb),       \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_GetEnvelopedDataKariRid),     \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_EncodeEncryptedData),         \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_DecodeEncryptedKeyPackage),   \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_DecodeSymmetricKeyPackage),   \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_DecodeOneSymmetricKey),       \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_SetOriEncryptCtx),            \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_SetOriDecryptCtx),            \
    TEST_DECL_GROUP("pkcs7_ed", test_wc_PKCS7_DecodeEnvelopedData_multiple_recipients)

#define TEST_PKCS7_SIGNED_ENCRYPTED_DATA_DECLS                              \
    TEST_DECL_GROUP("pkcs7_sed", test_wc_PKCS7_signed_enveloped)

#define TEST_PKCS7_COMPRESSED_DATA_DECLS                                    \
    TEST_DECL_GROUP("pkcs7_cd", test_wc_PKCS7_DecodeCompressedData)

#endif /* WOLFCRYPT_TEST_PKCS7_H */
