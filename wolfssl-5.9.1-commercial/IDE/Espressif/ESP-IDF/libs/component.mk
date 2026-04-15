#
# Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfSSL.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#

#
# Component Makefile
#

COMPONENT_ADD_INCLUDEDIRS := . ./include

COMPONENT_ADD_INCLUDEDIRS += "$ENV{IDF_PATH}/components/freertos/include/freertos"
# COMPONENT_ADD_INCLUDEDIRS += "$ENV{IDF_PATH}/soc/esp32s3/include/soc"

COMPONENT_SRCDIRS := src wolfcrypt/src
COMPONENT_SRCDIRS += wolfcrypt/src/port/Espressif
COMPONENT_SRCDIRS += wolfcrypt/src/port/atmel
COMPONENT_SRCDIRS += wolfcrypt/benchmark
COMPONENT_SRCDIRS += wolfcrypt/test

CFLAGS +=-DWOLFSSL_USER_SETTINGS

COMPONENT_OBJEXCLUDE := wolfcrypt/src/aes_asm.o
COMPONENT_OBJEXCLUDE += wolfcrypt/src/evp.o
COMPONENT_OBJEXCLUDE += wolfcrypt/src/misc.o
COMPONENT_OBJEXCLUDE += src/bio.o
