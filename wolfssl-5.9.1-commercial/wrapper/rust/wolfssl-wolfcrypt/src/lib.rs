/*
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#![no_std]

/* bindgen-generated bindings to the C library */
pub mod sys;

pub mod aes;
pub mod blake2;
pub mod chacha20_poly1305;
pub mod cmac;
pub mod curve25519;
pub mod dh;
pub mod dilithium;
pub mod ecc;
pub mod ed25519;
pub mod ed448;
pub mod fips;
pub mod hkdf;
pub mod hmac;
pub mod kdf;
pub mod lms;
pub mod mlkem;
pub mod prf;
pub mod random;
pub mod rsa;
pub mod sha;

/// Initialize resources used by wolfCrypt.
///
/// # Returns
///
/// Returns either Ok(()) on success or Err(e) containing the wolfSSL
/// library error code value.
///
/// # Example
///
/// ```rust
/// use wolfssl_wolfcrypt::*;
/// wolfcrypt_init().expect("Error with wolfcrypt_init()");
/// // ... use the library ...
/// wolfcrypt_cleanup().expect("wolfCrypt_Cleanup failed");
/// ```
pub fn wolfcrypt_init() -> Result<(), i32> {
    let rc = unsafe { sys::wolfCrypt_Init() };
    if rc != 0 {
        return Err(rc);
    }
    Ok(())
}

/// Clean up resources used by wolfCrypt.
///
/// # Returns
///
/// Returns either Ok(()) on success or Err(e) containing the wolfSSL
/// library error code value.
///
/// See also: [`wolfcrypt_init`]
pub fn wolfcrypt_cleanup() -> Result<(), i32> {
    let rc = unsafe { sys::wolfCrypt_Cleanup() };
    if rc != 0 {
        return Err(rc);
    }
    Ok(())
}
