// utils.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_IMPL_UTILS_HPP_
#define _MJMEM_IMPL_UTILS_HPP_
#include <crtdbg.h>
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
            return _Value > 0 && (_Value & (_Value - 1)) == 0;
        }

        constexpr size_t _Align_value(const size_t _Value, const size_t _Align) noexcept {
            return (_Value + _Align - 1) & ~(_Align - 1);
        }
    } // namespace mjmem_impl
} // namespace mjx

#endif // _MJMEM_IMPL_UTILS_HPP_