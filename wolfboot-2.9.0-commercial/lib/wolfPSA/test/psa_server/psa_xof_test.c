/* psa_xof_test.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "psa_api_test_user_settings.h"

#ifndef WOLFSSL_USER_SETTINGS
#define WOLFSSL_USER_SETTINGS
#endif

#include <wolfssl/wolfcrypt/settings.h>

#include <stdio.h>
#include <string.h>

#include <wolfpsa/psa/crypto.h>

/* -----------------------------------------------------------------------
 * Helpers
 * ----------------------------------------------------------------------- */

static int expect_status(const char *label, psa_status_t got,
                         psa_status_t expected)
{
    if (got != expected) {
        printf("FAIL %s status=%d expected=%d\n", label, (int)got,
               (int)expected);
        return 1;
    }
    return 0;
}

static int expect_bytes(const char *label, const uint8_t *got,
                        const uint8_t *expected, size_t len)
{
    if (memcmp(got, expected, len) != 0) {
        size_t i;
        printf("FAIL %s output mismatch\n  got:", label);
        for (i = 0; i < len; i++) printf(" %02x", got[i]);
        printf("\n  exp:");
        for (i = 0; i < len; i++) printf(" %02x", expected[i]);
        printf("\n");
        return 1;
    }
    return 0;
}

/* -----------------------------------------------------------------------
 * Known-answer vectors
 *
 * NIST standard vectors (source: NIST FIPS 202 / SHA-3 test vectors):
 *   - SHAKE128 empty → first 32 bytes
 *   - SHAKE256 empty → first 32 bytes
 *   - SHAKE128 "The quick brown fox…" (43 bytes) → first 16 bytes
 *
 * Python-generated vectors (python3 -c "import hashlib; …"):
 *   - SHAKE128 bytes(range(100)) → 64 bytes
 *   - SHAKE256 bytes(range(100)) → 64 bytes
 *   - SHAKE128 bytes(range(100)) → 200 bytes (crosses rate=168 boundary)
 *   - SHAKE256 bytes(range(100)) → 200 bytes (crosses rate=136 boundary)
 * ----------------------------------------------------------------------- */

/* NIST: SHAKE128, empty message, first 32 output bytes */
static const uint8_t kat_shake128_empty_32[32] = {
    0x7f, 0x9c, 0x2b, 0xa4, 0xe8, 0x8f, 0x82, 0x7d,
    0x61, 0x60, 0x45, 0x50, 0x76, 0x05, 0x85, 0x3e,
    0xd7, 0x3b, 0x80, 0x93, 0xf6, 0xef, 0xbc, 0x88,
    0xeb, 0x1a, 0x6e, 0xac, 0xfa, 0x66, 0xef, 0x26
};

/* NIST: SHAKE256, empty message, first 32 output bytes */
static const uint8_t kat_shake256_empty_32[32] = {
    0x46, 0xb9, 0xdd, 0x2b, 0x0b, 0xa8, 0x8d, 0x13,
    0x23, 0x3b, 0x3f, 0xeb, 0x74, 0x3e, 0xeb, 0x24,
    0x3f, 0xcd, 0x52, 0xea, 0x62, 0xb8, 0x1b, 0x82,
    0xb5, 0x0c, 0x27, 0x64, 0x6e, 0xd5, 0x76, 0x2f
};

/* NIST: SHAKE128, "The quick brown fox jumps over the lazy dog" → first 16 B */
static const uint8_t fox_msg[] = {
    'T','h','e',' ','q','u','i','c','k',' ','b','r','o','w','n',' ',
    'f','o','x',' ','j','u','m','p','s',' ','o','v','e','r',' ','t',
    'h','e',' ','l','a','z','y',' ','d','o','g'
};
static const uint8_t kat_shake128_fox_16[16] = {
    0xf4, 0x20, 0x2e, 0x3c, 0x58, 0x52, 0xf9, 0x18,
    0x2a, 0x04, 0x30, 0xfd, 0x81, 0x44, 0xf0, 0xa7
};

/* Pattern input: bytes(range(100)) */
static uint8_t pattern100[100]; /* filled in main() */

