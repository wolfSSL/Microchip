# POSIX SHM DMA Transport

## Overview

There are two independent features at play in the POSIX SHM transport port. Understanding which is which is key.

## 1. The Transport: POSIX Shared Memory (`posix_transport_shm`)

This is purely a **transport layer** -- it moves request/response messages between client and server processes. It works like this:

- **Server** creates a POSIX shared memory object (`shm_open`) with a layout of:
  ```
  [ 64-byte header | request buffer | response buffer | optional DMA section ]
  ```
- **Client** opens the same named object and `mmap`s it into its address space
- Both sides then delegate to `wh_transport_mem` (the generic memory-based transport) for actual message passing via CSR registers in the request/response buffers
- The header contains PIDs for RT-signal-based async notification

The transport's job is **only** to shuttle serialized request/response packets. It knows nothing about crypto, keys, or DMA semantics.

The optional **DMA section** at the end of the shared memory region is the transport providing a chunk of shared address space that *both* processes can access. This is just raw shared memory -- the transport allocates it but doesn't use it itself. It's plumbing for the DMA feature.

## 2. The Feature: DMA (`WOLFHSM_CFG_DMA`)

DMA is a **separate, transport-agnostic feature** in wolfHSM core (`wh_dma.h`, `wh_server_dma.c`, `wh_client_dma.c`). It allows crypto operations to reference client memory **by address** rather than copying data into the transport's request/response buffers. This matters because:

- Standard messages are limited by `WOLFHSM_CFG_COMM_DATA_LEN` (typically ~4KB)
- DMA messages send *addresses* in the request, and the server reads/writes client memory directly

The DMA feature has a callback-based architecture:
- `wh_Server_DmaProcessClientAddress()` -- server calls this with a client address, the registered callback transforms it to something the server can dereference
- `wh_Client_DmaProcessClientAddress()` -- client calls this to transform its local address into whatever the server will receive in the message
- PRE/POST operations handle setup and teardown (cache flush/invalidate, temporary buffer allocation, etc.)

On real hardware (e.g. Infineon TC3xx), this is literal hardware DMA -- client and server are on different cores with different address maps, and the callbacks handle the MMU/bus address translation.

## 3. The Glue: Static Memory Pool Allocator in the SHM DMA Callbacks

The `posixTransportShm_ClientStaticMemDmaCallback` and `posixTransportShm_ServerStaticMemDmaCallback` in `posix_transport_shm.c` are the **port-specific DMA callbacks** that bridge the POSIX SHM transport with the DMA feature. Here's the clever part:

**Problem:** On POSIX, client and server are separate processes with separate virtual address spaces. A raw client pointer like `0x7fff12345000` means nothing to the server. But the DMA section in shared memory is mapped into *both* processes (at potentially different virtual addresses).

**Solution using the pool allocator:**

1. wolfCrypt's `WOLFSSL_STATIC_MEMORY` pool allocator (`wc_LoadStaticMemory_ex`) is initialized with the DMA section as its backing memory pool
2. When the client DMA callback gets a PRE operation with a client address that's **not** already in the DMA area, it:
   - Allocates a temporary buffer from the pool (`XMALLOC` with the heap hint)
   - Copies client data into it
   - Returns an **offset** from the DMA base (not a pointer) -- this is what gets sent to the server
3. The server DMA callback simply takes that offset, validates it's in bounds, and returns `dma_base + offset`
4. On POST, the client callback copies results back (for writes) and frees the temporary buffer

If the client address **is already** in the DMA section (the client allocated directly from the pool), it skips the copy and just computes the offset -- zero-copy.

The pool allocator here is used as a **bump/slab allocator for the shared DMA region**. It has nothing to do with the transport itself -- it's the DMA callback's strategy for managing the shared buffer. wolfHSM could use a different allocator; the pool allocator was chosen because it's already available in wolfCrypt and works without `malloc`.

## Summary Table

| Aspect | Transport (SHM) | DMA Feature | Pool Allocator |
|--------|-----------------|-------------|----------------|
| **Layer** | Communication | Application/Crypto | Memory management |
| **Scope** | Port-specific (POSIX) | Core wolfHSM | DMA callback impl detail |
| **Purpose** | Move request/response packets | Let server access client memory by address | Manage temporary buffers in shared DMA area |
| **Config** | `posixTransportShmConfig` | `WOLFHSM_CFG_DMA` | `WOLFSSL_STATIC_MEMORY` |
| **Without it** | No communication | Data must fit in request/response buffers | Would need a different allocator for DMA region |

The DMA section is **allocated by the transport** but **used by the DMA callbacks**. The pool allocator is **used by the DMA callbacks** to subdivide that DMA section. Three layers, three concerns.
