# CMakeLists.txt

# Copyright (c) Mateusz Jandura. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.21.0)

set(MJMEM_INC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/api.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/block_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/dynamic_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/endian.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/exception.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/object_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/pool_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/pool_resource.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/smart_pointer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/synchronized_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/version.hpp"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/allocation_tracking.hpp"    
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/bitops.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/dllmain.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/global_allocator.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/rwlock.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/tinywin.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/impl/utils.hpp"
)
set(MJMEM_RES_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/mjmem/res/mjmem.rc"
)

# Note: These definitions are the core macros for all MJX modules. Since the MJMEM module
#       is the base for all modules, the macros are defined here. However, if this changes
#       in the future, move the definitions to the module which becomes the base for all modules.
set(MJX_BASE_DEFS)

# detect the platform and set the corresponding macro, terminate if the platform is not recognized
if(WIN32)
    list(APPEND MJX_BASE_DEFS _MJX_WINDOWS=1)
elseif(UNIX)
    list(APPEND MJX_BASE_DEFS _MJX_LINUX=1)
else()
    # unsupported platform, report an error and terminate
    message(FATAL_ERROR "Unsupported platform detected.")
endif()

# detect the compiler and set the corresponding macro, terminate if the compiler is not recognized
set(is_clang FALSE)
set(is_gcc FALSE)
set(is_msvc FALSE)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(is_clang TRUE)
    list(APPEND MJX_BASE_DEFS _MJX_CLANG=1)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(is_gcc TRUE)
    list(APPEND MJX_BASE_DEFS _MJX_GCC=1)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(is_msvc TRUE)
    list(APPEND MJX_BASE_DEFS _MJX_MSVC=1)
else()
    # unrecognized compiler, report an error and terminate
    message(FATAL_ERROR "Detected unregonized compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# detect the architecture and set the corresponding macro (never fails)
if(${MJX_PLATFORM_ARCH} STREQUAL "x64")
    list(APPEND MJX_BASE_DEFS _MJX_X64=1)
elseif(${MJX_PLATFORM_ARCH} STREQUAL "x86")
    list(APPEND MJX_BASE_DEFS _MJX_X86=1)
endif()

# detect the byte order and set the corresponding macro, terminate if unable to detect the byte order
if(CMAKE_CXX_BYTE_ORDER STREQUAL "LITTLE_ENDIAN")
    list(APPEND MJX_BASE_DEFS _MJX_LITTLE_ENDIAN=1)
elseif(CMAKE_CXX_BYTE_ORDER STREQUAL "BIG_ENDIAN")
    list(APPEND MJX_BASE_DEFS _MJX_BIG_ENDIAN=1)
else()
    # failed to detect the byte order, report an error and terminate
    message(FATAL_ERROR "Byte order could not be detected.")
endif()

# detect support for 128-bit integers and set the corresponding macro (definitely not supported on MSVC)
if(${is_clang} OR ${is_gcc})
    # use check_cxx_source_compiles() to detect whether a program that uses 128-bit integers will compile
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles([=[
        using _Int128_t  = __int128;
        using _Uint128_t = unsigned __int128;
        static_assert(sizeof(_Int128_t) == 16, "128-bit integer size mismatch");
        static_assert(sizeof(_Uint128_t) == 16, "128-bit integer size mismatch");

        int main() {
            return 0;
        }
    ]=] int128_supported)
    if(${int128_supported})
        # 128-bit integers are supported, append the corresponding macro
        list(APPEND MJX_BASE_DEFS _MJX_INT128_SUPPORTED=1)
    endif()
endif()

# organize source files into directories for better readability
source_group("src" FILES ${MJMEM_INC_FILES} ${MJMEM_SRC_FILES})
source_group("src/impl" FILES ${MJMEM_IMPL_FILES})
source_group("res" FILES ${MJMEM_RES_FILES})

# add the MJMEM shared library and adjust its properties
add_library(mjmem SHARED ${MJMEM_INC_FILES} ${MJMEM_SRC_FILES} ${MJMEM_IMPL_FILES})
target_compile_definitions(mjmem PRIVATE _MJMEM_BUILD=1 PUBLIC ${MJX_BASE_DEFS})
target_compile_features(mjmem PRIVATE cxx_std_20)
target_include_directories(mjmem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(mjmem PROPERTIES PREFIX "") # prevent compilers from adding "lib" prefix
if(${is_clang})
    # add '-fsized-deallocation' flag to enable sized operator delete
    target_compile_options(mjmem PUBLIC -fsized-deallocation)
endif()

# Note: GCC doesn't generates LIB files, as it uses its own archive files. To maintain compatibility
#       between compilers, it must generate a LIB file. To do so, 'pexports' and 'dlltool' tools can be used,
#       the first one to generate definition file (DEF), and the second one to generate a LIB file.
if(${is_gcc} AND WIN32)
    set(target_dir "$<TARGET_FILE_DIR:mjmem>")
    add_custom_command(TARGET mjmem POST_BUILD
        COMMAND pexports ${target_dir}/mjmem.dll > ${target_dir}/mjmem.def
        COMMAND dlltool -d ${target_dir}/mjmem.def -l ${target_dir}/mjmem.lib
    )
    unset(target_dir)
endif()

# Note: RC files are used only on Windows and are compiled with rc.exe (MSVC), windres.exe (GCC),
#       or llvm-windres.exe (Clang). Therefore, they are included only when compiling for Windows.
if(WIN32)
    target_sources(mjmem PRIVATE ${MJMEM_RES_FILES})
endif()

if(MJMEM_INSTALL_LIBRARY)
    if(NOT DEFINED CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        # set the install prefix to the default path
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Path to install directory" FORCE)
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
    install(FILES ${MJMEM_INC_FILES} DESTINATION "inc/mjmem")
    if(${is_gcc} AND WIN32)
        # copy manually generated mjmem.lib to the installation directory
        install(FILES "$<TARGET_FILE_DIR:mjmem>/mjmem.lib" DESTINATION "bin/$<CONFIG>")
    endif()
endif()