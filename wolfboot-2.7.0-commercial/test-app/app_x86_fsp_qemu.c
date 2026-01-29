/* app_x86_fsp_qemu.c
 *
 * Test bare-metal boot application
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */


#ifdef TARGET_x86_fsp_qemu

#include <printf.h>
#include <stdint.h>

struct mb2_header {
    uint32_t magic;
    uint32_t architecture;
    uint32_t header_length;
    uint32_t checksum;
} __attribute__((__packed__));

struct mb2_tag_info_req {
    uint16_t type;
    uint16_t flags;
    uint32_t size;
    uint32_t mbi_tag_types[2];
} __attribute__((__packed__));

struct multiboot_header {
    struct mb2_header hdr;
    struct mb2_tag_info_req req;
} __attribute__((__packed__));

__attribute__((aligned(8))) struct multiboot_header mbh = {
    .hdr.magic = 0xe85250d6,
    .hdr.architecture = 0,
    .hdr.checksum = 0,
    .hdr.header_length = sizeof(struct mb2_header),
    .req.type = 1,
    .req.flags = 0,
    .req.size = sizeof(struct mb2_tag_info_req),
    /* basic mem info */
    .req.mbi_tag_types[0] = 4,
    /* mem map */
    .req.mbi_tag_types[1] = 6,
};

void start()
{
    wolfBoot_printf("wolfBoot QEMU x86 FSP test app\r\n");
    __asm__ ("hlt\r\n");
}
#endif
