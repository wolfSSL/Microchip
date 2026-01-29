# write_size.cmake
#
# Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfBoot.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#/


# Args: -DINPUT=... -DOUT=... -DTOOLCHAIN_SIZE=...
execute_process(
    COMMAND "${TOOLCHAIN_SIZE}" "${INPUT}"
    OUTPUT_VARIABLE SIZE_OUT
    RESULT_VARIABLE RC
)
if(NOT RC EQUAL 0)
    message(FATAL_ERROR "size failed with code ${RC}")
endif()

# Echo to console (so you still see it in the build log)
message("${SIZE_OUT}")

# Save to file
file(WRITE "${OUT}" "${SIZE_OUT}")
