/* test_session.h
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef WOLFCRYPT_TEST_SESSION_H
#define WOLFCRYPT_TEST_SESSION_H

#include <tests/api/api_decl.h>

int test_wolfSSL_CTX_add_session(void);
int test_wolfSSL_CTX_add_session_ext_tls13(void);
int test_wolfSSL_CTX_add_session_ext_dtls13(void);
int test_wolfSSL_CTX_add_session_ext_tls12(void);
int test_wolfSSL_CTX_add_session_ext_dtls12(void);
int test_wolfSSL_CTX_add_session_ext_tls11(void);
int test_wolfSSL_CTX_add_session_ext_dtls1(void);
int test_wolfSSL_SESSION(void);
int test_wolfSSL_SESSION_expire_downgrade(void);
int test_wolfSSL_CTX_sess_set_remove_cb(void);
int test_wolfSSL_ticket_keys(void);
int test_wolfSSL_SESSION_get_ex_new_index(void);

#define TEST_SESSION_DECLS                                                     \
    TEST_DECL_GROUP("session", test_wolfSSL_CTX_add_session),                  \
    TEST_DECL_GROUP("session", test_wolfSSL_CTX_add_session_ext_tls13),        \
    TEST_DECL_GROUP("session", test_wolfSSL_CTX_add_session_ext_dtls13),       \
    TEST_DECL_GROUP("session", test_wolfSSL_CTX_add_session_ext_tls12),        \
    TEST_DECL_GROUP("session", test_wolfSSL_CTX_add_session_ext_dtls12),       \
    TEST_DECL_GROUP("session", test_wolfSSL_CTX_add_session_ext_tls11),        \
    TEST_DECL_GROUP("session", test_wolfSSL_CTX_add_session_ext_dtls1),        \
    TEST_DECL_GROUP("session", test_wolfSSL_SESSION),                          \
    TEST_DECL_GROUP("session", test_wolfSSL_SESSION_expire_downgrade),         \
    TEST_DECL_GROUP("session", test_wolfSSL_CTX_sess_set_remove_cb),           \
    TEST_DECL_GROUP("session", test_wolfSSL_ticket_keys),                      \
    TEST_DECL_GROUP("session", test_wolfSSL_SESSION_get_ex_new_index)

#endif /* WOLFCRYPT_TEST_SESSION_H */
