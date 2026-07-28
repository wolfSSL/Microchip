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

#[cfg(feature = "alloc")]
extern crate alloc;

/* bindgen-generated bindings to the C library */
pub mod sys;

/// Zeroize the raw bytes of a value. For use in `zeroize()` methods on C FFI
/// structs where `#[derive(Zeroize)]` cannot be used.
///
/// # Safety
///
/// `val` must be a valid, initialized value whose entire `size_of_val` byte
/// representation is safe to overwrite with zeroes.
pub(crate) unsafe fn zeroize_raw<T>(val: &mut T) {
    use zeroize::Zeroize;
    unsafe {
        core::slice::from_raw_parts_mut(
            val as *mut T as *mut u8,
            core::mem::size_of_val(val),
        ).zeroize();
    }
}

pub mod aes;
pub mod blake2;
#[cfg(all(any(blake2b, blake2s), feature = "digest"))]
pub mod blake2_digest;
#[cfg(all(any(blake2b, blake2s), feature = "mac"))]
pub mod blake2_mac;
pub mod chacha20_poly1305;
pub mod cmac;
#[cfg(all(cmac, feature = "mac"))]
pub mod cmac_mac;
pub mod curve25519;
pub mod dh;
pub mod dilithium;
pub mod ecc;
#[cfg(feature = "signature")]
pub mod ecdsa;
pub mod ed25519;
pub mod ed448;
pub mod fips;
pub mod hkdf;
pub mod hmac;
#[cfg(all(hmac, feature = "mac"))]
pub mod hmac_mac;
pub mod kdf;
pub mod lms;
pub mod mlkem;
#[cfg(all(feature = "kem", mlkem))]
pub mod mlkem_kem;
pub mod prf;
pub mod random;
pub mod rsa;
#[cfg(rsa_oaep)]
pub mod rsa_oaep;
#[cfg(feature = "signature")]
pub mod rsa_pkcs1v15;
pub mod sha;
#[cfg(all(feature = "password-hash", hmac, kdf_pbkdf2))]
pub mod pbkdf2_password_hash;
#[cfg(all(feature = "password-hash", kdf_scrypt))]
pub mod scrypt_password_hash;
#[cfg(feature = "digest")]
pub mod sha_digest;

/// Convert a buffer length to `u32`, returning `BUFFER_E` if it overflows.
pub(crate) fn buffer_len_to_u32(len: usize) -> Result<u32, i32> {
    u32::try_from(len).map_err(|_| sys::wolfCrypt_ErrorCodes_BUFFER_E)
}

/// Convert a buffer length to `i32`, returning `BUFFER_E` if it overflows.
pub(crate) fn buffer_len_to_i32(len: usize) -> Result<i32, i32> {
    i32::try_from(len).map_err(|_| sys::wolfCrypt_ErrorCodes_BUFFER_E)
}

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
