/* mqttport.c
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfMQTT.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/* Include the autoconf generated config.h */
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include "wolfmqtt/mqtt_client.h"
#include "examples/mqttnet.h"
#include "examples/mqttexample.h"
#include "examples/mqttport.h"

#ifdef WOLFMQTT_ZEPHYR

#ifndef NO_FILESYSTEM
#ifndef WOLFSSL_ZEPHYR
XFILE z_fs_open(const char* filename, const char* mode)
{
    XFILE file;
    fs_mode_t flags = 0;

    if (mode == NULL)
        return NULL;

    /* Parse mode */
    switch (*mode++) {
        case 'r':
            flags |= FS_O_READ;
            break;
        case 'w':
            flags |= FS_O_WRITE|FS_O_CREATE;
            break;
        case 'a':
            flags |= FS_O_APPEND|FS_O_CREATE;
            break;
        default:
            return NULL;
    }

    /* Ignore binary flag */
    if (*mode == 'b')
        mode++;
    if (*mode == '+') {
        flags |= FS_O_READ;
        /* Don't add write flag if already appending */
        if (!(flags & FS_O_APPEND))
            flags |= FS_O_RDWR;
    }
    /* Ignore binary flag */
    if (*mode == 'b')
        mode++;
    /* Incorrect mode string */
    if (*mode != '\0')
        return NULL;

    file = (XFILE)WOLFMQTT_MALLOC(sizeof(*file));
    if (file != NULL) {
        if (fs_open(file, filename, flags) != 0) {
            WOLFMQTT_FREE(file);
            file = NULL;
        }
    }

    return file;
}

int z_fs_close(XFILE file)
{
    int ret;

    if (file == NULL)
        return -1;
    ret = (fs_close(file) == 0) ? 0 : -1;

    WOLFMQTT_FREE(file);

    return ret;
}
#endif /* !WOLFSSL_ZEPHYR */
#endif /* !NO_FILESYSTEM */

#else

/* Default implementations */

#endif
