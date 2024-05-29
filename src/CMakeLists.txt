# CMakeLists.txt

# Copyright (c) Mateusz Jandura. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.21.0)

set(MJMEM_INC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/api.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/block_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/dynamic_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/exception.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/object_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/pool_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/pool_resource.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/smart_pointer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/synchronized_allocator.hpp"
)
set(MJMEM_SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/allocator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/block_allocator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/dynamic_allocator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/exception.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/pool_allocator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/pool_resource.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/smart_pointer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/synchronized_allocator.cpp"
)
set(MJMEM_IMPL_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/global_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/tinywin.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/utils.hpp"
)
set(MJMEM_RES_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/res/mjmem.rc"
)

# organize source files into directories for better readability
source_group("src" FILES ${MJMEM_INC_FILES} ${MJMEM_SRC_FILES})
source_group("src/impl" FILES ${MJMEM_IMPL_FILES})
source_group("res" FILES ${MJMEM_RES_FILES})

# add the MJMEM shared library and adjust its properties
add_library(mjmem SHARED ${MJMEM_INC_FILES} ${MJMEM_SRC_FILES} ${MJMEM_IMPL_FILES} ${MJMEM_RES_FILES})
target_compile_definitions(mjmem PRIVATE _MJMEM_BUILD=1)
target_compile_features(mjmem PRIVATE cxx_std_20)
target_include_directories(mjmem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(INSTALL_MJMEM)
    if(NOT DEFINED CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        # set the install prefix to the default path
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/rules/mjmem" CACHE PATH "Path to install directory" FORCE)
    endif()

    install(TARGETS mjmem
        EXPORT mjmem-config
        RUNTIME DESTINATION "bin/$<CONFIG>"
        LIBRARY DESTINATION "bin/$<CONFIG>"
        ARCHIVE DESTINATION "bin/$<CONFIG>"
    )
    install(EXPORT mjmem-config
        DESTINATION "cmake/mjmem"
        NAMESPACE mjx::
    )
    install(FILES ${MJMEM_INC_FILES} DESTINATION inc)
endif()