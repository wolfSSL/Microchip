/*
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*
 * Registry of every test function. To add a test:
 *   1. Add a WH_TEST_DECL(name); line below so the test has a
 *      weak skip stub when its feature gate is off.
 *   2. Add a row to the appropriate per-group array (Misc /
 *      Server / Client) so the runner picks it up.
 *
 * The weak stub returns WH_TEST_SKIPPED; the real test, when
 * compiled in, provides a strong symbol that the linker picks
 * instead.
 *
 * Per-file crypto suites are aggregated into a single whTest_Crypto_*
 * entry point per source file; the per-subtest functions are file-static
 * and run via WH_TEST_RUN_SUBTEST from inside the group entry point.
 */

#include "wh_test_list.h"

/* Test declarations and weak skip implementations. */
WH_TEST_DECL(whTest_Comm);
WH_TEST_DECL(whTest_Dma);
WH_TEST_DECL(whTest_KeystoreReqSize);
WH_TEST_DECL(whTest_CertVerify);
WH_TEST_DECL(whTest_NvmOptional);
WH_TEST_DECL(whTest_ClientCerts);
WH_TEST_DECL(whTest_Crypto_Aes);
WH_TEST_DECL(whTest_CryptoAesKeyUsagePolicies);
WH_TEST_DECL(whTest_Crypto_Cmac);
WH_TEST_DECL(whTest_Crypto_Curve25519);
WH_TEST_DECL(whTest_Crypto_Ecc);
WH_TEST_DECL(whTest_Crypto_Ed25519);
WH_TEST_DECL(whTest_Crypto_Kdf);
WH_TEST_DECL(whTest_Crypto_KeyPolicy);
WH_TEST_DECL(whTest_Crypto_MlDsa);
WH_TEST_DECL(whTest_Crypto_Rng);
WH_TEST_DECL(whTest_Crypto_Rsa);
WH_TEST_DECL(whTest_Crypto_Sha);
WH_TEST_DECL(whTest_Echo);
WH_TEST_DECL(whTest_ServerInfo);
WH_TEST_DECL(whTest_WolfCryptTest);

const whTestCase whTestsMisc[] = {
    { "whTest_Comm",             whTest_Comm },
    { "whTest_Dma",              whTest_Dma },
    { "whTest_KeystoreReqSize",  whTest_KeystoreReqSize },
};
const size_t whTestsMiscCount = sizeof(whTestsMisc) / sizeof(whTestsMisc[0]);

const whTestCase whTestsServer[] = {
    {"whTest_CertVerify", whTest_CertVerify},
    {"whTest_NvmOptional", whTest_NvmOptional},
};
const size_t whTestsServerCount = sizeof(whTestsServer) / sizeof(whTestsServer[0]);

const whTestCase whTestsClient[] = {
    { "whTest_ClientCerts", whTest_ClientCerts },
    { "whTest_Crypto_Aes", whTest_Crypto_Aes },
    { "whTest_CryptoAesKeyUsagePolicies", whTest_CryptoAesKeyUsagePolicies },
    { "whTest_Crypto_Cmac", whTest_Crypto_Cmac },
    { "whTest_Crypto_Curve25519", whTest_Crypto_Curve25519 },
    { "whTest_Crypto_Ecc", whTest_Crypto_Ecc },
    { "whTest_Crypto_Ed25519", whTest_Crypto_Ed25519 },
    { "whTest_Crypto_Kdf", whTest_Crypto_Kdf },
    { "whTest_Crypto_KeyPolicy", whTest_Crypto_KeyPolicy },
    { "whTest_Crypto_MlDsa", whTest_Crypto_MlDsa },
    { "whTest_Crypto_Rng", whTest_Crypto_Rng },
    { "whTest_Crypto_Rsa", whTest_Crypto_Rsa },
    { "whTest_Crypto_Sha", whTest_Crypto_Sha },
    { "whTest_Echo", whTest_Echo },
    { "whTest_ServerInfo", whTest_ServerInfo },
    { "whTest_WolfCryptTest", whTest_WolfCryptTest },
};
const size_t whTestsClientCount = sizeof(whTestsClient) / sizeof(whTestsClient[0]);
