/* mynewt_port.c
 *
 * Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#ifdef WOLFSSL_APACHE_MYNEWT

#ifndef NO_FILESYSTEM

#include "fs/fs.h"
#define FILE struct fs_file

FILE* mynewt_fopen(const char * restrict path, const char * restrict mode)
{
    FILE *file;
    uint8_t access_flags = 0;
    const char *p = mode;

    while (*p != '\0') {
        switch(*p) {
            case 'r':
                access_flags |= FS_ACCESS_READ;
                if(*(p+1) == '+') {
                    access_flags |= FS_ACCESS_WRITE;
                }
                break;

            case 'w':
                access_flags |= (FS_ACCESS_WRITE | FS_ACCESS_TRUNCATE);
                if(*(p+1) == '+') {
                    access_flags |= FS_ACCESS_READ;
                }
                break;

            case 'a':
                access_flags |= (FS_ACCESS_WRITE | FS_ACCESS_APPEND);
                if(*(p+1) == '+') {
                    access_flags |= FS_ACCESS_READ;
                }
                break;
        }
        p++;
    }

    /* Open the file for reading/writing/appending. */
    int rc = fs_open(path, access_flags, &file);
    if (rc != 0) {
        return NULL;
    }
    return file;
}

int mynewt_fseek(FILE *stream, long offset, int whence)
{
    uint32_t fs_offset;
    long signed_pos;

    switch (whence) {
        case 0: /* SEEK_SET */
            if (offset < 0)
                return -1;
            fs_offset = (uint32_t)offset;
            break;

        case 1: /* SEEK_CUR */
            fs_offset = fs_getpos(stream);
            if ((int32_t)fs_offset < 0) {
                return -1;
            }
            signed_pos = (long)fs_offset + offset;
            if (signed_pos < 0)
                return -1;
            fs_offset = (uint32_t)signed_pos;
            break;

        case 2: /* SEEK_END */
            if (fs_filelen(stream, &fs_offset) != 0) {
                return -1;
            }
            signed_pos = (long)fs_offset + offset;
            if (signed_pos < 0)
                return -1;
            fs_offset = (uint32_t)signed_pos;
            break;

        default:
            return -1;
    }

    if (fs_seek(stream, fs_offset) != 0) {
        return -1;
    }

    return 0;
}

long mynewt_ftell(FILE *stream)
{
    return (long)fs_getpos(stream);
}

void mynewt_rewind(FILE *stream)
{
    fs_seek(stream, 0);
}

size_t mynewt_fread(void *restrict ptr, size_t size, size_t nitems,
                    FILE *restrict stream)
{
    size_t to_read;
    uint32_t read_size;
    int rc;

    if (size == 0 || nitems == 0 || nitems > SIZE_MAX / size)
        return 0;

    to_read = size * nitems;
    rc = fs_read(stream, to_read, ptr, &read_size);
    if (rc != 0) {
        return 0;
    }

    return (size_t)(read_size / size);
}

size_t mynewt_fwrite(const void *restrict ptr, size_t size, size_t nitems,
                     FILE *restrict stream)
{
    size_t to_write;
    int rc;

    if (size == 0 || nitems == 0 || nitems > SIZE_MAX / size)
        return 0;

    to_write = size * nitems;
    rc = fs_write(stream, ptr, to_write);
    if (rc != 0) {
        return 0;
    }

    return nitems;
}

int mynewt_fclose(FILE *stream)
{
    if (fs_close(stream) != 0) {
        return EOF;
    }
    return 0;
}

#endif /* !NO_FILESYSTEM */
#endif /* WOLFSSL_APACHE_MYNEWT */
