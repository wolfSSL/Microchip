/* paging.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef WOLFBOOT_64BIT
#include <stdint.h>
/* build 1:1 virtual mapping in the range from 0 to top_address, return the root
 * of the memory mapping in the **cr3 register */
int x86_paging_build_identity_mapping(uint64_t top_address,
                                      uint8_t *page_table);
/* if not already mapped, map virtual address range (address, address + size)
 * using new physical memory */
int x86_paging_map_range(uint64_t address, uint32_t size);
int x86_paging_get_page_table_size();
int x86_paging_set_page_table();

#if !defined(BUILD_LOADER_STAGE1)
int x86_paging_map_memory(uint64_t va, uint64_t pa, uint32_t size);
int x86_paging_dump_info();
#endif /* !BUILD_LOADER_STAGE1 */

#endif /* WOLFBOOT_64BIT */
