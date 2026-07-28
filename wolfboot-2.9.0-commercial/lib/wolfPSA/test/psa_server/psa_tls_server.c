/* psa_tls_server.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef NO_FILESYSTEM
#define NO_FILESYSTEM
#endif
#ifndef USE_CERT_BUFFERS_256
#define USE_CERT_BUFFERS_256
#endif

#include <wolfssl/options.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wolfssl/ssl.h>
#include <wolfssl/error-ssl.h>

#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <wolfssl/wolfcrypt/asn_public.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/port/psa/psa.h>
#include <wolfpsa/psa/crypto.h>

#ifndef INVALID_DEVID
#define INVALID_DEVID -2
#endif

#define DEFAULT_PORT 11111
#define WOLFSSL_CERTS_DIR "../../wolfssl/certs"
#define SERVER_CERT_PATH WOLFSSL_CERTS_DIR "/server-ecc.der"
#define SERVER_KEY_PATH WOLFSSL_CERTS_DIR "/ecc-key.der"
#define CLIENT_CERT_PATH WOLFSSL_CERTS_DIR "/client-ecc-cert.der"

#define PSA_SERVER_KEY_ID   ((psa_key_id_t)0x1A01u)
#define PSA_SERVER_CERT_ID  ((psa_key_id_t)0x1A02u)
#define PSA_CLIENT_CERT_ID  ((psa_key_id_t)0x1A03u)

static uint8_t* g_client_cert_buf = NULL;
static size_t g_client_cert_len = 0;

static int load_file(const char* path, uint8_t** data, size_t* len)
{
    FILE* f;
    long size;
    uint8_t* buf;

    if (data == NULL || len == NULL)
        return -1;

    f = fopen(path, "rb");
    if (f == NULL)
        return -1;

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return -1;
    }

    size = ftell(f);
    if (size < 0) {
        fclose(f);
        return -1;
    }
    rewind(f);

    buf = (uint8_t*)malloc((size_t)size);
    if (buf == NULL) {
        fclose(f);
        return -1;
    }

    if (fread(buf, 1, (size_t)size, f) != (size_t)size) {
        free(buf);
        fclose(f);
        return -1;
    }

    fclose(f);
    *data = buf;
    *len = (size_t)size;
    return 0;
}

static void log_status(const char* what, psa_status_t st)
{
    const char* name = NULL;
    switch (st) {
        case PSA_SUCCESS: name = "PSA_SUCCESS"; break;
        case PSA_ERROR_PROGRAMMER_ERROR: name = "PSA_ERROR_PROGRAMMER_ERROR"; break;
        case PSA_ERROR_CONNECTION_REFUSED: name = "PSA_ERROR_CONNECTION_REFUSED"; break;
        case PSA_ERROR_CONNECTION_BUSY: name = "PSA_ERROR_CONNECTION_BUSY"; break;
        case PSA_ERROR_GENERIC_ERROR: name = "PSA_ERROR_GENERIC_ERROR"; break;
        case PSA_ERROR_NOT_PERMITTED: name = "PSA_ERROR_NOT_PERMITTED"; break;
        case PSA_ERROR_NOT_SUPPORTED: name = "PSA_ERROR_NOT_SUPPORTED"; break;
        case PSA_ERROR_INVALID_ARGUMENT: name = "PSA_ERROR_INVALID_ARGUMENT"; break;
        case PSA_ERROR_INVALID_HANDLE: name = "PSA_ERROR_INVALID_HANDLE"; break;
        case PSA_ERROR_BAD_STATE: name = "PSA_ERROR_BAD_STATE"; break;
        case PSA_ERROR_BUFFER_TOO_SMALL: name = "PSA_ERROR_BUFFER_TOO_SMALL"; break;
        case PSA_ERROR_ALREADY_EXISTS: name = "PSA_ERROR_ALREADY_EXISTS"; break;
        case PSA_ERROR_DOES_NOT_EXIST: name = "PSA_ERROR_DOES_NOT_EXIST"; break;
        case PSA_ERROR_INSUFFICIENT_MEMORY: name = "PSA_ERROR_INSUFFICIENT_MEMORY"; break;
        case PSA_ERROR_INSUFFICIENT_STORAGE: name = "PSA_ERROR_INSUFFICIENT_STORAGE"; break;
        case PSA_ERROR_INSUFFICIENT_DATA: name = "PSA_ERROR_INSUFFICIENT_DATA"; break;
        case PSA_ERROR_SERVICE_FAILURE: name = "PSA_ERROR_SERVICE_FAILURE"; break;
        case PSA_ERROR_COMMUNICATION_FAILURE: name = "PSA_ERROR_COMMUNICATION_FAILURE"; break;
        case PSA_ERROR_STORAGE_FAILURE: name = "PSA_ERROR_STORAGE_FAILURE"; break;
        case PSA_ERROR_HARDWARE_FAILURE: name = "PSA_ERROR_HARDWARE_FAILURE"; break;
        case PSA_ERROR_INVALID_SIGNATURE: name = "PSA_ERROR_INVALID_SIGNATURE"; break;
        case PSA_ERROR_CORRUPTION_DETECTED: name = "PSA_ERROR_CORRUPTION_DETECTED"; break;
        case PSA_ERROR_DATA_CORRUPT: name = "PSA_ERROR_DATA_CORRUPT"; break;
        case PSA_ERROR_DATA_INVALID: name = "PSA_ERROR_DATA_INVALID"; break;
        case PSA_OPERATION_INCOMPLETE: name = "PSA_OPERATION_INCOMPLETE"; break;
        default: name = "PSA_ERROR_UNKNOWN"; break;
    }

    if (st != PSA_SUCCESS)
        fprintf(stderr, "PSA: %s failed (status=%d %s)\n", what, (int)st, name);
    else
        fprintf(stderr, "PSA: %s ok\n", what);
    fflush(stderr);
}

static psa_ecc_family_t psa_ecc_family_from_curve_id(int curve_id)
{
    switch (curve_id) {
        case ECC_SECP256R1:
        case ECC_SECP192R1:
        case ECC_SECP224R1:
        case ECC_SECP384R1:
        case ECC_SECP521R1:
            return PSA_ECC_FAMILY_SECP_R1;
        case ECC_SECP256K1:
            return PSA_ECC_FAMILY_SECP_K1;
        default:
            return (psa_ecc_family_t)0;
    }
}

/* Store a certificate blob in the PSA persistent key store.
 * We treat the certificate as PSA_KEY_TYPE_RAW_DATA and assign a fixed key ID
 * so the application can reference it later without relying on files.
 */