/* Python hashlib: SHAKE128(bytes(range(100)), 64 bytes) */
static const uint8_t kat_shake128_p100_64[64] = {
    0x04, 0xeb, 0xa3, 0x0b, 0x78, 0x55, 0x0e, 0xe4,
    0x61, 0xbb, 0x4d, 0x59, 0x1d, 0x2b, 0x36, 0x67,
    0xeb, 0x84, 0x40, 0x02, 0xee, 0xe5, 0xa1, 0xc7,
    0x19, 0x9f, 0x7d, 0x04, 0x20, 0x38, 0x5f, 0x11,
    0x18, 0xa3, 0x6d, 0xbd, 0x5a, 0xb1, 0x97, 0x39,
    0xee, 0xa2, 0xd2, 0xe1, 0x78, 0x90, 0x08, 0xf9,
    0x49, 0x23, 0x02, 0xb3, 0x11, 0x5e, 0x36, 0xf4,
    0x7e, 0x83, 0x8c, 0x8a, 0xf0, 0xeb, 0x8e, 0x93
};

/* Python hashlib: SHAKE256(bytes(range(100)), 64 bytes) */
static const uint8_t kat_shake256_p100_64[64] = {
    0xbc, 0x98, 0xc7, 0x6f, 0xbb, 0x61, 0xfc, 0xa7,
    0xda, 0x03, 0x2d, 0x69, 0x42, 0x3d, 0x14, 0x0a,
    0xbf, 0x2a, 0xb5, 0xaa, 0xb4, 0x27, 0x1c, 0x29,
    0x19, 0x7c, 0x84, 0x30, 0x3c, 0x0d, 0x90, 0xff,
    0x78, 0xfe, 0xb8, 0x85, 0xfe, 0xd1, 0xc9, 0x8c,
    0x9f, 0xa1, 0xbd, 0xe0, 0x66, 0xe2, 0xe1, 0x45,
    0x4d, 0xc6, 0xe2, 0xea, 0xbb, 0x3a, 0x2c, 0xfc,
    0xff, 0x06, 0x6b, 0x26, 0x6b, 0x03, 0x5c, 0x5c
};

/* Python hashlib: SHAKE128(bytes(range(100)), 200 bytes)
 * Rate = 168 bytes, so 200 bytes crosses exactly one block boundary. */
static const uint8_t kat_shake128_p100_200[200] = {
    0x04, 0xeb, 0xa3, 0x0b, 0x78, 0x55, 0x0e, 0xe4,
    0x61, 0xbb, 0x4d, 0x59, 0x1d, 0x2b, 0x36, 0x67,
    0xeb, 0x84, 0x40, 0x02, 0xee, 0xe5, 0xa1, 0xc7,
    0x19, 0x9f, 0x7d, 0x04, 0x20, 0x38, 0x5f, 0x11,
    0x18, 0xa3, 0x6d, 0xbd, 0x5a, 0xb1, 0x97, 0x39,
    0xee, 0xa2, 0xd2, 0xe1, 0x78, 0x90, 0x08, 0xf9,
    0x49, 0x23, 0x02, 0xb3, 0x11, 0x5e, 0x36, 0xf4,
    0x7e, 0x83, 0x8c, 0x8a, 0xf0, 0xeb, 0x8e, 0x93,
    0x56, 0x98, 0x15, 0xca, 0xd9, 0x98, 0xde, 0xce,
    0xd9, 0xbf, 0xb0, 0x64, 0xbe, 0xd1, 0xfc, 0xb8,
    0xb2, 0xc1, 0x4b, 0x78, 0x47, 0xa9, 0x5d, 0x8a,
    0xc3, 0xeb, 0x63, 0xa3, 0x0b, 0x62, 0x89, 0xd9,
    0x6f, 0xc8, 0x55, 0x39, 0x47, 0x27, 0x56, 0x0b,
    0x20, 0x1e, 0x07, 0x40, 0x63, 0xa5, 0x95, 0xc9,
    0xe4, 0x1a, 0xf0, 0x91, 0x36, 0x2e, 0x55, 0xfc,
    0x1e, 0x8b, 0x13, 0xc0, 0xa9, 0x20, 0xae, 0x83,
    0x96, 0x1e, 0x46, 0x64, 0xf9, 0xa1, 0x23, 0x5d,
    0x4d, 0x0f, 0x4e, 0xa2, 0xc9, 0x3c, 0x89, 0xf7,
    0xf8, 0x48, 0x08, 0xac, 0x94, 0x3d, 0x1a, 0x3d,
    0x92, 0x7b, 0x64, 0xb4, 0x0b, 0xf3, 0x3d, 0x47,
    0x0b, 0x42, 0x60, 0x1e, 0xff, 0x17, 0xc0, 0xb6,
    0x2e, 0x03, 0x2c, 0xb1, 0x02, 0xea, 0xcd, 0xa8,
    0x39, 0x2d, 0x75, 0x64, 0x1d, 0x8e, 0x3c, 0x4b,
    0x27, 0xd0, 0xa9, 0x48, 0x7d, 0x6a, 0xd7, 0xb0,
    0x4c, 0xa4, 0x70, 0x79, 0xa4, 0x59, 0xa6, 0x43
};

