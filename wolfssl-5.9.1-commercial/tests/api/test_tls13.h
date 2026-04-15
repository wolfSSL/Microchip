/* test_tls13.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_TLS13_H
#define WOLFCRYPT_TEST_TLS13_H

#include <tests/api/api_decl.h>

int test_tls13_apis(void);
int test_tls13_cipher_suites(void);
int test_tls13_bad_psk_binder(void);
int test_tls13_rpk_handshake(void);
int test_tls13_pq_groups(void);
int test_tls13_early_data(void);
int test_tls13_same_ch(void);
int test_tls13_hrr_different_cs(void);
int test_tls13_ch2_different_cs(void);
int test_tls13_sg_missing(void);
int test_tls13_ks_missing(void);
int test_tls13_duplicate_extension(void);
int test_key_share_mismatch(void);
int test_tls13_middlebox_compat_empty_session_id(void);
int test_tls13_plaintext_alert(void);
int test_tls13_warning_alert_is_fatal(void);
int test_tls13_cert_req_sigalgs(void);
int test_tls13_derive_keys_no_key(void);
int test_tls13_pqc_hybrid_truncated_keyshare(void);
int test_tls13_short_session_ticket(void);

#define TEST_TLS13_DECLS                                        \
    TEST_DECL_GROUP("tls13", test_tls13_apis),                  \
    TEST_DECL_GROUP("tls13", test_tls13_cipher_suites),         \
    TEST_DECL_GROUP("tls13", test_tls13_bad_psk_binder),        \
    TEST_DECL_GROUP("tls13", test_tls13_rpk_handshake),         \
    TEST_DECL_GROUP("tls13", test_tls13_pq_groups),             \
    TEST_DECL_GROUP("tls13", test_tls13_early_data),            \
    TEST_DECL_GROUP("tls13", test_tls13_same_ch),               \
    TEST_DECL_GROUP("tls13", test_tls13_hrr_different_cs),      \
    TEST_DECL_GROUP("tls13", test_tls13_ch2_different_cs),      \
    TEST_DECL_GROUP("tls13", test_tls13_sg_missing),            \
    TEST_DECL_GROUP("tls13", test_tls13_ks_missing),            \
    TEST_DECL_GROUP("tls13", test_tls13_duplicate_extension),   \
    TEST_DECL_GROUP("tls13", test_key_share_mismatch),          \
    TEST_DECL_GROUP("tls13", test_tls13_middlebox_compat_empty_session_id), \
    TEST_DECL_GROUP("tls13", test_tls13_plaintext_alert),       \
    TEST_DECL_GROUP("tls13", test_tls13_warning_alert_is_fatal), \
    TEST_DECL_GROUP("tls13", test_tls13_cert_req_sigalgs),       \
    TEST_DECL_GROUP("tls13", test_tls13_derive_keys_no_key),    \
    TEST_DECL_GROUP("tls13", test_tls13_pqc_hybrid_truncated_keyshare), \
    TEST_DECL_GROUP("tls13", test_tls13_short_session_ticket)

#endif /* WOLFCRYPT_TEST_TLS13_H */
