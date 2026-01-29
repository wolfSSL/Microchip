# wolfboot/cmake/current_user.cmake
#
# Copyright (C) 2014-2025 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfBoot.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#
# get_current_user(<OUT_VAR>)
# Sets <OUT_VAR> to the best guess of the current user across Windows, Linux, macOS, and WSL.

# Example usage
#   get_current_user(CURRENT_USER)
#   message(STATUS "Current user detected: ${CURRENT_USER}")

# Ensure this file is only included and initialized once
if(CMAKE_VERSION VERSION_LESS 3.10)
    # Fallback path for older CMake, and anything else that wants to detect is loaded
    if(DEFINED CURRENT_USER_CMAKE_INCLUDED)
        return()
    endif()
else()
    include_guard(GLOBAL)
endif()

function(get_current_user OUT_VAR)
  set(_user "")

  # Fast path from environment
  foreach(var USER USERNAME LOGNAME)
    if(DEFINED ENV{${var}} AND NOT "$ENV{${var}}" STREQUAL "")
      set(_user "$ENV{${var}}")
      break()
    endif()
  endforeach()

  # Windows specific fallbacks (native Win or WSL)
  if(_user STREQUAL "")
    if(WIN32 OR DEFINED ENV{WSL_DISTRO_NAME})
      # Try PowerShell first
      execute_process(
        COMMAND powershell -NoProfile -Command "$env:USERNAME"
        OUTPUT_VARIABLE _user
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
      )
      if(_user STREQUAL "")
        # Fallback to cmd.exe
        execute_process(
          COMMAND cmd.exe /c echo %USERNAME%
          OUTPUT_VARIABLE _user
          ERROR_QUIET
        )
        string(REPLACE "\r" "" _user "${_user}")
        string(STRIP "${_user}" _user)
      endif()
    endif()
  endif()

  # POSIX fallbacks
  if(_user STREQUAL "")
    execute_process(
      COMMAND id -un
      OUTPUT_VARIABLE _user
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
    )
  endif()
  if(_user STREQUAL "")
    execute_process(
      COMMAND whoami
      OUTPUT_VARIABLE _user
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
    )
  endif()

  # Last resort: CI hints or placeholder
  if(_user STREQUAL "")
    foreach(var GITHUB_ACTOR BUILD_USER USERNAME USER LOGNAME)
      if(DEFINED ENV{${var}} AND NOT "$ENV{${var}}" STREQUAL "")
        set(_user "$ENV{${var}}")
        break()
      endif()
    endforeach()
  endif()
  if(_user STREQUAL "")
    set(_user "unknown")
  endif()

  set(${OUT_VAR} "${_user}" PARENT_SCOPE)
endfunction()

set(CURRENT_USER_CMAKE_INCLUDED true)
