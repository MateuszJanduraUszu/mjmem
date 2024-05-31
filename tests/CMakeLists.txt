# CMakeLists.txt

# Copyright (c) Mateusz Jandura. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.21.0)
project(mjmem_tests LANGUAGES CXX)

# build Google Test as a static library before building any tests
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(google-test "${CMAKE_BINARY_DIR}/google-test" EXCLUDE_FROM_ALL)

function(copy_files_required_for_test test_name)
    # copy all required files to the output directory of the specified test
    add_custom_command(TARGET ${test_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_BINARY_DIR}/mjmem/$<CONFIG>/mjmem.dll"
        "$<TARGET_FILE_DIR:${test_name}>"
    )
endfunction()

function(add_isolated_test test_name test_path)
    # create an executable for the specified test, linking against necessary libraries
    add_executable(${test_name} ${test_path})
    target_compile_features(${test_name} PRIVATE cxx_std_20)
    target_include_directories(${test_name} PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        "${gtest_SOURCE_DIR}/include"
    )
    target_link_libraries(${test_name} PRIVATE gtest gtest_main mjmem)
    add_test(NAME ${test_name} COMMAND ${test_name})
    copy_files_required_for_test(${test_name})
endfunction()

add_isolated_test(smart_array "src/smart_array/test.cpp")