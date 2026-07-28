/* psa_rsa_pss_interop_test.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <wolfssl/options.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wolfpsa/psa/crypto.h>

#include <wolfssl/wolfcrypt/rsa.h>
#include <wolfssl/wolfcrypt/random.h>

#ifndef INVALID_DEVID
#define INVALID_DEVID -2
#endif

#define WOLFSSL_CERTS_DIR "../wolfssl/certs"
#define RSA_PRIVATE_KEY_PATH WOLFSSL_CERTS_DIR "/server-key.der"

static int load_file(const char* path, uint8_t** data, size_t* len)
{
    FILE* f;
    long size;
    uint8_t* buf;

    if (data == NULL || len == NULL) {
        return -1;
    }

    f = fopen(path, "rb");
    if (f == NULL) {
        return -1;
    }
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

static int check_status(const char* what, psa_status_t st)
{
    if (st != PSA_SUCCESS) {
        printf("FAIL: %s (status=%d)\n", what, (int)st);
        return 1;
    }
    return 0;
}

static int check_pss_padding(const uint8_t* hash, size_t hash_len,
                             const uint8_t* encoded, size_t encoded_len,
                             RsaKey* rsa_key)
{
#if (defined(HAVE_SELFTEST) && \
     (!defined(HAVE_SELFTEST_VERSION) || (HAVE_SELFTEST_VERSION < 2))) || \
    (defined(HAVE_FIPS) && defined(HAVE_FIPS_VERSION) && \
     (HAVE_FIPS_VERSION < 2))
    return wc_RsaPSS_CheckPadding_ex(hash, (word32)hash_len, encoded,
                                     (word32)encoded_len,
                                     WC_HASH_TYPE_SHA256,
                                     RSA_PSS_SALT_LEN_DEFAULT);
#elif (defined(HAVE_SELFTEST) && (HAVE_SELFTEST_VERSION == 2)) || \
      (defined(HAVE_FIPS) && defined(HAVE_FIPS_VERSION) && \
       (HAVE_FIPS_VERSION == 2))
    return wc_RsaPSS_CheckPadding_ex(hash, (word32)hash_len, encoded,
                                     (word32)encoded_len,
                                     WC_HASH_TYPE_SHA256,
                                     RSA_PSS_SALT_LEN_DEFAULT, 0);
#else
    return wc_RsaPSS_CheckPadding_ex2(hash, (word32)hash_len, encoded,
                                      (word32)encoded_len,
                                      WC_HASH_TYPE_SHA256,
                                      RSA_PSS_SALT_LEN_DEFAULT,
                                      wc_RsaEncryptSize(rsa_key) * 8, NULL);
#endif
}

int main(void)
{
#ifndef WC_RSA_PSS
    puts("SKIP: WC_RSA_PSS not enabled");
    return 0;
#else
    static const uint8_t hash[32] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
        0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
        0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f
    };
    psa_key_attributes_t priv_attrs = psa_key_attributes_init();
    psa_key_id_t priv_key = 0;
    uint8_t* priv_der = NULL;
    size_t priv_der_len = 0;
    uint8_t psa_sig[256];
    size_t psa_sig_len = 0;
    byte wc_sig[256];
    int wc_sig_len;
    byte decoded[256];
    RsaKey rsa_key;
    WC_RNG rng;
    word32 idx = 0;
    int ret;
    psa_status_t st;

    st = psa_crypto_init();
    if (check_status("psa_crypto_init", st) != 0) return 1;

    if (load_file(RSA_PRIVATE_KEY_PATH, &priv_der, &priv_der_len) != 0) {
        printf("FAIL: load %s\n", RSA_PRIVATE_KEY_PATH);
        return 1;
    }
    psa_set_key_type(&priv_attrs, PSA_KEY_TYPE_RSA_KEY_PAIR);
    psa_set_key_bits(&priv_attrs, 2048);
    psa_set_key_usage_flags(&priv_attrs,
                            PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH);
    psa_set_key_algorithm(&priv_attrs, PSA_ALG_RSA_PSS(PSA_ALG_SHA_256));
    st = psa_import_key(&priv_attrs, priv_der, priv_der_len, &priv_key);
    if (check_status("psa_import_key(private)", st) != 0) goto fail;

    ret = wc_InitRsaKey(&rsa_key, NULL);
    if (ret != 0) {
        printf("FAIL: wc_InitRsaKey (%d)\n", ret);
        goto fail;
    }
    ret = wc_InitRng(&rng);
    if (ret != 0) {
        printf("FAIL: wc_InitRng (%d)\n", ret);
        wc_FreeRsaKey(&rsa_key);
        goto fail;
    }
    ret = wc_RsaPrivateKeyDecode(priv_der, &idx, &rsa_key, (word32)priv_der_len);
    if (ret != 0) {
        printf("FAIL: wc_RsaPrivateKeyDecode (%d)\n", ret);
        wc_FreeRng(&rng);
        wc_FreeRsaKey(&rsa_key);
        goto fail;
    }

    wc_sig_len = wc_RsaPSS_Sign(hash, (word32)sizeof(hash), wc_sig, (word32)sizeof(wc_sig),
                                WC_HASH_TYPE_SHA256, WC_MGF1SHA256, &rsa_key, &rng);
    if (wc_sig_len <= 0) {
        printf("FAIL: wc_RsaPSS_Sign (%d)\n", wc_sig_len);
        wc_FreeRng(&rng);
        wc_FreeRsaKey(&rsa_key);
        goto fail;
    }

    st = psa_verify_hash(priv_key, PSA_ALG_RSA_PSS(PSA_ALG_SHA_256),
                         hash, sizeof(hash), wc_sig, (size_t)wc_sig_len);
    if (check_status("psa_verify_hash(private)", st) != 0) {
        wc_FreeRng(&rng);
        wc_FreeRsaKey(&rsa_key);
        goto fail;
    }

    st = psa_sign_hash(priv_key, PSA_ALG_RSA_PSS(PSA_ALG_SHA_256),
                       hash, sizeof(hash), psa_sig, sizeof(psa_sig), &psa_sig_len);
    if (check_status("psa_sign_hash(private)", st) != 0) {
        wc_FreeRng(&rng);
        wc_FreeRsaKey(&rsa_key);
        goto fail;
    }

    ret = wc_RsaPSS_Verify_ex(psa_sig, (word32)psa_sig_len, decoded,
                              (word32)sizeof(decoded), WC_HASH_TYPE_SHA256,
                              WC_MGF1SHA256, RSA_PSS_SALT_LEN_DEFAULT,
                              &rsa_key);
    if (ret <= 0 ||
        check_pss_padding(hash, sizeof(hash), decoded, (size_t)ret,
                          &rsa_key) != 0) {
        printf("FAIL: wc_RsaPSS_Verify_ex mismatch (%d)\n", ret);
        wc_FreeRng(&rng);
        wc_FreeRsaKey(&rsa_key);
        goto fail;
    }

    wc_FreeRng(&rng);
    wc_FreeRsaKey(&rsa_key);
    (void)psa_destroy_key(priv_key);
    free(priv_der);
    puts("RSA-PSS interop: OK");
    return 0;

fail:
    if (priv_key != 0) {
        (void)psa_destroy_key(priv_key);
    }
    free(priv_der);
    return 1;
#endif
}
