// global_allocator.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_IMPL_GLOBAL_ALLOCATOR_HPP_
#define _MJMEM_IMPL_GLOBAL_ALLOCATOR_HPP_
#include <mjmem/allocator.hpp>
#include <mjmem/heap_allocator.hpp>
#include <new>

namespace mjx {
    namespace mjmem_impl {
        struct _Alloc_pair { // stores normal and shared allocators
            _Alloc_pair() noexcept : _Default(), _Normal(_Default), _Shared(_Default) {}

            heap_allocator _Default; // the default allocator that has no state or associated resource
            allocator& _Normal; // reference to one of heap_allocator, bitmap_allocator or pool_allocator
            shared_allocator _Shared; // wraps _Normal to make allocation/deallocation thread-safe
        };

        class _Global_alloc { // singleton class that stores global allocator
        public:
            ~_Global_alloc() noexcept {}

            _Global_alloc(const _Global_alloc&)            = delete;
            _Global_alloc& operator=(const _Global_alloc&) = delete;

            static _Global_alloc& _Instance() noexcept {
                static _Global_alloc _Obj;
                return _Obj;
            }

            void _Set(allocator& _New_al) noexcept {
                _Mypair._Normal = _New_al;
                _Mypair._Shared.bind(_New_al);
            }

            allocator& _Get() noexcept {
                return _Mypair._Normal;
            }

            shared_allocator& _Get_shared() noexcept {
                return _Mypair._Shared;
            }

        private:
            _Global_alloc() noexcept : _Mypair() {}

            _Alloc_pair _Mypair;
        };
    } // namespace mjmem_impl
} // namespace mjx

#endif // _MJMEM_IMPL_GLOBAL_ALLOCATOR_HPP_