/* fsp.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */
#ifndef FSP_H
#define FSP_H

#include <x86/fsp/FspCommon.h>

int fsp_info_header_is_ok(struct fsp_info_header *hdr);
int fsp_get_image_revision(struct fsp_info_header *h, int *build,
                                  int *rev, int *maj, int *min);
void print_fsp_image_revision(struct fsp_info_header *h);
void fsp_init_silicon(void);

#endif /* FSP_H */
