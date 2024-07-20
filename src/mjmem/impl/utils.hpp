// utils.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_IMPL_UTILS_HPP_
#define _MJMEM_IMPL_UTILS_HPP_
#include <crtdbg.h>
#include <cstddef>
#include <mjmem/impl/tinywin.hpp>

// generic assert macro, useful in debug mode
#define _INTERNAL_ASSERT(_Cond, _Msg)                                   \
    if (!(_Cond)) {                                                     \
        ::_CrtDbgReport(_CRT_ERROR, __FILE__, __LINE__, nullptr, _Msg); \
    }

namespace mjx {
    namespace mjmem_impl {
        template <bool _Shared>
        class _Lock_guard { // RAII class for SRWLOCK
        public:
            constexpr _Lock_guard(void* const _Lock) noexcept : _Mylock(static_cast<SRWLOCK*>(_Lock)) {
                if constexpr (_Shared) {
                    ::AcquireSRWLockShared(_Mylock);
                } else {
                    ::AcquireSRWLockExclusive(_Mylock);
                }
            }

            constexpr ~_Lock_guard() noexcept {
                if constexpr (_Shared) {
                    ::ReleaseSRWLockShared(_Mylock);
                } else {
                    ::ReleaseSRWLockExclusive(_Mylock);
                }
            }

        private:
            SRWLOCK* _Mylock;
        };

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