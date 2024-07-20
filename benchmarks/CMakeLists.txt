# CMakeLists.txt

# Copyright (c) Mateusz Jandura. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.21.0)
project(mjmem_benchmarks LANGUAGES CXX)

# build Google Benchmark before building any benchmarks
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
add_subdirectory(google-benchmark "${CMAKE_BINARY_DIR}/google-benchmark" EXCLUDE_FROM_ALL)

function(copy_files_required_for_benchmark benchmark_name)
    # copy all required files to the output directory of the specified benchmark
    add_custom_command(TARGET ${benchmark_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:mjmem>"
        "$<TARGET_FILE_DIR:${benchmark_name}>"
    )
endfunction()

function(add_isolated_benchmark benchmark_name benchmark_path)
    # create an executable for the specified benchmark, linking against necessary libraries
    add_executable(${benchmark_name} ${benchmark_path})
    target_compile_definitions(${benchmark_name} PRIVATE BENCHMARK_STATIC_DEFINE)
    target_compile_features(${benchmark_name} PRIVATE cxx_std_20)
    target_include_directories(${benchmark_name} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
        "${benchmark_SOURCE_DIR}/include"
    )
    target_link_libraries(${benchmark_name} PRIVATE benchmark::benchmark mjmem Shlwapi)
    copy_files_required_for_benchmark(${benchmark_name})
endfunction()

add_isolated_benchmark(benchmark_bitops "src/bitops/benchmark.cpp")
add_isolated_benchmark(benchmark_block_allocator "src/block_allocator/benchmark.cpp")
add_isolated_benchmark(benchmark_pool_allocator "src/pool_allocator/benchmark.cpp")