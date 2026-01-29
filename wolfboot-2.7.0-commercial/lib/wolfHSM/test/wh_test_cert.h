/*
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
/*
 * test/wh_test_cert.h
 */

#ifndef WOLFHSM_WH_TEST_CERT_H_
#define WOLFHSM_WH_TEST_CERT_H_

#include "wolfhsm/wh_server.h"
#include "wolfhsm/wh_client.h"

#include "wh_test_common.h"

/* Run certificate configuration tests */
int whTest_CertRamSim(whTestNvmBackendType nvmType);
int whTest_CertServerCfg(whServerConfig* serverCfg);
int whTest_CertClient(whClientContext* client);
#if defined(WOLFHSM_CFG_DMA)
int whTest_CertClientDma_ClientServerTestInternal(whClientContext* client);
#endif

#if defined(WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT)
int whTest_CertClientAcert(whClientContext* client);
#if defined(WOLFHSM_CFG_DMA)
int whTest_CertClientAcertDma_ClientServerTestInternal(whClientContext* client);
#endif /* WOLFHSM_CFG_DMA */
#endif /* WOLFHSM_CFG_CERTIFICATE_MANAGER_ACERT */

#endif /* !WOLFHSM_WH_TEST_CERT_H_ */