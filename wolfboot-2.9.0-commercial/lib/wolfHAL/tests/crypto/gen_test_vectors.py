#!/usr/bin/env python3
# gen_test_vectors.py
#
# Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfBoot.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#

"""Generate streaming-API test vectors for wolfHAL crypto tests.

Computes expected outputs from fixed inputs using PyCA cryptography. The
purpose of this script is to keep humans (and LLMs) out of the trust loop
for the hex constants in tests/crypto/test_<algo>.c — every expected
ciphertext, tag, digest, or MAC committed there should originate here.

Usage:
    python3 tests/crypto/gen_test_vectors.py

Then paste each printed section into the matching tests/crypto/test_<algo>.c.
Inputs (keys, IVs, AAD, plaintext, message) are reused from the existing
KAT tests where possible, with new per-streaming-test buffers added for
non-block-aligned payloads.
"""

import sys

try:
    from cryptography.hazmat.primitives.ciphers.aead import AESGCM, AESCCM
    from cryptography.hazmat.primitives import hashes, hmac as hmac_mod
except ImportError:
    sys.exit("install cryptography: pip install cryptography")


def emit(name, data):
    """Print a `static const uint8_t name[N] = { ... };` block."""
    print(f"static const uint8_t {name}[{len(data)}] = {{")
    for i in range(0, len(data), 8):
        chunk = data[i:i + 8]
        line = "    " + ", ".join(f"0x{b:02X}" for b in chunk) + ","
        print(line)
    print("};")
    print()


def banner(text):
    print(f"\n/* ==== {text} ==== */\n")


# Deterministic 100-byte buffer used as the plaintext / message for streaming
# tests. Length 100 is non-aligned for AES (16-byte block), SHA-1/224/256
# (64-byte block), and gives room for split points anywhere.
LONG_BUF = bytes((i * 7 + 3) & 0xFF for i in range(100))

# 50-byte slice used as the AEAD streaming plaintext (3 full AES blocks + 2).
AEAD_PT = LONG_BUF[:50]

# 20-byte AAD used in the with-AAD AEAD streaming tests.
AEAD_AAD = bytes((i * 11 + 5) & 0xFF for i in range(20))


# ---- AES-GCM streaming ----
# Reuses gcmKey/gcmIv from tests/crypto/test_aes_gcm.c (NIST GCM TC15).
gcm_key = bytes.fromhex(
    "FEFFE9928665731C6D6A8F9467308308"
    "FEFFE9928665731C6D6A8F9467308308"
)
gcm_iv = bytes.fromhex("CAFEBABEFACEDBADDECAF888")

aesgcm = AESGCM(gcm_key)

# Basic: AAD + payload
ct_full = aesgcm.encrypt(gcm_iv, AEAD_PT, AEAD_AAD)
gcm_ct, gcm_tag = ct_full[:-16], ct_full[-16:]

# No-AAD: payload only
ct_full = aesgcm.encrypt(gcm_iv, AEAD_PT, None)
gcm_noaad_ct, gcm_noaad_tag = ct_full[:-16], ct_full[-16:]

# No-payload: AAD only (GMAC-style — but via the GCM API)
ct_full = aesgcm.encrypt(gcm_iv, b"", AEAD_AAD)
gcm_nopt_tag = ct_full  # no ciphertext, just the tag

banner("test_aes_gcm.c — streaming vectors (paste alongside existing gcm* arrays)")
emit("gcmStreamAad", AEAD_AAD)
emit("gcmStreamPt", AEAD_PT)
emit("gcmStreamCt", gcm_ct)
emit("gcmStreamTag", gcm_tag)
emit("gcmStreamNoAadCt", gcm_noaad_ct)
emit("gcmStreamNoAadTag", gcm_noaad_tag)
emit("gcmStreamNoPtTag", gcm_nopt_tag)


# ---- AES-CCM streaming ----
# Reuses ccmKey/ccmNonce from tests/crypto/test_aes_ccm.c.
ccm_key = bytes.fromhex(
    "314A202F836F9F257E22D8C11757832A"
    "E5131D357A72DF88F3EFF0FFCEE0DA4E"
)
ccm_nonce = bytes.fromhex("A544218DADD3C10583DB49CF39")

aesccm = AESCCM(ccm_key, tag_length=16)

ct_full = aesccm.encrypt(ccm_nonce, AEAD_PT, AEAD_AAD)
ccm_ct, ccm_tag = ct_full[:-16], ct_full[-16:]

