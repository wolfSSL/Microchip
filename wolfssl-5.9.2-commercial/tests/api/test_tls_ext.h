/* test_tls_ext.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef TESTS_API_TEST_TLS_EXT_H
#define TESTS_API_TEST_TLS_EXT_H

int test_tls_ems_downgrade(void);
int test_tls_ems_resumption_downgrade(void);
int test_tls_ems_resumption_server_downgrade(void);
int test_tls12_chacha20_poly1305_bad_tag(void);
int test_tls13_null_cipher_bad_hmac(void);
int test_scr_verify_data_mismatch(void);
int test_scr_no_renegotiation_option(void);
int test_helloRequest_no_renegotiation_option(void);
int test_tls13_hrr_cipher_suite_mismatch(void);
int test_tls13_ticket_age_out_of_window(void);
int test_wolfSSL_DisableExtendedMasterSecret(void);
int test_certificate_authorities_certificate_request(void);
int test_certificate_authorities_client_hello(void);
int test_TLSX_TCA_Find(void);
int test_TLSX_SNI_GetSize_overflow(void);
int test_TLSX_ECH_msg_type_validation(void);
int test_TLSX_SRTP_msg_type_validation(void);
int test_TLSX_ALPN_server_response_count(void);
int test_TLSX_SupportedCurve_empty_or_unsupported(void);
int test_TLSX_PointFormat_uncompressed_required(void);

#endif /* TESTS_API_TEST_TLS_EMS_H */
