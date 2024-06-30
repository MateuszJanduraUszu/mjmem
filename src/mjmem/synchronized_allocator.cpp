// synchronized_allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <mjmem/impl/utils.hpp>
#include <mjmem/synchronized_allocator.hpp>
#include <type_traits>

namespace mjx {
    synchronized_allocator::synchronized_allocator(allocator& _Al) noexcept
        : _Mywrapped(_Al), _Mylock{0} {}

    synchronized_allocator::~synchronized_allocator() noexcept {}

    synchronized_allocator::pointer synchronized_allocator::allocate(const size_type _Count) {
        mjmem_impl::_Lock_guard<false> _Guard(&_Mylock);
        return _Mywrapped.allocate(_Count);
    }

    synchronized_allocator::pointer
        synchronized_allocator::allocate_aligned(const size_type _Count, const size_type _Align) {
        mjmem_impl::_Lock_guard<false> _Guard(&_Mylock);
        return _Mywrapped.allocate_aligned(_Count, _Align);
    }

    void synchronized_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        mjmem_impl::_Lock_guard<false> _Guard(&_Mylock);
        _Mywrapped.deallocate(_Ptr, _Count);
    }

    synchronized_allocator::size_type synchronized_allocator::max_size() const noexcept {
        mjmem_impl::_Lock_guard<true> _Guard(&_Mylock);
        return _Mywrapped.max_size();
    }

    bool synchronized_allocator::is_equal(const allocator& _Other) const noexcept {
        // cast to a pointer to avoid a bad_cast exception
        const synchronized_allocator* const _Other_ptr =
            dynamic_cast<const synchronized_allocator*>(::std::addressof(_Other));
        if (!_Other_ptr) {
            return false;
        }

        mjmem_impl::_Lock_guard<true> _Guard(&_Mylock);
        return _Mywrapped.is_equal(_Other_ptr->_Mywrapped);
    }
} // namespace mjx