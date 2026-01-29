# utils.cmake
#
# Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfBoot.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com


# Ensure this file is only included and initialized once
if(CMAKE_VERSION VERSION_LESS 3.10)
    # Fallback path for older CMake
    if(DEFINED UTILS_CMAKE_INCLUDED)
        return()
    endif()
else()
    include_guard(GLOBAL)
endif()

# --------------------------------------------------------------------------------------------------
# Utility for properly installing a file output regardless of if the current configuration is multi
# config or not
# --------------------------------------------------------------------------------------------------

macro(multiConfigFileInstall FILE_OUT DESTINATION)
    # check for multi-config
    get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(isMultiConfig)
        install(
            FILES ${CMAKE_CURRENT_BINARY_DIR}/Debug/${FILE_OUT}
            CONFIGURATIONS Debug
            DESTINATION ${DESTINATION})
        install(
            FILES ${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/${FILE_OUT}
            CONFIGURATIONS RelWithDebInfo
            DESTINATION ${DESTINATION})
        install(
            FILES ${CMAKE_CURRENT_BINARY_DIR}/Release/${FILE_OUT}
            CONFIGURATIONS Release
            DESTINATION ${DESTINATION})
        install(
            FILES ${CMAKE_CURRENT_BINARY_DIR}/MinSizeRel/${FILE_OUT}
            CONFIGURATIONS MinSizeRel
            DESTINATION ${DESTINATION})
    else()
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${FILE_OUT} DESTINATION ${DESTINATION})
    endif()
endmacro()

# --------------------------------------------------------------------------------------------------
# Utility for creating MCU binary outputs
# --------------------------------------------------------------------------------------------------
macro(gen_bin_target_outputs TARGET)
    get_filename_component(FILENAME ${TARGET} NAME_WE)

    # Create bin from elf target
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}.bin"
        COMMAND "${TOOLCHAIN_OBJCOPY}"
                -O binary "$<TARGET_FILE:${TARGET}>"
                "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}.bin"
        DEPENDS ${TARGET}
        VERBATIM
    )
    list(APPEND TARGET_OUTPUTS ${FILENAME}.bin)

    # Print size of bin target
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}.size"
        DEPENDS ${TARGET}
        COMMAND "${CMAKE_COMMAND}"
                -DTOOLCHAIN_SIZE=${TOOLCHAIN_SIZE}
                -DINPUT=$<TARGET_FILE:${TARGET}>
                -DOUT=${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}.size
                -P "${SIZE_SCRIPT}"
        VERBATIM
    )
    list(APPEND TARGET_OUTPUTS ${FILENAME}.size)

    # Add top level target for all MCU standard outputs
    add_custom_target(${FILENAME}_outputs ALL DEPENDS ${TARGET_OUTPUTS})
endmacro()

set(UTILS_CMAKE_INCLUDED true)
