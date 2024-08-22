# CMakeLists.txt

# Copyright (c) Mateusz Jandura. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.21.0)
project(mjmem_tests LANGUAGES CXX)

# build Google Test as a static library before building any tests
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(google-test "${CMAKE_CURRENT_BINARY_DIR}/google-test" EXCLUDE_FROM_ALL)

function(add_isolated_test test_name test_path)
    # create an executable for the specified test, linking against necessary libraries
    add_executable(${test_name} ${test_path})
    target_compile_features(${test_name} PRIVATE cxx_std_20)
    target_include_directories(${test_name} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
        "${gtest_SOURCE_DIR}/include"
    )
    target_link_libraries(${test_name} PRIVATE gtest gtest_main mjmem)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

add_isolated_test(test_allocators_compatibility "src/allocators_compatibility/test.cpp")
add_isolated_test(test_bitops "src/bitops/test.cpp")
add_isolated_test(test_block_allocator "src/block_allocator/test.cpp")
add_isolated_test(test_dynamic_allocator "src/dynamic_allocator/test.cpp")
add_isolated_test(test_endian "src/endian/test.cpp")
add_isolated_test(test_global_allocator "src/global_allocator/test.cpp")
add_isolated_test(test_pool_allocator "src/pool_allocator/test.cpp")
add_isolated_test(test_pool_resource "src/pool_resource/test.cpp")
add_isolated_test(test_reference_counter "src/reference_counter/test.cpp")
add_isolated_test(test_smart_array "src/smart_array/test.cpp")
add_isolated_test(test_smart_ptr "src/smart_ptr/test.cpp")
add_isolated_test(test_synchronized_allocator "src/synchronized_allocator/test.cpp")
add_isolated_test(test_unique_smart_array "src/unique_smart_array/test.cpp")
add_isolated_test(test_unique_smart_ptr "src/unique_smart_ptr/test.cpp")
add_isolated_test(test_version_encoding "src/version_encoding/test.cpp")

# use a custom target to combine all targets into a single one,
# this allows only one post-build call instead of per-test copying
add_custom_target(mjmem_and_tests ALL DEPENDS
    mjmem
    test_allocators_compatibility
    test_bitops
    test_block_allocator
    test_dynamic_allocator
    test_endian
    test_global_allocator
    test_pool_allocator
    test_pool_resource
    test_reference_counter
    test_smart_array
    test_smart_ptr
    test_synchronized_allocator
    test_unique_smart_array
    test_unique_smart_ptr
    test_version_encoding
)
add_custom_command(TARGET mjmem_and_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:mjmem>"
    "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>" # copy to the tests' output directory
)