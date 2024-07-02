// dynamic_allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/exception.hpp>
#include <mjmem/impl/utils.hpp>
#include <new>

namespace mjx {
    dynamic_allocator::dynamic_allocator() noexcept {}

    dynamic_allocator::dynamic_allocator(const dynamic_allocator&) noexcept {}

    dynamic_allocator::dynamic_allocator(dynamic_allocator&&) noexcept {}

    dynamic_allocator::~dynamic_allocator() noexcept {}

    dynamic_allocator& dynamic_allocator::operator=(const dynamic_allocator&) noexcept {
        return *this;
    }

    dynamic_allocator& dynamic_allocator::operator=(dynamic_allocator&&) noexcept {
        return *this;
    }

    dynamic_allocator::pointer dynamic_allocator::allocate(const size_type _Count) {
        if (_Count == 0) { // no allocation, do nothing
            return nullptr;
        }

        void* const _Ptr = ::operator new(_Count, ::std::nothrow);
        if (!_Ptr) { // allocation failed, raise an exception
            allocation_failure::raise();
        }

        return _Ptr;
    }

    dynamic_allocator::pointer dynamic_allocator::allocate_aligned(const size_type _Count, const size_type _Align) {
        if (_Count == 0) { // no allocation, do nothing
            return nullptr;
        }

#ifdef _DEBUG
        _INTERNAL_ASSERT(mjmem_impl::_Is_pow_of_2(_Align), "alignment must be a power of 2");
#endif // _DEBUG
        void* const _Ptr = ::operator new(mjmem_impl::_Align_value(_Count, _Align), ::std::nothrow);
        if (!_Ptr) { // allocation failed, raise an exception
            allocation_failure::raise();
        }

        return _Ptr;
    }

    void dynamic_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        if (_Ptr && _Count > 0) {
            ::operator delete(_Ptr, _Count);
        }
    }

    dynamic_allocator::size_type dynamic_allocator::max_size() const noexcept {
        return static_cast<size_type>(-1);
    }

    bool dynamic_allocator::is_equal(const allocator& _Other) const noexcept {
        // cast to a pointer to avoid a bad_cast exception
        return dynamic_cast<const dynamic_allocator*>(::std::addressof(_Other)) != nullptr;
    }
} // namespace mjx