/* Python hashlib: SHAKE256(bytes(range(100)), 200 bytes)
 * Rate = 136 bytes, so 200 bytes crosses exactly one block boundary. */
static const uint8_t kat_shake256_p100_200[200] = {
    0xbc, 0x98, 0xc7, 0x6f, 0xbb, 0x61, 0xfc, 0xa7,
    0xda, 0x03, 0x2d, 0x69, 0x42, 0x3d, 0x14, 0x0a,
    0xbf, 0x2a, 0xb5, 0xaa, 0xb4, 0x27, 0x1c, 0x29,
    0x19, 0x7c, 0x84, 0x30, 0x3c, 0x0d, 0x90, 0xff,
    0x78, 0xfe, 0xb8, 0x85, 0xfe, 0xd1, 0xc9, 0x8c,
    0x9f, 0xa1, 0xbd, 0xe0, 0x66, 0xe2, 0xe1, 0x45,
    0x4d, 0xc6, 0xe2, 0xea, 0xbb, 0x3a, 0x2c, 0xfc,
    0xff, 0x06, 0x6b, 0x26, 0x6b, 0x03, 0x5c, 0x5c,
    0xc2, 0xad, 0x2e, 0xc3, 0x27, 0x02, 0x1f, 0x9f,
    0x00, 0xbe, 0x0a, 0xba, 0x38, 0x54, 0x63, 0x74,
    0xdc, 0x5f, 0xc3, 0xf1, 0xa6, 0xa6, 0x1a, 0xe0,
    0x76, 0xd4, 0x99, 0x89, 0x97, 0x55, 0x0a, 0x2d,
    0xfa, 0x91, 0x73, 0x99, 0xa3, 0x45, 0xd2, 0xc0,
    0xc4, 0xf5, 0x6f, 0x44, 0x11, 0xf4, 0x12, 0xa7,
    0x4a, 0xdd, 0x45, 0xe2, 0xd0, 0x4b, 0xf4, 0x79,
    0xd1, 0xf6, 0xe4, 0xf9, 0x2a, 0xb0, 0x6f, 0x63,
    0xb0, 0xa7, 0x7b, 0x8a, 0x82, 0x80, 0xaf, 0xe8,
    0xe5, 0xa0, 0x6f, 0x63, 0x8e, 0xc5, 0x51, 0x60,
    0xa9, 0x84, 0x2e, 0x4c, 0x5e, 0x87, 0x59, 0x9d,
    0x16, 0x68, 0x38, 0x27, 0xa7, 0x1f, 0x50, 0x5c,
    0x8c, 0x61, 0x6a, 0x96, 0xe0, 0x72, 0xdd, 0x72,
    0x34, 0x44, 0x39, 0x10, 0xb1, 0x5c, 0xc0, 0x37,
    0x39, 0x4e, 0x12, 0x58, 0xc8, 0xfe, 0x3c, 0x10,
    0x67, 0x26, 0xad, 0x38, 0x28, 0x62, 0x0b, 0x03,
    0xdd, 0xf5, 0xc6, 0x50, 0x80, 0x3e, 0x56, 0x61
};

