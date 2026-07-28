# wolfPSA Host Target

This target configuration is intended to run the PSA Architecture Test Suite
against the wolfPSA implementation on a Linux host.

- **WDT**: Lacks functionality to recover after a hang; the hooks return
  success or failure without any reset recovery.

- **NVMEM**: Stores data in an in-memory array, so contents are lost between
  runs because it is not non-volatile.

- The test harness expects the wolfPSA static library to be provided via
  `-DPSA_CRYPTO_LIB_FILENAME` and the headers via `-DPSA_INCLUDE_PATHS`.

## License

wolfPSA is Copyright (c) 2026 wolfSSL Inc. and it's distributed under GPLv3 License.

Arm PSA test suite components remain under the Apache 2.0 License.