static psa_status_t ensure_psa_raw_data(psa_key_id_t id,
                                        const uint8_t* data, size_t data_len)
{
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_status_t st;

    /* If the object already exists, reuse it. */
    fprintf(stderr, "PSA: check cert object id=0x%08X len=%zu\n",
            (unsigned)id, data_len);
    fflush(stderr);
    st = psa_get_key_attributes(id, &attrs);
    if (st == PSA_SUCCESS) {
        psa_reset_key_attributes(&attrs);
        fprintf(stderr, "PSA: cert already provisioned\n");
        fflush(stderr);
        return PSA_SUCCESS;
    }

    psa_reset_key_attributes(&attrs);
    if (st == PSA_ERROR_INVALID_HANDLE) {
        fprintf(stderr, "PSA: store not available or empty (treat as not found)\n");
        fflush(stderr);
        st = PSA_ERROR_DOES_NOT_EXIST;
    }
    if (st != PSA_ERROR_DOES_NOT_EXIST) {
        log_status("psa_get_key_attributes(cert)", st);
        return st;
    }

    /* Create a persistent RAW_DATA object to hold the DER cert bytes. */
    attrs = psa_key_attributes_init();
    psa_set_key_type(&attrs, PSA_KEY_TYPE_RAW_DATA);
    psa_set_key_bits(&attrs, data_len * 8u);
    psa_set_key_usage_flags(&attrs, PSA_KEY_USAGE_EXPORT);
    psa_set_key_lifetime(&attrs, PSA_KEY_LIFETIME_PERSISTENT);
    psa_set_key_id(&attrs, id);

    st = psa_import_key(&attrs, data, data_len, &id);
    psa_reset_key_attributes(&attrs);
    log_status("import cert (RAW_DATA)", st);
    return st;
}

