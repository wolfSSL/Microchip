/* gdt.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef GDT_H
#define GDT_H

#define GDT_DS (0x08)
#define GDT_CS_32BIT (0x10)
#define GDT_CS_64BIT (0x18)
#define GDT_CS_32BIT_COMPAT (0x20)

int gdt_setup_table(void);
int gdt_update_segments(void);

#endif /* GDT_H */
