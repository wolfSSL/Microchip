# wolfboot/cmake/functions.cmake
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
    # Fallback path for older CMake, and anything else that wants to detect is loaded
    if(DEFINED FUNCTIONS_CMAKE_INCLUDED)
        return()
    endif()
    set(FUNCTIONS_CMAKE_INCLUDED TRUE)
else()
    include_guard(GLOBAL)
endif()

function(override_cache VAR VAL)
    get_property(VAR_STRINGS CACHE ${VAR} PROPERTY STRINGS)
    LIST(FIND VAR_STRINGS ${VAL} CK)
    if(-1 EQUAL ${CK})
        message(SEND_ERROR
            "\"${VAL}\" is not valid override value for \"${VAR}\"."
            " Please select value from \"${VAR_STRINGS}\"\n")
    endif()
    set_property(CACHE ${VAR} PROPERTY VALUE ${VAL})
endfunction()

function(add_option NAME HELP_STRING DEFAULT VALUES)
    # Set the default value for the option.
    set(${NAME} ${DEFAULT} CACHE STRING ${HELP_STRING})
    # Set the list of allowed values for the option.
    set_property(CACHE ${NAME} PROPERTY STRINGS ${VALUES})

    if(DEFINED ${NAME})
        list(FIND VALUES ${${NAME}} IDX)
        #
        # If the given value isn't in the list of allowed values for the option,
        # reduce it to yes/no according to CMake's "if" logic:
        # https://cmake.org/cmake/help/latest/command/if.html#basic-expressions
        #
        # This has no functional impact; it just makes the settings in
        # CMakeCache.txt and cmake-gui easier to read.
        #
        if (${IDX} EQUAL -1)
            if(${${NAME}})
                override_cache(${NAME} "yes")
            else()
                override_cache(${NAME} "no")
            endif()
        endif()
    endif()
endfunction()

function(print_env VAR)
    if(DEFINED ENV{${VAR}} AND NOT "$ENV{${VAR}}" STREQUAL "")
        message(STATUS "${VAR} = $ENV{${VAR}}")
    else()
        message(STATUS "${VAR} = (not set)")
    endif()
endfunction()

# Sets <var_name> to <value_expr>.
# If <value_expr> points to an existing directory, prints a STATUS message.
function(set_and_echo_dir var_name value_expr)
    set(_val "${value_expr}")
    # Export to caller's scope
    set(${var_name} "${_val}" PARENT_SCOPE)

    if(IS_DIRECTORY "${_val}")
        message(STATUS "-- set ${var_name}; Found directory: ${_val}")
    else()
        message(STATUS "-- Warning: set ${var_name}")
        message(STATUS "-- !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
        message(STATUS "-- Directory not found: ${_val}")
        message(STATUS "-- !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
    endif()
endfunction()

set(FUNCTIONS_CMAKE_INCLUDED true)
