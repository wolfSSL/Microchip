# component.mk
#
# Copyright (C) 2006-2025 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfMQTT.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#
#
# This file is for legacy build systems only

CFLAGS += -DWOLFSSL_USER_SETTINGS
CFLAGS += -DWOLFMQTT_USER_SETTINGS

COMPONENT_ADD_INCLUDEDIRS := . ./include

COMPONENT_ADD_INCLUDEDIRS += "$ENV{IDF_PATH}/components/freertos/include/freertos"
# COMPONENT_ADD_INCLUDEDIRS += "$ENV{IDF_PATH}/components/soc/esp32s3/include/soc"

COMPONENT_SRCDIRS := src ../wolfssl/wolfcrypt/src
COMPONENT_SRCDIRS += ../wolfssl/wolfcrypt/src/port/Espressif
COMPONENT_SRCDIRS += ../wolfssl/wolfcrypt/src/port/atmel

CFLAGS +=-DWOLFSSL_USER_SETTINGS

COMPONENT_OBJEXCLUDE := ../wolfssl/wolfcrypt/src/aes_asm.o
COMPONENT_OBJEXCLUDE += ../wolfssl/wolfcrypt/src/evp.o
COMPONENT_OBJEXCLUDE += ../wolfssl/wolfcrypt/src/misc.o
COMPONENT_OBJEXCLUDE += src/bio.o