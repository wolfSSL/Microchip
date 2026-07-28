# wolfPSA tests

This directory contains standalone tests and demos for wolfPSA integration.

## Tests

- `psa_api_test`
  - Standalone test for PSA Crypto API calls.
  - Source: `psa_server/psa_api_test.c`

- `wolfcrypt-psa-benchmark`
  - wolfCrypt benchmark that loads `libwolfpsa.so` at runtime and exercises
    PSA-backed code paths via `WOLFSSL_HAVE_PSA`.
  - Source: `wolfcrypt-benchmark/main.c` (build uses local wolfCrypt sources).

- `psa_tls_server` + `psa_tls_client`
  - TLS server built with wolfPSA, and a static client built from wolfSSL
    sources (`psa_server/tls_client`).
  - Demonstrates PSA ECC callbacks (sign/verify/ECDH) on the server during the
    TLS handshake.
  - Mutual authentication is enabled. The server pulls its own certificate and
    key from the PSA store and also validates the client certificate against a
    PSA-stored copy (certificate pinning).
  - Shows PSA Store usage using the POSIX PSA store backed by the filesystem
    (see `.store/` under this directory).

## Build

```sh
make -C wolfPSA/test
```

## Run

```sh
# Run the PSA API test
./wolfPSA/test/psa_api_test

# Run the wolfCrypt PSA benchmark
./wolfPSA/test/wolfcrypt-psa-benchmark

# Run the TLS server + client demo (mutual auth, PSA store)
./wolfPSA/test/run_psa_tls_server_client.sh
```
