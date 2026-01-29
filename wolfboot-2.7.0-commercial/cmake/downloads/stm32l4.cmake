# wolfboot/cmake/downloads/stm32l4.cmake
#
# Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfBoot.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#

# The STM32L4 is known to need additional HAL source files:
add_download(
    NAME st_hal
    URL  https://github.com/STMicroelectronics/stm32l4xx_hal_driver.git
    TAG  v1.13.5
)

add_download(
    NAME cmsis_dev
    URL  https://github.com/STMicroelectronics/cmsis_device_l4.git
    TAG  v1.7.4
)

add_download(
    NAME cmsis_core
    URL  https://github.com/ARM-software/CMSIS_5.git
    TAG  5.9.0
)
