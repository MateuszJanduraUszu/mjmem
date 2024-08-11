// utils.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_IMPL_UTILS_HPP_
#define _MJMEM_IMPL_UTILS_HPP_
#include <cstddef>
#ifdef _MJX_WINDOWS
#include <crtdbg.h>
#else // ^^^ _MJX_WINDOWS ^^^ / vvv _MJX_LINUX vvv
#include <cstdio>
#include <cstdlib>
#endif // _MJX_WINDOWS

// generic assertion macros, useful in debug mode
#ifdef _MJX_WINDOWS
#define _REPORT_ERROR(_Msg) ::_CrtDbgReport(_CRT_ERROR, __FILE__, __LINE__, nullptr, _Msg)
#else // ^^^ _MJX_WINDOWS ^^^ / vvv _MJX_LINUX vvv
#define _REPORT_ERROR(_Msg)                                                              \
    ::fprintf(stderr, "%s:%d: %s: %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, _Msg); \
    ::abort()
#endif // _MJX_WINDOWS

#define _INTERNAL_ASSERT(_Cond, _Msg) \
    if (!(_Cond)) {                   \
        _REPORT_ERROR(_Msg);          \
    }

namespace mjx {
    namespace mjmem_impl {
        constexpr bool _Is_pow_of_2(const size_t _Value) noexcept {
            // check if the given value is a power of 2 (only one bit is set)
            return _Value > 0 && (_Value & (_Value - 1)) == 0;
        }

        constexpr size_t _Align_value(const size_t _Value, const size_t _Align) noexcept {
            // align the given value to the nearest multiple of the given alignment
            return (_Value + _Align - 1) & ~(_Align - 1);
        }
        
        inline void* _Adjust_address_by_offset(void* const _Base_address, const size_t _Off) noexcept {
            // create a new address by moving the base address by the given offset
            return static_cast<void*>(static_cast<unsigned char*>(_Base_address) + _Off);
        }

        inline size_t _Calculate_offset_from_address(
            const void* const _Base_address, const void* const _Address) noexcept {
            // retrieve the offset used to create a new address from the base address
            return static_cast<const unsigned char*>(_Address) - static_cast<const unsigned char*>(_Base_address);
        }

        inline bool _Is_memory_block_in_address_range(const void* const _Range_begin,
            const void* const _Range_end, const void* const _Block_begin, const void* const _Block_end) noexcept {
            // check whether the memory block is within the address range
            return _Block_begin >= _Range_begin && _Block_end <= _Range_end;
        }
    } // namespace mjmem_impl
} // namespace mjx

#endif // _MJMEM_IMPL_UTILS_HPP_