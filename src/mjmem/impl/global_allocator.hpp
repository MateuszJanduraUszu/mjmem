// global_allocator.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_IMPL_GLOBAL_ALLOCATOR_HPP_
#define _MJMEM_IMPL_GLOBAL_ALLOCATOR_HPP_
#include <atomic>
#include <mjmem/allocator.hpp>
#include <mjmem/dynamic_allocator.hpp>
#include <type_traits>

namespace mjx {
    namespace mjmem_impl {
        class _Global_alloc { // singleton class that stores the global allocator
        public:
            ~_Global_alloc() noexcept {}

            _Global_alloc(const _Global_alloc&)            = delete;
            _Global_alloc& operator=(const _Global_alloc&) = delete;

            static _Global_alloc& _Instance() noexcept {
                static _Global_alloc _Obj;
                return _Obj;
            }

            allocator& _Get() noexcept {
                return *_Myal.load(::std::memory_order_relaxed);
            }

            void _Set(allocator& _New_al) noexcept {
                _Myal.store(::std::addressof(_New_al), ::std::memory_order_relaxed);
            }

        private:
            _Global_alloc() noexcept : _Mydef(), _Myal(&_Mydef) {}

            dynamic_allocator _Mydef; // the default allocator that has no state or associated resource
            ::std::atomic<allocator*> _Myal; // pointer to the currently used allocator
        };
    } // namespace mjmem_impl
} // namespace mjx

#endif // _MJMEM_IMPL_GLOBAL_ALLOCATOR_HPP_