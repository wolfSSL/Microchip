# wolfCrypt benchmark via wolfPSA (PSA backend)

This benchmark binary runs wolfCrypt benchmarks through the PSA backend
(`WOLFSSL_HAVE_PSA`) using wolfPSA loaded at runtime with `dlopen`.

## Build

By default this expects a sibling `wolfssl` checkout (relative to the
wolfPSA root). The benchmark compiles wolfCrypt sources directly from
`../wolfssl/wolfcrypt/src` (no `libwolfssl.a` link) and uses the
`user_settings.h` in this directory (wolfCrypt-only build).

```sh
# Build wolfPSA (shared library)
make -C wolfPSA

# Build the benchmark (uses wolfssl sources directly)
make -C wolfPSA/test/wolfcrypt-benchmark \
  WOLFPSA_PATH=wolfPSA \
  WOLFSSL_PATH=../wolfssl
```

If `libwolfpsa.so` is not in your loader path, pass it explicitly to dlopen:

```sh
export WOLFPSA_LIB=/path/to/libwolfpsa.so
```

## Run

```sh
# Optionally point dlopen to libwolfpsa.so
export WOLFPSA_LIB=/path/to/libwolfpsa.so

./wolfPSA/test/wolfcrypt-psa-benchmark -?
./wolfPSA/test/wolfcrypt-psa-benchmark
```

## Debugging / Verification

To confirm crypto calls are flowing through the PSA API, run with `ltrace` and
look for `psa_*` calls:

```sh
ltrace -e 'psa_*' ./wolfPSA/test/wolfcrypt-psa-benchmark -aes-cbc
```
