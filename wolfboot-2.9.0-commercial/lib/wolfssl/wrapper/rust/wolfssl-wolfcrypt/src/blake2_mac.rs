/*
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*!
RustCrypto `digest::Mac` trait implementations for the wolfCrypt keyed
BLAKE2 types.

These wrappers cover keyed BLAKE2 (the construction exposed by RustCrypto's
`blake2` crate as `Blake2bMac` / `Blake2sMac`), not the wolfCrypt-specific
HMAC-BLAKE2 construction. With these implementations the `digest::Mac`
trait becomes available via its blanket implementation, allowing these
types to be used anywhere a RustCrypto `Mac` is accepted.

Each typed wrapper pins the digest size and the maximum key size to a
specific algorithm parameterization. The `Blake2sMac128`, `Blake2sMac192`,
and `Blake2sMac256` wrappers all accept keys of any length up to 32 bytes
(the BLAKE2s maximum), and the `Blake2bMac512` wrapper accepts keys of any
length up to 64 bytes (the BLAKE2b maximum), matching the variable-length
key behavior of the RustCrypto `blake2` crate's `Blake2sMac` / `Blake2bMac`
types.

Any failure returned by the underlying wolfCrypt call in a trait method
will result in a panic, matching the infallible signatures required by the
RustCrypto traits.
*/

use digest::consts::{U16, U24, U32, U48, U64};

macro_rules! impl_blake2_mac {
    (
        $(#[$attr:meta])*
        $name:ident,
        wc_ty = $wc_ty:path,
        digest_size = $digest_size:literal,
        out = $out_size:ty,
        key = $key_size:ty
    ) => {
        $(#[$attr])*
        pub struct $name {
            blake2: $wc_ty,
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
                    blake2: <$wc_ty>::new_with_key($digest_size, key.as_slice())
                        .expect("wolfCrypt BLAKE2 init failed"),
                }
            }

            fn new_from_slice(key: &[u8]) -> Result<Self, digest::InvalidLength> {
                if key.len() > <Self as digest::common::KeySizeUser>::key_size() {
                    return Err(digest::InvalidLength);
                }
                Ok(Self {
                    blake2: <$wc_ty>::new_with_key($digest_size, key)
                        .map_err(|_| digest::InvalidLength)?,
                })
            }
        }

        $(#[$attr])*
        impl digest::Update for $name {
            fn update(&mut self, data: &[u8]) {
                <$wc_ty>::update(&mut self.blake2, data)
                    .expect("wolfCrypt BLAKE2 update failed");
            }
        }

        $(#[$attr])*
        impl digest::FixedOutput for $name {
            fn finalize_into(mut self, out: &mut digest::Output<Self>) {
                <$wc_ty>::finalize(&mut self.blake2, out.as_mut_slice())
                    .expect("wolfCrypt BLAKE2 finalize failed");
            }
        }
    };
}

impl_blake2_mac! {
    #[cfg(blake2b)]
    Blake2bMac256,
    wc_ty = crate::blake2::BLAKE2b,
    digest_size = 32,
    out = U32,
    key = U64
}

impl_blake2_mac! {
    #[cfg(blake2b)]
    Blake2bMac384,
    wc_ty = crate::blake2::BLAKE2b,
    digest_size = 48,
    out = U48,
    key = U64
}

impl_blake2_mac! {
    #[cfg(blake2b)]
    Blake2bMac512,
    wc_ty = crate::blake2::BLAKE2b,
    digest_size = 64,
    out = U64,
    key = U64
}

impl_blake2_mac! {
    #[cfg(blake2s)]
    Blake2sMac128,
    wc_ty = crate::blake2::BLAKE2s,
    digest_size = 16,
    out = U16,
    key = U32
}

impl_blake2_mac! {
    #[cfg(blake2s)]
    Blake2sMac192,
    wc_ty = crate::blake2::BLAKE2s,
    digest_size = 24,
    out = U24,
    key = U32
}

impl_blake2_mac! {
    #[cfg(blake2s)]
    Blake2sMac256,
    wc_ty = crate::blake2::BLAKE2s,
    digest_size = 32,
    out = U32,
    key = U32
}
