// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/allocator.hpp>
#include <mjmem/block_allocator.hpp>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/pool_allocator.hpp>
#include <mjmem/pool_resource.hpp>
#include <mjmem/synchronized_allocator.hpp>

namespace mjx {
    class wrapped_allocator : public allocator {
    public:
        wrapped_allocator() noexcept : _Myctr(nullptr) {}

        wrapped_allocator(const wrapped_allocator& _Other) noexcept : _Myctr(_Other._Myctr) {}

        wrapped_allocator(wrapped_allocator&& _Other) noexcept : _Myctr(_Other._Myctr) {}

        ~wrapped_allocator() noexcept override {}

        wrapped_allocator& operator=(const wrapped_allocator&) noexcept {
            return *this;
        }

        wrapped_allocator& operator=(wrapped_allocator&&) noexcept {
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

        bool is_equal(const allocator& _Other) const noexcept override {
            if (_Myctr) {
                ++*_Myctr;
            }

            return dynamic_cast<const wrapped_allocator*>(::std::addressof(_Other)) != nullptr;
        }

        void set_counter(size_t& _Counter) noexcept {
            _Myctr = &_Counter;
        }

    private:
        size_t* _Myctr;
    };

    TEST(synchronized_allocator, wrap_external_allocator) {
        constexpr size_t _Expected_counter = 5;
        size_t _Counter                    = 0;
        wrapped_allocator _Wrapped;
        _Wrapped.set_counter(_Counter);
        synchronized_allocator _Al(_Wrapped);
        _Al.allocate(0);
        _Al.allocate_aligned(0, 0);
        _Al.deallocate(nullptr, 0);
        _Al.max_size();
        _Al.is_equal(_Al);
        EXPECT_EQ(_Counter, _Expected_counter);
    }

    TEST(synchronized_allocator, allocators_equality) {
        dynamic_allocator _Wrapped;
        synchronized_allocator _Al0(_Wrapped);
        synchronized_allocator _Al1(_Wrapped);
        EXPECT_EQ(_Al0, _Al1);
    }

    TEST(synchronized_allocator, allocators_inequality) {
        pool_resource _Res0(128);
        pool_resource _Res1(128);
        pool_allocator _Wrapped0(_Res0);
        pool_allocator _Wrapped1(_Res1);
        synchronized_allocator _Al0(_Wrapped0);
        synchronized_allocator _Al1(_Wrapped1);
        EXPECT_NE(_Al0, _Al1);
    }

    TEST(synchronized_allocator, predefined_allocators_inequality) {
        pool_resource _Res(128);
        block_allocator _Block_al(_Res, 16);
        dynamic_allocator _Dynamic_al;
        pool_allocator _Pool_al(_Res);
        synchronized_allocator _Sync_al(_Dynamic_al);
        EXPECT_NE(_Sync_al, _Block_al);
        EXPECT_NE(_Sync_al, _Dynamic_al);
        EXPECT_NE(_Sync_al, _Pool_al);
    }
} // namespace mjx