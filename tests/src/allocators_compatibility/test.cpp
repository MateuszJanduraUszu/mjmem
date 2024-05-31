// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/allocator.hpp>
#include <mjmem/block_allocator.hpp>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/object_allocator.hpp>
#include <mjmem/pool_allocator.hpp>
#include <mjmem/synchronized_allocator.hpp>

namespace mjx {
    class comp_allocator : public allocator {
    public:
        comp_allocator() noexcept {}
        
        comp_allocator(const comp_allocator&) noexcept {}

        comp_allocator(comp_allocator&&) noexcept {}

        ~comp_allocator() noexcept override {}

        comp_allocator& operator=(const comp_allocator&) noexcept {
            return *this;
        }

        comp_allocator& operator=(comp_allocator&&) noexcept {
            return *this;
        }

        pointer allocate(const size_type) override {
            return nullptr;
        }

        pointer allocate_aligned(const size_type, const size_type) override {
            return nullptr;
        }

        void deallocate(pointer, const size_type) noexcept override {}

        size_type max_size() const noexcept override {
            return 0;
        }

        bool is_equal(const allocator&) const noexcept override {
            return true;
        }
    };

    class incomp_allocator {
    public:
        using value_type      = void;
        using size_type       = size_t;
        using difference_type = ptrdiff_t;
        using pointer         = void*;

        incomp_allocator() noexcept {}
        
        incomp_allocator(const incomp_allocator&) noexcept {}

        incomp_allocator(incomp_allocator&&) noexcept {}

        ~incomp_allocator() noexcept {}

        incomp_allocator& operator=(const incomp_allocator&) noexcept {
            return *this;
        }

        incomp_allocator& operator=(incomp_allocator&&) noexcept {
            return *this;
        }

        pointer allocate(const size_type) {
            return nullptr;
        }

        pointer allocate_aligned(const size_type, const size_type) {
            return nullptr;
        }

        void deallocate(pointer, const size_type) noexcept {}

        size_type max_size() const noexcept {
            return 0;
        }

        bool is_equal(const allocator&) const noexcept {
            return true;
        }
    };

    TEST(allocators_compatibility, predefined_allocators) {
        EXPECT_TRUE(compatible_allocator<block_allocator>);
        EXPECT_TRUE(compatible_allocator<dynamic_allocator>);
        EXPECT_TRUE(compatible_allocator<pool_allocator>);
        EXPECT_TRUE(compatible_allocator<synchronized_allocator>);
    }

    TEST(allocators_compatibility, custom_allocators) {
        EXPECT_TRUE(compatible_allocator<comp_allocator>);
        EXPECT_FALSE(compatible_allocator<incomp_allocator>);
    }
} // namespace mjx