static int verify_client_cert(int preverify, WOLFSSL_X509_STORE_CTX* store)
{
    int depth = wolfSSL_X509_STORE_CTX_get_error_depth(store);
    int err = wolfSSL_X509_STORE_CTX_get_error(store);

    if (depth == 0 && store != NULL && store->certs != NULL &&
        store->totalCerts > 0) {
        const unsigned char* der = store->certs[0].buffer;
        word32 der_sz = store->certs[0].length;

        if (der != NULL && der_sz > 0 &&
            (size_t)der_sz == g_client_cert_len &&
            XMEMCMP(der, g_client_cert_buf, g_client_cert_len) == 0) {
            fprintf(stderr, "Server: client cert matches PSA store\n");
            fflush(stderr);
            return 1;
        }

        fprintf(stderr, "Server: client cert mismatch (preverify=%d err=%d)\n",
                preverify, err);
        fflush(stderr);
        return 0;
    }

    return preverify;
}

/* Store an ECC private key in the PSA persistent key store.
 * We import from DER, extract the private scalar, and store it as a PSA
 * ECC key pair with a fixed key ID for later use by the TLS callbacks.
 */
static psa_status_t ensure_psa_ecc_key(psa_key_id_t id, const uint8_t* der,
                                       size_t der_len)
{
    word32 idx = 0;
    ecc_key key;
    psa_key_attributes_t attrs = psa_key_attributes_init();
    psa_ecc_family_t family;
    uint8_t priv_raw[MAX_ECC_BYTES];
    word32 priv_len = sizeof(priv_raw);
    psa_status_t st;
    int ret;

    /* If the key already exists, reuse it. */
    fprintf(stderr, "PSA: check key object id=0x%08X\n", (unsigned)id);
    fflush(stderr);
    st = psa_get_key_attributes(id, &attrs);
    if (st == PSA_SUCCESS) {
        psa_reset_key_attributes(&attrs);
        fprintf(stderr, "PSA: key already provisioned\n");
        fflush(stderr);
        return PSA_SUCCESS;
    }
    psa_reset_key_attributes(&attrs);
    if (st == PSA_ERROR_INVALID_HANDLE) {
        fprintf(stderr, "PSA: store not available or empty (treat as not found)\n");
        fflush(stderr);
        st = PSA_ERROR_DOES_NOT_EXIST;
    }
    if (st != PSA_ERROR_DOES_NOT_EXIST) {
        log_status("psa_get_key_attributes(key)", st);
        return st;
    }

    /* Decode the DER key into a wolfCrypt ecc_key so we can discover curve
     * parameters and export the raw private scalar expected by PSA import.
     */
    ret = wc_ecc_init(&key);
    if (ret != 0) {
        printf("FAIL: wc_ecc_init (%d)\n", ret);
        fflush(stderr);
        return PSA_ERROR_GENERIC_ERROR;
    }

    ret = wc_EccPrivateKeyDecode(der, &idx, &key, (word32)der_len);
    if (ret != 0) {
        wc_ecc_free(&key);
        printf("FAIL: wc_EccPrivateKeyDecode (%d)\n", ret);
        fflush(stderr);
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* Export just the private scalar (d) in big-endian form. */
    ret = wc_ecc_export_private_only(&key, priv_raw, &priv_len);
    if (ret != 0) {
        wc_ecc_free(&key);
        printf("FAIL: wc_ecc_export_private_only (%d)\n", ret);
        fflush(stderr);
        return PSA_ERROR_GENERIC_ERROR;
    }

    family = psa_ecc_family_from_curve_id(key.dp->id);
    if (family == 0) {
        wc_ecc_free(&key);
        printf("FAIL: unsupported ECC curve %d\n", key.dp->id);
        fflush(stderr);
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Create a persistent ECC key pair object. */
    psa_set_key_type(&attrs, PSA_KEY_TYPE_ECC_KEY_PAIR(family));
    psa_set_key_bits(&attrs, (size_t)key.dp->size * 8u);
    psa_set_key_usage_flags(&attrs, PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH | PSA_KEY_USAGE_DERIVE);
    psa_set_key_algorithm(&attrs, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
    psa_set_key_lifetime(&attrs, PSA_KEY_LIFETIME_PERSISTENT);
    psa_set_key_id(&attrs, id);

    st = psa_import_key(&attrs, priv_raw, priv_len, &id);
    wc_ecc_free(&key);
    if (st != PSA_SUCCESS) {
        printf("FAIL: psa_import_key (status=%d)\n", (int)st);
        fflush(stderr);
        return st;
    }

    fprintf(stderr, "PSA: imported ECC key (id=0x%08X bits=%u)\n",
            (unsigned)id, (unsigned)(priv_len * 8u));
    fflush(stderr);
    return PSA_SUCCESS;
}

int main(int argc, char** argv)
{
    WOLFSSL_CTX* ctx = NULL;
    WOLFSSL* ssl = NULL;
    int sockfd = -1;
    int clientfd = -1;
    word16 port = DEFAULT_PORT;
    struct psa_ssl_ctx psa_ctx;
    psa_key_id_t key_id = PSA_SERVER_KEY_ID;
    psa_key_id_t cert_id = PSA_SERVER_CERT_ID;
    psa_key_id_t client_cert_id = PSA_CLIENT_CERT_ID;
    uint8_t* cert_buf = NULL;
    size_t cert_len = 0;
    uint8_t* server_cert_der = NULL;
    size_t server_cert_der_len = 0;
    uint8_t* server_key_der = NULL;
    size_t server_key_der_len = 0;
    uint8_t* client_cert_der = NULL;
    size_t client_cert_der_len = 0;
    int ret;

    if (argc > 2 && strcmp(argv[1], "-p") == 0)
        port = (word16)atoi(argv[2]);

    /* Initialize PSA Crypto subsystem. Required before any PSA calls. */
    fprintf(stderr, "PSA: init\n");
    fflush(stderr);
    if (psa_crypto_init() != PSA_SUCCESS) {
        printf("FAIL: psa_crypto_init\n");
        fflush(stderr);
        return 1;
    }

    XMEMSET(&psa_ctx, 0, sizeof(psa_ctx));

    if (load_file(SERVER_CERT_PATH, &server_cert_der, &server_cert_der_len) != 0 ||
        load_file(SERVER_KEY_PATH, &server_key_der, &server_key_der_len) != 0 ||
        load_file(CLIENT_CERT_PATH, &client_cert_der, &client_cert_der_len) != 0) {
        fprintf(stderr, "FAIL: could not load cert/key files from %s\n",
                WOLFSSL_CERTS_DIR);
        return 1;
    }

    /* Provision certificate into PSA store (persistent RAW_DATA object). */
    if (ensure_psa_raw_data(cert_id, server_cert_der,
                            server_cert_der_len) != PSA_SUCCESS)
        return 1;
    /* Provision private key into PSA store (persistent ECC key pair). */
    if (ensure_psa_ecc_key(key_id, server_key_der,
                           server_key_der_len) != PSA_SUCCESS)
        return 1;
    /* Provision client certificate into PSA store for mutual auth pinning. */
    if (ensure_psa_raw_data(client_cert_id, client_cert_der,
                            client_cert_der_len) != PSA_SUCCESS)
        return 1;

    /* Read the certificate back from PSA store into memory for wolfSSL.
     * wolfSSL_CTX_use_certificate_buffer() still requires a DER buffer.
     */
    {
        psa_status_t st;
        cert_buf = (uint8_t*)malloc(server_cert_der_len);
        if (cert_buf == NULL)
            return 1;
        st = psa_export_key(cert_id, cert_buf, server_cert_der_len, &cert_len);
        log_status("export cert", st);
        if (st != PSA_SUCCESS)
            return 1;
        fprintf(stderr, "PSA: exported cert len=%zu\n", cert_len);
        fflush(stderr);
    }
    {
        psa_status_t st;
        g_client_cert_buf = (uint8_t*)malloc(client_cert_der_len);
        if (g_client_cert_buf == NULL)
            return 1;
        st = psa_export_key(client_cert_id, g_client_cert_buf,
                                         client_cert_der_len,
                                         &g_client_cert_len);
        log_status("export client cert", st);
        if (st != PSA_SUCCESS)
            return 1;
        fprintf(stderr, "PSA: exported client cert len=%zu\n", g_client_cert_len);
        fflush(stderr);
    }

    fprintf(stderr, "Server: wolfSSL_Init\n");
    fflush(stderr);
    ret = wolfSSL_Init();
    if (ret != WOLFSSL_SUCCESS) {
        printf("FAIL: wolfSSL_Init (%d)\n", ret);
        fflush(stderr);
        return 1;
    }
    fprintf(stderr, "Server: wolfSSL_Init ok\n");
    fflush(stderr);

    ctx = wolfSSL_CTX_new(wolfTLSv1_2_server_method());
    if (ctx == NULL) {
        printf("FAIL: wolfSSL_CTX_new\n");
        return 1;
    }
    fprintf(stderr, "Server: ctx created\n");
    fflush(stderr);

    ret = wolfSSL_CTX_use_certificate_buffer(ctx, cert_buf, (int)cert_len,
                                             WOLFSSL_FILETYPE_ASN1);
    if (ret != WOLFSSL_SUCCESS) {
        printf("FAIL: wolfSSL_CTX_use_certificate_buffer (%d)\n", ret);
        fflush(stderr);
        return 1;
    }
    fprintf(stderr, "Server: certificate loaded from PSA store\n");
    fflush(stderr);

    ret = wolfSSL_CTX_set_cipher_list(ctx, "TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256");
    if (ret != WOLFSSL_SUCCESS) {
        printf("FAIL: wolfSSL_CTX_set_cipher_list (%d)\n", ret);
        fflush(stderr);
        return 1;
    }
    fprintf(stderr, "Server: cipher list set\n");
    fflush(stderr);

    /* Require client certificate and verify against PSA-stored client cert. */
    wolfSSL_CTX_set_verify(ctx,
            WOLFSSL_VERIFY_PEER | WOLFSSL_VERIFY_FAIL_IF_NO_PEER_CERT,
            verify_client_cert);
    fprintf(stderr, "Server: mutual auth enabled (PSA client cert pinning)\n");
    fflush(stderr);

    /* Register PSA-based PK callbacks (ECDSA/ECDH) on this context.
     * These callbacks will fetch and use the PSA-stored private key by key ID.
     */
    ret = wolfSSL_CTX_psa_enable(ctx);
    if (ret != WOLFSSL_SUCCESS) {
        printf("FAIL: wolfSSL_CTX_psa_enable (%d)\n", ret);
        fflush(stderr);
        return 1;
    }
    fprintf(stderr, "Server: PSA callbacks enabled\n");
    fflush(stderr);

    /* Bind the PSA key id to this TLS session so callbacks know which key
     * to use during ECDSA sign/verify and ECDH key agreement.
     */
    ret = wolfSSL_psa_set_private_key_id(&psa_ctx, key_id);
    if (ret != WOLFSSL_SUCCESS) {
        printf("FAIL: wolfSSL_psa_set_private_key_id (%d)\n", ret);
        fflush(stderr);
        return 1;
    }
    fprintf(stderr, "Server: PSA key id bound to session\n");
    fflush(stderr);

    fprintf(stderr, "Server: listening on port %u\n", (unsigned)port);
    fflush(stderr);
    {
        struct sockaddr_in addr;
        int opt = 1;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            fprintf(stderr, "FAIL: socket (%d)\n", errno);
            return 1;
        }

        (void)setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        XMEMSET(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            fprintf(stderr, "FAIL: bind (%d)\n", errno);
            close(sockfd);
            return 1;
        }
        if (listen(sockfd, 1) < 0) {
            fprintf(stderr, "FAIL: listen (%d)\n", errno);
            close(sockfd);
            return 1;
        }

        clientfd = accept(sockfd, NULL, NULL);
        if (clientfd < 0) {
            fprintf(stderr, "FAIL: accept (%d)\n", errno);
            close(sockfd);
            return 1;
        }
    }
    fprintf(stderr, "Server: client accepted\n");
    fflush(stderr);

    ssl = wolfSSL_new(ctx);
    if (ssl == NULL) {
        printf("FAIL: wolfSSL_new\n");
        return 1;
    }
    fprintf(stderr, "Server: ssl created\n");
    fflush(stderr);

    ret = wolfSSL_set_psa_ctx(ssl, &psa_ctx);
    if (ret != WOLFSSL_SUCCESS) {
        printf("FAIL: wolfSSL_set_psa_ctx (%d)\n", ret);
        return 1;
    }
    fprintf(stderr, "Server: psa ctx attached\n");
    fflush(stderr);

    wolfSSL_set_fd(ssl, clientfd);
    fprintf(stderr, "Server: socket fd attached\n");
    fflush(stderr);

    fprintf(stderr, "Server: starting handshake\n");
    fflush(stderr);
    ret = wolfSSL_accept(ssl);
    if (ret != WOLFSSL_SUCCESS) {
        int err = wolfSSL_get_error(ssl, ret);
        printf("FAIL: wolfSSL_accept (err=%d)\n", err);
        fflush(stderr);
        wolfSSL_free(ssl);
        wolfSSL_CTX_free(ctx);
        return 1;
    }

    fprintf(stderr, "Handshake complete (PSA ECC callbacks active)\n");
    fflush(stderr);

    /* Read one application record and respond so the example client can
     * complete its write/read cycle without treating close_notify as failure.
     */
    {
        char app_buf[512];
        int rd = wolfSSL_read(ssl, app_buf, (int)(sizeof(app_buf) - 1));
        if (rd > 0) {
            const char kHttpResp[] =
                "HTTP/1.0 200 OK\r\n"
                "Content-Length: 2\r\n"
                "Connection: close\r\n"
                "\r\n"
                "OK";
            app_buf[rd] = '\0';
            fprintf(stderr, "Server: received %d bytes of app data\n", rd);
            fflush(stderr);
            (void)wolfSSL_write(ssl, kHttpResp, (int)XSTRLEN(kHttpResp));
        }
        else {
            int err = wolfSSL_get_error(ssl, rd);
            fprintf(stderr, "Server: wolfSSL_read returned %d (err=%d)\n", rd, err);
            fflush(stderr);
        }
    }

    wolfSSL_shutdown(ssl);
    wolfSSL_free(ssl);
    wolfSSL_CTX_free(ctx);
    wolfSSL_Cleanup();

    wolfSSL_free_psa_ctx(&psa_ctx);
    psa_destroy_key(key_id);
    psa_destroy_key(cert_id);
    psa_destroy_key(client_cert_id);

    if (clientfd >= 0)
        close(clientfd);
    if (sockfd >= 0)
        close(sockfd);
    free(cert_buf);
    free(server_cert_der);
    free(server_key_der);
    free(client_cert_der);
    free(g_client_cert_buf);

    return 0;
}
