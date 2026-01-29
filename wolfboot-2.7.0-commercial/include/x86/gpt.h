/* gpt.h
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifndef GPT_H
#define GPT_H
int disk_open(int drv);
int disk_read(int drv, int part, uint64_t off, uint64_t sz, uint8_t *buf);
int disk_write(int drv, int part, uint64_t off, uint64_t sz, const uint8_t *buf);
int disk_find_partition_by_label(int drv, const char *label);
#endif
