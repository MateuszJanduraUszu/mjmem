// allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <mjmem/allocator.hpp>
#include <mjmem/impl/global_allocator.hpp>
#include <mjmem/impl/utils.hpp>

namespace mjx {
    allocator::allocator() noexcept {}

    allocator::allocator(const allocator&) noexcept {}

    allocator::allocator(allocator&&) noexcept {}

    allocator::~allocator() noexcept {}

    allocator& allocator::operator=(const allocator&) noexcept {
        return *this;
    }

    allocator& allocator::operator=(allocator&&) noexcept {
        return *this;
    }

    bool operator==(const allocator& _Left, const allocator& _Right) noexcept {
        return _Left.is_equal(_Right);
    }

    bool operator!=(const allocator& _Left, const allocator& _Right) noexcept {
        return !_Left.is_equal(_Right);
    }

    shared_allocator::shared_allocator(allocator& _Al) noexcept : _Myal(_Al), _Mylock{0} {}

    shared_allocator::~shared_allocator() noexcept {}

    shared_allocator::pointer shared_allocator::allocate(const size_type _Count) {
        mjmem_impl::_Lock_guard<false> _Guard(&_Mylock);
        return _Myal.allocate(_Count);
    }

    shared_allocator::pointer
        shared_allocator::allocate_aligned(const size_type _Count, const size_type _Align) {
        mjmem_impl::_Lock_guard<false> _Guard(&_Mylock);
        return _Myal.allocate_aligned(_Count, _Align);
    }

    void shared_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        mjmem_impl::_Lock_guard<false> _Guard(&_Mylock);
        _Myal.deallocate(_Ptr, _Count);
    }

    shared_allocator::size_type shared_allocator::max_size() const noexcept {
        mjmem_impl::_Lock_guard<true> _Guard(&_Mylock);
        return _Myal.max_size();
    }

    void shared_allocator::bind(allocator& _New_al) noexcept {
        mjmem_impl::_Lock_guard<false> _Guard(&_Mylock);
        _Myal = _New_al;
    }

    void set_allocator(allocator& _New_al) noexcept {
        mjmem_impl::_Global_alloc::_Instance()._Set(_New_al);
    }

    allocator& get_allocator() noexcept {
        return mjmem_impl::_Global_alloc::_Instance()._Get();
    }

    shared_allocator& get_shared_allocator() noexcept {
        return mjmem_impl::_Global_alloc::_Instance()._Get_shared();
    }
} // namespace mjx