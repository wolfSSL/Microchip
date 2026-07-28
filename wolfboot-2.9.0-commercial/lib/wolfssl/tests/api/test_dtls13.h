/* test_dtls13.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef TESTS_API_DTLS13_H
#define TESTS_API_DTLS13_H

#include <tests/api/api_decl.h>

/* DTLSv1.3-only tests. None share helpers with DTLS<=1.2 tests, so they
 * live in their own translation unit and register under the "dtls13"
 * group. Each function is defined unconditionally with the body (or the
 * whole function via #else stub) guarded by WOLFSSL_DTLS13. */
int test_dtls13_bad_epoch_ch(void);
int test_wolfSSL_dtls13_null_cipher(void);
int test_dtls13_frag_ch_pq(void);
int test_dtls_frag_ch(void);
int test_dtls_empty_keyshare_with_cookie(void);
int test_dtls13_missing_finished_client(void);
int test_dtls13_missing_finished_server(void);
int test_dtls13_finished_send_error_propagation(void);

/* DTLSv1.3-only tests moved from test_dtls.c (isolated from DTLS<=1.2 code,
 * none share helpers with non-DTLS13 tests). */
int test_dtls13_basic_connection_id(void);
int test_dtls13_hrr_want_write(void);
int test_dtls13_every_write_want_write(void);
int test_dtls13_epochs(void);
int test_dtls13_ack_order(void);
int test_dtls13_ack_overflow(void);
int test_dtls13_ack_dup_write_counter(void);
int test_dtls13_ch2_rtx_no_ch1(void);
int test_dtls13_frag_ch2_with_ch1_rtx(void);
int test_dtls_srtp(void);
int test_dtls13_min_rtx_interval(void);
int test_dtls13_no_session_id_echo(void);
int test_dtls13_5_9_0_compat(void);
int test_dtls13_oversized_cert_chain(void);

#define TEST_DTLS13_DECLS                                                      \
    TEST_DECL_GROUP("dtls13", test_dtls13_bad_epoch_ch),                       \
    TEST_DECL_GROUP("dtls13", test_wolfSSL_dtls13_null_cipher),                \
    TEST_DECL_GROUP("dtls13", test_dtls13_frag_ch_pq),                         \
    TEST_DECL_GROUP("dtls13", test_dtls_frag_ch),                              \
    TEST_DECL_GROUP("dtls13", test_dtls_empty_keyshare_with_cookie),           \
    TEST_DECL_GROUP("dtls13", test_dtls13_missing_finished_client),            \
    TEST_DECL_GROUP("dtls13", test_dtls13_missing_finished_server),            \
    TEST_DECL_GROUP("dtls13", test_dtls13_finished_send_error_propagation),    \
    TEST_DECL_GROUP("dtls13", test_dtls13_basic_connection_id),                \
    TEST_DECL_GROUP("dtls13", test_dtls13_hrr_want_write),                     \
    TEST_DECL_GROUP("dtls13", test_dtls13_every_write_want_write),             \
    TEST_DECL_GROUP("dtls13", test_dtls13_epochs),                             \
    TEST_DECL_GROUP("dtls13", test_dtls13_ack_order),                          \
    TEST_DECL_GROUP("dtls13", test_dtls13_ack_overflow),                       \
    TEST_DECL_GROUP("dtls13", test_dtls13_ack_dup_write_counter),              \
    TEST_DECL_GROUP("dtls13", test_dtls13_ch2_rtx_no_ch1),                     \
    TEST_DECL_GROUP("dtls13", test_dtls13_frag_ch2_with_ch1_rtx),              \
    TEST_DECL_GROUP("dtls13", test_dtls_srtp),                                 \
    TEST_DECL_GROUP("dtls13", test_dtls13_min_rtx_interval),                   \
    TEST_DECL_GROUP("dtls13", test_dtls13_no_session_id_echo),                 \
    TEST_DECL_GROUP("dtls13", test_dtls13_5_9_0_compat),                       \
    TEST_DECL_GROUP("dtls13", test_dtls13_oversized_cert_chain)

#endif /* TESTS_API_DTLS13_H */
