/* test_ssl_cert.h
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef TESTS_API_SSL_CERT_H
#define TESTS_API_SSL_CERT_H

int test_wolfSSL_get_verify_mode(void);
int test_wolfSSL_CTX_get_verify_mode(void);
int test_wolfSSL_get_verify_callback(void);
int test_wolfSSL_CTX_get_extra_chain_certs(void);
int test_wolfSSL_get_peer_chain(void);
int test_wolfSSL_get_chain_X509(void);
int test_wolfSSL_get_chain_cert_pem(void);
int test_wolfSSL_cmp_peer_cert_to_file(void);

#define TEST_SSL_CERT_DECLS                                                    \
        TEST_DECL_GROUP("ssl_cert", test_wolfSSL_get_verify_mode),             \
        TEST_DECL_GROUP("ssl_cert", test_wolfSSL_CTX_get_verify_mode),         \
        TEST_DECL_GROUP("ssl_cert", test_wolfSSL_get_verify_callback),         \
        TEST_DECL_GROUP("ssl_cert", test_wolfSSL_CTX_get_extra_chain_certs),   \
        TEST_DECL_GROUP("ssl_cert", test_wolfSSL_get_peer_chain),              \
        TEST_DECL_GROUP("ssl_cert", test_wolfSSL_get_chain_X509),             \
        TEST_DECL_GROUP("ssl_cert", test_wolfSSL_get_chain_cert_pem),         \
        TEST_DECL_GROUP("ssl_cert", test_wolfSSL_cmp_peer_cert_to_file)

#endif /* TESTS_API_SSL_CERT_H */
