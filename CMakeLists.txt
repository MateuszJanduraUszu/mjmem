# CMakeLists.txt

# Copyright (c) Mateusz Jandura. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.21.0)
project(mjmem_library LANGUAGES CXX)

# check if the platform architecture is supported
if(NOT CMAKE_GENERATOR_PLATFORM MATCHES "^x64$|^Win32$")
    message(FATAL_ERROR "The MJMEM library can only be built for x64 and x86 architectures.")
endif()

option(BUILD_BENCHMARKS "Build MJMEM benchmarks" OFF)
option(BUILD_TESTS "Build MJMEM tests" OFF)

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks "${CMAKE_BINARY_DIR}/benchmarks")
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests "${CMAKE_BINARY_DIR}/tests")
endif()

add_subdirectory(src)