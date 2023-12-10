// heap_allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <mjmem/exception.hpp>
#include <mjmem/heap_allocator.hpp>
#include <mjmem/impl/utils.hpp>
#include <new>

namespace mjx {
    heap_allocator::heap_allocator() noexcept {}

    heap_allocator::heap_allocator(const heap_allocator&) noexcept {}

    heap_allocator::heap_allocator(heap_allocator&&) noexcept {}

    heap_allocator::~heap_allocator() noexcept {}

    heap_allocator& heap_allocator::operator=(const heap_allocator&) noexcept {
        return *this;
    }

    heap_allocator& heap_allocator::operator=(heap_allocator&&) noexcept {
        return *this;
    }

    heap_allocator::pointer heap_allocator::allocate(const size_type _Count) {
        void* const _Ptr = ::operator new(_Count, ::std::nothrow);
        if (!_Ptr) { // allocation failed, raise an exception
            allocation_failure::raise();
        }

        return _Ptr;
    }

    heap_allocator::pointer heap_allocator::allocate_aligned(const size_type _Count, const size_type _Align) {
#ifdef _DEBUG
        _INTERNAL_ASSERT(mjmem_impl::_Is_pow_of_2(_Align), "alignment must be a power of 2");
#endif // _DEBUG
        void* const _Ptr = ::operator new(mjmem_impl::_Align_value(_Count, _Align), ::std::nothrow);
        if (!_Ptr) { // allocation failed, raise an exception
            allocation_failure::raise();
        }

        return _Ptr;
    }

    void heap_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        ::operator delete(_Ptr, _Count);
    }

    heap_allocator::size_type heap_allocator::max_size() const noexcept {
        return static_cast<size_type>(-1);
    }

    bool heap_allocator::is_equal(const allocator&) const noexcept {
        return true; // always equal
    }
} // namespace mjx