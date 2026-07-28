/* psa_key_wrap_test.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*
 * Coverage test for psa_wrap_key() / psa_unwrap_key() (PSA Crypto API 1.4).
 *
 * Test cases
 * ----------
 * 1. RFC 3394 §4.1 KAT: wrap a 16-byte AES-128 key with a 128-bit KEK and
 *    verify the exact 24-byte ciphertext from the RFC.
 * 2. Unwrap the RFC ciphertext with the same KEK; export and compare to the
 *    original 16-byte plaintext.
 * 3. Roundtrip with an AES-256 target generated via psa_generate_key: wrap,
 *    unwrap, export, and confirm the 32 bytes are identical.
 * 4. KEK without PSA_KEY_USAGE_WRAP  → PSA_ERROR_NOT_PERMITTED from
 *    psa_wrap_key; KEK without PSA_KEY_USAGE_UNWRAP → NOT_PERMITTED from
 *    psa_unwrap_key.
 * 5. Target key without PSA_KEY_USAGE_EXPORT → PSA_ERROR_NOT_PERMITTED from
 *    psa_wrap_key (psa_export_key rejects it internally).
 * 6. PSA_ALG_KWP → PSA_ERROR_NOT_SUPPORTED.
 * 7. Corrupted wrapped data (one byte flipped) → PSA_ERROR_INVALID_SIGNATURE.
 * 8. Output buffer one byte too small → PSA_ERROR_BUFFER_TOO_SMALL.
 */

#include "psa_api_test_user_settings.h"

#ifndef WOLFSSL_USER_SETTINGS
#define WOLFSSL_USER_SETTINGS
#endif

#include <wolfssl/wolfcrypt/settings.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <wolfpsa/psa/crypto.h>

/* -------------------------------------------------------------------------
 * Helpers
 * ---------------------------------------------------------------------- */

static int expect_status(const char *label, psa_status_t status,
                         psa_status_t expected)
{
    if (status != expected) {
        printf("FAIL %s: status=%d expected=%d\n", label,
               (int)status, (int)expected);
        return 1;
    }
    return 0;
}

/* Destroy a key only if it is not PSA_KEY_ID_NULL. */
static void destroy_if_valid(psa_key_id_t key)
{
    if (key != PSA_KEY_ID_NULL) {
        (void)psa_destroy_key(key);
    }
}

/* Import an AES key with the given raw bytes.  Returns PSA_KEY_ID_NULL on
 * failure (and prints a diagnostic). */
static psa_key_id_t import_aes_key(const char *label,
                                   const uint8_t *raw, size_t raw_len,
                                   psa_key_usage_t usage,
                                   psa_algorithm_t alg)
{
    psa_key_attributes_t attr = psa_key_attributes_init();
    psa_key_id_t kid = PSA_KEY_ID_NULL;
    psa_status_t st;

    psa_set_key_type(&attr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&attr, raw_len * 8u);
    psa_set_key_usage_flags(&attr, usage);
    psa_set_key_algorithm(&attr, alg);

    st = psa_import_key(&attr, raw, raw_len, &kid);
    if (st != PSA_SUCCESS) {
        printf("FAIL %s: psa_import_key status=%d\n", label, (int)st);
        return PSA_KEY_ID_NULL;
    }
    return kid;
}

/* -------------------------------------------------------------------------
 * RFC 3394 §4.1 known-answer data
 * KEK  : 000102030405060708090A0B0C0D0E0F  (AES-128)
 * PT   : 00112233445566778899AABBCCDDEEFF  (16 bytes)
 * CT   : 1FA68B0A8112B447AEF34BD8FB5A7B829D3E862371D2CFE5  (24 bytes)
 * ---------------------------------------------------------------------- */

static const uint8_t kKekRfc3394[16] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

static const uint8_t kPlainRfc3394[16] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
};

static const uint8_t kCipherRfc3394[24] = {
    0x1F, 0xA6, 0x8B, 0x0A, 0x81, 0x12, 0xB4, 0x47,
    0xAE, 0xF3, 0x4B, 0xD8, 0xFB, 0x5A, 0x7B, 0x82,
    0x9D, 0x3E, 0x86, 0x23, 0x71, 0xD2, 0xCF, 0xE5
};

/* -------------------------------------------------------------------------
 * Test 1: RFC 3394 §4.1 known-answer (wrap direction)
 * ---------------------------------------------------------------------- */
