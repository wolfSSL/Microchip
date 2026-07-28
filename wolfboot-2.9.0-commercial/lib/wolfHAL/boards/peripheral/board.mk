# board.mk
#
# Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfBoot.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#

_PERIPHERAL_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

BOARD_SOURCE += $(_PERIPHERAL_DIR)/peripheral.c

ifneq ($(filter sdhc_spi_sdcard32gb,$(PERIPHERALS)),)
CFLAGS += -DPERIPHERAL_SDHC_SPI_SDCARD32GB
BOARD_SOURCE += $(_PERIPHERAL_DIR)/block/sdhc_spi_sdcard32gb.c
BOARD_SOURCE += $(WHAL_DIR)/src/block/sdhc_spi_block.c
endif

ifneq ($(filter spi_nor_w25q64,$(PERIPHERALS)),)
CFLAGS += -DPERIPHERAL_SPI_NOR_W25Q64
BOARD_SOURCE += $(_PERIPHERAL_DIR)/flash/spi_nor_w25q64.c
BOARD_SOURCE += $(WHAL_DIR)/src/flash/spi_nor_flash.c
endif

ifneq ($(filter bmi270,$(PERIPHERALS)),)
CFLAGS += -DPERIPHERAL_BMI270
BOARD_SOURCE += $(_PERIPHERAL_DIR)/sensor/imu/bmi270.c
BOARD_SOURCE += $(WHAL_DIR)/src/sensor/imu/bmi270_sensor.c
endif
