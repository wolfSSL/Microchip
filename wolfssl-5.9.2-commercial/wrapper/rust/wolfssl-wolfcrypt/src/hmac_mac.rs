/*
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*!
RustCrypto `digest::Mac` trait implementations for the wolfCrypt HMAC types.

This module provides typed HMAC wrappers with implementations of the traits
from the `digest` crate (`MacMarker`, `KeyInit`, `Update`, `FixedOutput`)
for each supported hash algorithm. With these implementations the
`digest::Mac` trait becomes available via its blanket implementation,
allowing these HMAC types to be used anywhere a RustCrypto `Mac` is accepted.

Any failure returned by the underlying wolfCrypt call in a trait method will
result in a panic, matching the infallible signatures required by the
RustCrypto traits.
*/

use digest::consts::{
    U20, U28, U32, U48, U64, U72, U104, U128, U136, U144,
};

macro_rules! impl_hmac_mac {
    (
        $(#[$attr:meta])*
        $name:ident, hmac_type = $hmac_type:expr, key = $key_size:ty, out = $out_size:ty
    ) => {
        $(#[$attr])*
        #[derive(Clone)]
        pub struct $name {
            hmac: crate::hmac::HMAC,
        }

        $(#[$attr])*
        impl digest::MacMarker for $name {}

        $(#[$attr])*
        impl digest::OutputSizeUser for $name {
            type OutputSize = $out_size;
        }

        $(#[$attr])*
        impl digest::common::KeySizeUser for $name {
            type KeySize = $key_size;
        }

        $(#[$attr])*
        impl digest::KeyInit for $name {
            fn new(key: &digest::Key<Self>) -> Self {
                Self {
                    hmac: crate::hmac::HMAC::new($hmac_type, key.as_slice())
                        .expect("wolfCrypt HMAC init failed"),
                }
            }

            fn new_from_slice(key: &[u8]) -> Result<Self, digest::InvalidLength> {
                crate::hmac::HMAC::new($hmac_type, key)
                    .map(|hmac| Self { hmac })
                    .map_err(|_| digest::InvalidLength)
            }
        }

        $(#[$attr])*
        impl digest::Update for $name {
            fn update(&mut self, data: &[u8]) {
                crate::hmac::HMAC::update(&mut self.hmac, data)
                    .expect("wolfCrypt HMAC update failed");
            }
        }

        $(#[$attr])*
        impl digest::FixedOutput for $name {
            fn finalize_into(mut self, out: &mut digest::Output<Self>) {
                crate::hmac::HMAC::finalize(&mut self.hmac, out.as_mut_slice())
                    .expect("wolfCrypt HMAC finalize failed");
            }
        }
    };
}

impl_hmac_mac! {
    #[cfg(sha)]
    HmacSha, hmac_type = crate::hmac::HMAC::TYPE_SHA, key = U64, out = U20
}

impl_hmac_mac! {
    #[cfg(sha224)]
    HmacSha224, hmac_type = crate::hmac::HMAC::TYPE_SHA224, key = U64, out = U28
}

impl_hmac_mac! {
    #[cfg(sha256)]
    HmacSha256, hmac_type = crate::hmac::HMAC::TYPE_SHA256, key = U64, out = U32
}

impl_hmac_mac! {
    #[cfg(sha384)]
    HmacSha384, hmac_type = crate::hmac::HMAC::TYPE_SHA384, key = U128, out = U48
}

impl_hmac_mac! {
    #[cfg(sha512)]
    HmacSha512, hmac_type = crate::hmac::HMAC::TYPE_SHA512, key = U128, out = U64
}

#[cfg(sha512_224)]
impl_hmac_mac! {
    #[cfg(sha512_224)]
    HmacSha512_224, hmac_type = crate::hmac::HMAC::TYPE_SHA512_224, key = U128, out = U28
}

#[cfg(sha512_256)]
impl_hmac_mac! {
    #[cfg(sha512_256)]
    HmacSha512_256, hmac_type = crate::hmac::HMAC::TYPE_SHA512_256, key = U128, out = U32
}

impl_hmac_mac! {
    #[cfg(sha3)]
    HmacSha3_224, hmac_type = crate::hmac::HMAC::TYPE_SHA3_224, key = U144, out = U28
}

impl_hmac_mac! {
    #[cfg(sha3)]
    HmacSha3_256, hmac_type = crate::hmac::HMAC::TYPE_SHA3_256, key = U136, out = U32
}

impl_hmac_mac! {
    #[cfg(sha3)]
    HmacSha3_384, hmac_type = crate::hmac::HMAC::TYPE_SHA3_384, key = U104, out = U48
}

impl_hmac_mac! {
    #[cfg(sha3)]
    HmacSha3_512, hmac_type = crate::hmac::HMAC::TYPE_SHA3_512, key = U72, out = U64
}
