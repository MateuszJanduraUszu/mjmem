// unique_smart_array.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_TEST_UNIT_UNIQUE_SMART_ARRAY_HPP_
#define _MJMEM_TEST_UNIT_UNIQUE_SMART_ARRAY_HPP_
#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    namespace test {
        TEST(unique_smart_array, null_construct) {
            const auto _Return_null = []() noexcept -> int* { return nullptr; };
            unique_smart_array<int> _Sarr(_Return_null(), 0);
            EXPECT_EQ(_Sarr.get(), nullptr);
            EXPECT_EQ(_Sarr.size(), 0);
        }

        TEST(unique_smart_array, move_construct) {
            unique_smart_array<int> _Sarr0 = ::mjx::make_unique_smart_array<int>(2);
            _Sarr0[0]                      = 10;
            _Sarr0[1]                      = 20;
            unique_smart_array<int> _Sarr1 = ::std::move(_Sarr0);
            EXPECT_EQ(_Sarr0.get(), nullptr);
            EXPECT_EQ(_Sarr1[0], 10);
            EXPECT_EQ(_Sarr1[1], 20);
        }

        TEST(unique_smart_array, move_assign) {
            unique_smart_array<int> _Sarr0 = ::mjx::make_unique_smart_array<int>(2);
            _Sarr0[0]                      = 100;
            _Sarr0[1]                      = 200;
            unique_smart_array<int> _Sarr1 = ::std::move(_Sarr0);
            EXPECT_EQ(_Sarr0.get(), nullptr);
            EXPECT_EQ(_Sarr0.size(), 0);
            EXPECT_EQ(_Sarr1[0], 100);
            EXPECT_EQ(_Sarr1[1], 200);
            EXPECT_EQ(_Sarr1.size(), 2);
        }

        TEST(unique_smart_array, assign_null) {
            unique_smart_array<int> _Sarr = ::mjx::make_unique_smart_array<int>(5);
            _Sarr                         = nullptr;
            EXPECT_EQ(_Sarr.get(), nullptr);
            EXPECT_EQ(_Sarr.size(), 0);
        }

        TEST(unique_smart_array, release) {
            unique_smart_array<int> _Sarr = ::mjx::make_unique_smart_array<int>(2);
            _Sarr[0]                      = 1000;
            _Sarr[1]                      = 2000;
            const auto& _Array            = _Sarr.release();
            EXPECT_EQ(_Sarr.get(), nullptr);
            EXPECT_EQ(_Sarr.size(), 0);
            EXPECT_EQ(_Array.ptr[0], 1000);
            EXPECT_EQ(_Array.ptr[1], 2000);
            EXPECT_EQ(_Array.size, 2);
            ::mjx::delete_object_array(_Array.ptr, _Array.size);
        }

        TEST(unique_smart_array, bounds_checking) {
            unique_smart_array<int> _Sarr = ::mjx::make_unique_smart_array<int>(5);
            bool _Reported                = false;
            try {
                _Sarr[5] = 0; // intentionally raise resource_overrun exception
            } catch (const resource_overrun&) {
                _Reported = true;
            }

            EXPECT_TRUE(_Reported);
        }
    } // namespace test
} // namespace mjx

#endif // _MJMEM_TEST_UNIT_UNIQUE_SMART_ARRAY_HPP_