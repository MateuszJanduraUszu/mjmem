// unique_array.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_TEST_UNIT_UNIQUE_ARRAY_HPP_
#define _MJMEM_TEST_UNIT_UNIQUE_ARRAY_HPP_
#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    namespace test {
        TEST(unique_array, null_construct) {
            const auto _Return_null = []() noexcept -> int* { return nullptr; };
            unique_array<int> _Unique(_Return_null(), 0);
            EXPECT_EQ(_Unique.get(), nullptr);
            EXPECT_EQ(_Unique.size(), 0);
        }

        TEST(unique_array, move_construct) {
            unique_array<int> _Unique0 = ::mjx::make_unique_array<int>(2);
            _Unique0[0]                = 10;
            _Unique0[1]                = 20;
            unique_array<int> _Unique1 = ::std::move(_Unique0);
            EXPECT_EQ(_Unique0.get(), nullptr);
            EXPECT_EQ(_Unique1[0], 10);
            EXPECT_EQ(_Unique1[1], 20);
        }

        TEST(unique_array, move_assign) {
            unique_array<int> _Unique0 = ::mjx::make_unique_array<int>(2);
            _Unique0[0]                = 100;
            _Unique0[1]                = 200;
            unique_array<int> _Unique1 = ::std::move(_Unique0);
            EXPECT_EQ(_Unique0.get(), nullptr);
            EXPECT_EQ(_Unique0.size(), 0);
            EXPECT_EQ(_Unique1[0], 100);
            EXPECT_EQ(_Unique1[1], 200);
            EXPECT_EQ(_Unique1.size(), 2);
        }

        TEST(unique_array, assign_null) {
            unique_array<int> _Unique = ::mjx::make_unique_array<int>(5);
            _Unique                   = nullptr;
            EXPECT_EQ(_Unique.get(), nullptr);
            EXPECT_EQ(_Unique.size(), 0);
        }

        template <class _Ty>
        struct _Custom_array_deleter {
            _Custom_array_deleter() noexcept = default;

            void operator()(_Ty* const _Ptr, const size_t _Size) noexcept {
                ::mjx::delete_objects(_Ptr, _Size);
                _Called = true;
            }

            bool _Called = false;
        };

        TEST(unique_array, custom_deleter) {
            unique_array<int, _Custom_array_deleter<int>> _Unique(::mjx::allocate_objects<int>(5), 5);
            _Unique.reset();
            EXPECT_EQ(_Unique.get_deleter()._Called, true);
        }

        TEST(unique_array, release) {
            unique_array<int> _Unique = ::mjx::make_unique_array<int>(2);
            _Unique[0]                = 1000;
            _Unique[1]                = 2000;
            const auto& _Array        = _Unique.release();
            EXPECT_EQ(_Unique.get(), nullptr);
            EXPECT_EQ(_Unique.size(), 0);
            EXPECT_EQ(_Array.ptr[0], 1000);
            EXPECT_EQ(_Array.ptr[1], 2000);
            EXPECT_EQ(_Array.size, 2);
            _Unique.get_deleter()(_Array.ptr, _Array.size);
        }

        TEST(unique_array, bounds_checking) {
            unique_array<int> _Unique = ::mjx::make_unique_array<int>(5);
            bool _Reported            = false;
            try {
                _Unique[5] = 0; // intentionally raise resource_overrun exception
            } catch (const resource_overrun&) {
                _Reported = true;
            }

            EXPECT_EQ(_Reported, true);
        }
    } // namespace test
} // namespace mjx

#endif // _MJMEM_TEST_UNIT_UNIQUE_ARRAY_HPP_