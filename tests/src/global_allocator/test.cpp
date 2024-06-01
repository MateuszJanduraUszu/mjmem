// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/allocator.hpp>
#include <mjmem/block_allocator.hpp>
#include <mjmem/pool_resource.hpp>

namespace mjx {
    class custom_allocator : public allocator {
    public:
        custom_allocator() noexcept {}

        custom_allocator(const custom_allocator&) noexcept {}

        custom_allocator(custom_allocator&&) noexcept {}

        ~custom_allocator() noexcept override {}

        custom_allocator& operator=(const custom_allocator&) noexcept {
            return *this;
        }

        custom_allocator& operator=(custom_allocator&&) noexcept {
            return *this;
        }

        pointer allocate(const size_type) override {
            if (_Myctr) {
                ++*_Myctr;
            }

            return nullptr;
        }

        pointer allocate_aligned(const size_type, const size_type) override {
            if (_Myctr) {
                ++*_Myctr;
            }
            
            return nullptr;
        }

        void deallocate(pointer, const size_type) noexcept override {
            if (_Myctr) {
                ++*_Myctr;
            }
        }

        size_type max_size() const noexcept override {
            if (_Myctr) {
                ++*_Myctr;
            }

            return 0;
        }

        bool is_equal(const allocator&) const noexcept override {
            if (_Myctr) {
                ++*_Myctr;
            }

            return true;
        }

        void set_counter(size_t& _Counter) noexcept {
            _Myctr = &_Counter;
        }

    private:
        size_t* _Myctr = nullptr;
    };

    TEST(global_allocator, use_custom_allocator) {
        size_t _Counter = 0;
        custom_allocator _Al;
        _Al.set_counter(_Counter);
        ::mjx::set_allocator(_Al);

        // call all global allocator methods, each call should increment the counter
        allocator& _Global = ::mjx::get_allocator();
        _Global.allocate(0);
        _Global.allocate_aligned(0, 2);
        _Global.deallocate(nullptr, 0);
        _Global.max_size();
        _Global.is_equal(_Al);
        EXPECT_EQ(_Counter, 5);
    }

    TEST(global_allocator, use_predefined_allocator) {
        pool_resource _Res(128);
        block_allocator _Al(_Res, 16);
        ::mjx::set_allocator(_Al);

        // allocate memory from the global allocator, the memory should come from the pool resource
        allocator& _Global = ::mjx::get_allocator();
        void* const _Ptr   = _Global.allocate(32);
        EXPECT_TRUE(_Res.contains(_Ptr, 32));
        _Global.deallocate(_Ptr, 32);
    }
} // namespace mjx