static int test_kat_wrap(void)
{
    psa_key_id_t kek = PSA_KEY_ID_NULL;
    psa_key_id_t target = PSA_KEY_ID_NULL;
    psa_key_attributes_t tattr = psa_key_attributes_init();
    uint8_t wrapped[32];
    size_t wrapped_len = 0;
    psa_status_t st;
    int ret = 0;

    /* KEK: AES-128 with WRAP|UNWRAP, algorithm PSA_ALG_KW */
    kek = import_aes_key("kat_wrap/kek", kKekRfc3394, sizeof(kKekRfc3394),
                         PSA_KEY_USAGE_WRAP | PSA_KEY_USAGE_UNWRAP,
                         PSA_ALG_KW);
    if (kek == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    /* Target: AES-128 with EXPORT */
    psa_set_key_type(&tattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&tattr, 128);
    psa_set_key_usage_flags(&tattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&tattr, PSA_ALG_KW);

    st = psa_import_key(&tattr, kPlainRfc3394, sizeof(kPlainRfc3394), &target);
    if (expect_status("kat_wrap/import_target", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    st = psa_wrap_key(kek, PSA_ALG_KW, target,
                      wrapped, sizeof(wrapped), &wrapped_len);
    if (expect_status("kat_wrap/psa_wrap_key", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    if (wrapped_len != sizeof(kCipherRfc3394)) {
        printf("FAIL kat_wrap/length: got %zu expected %zu\n",
               wrapped_len, sizeof(kCipherRfc3394));
        ret = 1; goto done;
    }

    if (memcmp(wrapped, kCipherRfc3394, sizeof(kCipherRfc3394)) != 0) {
        printf("FAIL kat_wrap/ciphertext: KAT mismatch\n");
        ret = 1; goto done;
    }

done:
    destroy_if_valid(target);
    destroy_if_valid(kek);
    return ret;
}

/* -------------------------------------------------------------------------
 * Test 2: Unwrap the RFC ciphertext, export, compare to plaintext
 * ---------------------------------------------------------------------- */
static int test_kat_unwrap(void)
{
    psa_key_id_t kek = PSA_KEY_ID_NULL;
    psa_key_id_t recovered = PSA_KEY_ID_NULL;
    psa_key_attributes_t rattr = psa_key_attributes_init();
    uint8_t exported[16];
    size_t exported_len = 0;
    psa_status_t st;
    int ret = 0;

    kek = import_aes_key("kat_unwrap/kek", kKekRfc3394, sizeof(kKekRfc3394),
                         PSA_KEY_USAGE_WRAP | PSA_KEY_USAGE_UNWRAP,
                         PSA_ALG_KW);
    if (kek == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    /* Attributes for the unwrapped key: AES-128, exportable */
    psa_set_key_type(&rattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&rattr, 128);
    psa_set_key_usage_flags(&rattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&rattr, PSA_ALG_KW);

    st = psa_unwrap_key(&rattr, kek, PSA_ALG_KW,
                        kCipherRfc3394, sizeof(kCipherRfc3394), &recovered);
    if (expect_status("kat_unwrap/psa_unwrap_key", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    st = psa_export_key(recovered, exported, sizeof(exported), &exported_len);
    if (expect_status("kat_unwrap/psa_export_key", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    if (exported_len != sizeof(kPlainRfc3394) ||
        memcmp(exported, kPlainRfc3394, sizeof(kPlainRfc3394)) != 0) {
        printf("FAIL kat_unwrap/plaintext: exported bytes do not match RFC PT\n");
        ret = 1; goto done;
    }

done:
    destroy_if_valid(recovered);
    destroy_if_valid(kek);
    return ret;
}

/* -------------------------------------------------------------------------
 * Test 3: Roundtrip with a generated AES-256 target key
 * ---------------------------------------------------------------------- */
static int test_roundtrip_aes256(void)
{
    psa_key_id_t kek = PSA_KEY_ID_NULL;
    psa_key_id_t target = PSA_KEY_ID_NULL;
    psa_key_id_t recovered = PSA_KEY_ID_NULL;
    psa_key_attributes_t gattr = psa_key_attributes_init();
    psa_key_attributes_t rattr = psa_key_attributes_init();
    /* AES-256: 32 bytes plain → 40 bytes wrapped */
    uint8_t wrapped[48];
    size_t wrapped_len = 0;
    uint8_t orig[32];
    size_t orig_len = 0;
    uint8_t recovered_bytes[32];
    size_t recovered_len = 0;
    psa_status_t st;
    int ret = 0;

    kek = import_aes_key("roundtrip256/kek", kKekRfc3394, sizeof(kKekRfc3394),
                         PSA_KEY_USAGE_WRAP | PSA_KEY_USAGE_UNWRAP,
                         PSA_ALG_KW);
    if (kek == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    /* Generate the AES-256 target */
    psa_set_key_type(&gattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&gattr, 256);
    psa_set_key_usage_flags(&gattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&gattr, PSA_ALG_KW);

    st = psa_generate_key(&gattr, &target);
    if (expect_status("roundtrip256/generate", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    /* Export original bytes so we can compare later */
    st = psa_export_key(target, orig, sizeof(orig), &orig_len);
    if (expect_status("roundtrip256/export_original", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }
    if (orig_len != 32u) {
        printf("FAIL roundtrip256/orig_len: got %zu expected 32\n", orig_len);
        ret = 1; goto done;
    }

    /* Wrap */
    st = psa_wrap_key(kek, PSA_ALG_KW, target,
                      wrapped, sizeof(wrapped), &wrapped_len);
    if (expect_status("roundtrip256/wrap", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }
    if (wrapped_len != 40u) {
        printf("FAIL roundtrip256/wrapped_len: got %zu expected 40\n",
               wrapped_len);
        ret = 1; goto done;
    }

    /* Unwrap */
    psa_set_key_type(&rattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&rattr, 256);
    psa_set_key_usage_flags(&rattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&rattr, PSA_ALG_KW);

    st = psa_unwrap_key(&rattr, kek, PSA_ALG_KW,
                        wrapped, wrapped_len, &recovered);
    if (expect_status("roundtrip256/unwrap", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    /* Export and compare */
    st = psa_export_key(recovered, recovered_bytes, sizeof(recovered_bytes),
                        &recovered_len);
    if (expect_status("roundtrip256/export_recovered", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    if (recovered_len != orig_len ||
        memcmp(recovered_bytes, orig, orig_len) != 0) {
        printf("FAIL roundtrip256/compare: recovered key does not match original\n");
        ret = 1; goto done;
    }

done:
    destroy_if_valid(recovered);
    destroy_if_valid(target);
    destroy_if_valid(kek);
    return ret;
}

/* -------------------------------------------------------------------------
 * Test 4: Missing WRAP / UNWRAP usage flags → PSA_ERROR_NOT_PERMITTED
 * ---------------------------------------------------------------------- */
static int test_missing_usage_flags(void)
{
    psa_key_id_t kek_no_wrap = PSA_KEY_ID_NULL;
    psa_key_id_t kek_no_unwrap = PSA_KEY_ID_NULL;
    psa_key_id_t target = PSA_KEY_ID_NULL;
    psa_key_id_t dummy_key = PSA_KEY_ID_NULL;
    psa_key_attributes_t tattr = psa_key_attributes_init();
    psa_key_attributes_t rattr = psa_key_attributes_init();
    uint8_t wrapped[32];
    size_t wrapped_len = 0;
    psa_status_t st;
    int ret = 0;

    /* KEK with UNWRAP only — psa_wrap_key must fail */
    kek_no_wrap = import_aes_key("missing_wrap/kek_no_wrap",
                                 kKekRfc3394, sizeof(kKekRfc3394),
                                 PSA_KEY_USAGE_UNWRAP, PSA_ALG_KW);
    if (kek_no_wrap == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    /* KEK with WRAP only — psa_unwrap_key must fail */
    kek_no_unwrap = import_aes_key("missing_wrap/kek_no_unwrap",
                                   kKekRfc3394, sizeof(kKekRfc3394),
                                   PSA_KEY_USAGE_WRAP, PSA_ALG_KW);
    if (kek_no_unwrap == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    /* Target key */
    psa_set_key_type(&tattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&tattr, 128);
    psa_set_key_usage_flags(&tattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&tattr, PSA_ALG_KW);

    st = psa_import_key(&tattr, kPlainRfc3394, sizeof(kPlainRfc3394), &target);
    if (expect_status("missing_wrap/import_target", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    /* psa_wrap_key with a no-WRAP key */
    st = psa_wrap_key(kek_no_wrap, PSA_ALG_KW, target,
                      wrapped, sizeof(wrapped), &wrapped_len);
    if (expect_status("missing_wrap/no_wrap_flag",
                      st, PSA_ERROR_NOT_PERMITTED) != 0) {
        ret = 1; goto done;
    }

    /* psa_unwrap_key with a no-UNWRAP key */
    psa_set_key_type(&rattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&rattr, 128);
    psa_set_key_usage_flags(&rattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&rattr, PSA_ALG_KW);

    st = psa_unwrap_key(&rattr, kek_no_unwrap, PSA_ALG_KW,
                        kCipherRfc3394, sizeof(kCipherRfc3394), &dummy_key);
    if (expect_status("missing_wrap/no_unwrap_flag",
                      st, PSA_ERROR_NOT_PERMITTED) != 0) {
        ret = 1; goto done;
    }

done:
    destroy_if_valid(target);
    destroy_if_valid(kek_no_wrap);
    destroy_if_valid(kek_no_unwrap);
    destroy_if_valid(dummy_key);
    return ret;
}

/* -------------------------------------------------------------------------
 * Test 5: Target key without PSA_KEY_USAGE_EXPORT → PSA_ERROR_NOT_PERMITTED
 * ---------------------------------------------------------------------- */
static int test_target_no_export(void)
{
    psa_key_id_t kek = PSA_KEY_ID_NULL;
    psa_key_id_t target = PSA_KEY_ID_NULL;
    psa_key_attributes_t tattr = psa_key_attributes_init();
    uint8_t wrapped[32];
    size_t wrapped_len = 0;
    psa_status_t st;
    int ret = 0;

    kek = import_aes_key("no_export/kek", kKekRfc3394, sizeof(kKekRfc3394),
                         PSA_KEY_USAGE_WRAP | PSA_KEY_USAGE_UNWRAP,
                         PSA_ALG_KW);
    if (kek == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    /* Target: no EXPORT flag */
    psa_set_key_type(&tattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&tattr, 128);
    psa_set_key_usage_flags(&tattr, 0);       /* no EXPORT */
    psa_set_key_algorithm(&tattr, PSA_ALG_KW);

    st = psa_import_key(&tattr, kPlainRfc3394, sizeof(kPlainRfc3394), &target);
    if (expect_status("no_export/import_target", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    st = psa_wrap_key(kek, PSA_ALG_KW, target,
                      wrapped, sizeof(wrapped), &wrapped_len);
    if (expect_status("no_export/psa_wrap_key",
                      st, PSA_ERROR_NOT_PERMITTED) != 0) {
        ret = 1; goto done;
    }

done:
    destroy_if_valid(target);
    destroy_if_valid(kek);
    return ret;
}

/* -------------------------------------------------------------------------
 * Test 6: PSA_ALG_KWP → PSA_ERROR_NOT_SUPPORTED
 * ---------------------------------------------------------------------- */
static int test_kwp_not_supported(void)
{
    psa_key_id_t kek = PSA_KEY_ID_NULL;
    psa_key_id_t target = PSA_KEY_ID_NULL;
    psa_key_id_t dummy_key = PSA_KEY_ID_NULL;
    psa_key_attributes_t tattr = psa_key_attributes_init();
    psa_key_attributes_t rattr = psa_key_attributes_init();
    uint8_t buf[32];
    size_t buf_len = 0;
    psa_status_t st;
    int ret = 0;

    /*
     * The KEK must carry PSA_ALG_KWP as its permitted algorithm because
     * psa_wrap_key checks wrap_alg != alg after the usage check.  We import
     * it with PSA_ALG_KWP so that the algorithm mismatch never fires before
     * the KWP-not-supported early-out.
     */
    kek = import_aes_key("kwp/kek", kKekRfc3394, sizeof(kKekRfc3394),
                         PSA_KEY_USAGE_WRAP | PSA_KEY_USAGE_UNWRAP,
                         PSA_ALG_KWP);
    if (kek == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    psa_set_key_type(&tattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&tattr, 128);
    psa_set_key_usage_flags(&tattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&tattr, PSA_ALG_KWP);

    st = psa_import_key(&tattr, kPlainRfc3394, sizeof(kPlainRfc3394), &target);
    if (expect_status("kwp/import_target", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    st = psa_wrap_key(kek, PSA_ALG_KWP, target, buf, sizeof(buf), &buf_len);
    if (expect_status("kwp/wrap_not_supported",
                      st, PSA_ERROR_NOT_SUPPORTED) != 0) {
        ret = 1; goto done;
    }

    psa_set_key_type(&rattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&rattr, 128);
    psa_set_key_usage_flags(&rattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&rattr, PSA_ALG_KWP);

    st = psa_unwrap_key(&rattr, kek, PSA_ALG_KWP,
                        kCipherRfc3394, sizeof(kCipherRfc3394), &dummy_key);
    if (expect_status("kwp/unwrap_not_supported",
                      st, PSA_ERROR_NOT_SUPPORTED) != 0) {
        ret = 1; goto done;
    }

done:
    destroy_if_valid(target);
    destroy_if_valid(kek);
    destroy_if_valid(dummy_key);
    return ret;
}

/* -------------------------------------------------------------------------
 * Test 7: Corrupted wrapped data → PSA_ERROR_INVALID_SIGNATURE
 * ---------------------------------------------------------------------- */
static int test_corrupt_wrapped(void)
{
    psa_key_id_t kek = PSA_KEY_ID_NULL;
    psa_key_id_t dummy_key = PSA_KEY_ID_NULL;
    psa_key_attributes_t rattr = psa_key_attributes_init();
    uint8_t corrupt[24];
    psa_status_t st;
    int ret = 0;

    kek = import_aes_key("corrupt/kek", kKekRfc3394, sizeof(kKekRfc3394),
                         PSA_KEY_USAGE_WRAP | PSA_KEY_USAGE_UNWRAP,
                         PSA_ALG_KW);
    if (kek == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    /* Copy the valid RFC ciphertext then flip byte 0 */
    memcpy(corrupt, kCipherRfc3394, sizeof(kCipherRfc3394));
    corrupt[0] ^= 0xFF;

    psa_set_key_type(&rattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&rattr, 128);
    psa_set_key_usage_flags(&rattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&rattr, PSA_ALG_KW);

    st = psa_unwrap_key(&rattr, kek, PSA_ALG_KW,
                        corrupt, sizeof(corrupt), &dummy_key);
    if (expect_status("corrupt/invalid_signature",
                      st, PSA_ERROR_INVALID_SIGNATURE) != 0) {
        ret = 1; goto done;
    }

done:
    destroy_if_valid(dummy_key);
    destroy_if_valid(kek);
    return ret;
}

/* -------------------------------------------------------------------------
 * Test 8: Output buffer one byte too small → PSA_ERROR_BUFFER_TOO_SMALL
 *
 * The RFC 3394 output for a 16-byte key is 24 bytes.  Passing a 23-byte
 * buffer must trigger the size guard.
 * ---------------------------------------------------------------------- */
static int test_buffer_too_small(void)
{
    psa_key_id_t kek = PSA_KEY_ID_NULL;
    psa_key_id_t target = PSA_KEY_ID_NULL;
    psa_key_attributes_t tattr = psa_key_attributes_init();
    uint8_t small_buf[23]; /* 24 - 1 */
    size_t out_len = 0;
    psa_status_t st;
    int ret = 0;

    kek = import_aes_key("buf_small/kek", kKekRfc3394, sizeof(kKekRfc3394),
                         PSA_KEY_USAGE_WRAP | PSA_KEY_USAGE_UNWRAP,
                         PSA_ALG_KW);
    if (kek == PSA_KEY_ID_NULL) { ret = 1; goto done; }

    psa_set_key_type(&tattr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&tattr, 128);
    psa_set_key_usage_flags(&tattr, PSA_KEY_USAGE_EXPORT);
    psa_set_key_algorithm(&tattr, PSA_ALG_KW);

    st = psa_import_key(&tattr, kPlainRfc3394, sizeof(kPlainRfc3394), &target);
    if (expect_status("buf_small/import_target", st, PSA_SUCCESS) != 0) {
        ret = 1; goto done;
    }

    st = psa_wrap_key(kek, PSA_ALG_KW, target,
                      small_buf, sizeof(small_buf), &out_len);
    if (expect_status("buf_small/buffer_too_small",
                      st, PSA_ERROR_BUFFER_TOO_SMALL) != 0) {
        ret = 1; goto done;
    }

done:
    destroy_if_valid(target);
    destroy_if_valid(kek);
    return ret;
}

/* -------------------------------------------------------------------------
 * main
 * ---------------------------------------------------------------------- */
int main(void)
{
    psa_status_t st;

    st = psa_crypto_init();
    if (st != PSA_SUCCESS) {
        printf("FAIL psa_crypto_init: status=%d\n", (int)st);
        return 1;
    }

    if (test_kat_wrap() != 0)            return 1;
    if (test_kat_unwrap() != 0)          return 1;
    if (test_roundtrip_aes256() != 0)    return 1;
    if (test_missing_usage_flags() != 0) return 1;
    if (test_target_no_export() != 0)    return 1;
    if (test_kwp_not_supported() != 0)   return 1;
    if (test_corrupt_wrapped() != 0)     return 1;
    if (test_buffer_too_small() != 0)    return 1;

    printf("PSA key wrap test: OK\n");
    return 0;
}
