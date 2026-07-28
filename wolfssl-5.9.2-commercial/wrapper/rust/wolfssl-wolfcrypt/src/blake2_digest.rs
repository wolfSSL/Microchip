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
RustCrypto `digest` trait implementations for the wolfCrypt BLAKE2 hash
types.

Because BLAKE2b and BLAKE2s have variable digest sizes, this module exposes
typed wrappers that pin the digest size of an underlying [`crate::blake2`]
instance to a specific value, matching the typed aliases provided by the
RustCrypto `blake2` crate (`Blake2b512`, `Blake2b256`, `Blake2s256`, etc.).

Each typed wrapper implements the traits from the `digest` crate
(`HashMarker`, `OutputSizeUser`, `BlockSizeUser`, `Update`, `Reset`,
`FixedOutput`, and `FixedOutputReset`). With these implementations the
`digest::Digest` trait becomes available via its blanket implementation,
allowing these hashers to be used anywhere a RustCrypto `Digest` is
accepted.

Any failure returned by the underlying wolfCrypt call in a trait method
will result in a panic, matching the infallible signatures required by the
RustCrypto traits.
*/

use digest::consts::{U16, U24, U32, U48, U64, U128};

macro_rules! impl_blake2_digest {
    (
        $(#[$attr:meta])*
        $name:ident,
        wc_ty = $wc_ty:path,
        digest_size = $digest_size:literal,
        out = $out_size:ty,
        block = $block_size:ty
    ) => {
        $(#[$attr])*
        pub struct $name {
            blake2: $wc_ty,
        }

        $(#[$attr])*
        impl Default for $name {
            fn default() -> Self {
                Self {
                    blake2: <$wc_ty>::new($digest_size)
                        .expect("wolfCrypt BLAKE2 init failed"),
                }
            }
        }

        $(#[$attr])*
        impl digest::HashMarker for $name {}

        $(#[$attr])*
        impl digest::OutputSizeUser for $name {
            type OutputSize = $out_size;
        }

        $(#[$attr])*
        impl digest::block_api::BlockSizeUser for $name {
            type BlockSize = $block_size;
        }

        $(#[$attr])*
        impl digest::Update for $name {
            fn update(&mut self, data: &[u8]) {
                <$wc_ty>::update(&mut self.blake2, data)
                    .expect("wolfCrypt BLAKE2 update failed");
            }
        }

        $(#[$attr])*
        impl digest::Reset for $name {
            fn reset(&mut self) {
                self.blake2 = <$wc_ty>::new($digest_size)
                    .expect("wolfCrypt BLAKE2 init failed");
            }
        }

        $(#[$attr])*
        impl digest::FixedOutput for $name {
            fn finalize_into(mut self, out: &mut digest::Output<Self>) {
                <$wc_ty>::finalize(&mut self.blake2, out.as_mut_slice())
                    .expect("wolfCrypt BLAKE2 finalize failed");
            }
        }

        $(#[$attr])*
        impl digest::FixedOutputReset for $name {
            fn finalize_into_reset(&mut self, out: &mut digest::Output<Self>) {
                <$wc_ty>::finalize(&mut self.blake2, out.as_mut_slice())
                    .expect("wolfCrypt BLAKE2 finalize failed");
                self.blake2 = <$wc_ty>::new($digest_size)
                    .expect("wolfCrypt BLAKE2 init failed");
            }
        }
    };
}

impl_blake2_digest! {
    #[cfg(blake2b)]
    Blake2b256,
    wc_ty = crate::blake2::BLAKE2b,
    digest_size = 32,
    out = U32,
    block = U128
}

impl_blake2_digest! {
    #[cfg(blake2b)]
    Blake2b384,
    wc_ty = crate::blake2::BLAKE2b,
    digest_size = 48,
    out = U48,
    block = U128
}

impl_blake2_digest! {
    #[cfg(blake2b)]
    Blake2b512,
    wc_ty = crate::blake2::BLAKE2b,
    digest_size = 64,
    out = U64,
    block = U128
}

impl_blake2_digest! {
    #[cfg(blake2s)]
    Blake2s128,
    wc_ty = crate::blake2::BLAKE2s,
    digest_size = 16,
    out = U16,
    block = U64
}

impl_blake2_digest! {
    #[cfg(blake2s)]
    Blake2s192,
    wc_ty = crate::blake2::BLAKE2s,
    digest_size = 24,
    out = U24,
    block = U64
}

impl_blake2_digest! {
    #[cfg(blake2s)]
    Blake2s256,
    wc_ty = crate::blake2::BLAKE2s,
    digest_size = 32,
    out = U32,
    block = U64
}
