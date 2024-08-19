// allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <mjmem/allocator.hpp>
#include <mjmem/impl/global_allocator.hpp>

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

    void set_allocator(allocator& _New_al) noexcept {
        mjmem_impl::_Global_alloc::_Instance()._Set(_New_al);
    }

    allocator& get_allocator() noexcept {
        return mjmem_impl::_Global_alloc::_Instance()._Get();
    }
} // namespace mjx