/* -----------------------------------------------------------------------
 * TC-1: SHAKE128 and SHAKE256 empty-input KATs (32 bytes, one-shot)
 * ----------------------------------------------------------------------- */
static int test_empty_kat(void)
{
    psa_xof_operation_t op;
    uint8_t out[32];
    psa_status_t st;

    /* SHAKE128 */
    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc1 shake128 setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op, out, sizeof(out));
    if (expect_status("tc1 shake128 output", st, PSA_SUCCESS) != 0) return 1;
    if (expect_bytes("tc1 shake128 empty 32", out, kat_shake128_empty_32,
                     sizeof(out)) != 0) return 1;
    (void)psa_xof_abort(&op);

    /* SHAKE256 */
    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE256);
    if (expect_status("tc1 shake256 setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op, out, sizeof(out));
    if (expect_status("tc1 shake256 output", st, PSA_SUCCESS) != 0) return 1;
    if (expect_bytes("tc1 shake256 empty 32", out, kat_shake256_empty_32,
                     sizeof(out)) != 0) return 1;
    (void)psa_xof_abort(&op);

    return 0;
}

/* -----------------------------------------------------------------------
 * TC-2: Non-empty input KATs (bytes(range(100)) → 64 bytes)
 *        Vectors generated with Python hashlib.
 * ----------------------------------------------------------------------- */
static int test_nonempty_kat(void)
{
    psa_xof_operation_t op;
    uint8_t out[64];
    psa_status_t st;

    /* SHAKE128 */
    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc2 shake128 setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op, pattern100, sizeof(pattern100));
    if (expect_status("tc2 shake128 update", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op, out, sizeof(out));
    if (expect_status("tc2 shake128 output", st, PSA_SUCCESS) != 0) return 1;
    if (expect_bytes("tc2 shake128 p100 64", out, kat_shake128_p100_64,
                     sizeof(out)) != 0) return 1;
    (void)psa_xof_abort(&op);

    /* SHAKE256 */
    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE256);
    if (expect_status("tc2 shake256 setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op, pattern100, sizeof(pattern100));
    if (expect_status("tc2 shake256 update", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op, out, sizeof(out));
    if (expect_status("tc2 shake256 output", st, PSA_SUCCESS) != 0) return 1;
    if (expect_bytes("tc2 shake256 p100 64", out, kat_shake256_p100_64,
                     sizeof(out)) != 0) return 1;
    (void)psa_xof_abort(&op);

    return 0;
}

/* -----------------------------------------------------------------------
 * TC-3: Incremental absorb — 3 chunks vs one-shot
 *        Split pattern100 into [33, 33, 34] bytes.
 * ----------------------------------------------------------------------- */
static int test_incremental_absorb(void)
{
    psa_xof_operation_t op_incremental, op_oneshot;
    uint8_t out_inc[64], out_one[64];
    psa_status_t st;

    /* SHAKE128 incremental */
    op_incremental = psa_xof_operation_init();
    st = psa_xof_setup(&op_incremental, PSA_ALG_SHAKE128);
    if (expect_status("tc3 shake128 inc setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op_incremental, pattern100, 33);
    if (expect_status("tc3 shake128 upd1", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op_incremental, pattern100 + 33, 33);
    if (expect_status("tc3 shake128 upd2", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op_incremental, pattern100 + 66, 34);
    if (expect_status("tc3 shake128 upd3", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_incremental, out_inc, sizeof(out_inc));
    if (expect_status("tc3 shake128 inc output", st, PSA_SUCCESS) != 0) return 1;
    (void)psa_xof_abort(&op_incremental);

    /* SHAKE128 one-shot */
    op_oneshot = psa_xof_operation_init();
    st = psa_xof_setup(&op_oneshot, PSA_ALG_SHAKE128);
    if (expect_status("tc3 shake128 one setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op_oneshot, pattern100, sizeof(pattern100));
    if (expect_status("tc3 shake128 one update", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_oneshot, out_one, sizeof(out_one));
    if (expect_status("tc3 shake128 one output", st, PSA_SUCCESS) != 0) return 1;
    (void)psa_xof_abort(&op_oneshot);

    if (expect_bytes("tc3 shake128 inc==one", out_inc, out_one,
                     sizeof(out_inc)) != 0) return 1;

    /* SHAKE256 incremental */
    op_incremental = psa_xof_operation_init();
    st = psa_xof_setup(&op_incremental, PSA_ALG_SHAKE256);
    if (expect_status("tc3 shake256 inc setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op_incremental, pattern100, 33);
    if (expect_status("tc3 shake256 upd1", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op_incremental, pattern100 + 33, 33);
    if (expect_status("tc3 shake256 upd2", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op_incremental, pattern100 + 66, 34);
    if (expect_status("tc3 shake256 upd3", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_incremental, out_inc, sizeof(out_inc));
    if (expect_status("tc3 shake256 inc output", st, PSA_SUCCESS) != 0) return 1;
    (void)psa_xof_abort(&op_incremental);

    /* SHAKE256 one-shot */
    op_oneshot = psa_xof_operation_init();
    st = psa_xof_setup(&op_oneshot, PSA_ALG_SHAKE256);
    if (expect_status("tc3 shake256 one setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op_oneshot, pattern100, sizeof(pattern100));
    if (expect_status("tc3 shake256 one update", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_oneshot, out_one, sizeof(out_one));
    if (expect_status("tc3 shake256 one output", st, PSA_SUCCESS) != 0) return 1;
    (void)psa_xof_abort(&op_oneshot);

    if (expect_bytes("tc3 shake256 inc==one", out_inc, out_one,
                     sizeof(out_inc)) != 0) return 1;

    return 0;
}

/* -----------------------------------------------------------------------
 * TC-4a: Incremental squeeze — 1+7+25+31 = 64 bytes equals one-shot 64B
 * TC-4b: 200-byte output in small pieces equals reference (block-boundary)
 * ----------------------------------------------------------------------- */
static int test_incremental_squeeze(void)
{
    psa_xof_operation_t op_pieces, op_oneshot;
    uint8_t out_pieces[64], out_one[64];
    uint8_t out_big_pieces[200], out_big_ref[200];
    size_t off;
    psa_status_t st;

    /* TC-4a SHAKE128: squeeze 1+7+25+31 bytes */
    op_pieces = psa_xof_operation_init();
    st = psa_xof_setup(&op_pieces, PSA_ALG_SHAKE128);
    if (expect_status("tc4a shake128 pieces setup", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_update(&op_pieces, pattern100, sizeof(pattern100));
    if (expect_status("tc4a shake128 update", st, PSA_SUCCESS) != 0) return 1;
    off = 0;
    st = psa_xof_output(&op_pieces, out_pieces + off, 1);  off += 1;
    if (expect_status("tc4a shake128 out1", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_pieces, out_pieces + off, 7);  off += 7;
    if (expect_status("tc4a shake128 out7", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_pieces, out_pieces + off, 25); off += 25;
    if (expect_status("tc4a shake128 out25", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_pieces, out_pieces + off, 31); off += 31;
    if (expect_status("tc4a shake128 out31", st, PSA_SUCCESS) != 0) return 1;
    (void)psa_xof_abort(&op_pieces);

    op_oneshot = psa_xof_operation_init();
    st = psa_xof_setup(&op_oneshot, PSA_ALG_SHAKE128);
    if (expect_status("tc4a shake128 one setup", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_update(&op_oneshot, pattern100, sizeof(pattern100));
    if (expect_status("tc4a shake128 one update", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_output(&op_oneshot, out_one, sizeof(out_one));
    if (expect_status("tc4a shake128 one output", st, PSA_SUCCESS) != 0)
        return 1;
    (void)psa_xof_abort(&op_oneshot);

    if (expect_bytes("tc4a shake128 pieces==one", out_pieces, out_one,
                     sizeof(out_one)) != 0) return 1;

    /* TC-4a SHAKE256: same split */
    op_pieces = psa_xof_operation_init();
    st = psa_xof_setup(&op_pieces, PSA_ALG_SHAKE256);
    if (expect_status("tc4a shake256 pieces setup", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_update(&op_pieces, pattern100, sizeof(pattern100));
    if (expect_status("tc4a shake256 update", st, PSA_SUCCESS) != 0) return 1;
    off = 0;
    st = psa_xof_output(&op_pieces, out_pieces + off, 1);  off += 1;
    if (expect_status("tc4a shake256 out1", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_pieces, out_pieces + off, 7);  off += 7;
    if (expect_status("tc4a shake256 out7", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_pieces, out_pieces + off, 25); off += 25;
    if (expect_status("tc4a shake256 out25", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op_pieces, out_pieces + off, 31); off += 31;
    if (expect_status("tc4a shake256 out31", st, PSA_SUCCESS) != 0) return 1;
    (void)psa_xof_abort(&op_pieces);

    op_oneshot = psa_xof_operation_init();
    st = psa_xof_setup(&op_oneshot, PSA_ALG_SHAKE256);
    if (expect_status("tc4a shake256 one setup", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_update(&op_oneshot, pattern100, sizeof(pattern100));
    if (expect_status("tc4a shake256 one update", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_output(&op_oneshot, out_one, sizeof(out_one));
    if (expect_status("tc4a shake256 one output", st, PSA_SUCCESS) != 0)
        return 1;
    (void)psa_xof_abort(&op_oneshot);

    if (expect_bytes("tc4a shake256 pieces==one", out_pieces, out_one,
                     sizeof(out_one)) != 0) return 1;

    /* TC-4b SHAKE128: 200-byte output in 8-byte pieces vs reference
     * 200 > rate(168), so this crosses the block boundary. */
    op_pieces = psa_xof_operation_init();
    st = psa_xof_setup(&op_pieces, PSA_ALG_SHAKE128);
    if (expect_status("tc4b shake128 big setup", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_update(&op_pieces, pattern100, sizeof(pattern100));
    if (expect_status("tc4b shake128 big update", st, PSA_SUCCESS) != 0)
        return 1;
    for (off = 0; off < sizeof(out_big_pieces); off += 8) {
        st = psa_xof_output(&op_pieces, out_big_pieces + off, 8);
        if (expect_status("tc4b shake128 big out chunk", st,
                          PSA_SUCCESS) != 0) return 1;
    }
    (void)psa_xof_abort(&op_pieces);

    op_oneshot = psa_xof_operation_init();
    st = psa_xof_setup(&op_oneshot, PSA_ALG_SHAKE128);
    if (expect_status("tc4b shake128 big one setup", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_update(&op_oneshot, pattern100, sizeof(pattern100));
    if (expect_status("tc4b shake128 big one update", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_output(&op_oneshot, out_big_ref, sizeof(out_big_ref));
    if (expect_status("tc4b shake128 big one output", st, PSA_SUCCESS) != 0)
        return 1;
    (void)psa_xof_abort(&op_oneshot);

    if (expect_bytes("tc4b shake128 big pieces==ref", out_big_pieces, out_big_ref,
                     sizeof(out_big_ref)) != 0) return 1;

    /* Also verify one-shot matches the python KAT */
    if (expect_bytes("tc4b shake128 ref==kat", out_big_ref, kat_shake128_p100_200,
                     sizeof(kat_shake128_p100_200)) != 0) return 1;

    /* TC-4b SHAKE256: 200-byte output in 8-byte pieces vs reference
     * 200 > rate(136), so this crosses the block boundary. */
    op_pieces = psa_xof_operation_init();
    st = psa_xof_setup(&op_pieces, PSA_ALG_SHAKE256);
    if (expect_status("tc4b shake256 big setup", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_update(&op_pieces, pattern100, sizeof(pattern100));
    if (expect_status("tc4b shake256 big update", st, PSA_SUCCESS) != 0)
        return 1;
    for (off = 0; off < sizeof(out_big_pieces); off += 8) {
        st = psa_xof_output(&op_pieces, out_big_pieces + off, 8);
        if (expect_status("tc4b shake256 big out chunk", st,
                          PSA_SUCCESS) != 0) return 1;
    }
    (void)psa_xof_abort(&op_pieces);

    op_oneshot = psa_xof_operation_init();
    st = psa_xof_setup(&op_oneshot, PSA_ALG_SHAKE256);
    if (expect_status("tc4b shake256 big one setup", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_update(&op_oneshot, pattern100, sizeof(pattern100));
    if (expect_status("tc4b shake256 big one update", st, PSA_SUCCESS) != 0)
        return 1;
    st = psa_xof_output(&op_oneshot, out_big_ref, sizeof(out_big_ref));
    if (expect_status("tc4b shake256 big one output", st, PSA_SUCCESS) != 0)
        return 1;
    (void)psa_xof_abort(&op_oneshot);

    if (expect_bytes("tc4b shake256 big pieces==ref", out_big_pieces, out_big_ref,
                     sizeof(out_big_ref)) != 0) return 1;

    if (expect_bytes("tc4b shake256 ref==kat", out_big_ref, kat_shake256_p100_200,
                     sizeof(kat_shake256_p100_200)) != 0) return 1;

    return 0;
}

/* -----------------------------------------------------------------------
 * TC-5: Zero-length update and zero-length output are no-op successes
 * ----------------------------------------------------------------------- */
static int test_zero_length_ops(void)
{
    psa_xof_operation_t op;
    uint8_t out[1];
    psa_status_t st;

    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc5 setup", st, PSA_SUCCESS) != 0) return 1;

    /* Zero-length update must succeed */
    st = psa_xof_update(&op, NULL, 0);
    if (expect_status("tc5 zero update", st, PSA_SUCCESS) != 0) return 1;

    /* Absorb some real data so the squeeze result is deterministic */
    st = psa_xof_update(&op, pattern100, sizeof(pattern100));
    if (expect_status("tc5 real update", st, PSA_SUCCESS) != 0) return 1;

    /* Start squeezing */
    st = psa_xof_output(&op, out, sizeof(out));
    if (expect_status("tc5 first output", st, PSA_SUCCESS) != 0) return 1;

    /* Zero-length output after squeezing has started must succeed */
    st = psa_xof_output(&op, NULL, 0);
    if (expect_status("tc5 zero output after squeeze", st, PSA_SUCCESS) != 0)
        return 1;

    (void)psa_xof_abort(&op);
    return 0;
}

/* -----------------------------------------------------------------------
 * TC-6: State-machine error cases
 *   a) update after output → PSA_ERROR_BAD_STATE
 *   b) setup on an active op → PSA_ERROR_BAD_STATE
 *   c) abort then reuse (setup again) works
 * ----------------------------------------------------------------------- */
static int test_state_errors(void)
{
    psa_xof_operation_t op;
    uint8_t out[8];
    psa_status_t st;

    /* TC-6a: update after output */
    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc6a setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op, out, sizeof(out));
    if (expect_status("tc6a first output", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op, pattern100, 10);
    if (expect_status("tc6a update after output", st,
                      PSA_ERROR_BAD_STATE) != 0) return 1;
    /* operation was aborted by the failed update */

    /* TC-6b: setup on an active (not-yet-squeezed) op */
    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc6b first setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op, pattern100, 10);
    if (expect_status("tc6b update", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc6b setup on active op", st,
                      PSA_ERROR_BAD_STATE) != 0) return 1;
    (void)psa_xof_abort(&op);

    /* TC-6c: abort then reuse */
    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc6c first setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op, pattern100, sizeof(pattern100));
    if (expect_status("tc6c update", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_abort(&op);
    if (expect_status("tc6c abort", st, PSA_SUCCESS) != 0) return 1;

    /* Re-setup the same operation object */
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc6c reuse setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op, out, sizeof(out));
    if (expect_status("tc6c reuse output", st, PSA_SUCCESS) != 0) return 1;
    /* Output must be the empty-message prefix */
    if (expect_bytes("tc6c reuse output==empty prefix", out,
                     kat_shake128_empty_32, sizeof(out)) != 0) return 1;
    (void)psa_xof_abort(&op);

    return 0;
}

/* -----------------------------------------------------------------------
 * TC-7: psa_xof_set_context on SHAKE → PSA_ERROR_INVALID_ARGUMENT
 * ----------------------------------------------------------------------- */
static int test_set_context_shake(void)
{
    psa_xof_operation_t op;
    static const uint8_t ctx_data[] = { 0x01, 0x02, 0x03 };
    psa_status_t st;

    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc7 shake128 setup", st, PSA_SUCCESS) != 0) return 1;

    st = psa_xof_set_context(&op, ctx_data, sizeof(ctx_data));
    if (expect_status("tc7 shake128 set_context", st,
                      PSA_ERROR_INVALID_ARGUMENT) != 0) return 1;
    (void)psa_xof_abort(&op);

    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE256);
    if (expect_status("tc7 shake256 setup", st, PSA_SUCCESS) != 0) return 1;

    st = psa_xof_set_context(&op, ctx_data, sizeof(ctx_data));
    if (expect_status("tc7 shake256 set_context", st,
                      PSA_ERROR_INVALID_ARGUMENT) != 0) return 1;
    (void)psa_xof_abort(&op);

    return 0;
}

/* -----------------------------------------------------------------------
 * TC-8: PSA_ALG_ASCON_XOF128 setup → PSA_ERROR_NOT_SUPPORTED
 * ----------------------------------------------------------------------- */
static int test_ascon_xof_not_supported(void)
{
    psa_xof_operation_t op;
    psa_status_t st;

    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_ASCON_XOF128);
    if (expect_status("tc8 ascon_xof128 setup", st,
                      PSA_ERROR_NOT_SUPPORTED) != 0) return 1;

    return 0;
}

/* -----------------------------------------------------------------------
 * TC-9: Non-XOF algorithm (PSA_ALG_SHA_256) → PSA_ERROR_INVALID_ARGUMENT
 * ----------------------------------------------------------------------- */
static int test_non_xof_alg(void)
{
    psa_xof_operation_t op;
    psa_status_t st;

    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHA_256);
    if (expect_status("tc9 sha256 as xof", st,
                      PSA_ERROR_INVALID_ARGUMENT) != 0) return 1;

    return 0;
}

/* -----------------------------------------------------------------------
 * TC-NIST-FOX: fox message 16-byte prefix KAT (NIST)
 * ----------------------------------------------------------------------- */
static int test_fox_kat(void)
{
    psa_xof_operation_t op;
    uint8_t out[16];
    psa_status_t st;

    op = psa_xof_operation_init();
    st = psa_xof_setup(&op, PSA_ALG_SHAKE128);
    if (expect_status("tc-fox shake128 setup", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_update(&op, fox_msg, sizeof(fox_msg));
    if (expect_status("tc-fox shake128 update", st, PSA_SUCCESS) != 0) return 1;
    st = psa_xof_output(&op, out, sizeof(out));
    if (expect_status("tc-fox shake128 output", st, PSA_SUCCESS) != 0) return 1;
    if (expect_bytes("tc-fox shake128 fox 16", out, kat_shake128_fox_16,
                     sizeof(out)) != 0) return 1;
    (void)psa_xof_abort(&op);

    return 0;
}

/* -----------------------------------------------------------------------
 * main
 * ----------------------------------------------------------------------- */
int main(void)
{
    psa_status_t st;
    size_t i;

    /* Build runtime pattern: bytes(range(100)) */
    for (i = 0; i < sizeof(pattern100); i++)
        pattern100[i] = (uint8_t)i;

    st = psa_crypto_init();
    if (st != PSA_SUCCESS) {
        printf("FAIL psa_crypto_init status=%d\n", (int)st);
        return 1;
    }

    if (test_empty_kat() != 0) return 1;
    if (test_fox_kat() != 0) return 1;
    if (test_nonempty_kat() != 0) return 1;
    if (test_incremental_absorb() != 0) return 1;
    if (test_incremental_squeeze() != 0) return 1;
    if (test_zero_length_ops() != 0) return 1;
    if (test_state_errors() != 0) return 1;
    if (test_set_context_shake() != 0) return 1;
    if (test_ascon_xof_not_supported() != 0) return 1;
    if (test_non_xof_alg() != 0) return 1;

    printf("PSA XOF test: OK\n");
    return 0;
}