ct_full = aesccm.encrypt(ccm_nonce, AEAD_PT, None)
ccm_noaad_ct, ccm_noaad_tag = ct_full[:-16], ct_full[-16:]

ct_full = aesccm.encrypt(ccm_nonce, b"", AEAD_AAD)
ccm_nopt_tag = ct_full

banner("test_aes_ccm.c — streaming vectors")
emit("ccmStreamAad", AEAD_AAD)
emit("ccmStreamPt", AEAD_PT)
emit("ccmStreamCt", ccm_ct)
emit("ccmStreamTag", ccm_tag)
emit("ccmStreamNoAadCt", ccm_noaad_ct)
emit("ccmStreamNoAadTag", ccm_noaad_tag)
emit("ccmStreamNoPtTag", ccm_nopt_tag)


# ---- SHA streaming (100-byte message) ----
def sha_digest(algo, data):
    h = hashes.Hash(algo)
    h.update(data)
    return h.finalize()


banner("test_sha1.c / test_sha224.c / test_sha256.c — streaming vectors")
emit("streamMsg", LONG_BUF)
emit("sha1StreamDigest", sha_digest(hashes.SHA1(), LONG_BUF))
emit("sha224StreamDigest", sha_digest(hashes.SHA224(), LONG_BUF))
emit("sha256StreamDigest", sha_digest(hashes.SHA256(), LONG_BUF))


# ---- HMAC streaming ----
# Use the same 20-byte key as the existing HMAC KAT (RFC 2202/4231 TC1) so
# the file already has it; only the message and MAC change.
hmac_key = bytes([0x0B] * 20)


def hmac_mac(algo, key, data):
    h = hmac_mod.HMAC(key, algo)
    h.update(data)
    return h.finalize()


banner("test_hmac_sha1.c / test_hmac_sha224.c / test_hmac_sha256.c — streaming vectors")
emit("hmacStreamMsg", LONG_BUF)
emit("hmacSha1StreamMac", hmac_mac(hashes.SHA1(), hmac_key, LONG_BUF))
emit("hmacSha224StreamMac", hmac_mac(hashes.SHA224(), hmac_key, LONG_BUF))
emit("hmacSha256StreamMac", hmac_mac(hashes.SHA256(), hmac_key, LONG_BUF))


# ---- RSA-1024 raw primitive KAT ----
# Fixed key matches the rsaN / rsaE / rsaD / ... arrays in test_pka.c.
# Test plaintext is 0x00..0x7F (128 bytes), guaranteed < n (which starts
# with 0xBD). The PKA computes raw RSA primitives — no padding — so the
# expected ciphertext and signature are simply pow(m, e, n) and pow(m, d, n).

rsa_n = int.from_bytes(bytes.fromhex(
    "BDF8AE2B270559303A254D077AE73339B1F9DCE4A72EAD07CEB5BA9F27D6FA6B"
    "F73A92EEB7B80907BA35A4F1FDDFB590E3E7A7A63FEE401EF0E519DB786C5B3A"
    "E4235EC4846AE15EF3657A215A78CFA4E4D3F5006044EC8EC8A4160057950F6A"
    "A3D68476311F5A8C0194B3D958845356A1D794EF3A8AD0CB06F35EC75E479691"
), 'big')

rsa_e = 65537

rsa_d = int.from_bytes(bytes.fromhex(
    "78858EA9DDE5ACC1C601E82EB8B079753F0E902F98492A896B812BD6D145B836"
    "4AF1244AC2CFC51ADBEE30A93E3171556CE18921162A270FFA30BF08D80B968C"
    "5C32D3C9F49B793F1AACB719956391611C856191CC3F9F48AD44AD77FF44BBEC"
    "98685D499B89CBFA85035E0F4B136C85B487282135A611CB5B5029500073DCE9"
), 'big')

rsa_pt_bytes = bytes(range(128))
rsa_pt = int.from_bytes(rsa_pt_bytes, 'big')

assert rsa_pt < rsa_n, "plaintext must be < n for raw RSA"

rsa_ct = pow(rsa_pt, rsa_e, rsa_n)
rsa_sig = pow(rsa_pt, rsa_d, rsa_n)

# Self-check: signature verified with public key should recover the plaintext.
assert pow(rsa_sig, rsa_e, rsa_n) == rsa_pt
assert pow(rsa_ct, rsa_d, rsa_n) == rsa_pt

banner("test_pka.c — known-answer vectors")
emit("expectedCtPublicExp",  rsa_ct.to_bytes(128, 'big'))
emit("expectedCtPrivateExp", rsa_sig.to_bytes(128, 'big'))
