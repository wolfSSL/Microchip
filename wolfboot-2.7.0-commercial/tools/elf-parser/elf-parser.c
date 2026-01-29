/* elf-parser.c
 *
 * Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include "wolfboot/wolfboot.h"
#include "printf.h"
#include "string.h"
#include "elf.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ret = 0;
    uint8_t *image = NULL;
    size_t imageSz = 0;
    FILE *f = NULL;
    uintptr_t entry = 0;
    const char* filename = "wolfboot.elf";

    if (argc >= 2) {
        filename = argv[1];
    }

    printf("ELF Parser:\n");

    /* open and load key buffer */
    f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Open file %s failed!\n", filename);
        ret = -1;
    }
    if (ret == 0) {
        fseek(f, 0, SEEK_END);
        imageSz = ftell(f);
        fseek(f, 0, SEEK_SET);
        image = malloc(imageSz);
        if (image == NULL) {
            printf("Allocate %lu failed!\n", imageSz);
            ret = -1;
        }
    }
    if (ret == 0) {
        size_t readSz = fread(image, 1, imageSz, f);
        if (readSz != imageSz) {
            printf("File read error! %lu\n", readSz);
            ret = -1;
        }
    }
    fclose(f);

    if (ret == 0) {
        ret = elf_load_image_mmu(image, &entry, NULL);
    }

    printf("Return %d, Load %p\n", ret, (void*)entry);

    free(image);

    return ret;
}
