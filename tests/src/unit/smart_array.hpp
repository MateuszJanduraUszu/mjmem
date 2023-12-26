// smart_array.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_TEST_UNIT_SMART_ARRAY_HPP_
#define _MJMEM_TEST_UNIT_SMART_ARRAY_HPP_
#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    namespace test {
        TEST(smart_array, copy_construct) {
            smart_array<int> _Sarr0 = ::mjx::make_smart_array<int>(5);
            smart_array<int> _Sarr1 = _Sarr0;
            EXPECT_EQ(_Sarr0, _Sarr1);
            EXPECT_EQ(_Sarr0.use_count(), 2);
            EXPECT_FALSE(_Sarr0.unique());
        }

        TEST(smart_array, move_construct) {
            smart_array<int> _Sarr0 = ::mjx::make_smart_array<int>(5);
            _Sarr0[0]               = 10;
            smart_array<int> _Sarr1 = ::std::move(_Sarr0);
            EXPECT_EQ(_Sarr0.get(), nullptr);
            EXPECT_EQ(_Sarr0.use_count(), 0);
            EXPECT_EQ(*_Sarr1, 10);
            EXPECT_EQ(_Sarr1.use_count(), 1);
        }

        TEST(smart_array, construct_from_unique) {
            unique_smart_array<int> _Uarr = ::mjx::make_unique_smart_array<int>(5);
            _Uarr[0]                      = 10;
            smart_array<int> _Sarr        = ::std::move(_Uarr);
            EXPECT_EQ(_Uarr.get(), nullptr);
            EXPECT_EQ(*_Sarr, 10);
            EXPECT_EQ(_Sarr.use_count(), 1);
            EXPECT_TRUE(_Sarr.unique());
        }

        TEST(smart_array, copy_assign) {
            smart_array<int> _Sarr0 = ::mjx::make_smart_array<int>(5);
            smart_array<int> _Sarr1 = nullptr;
            _Sarr1                  = _Sarr0;
            EXPECT_EQ(_Sarr0, _Sarr1);
            EXPECT_EQ(_Sarr0.use_count(), 2);
            EXPECT_FALSE(_Sarr0.unique());
        }

        TEST(smart_array, move_assign) {
            smart_array<int> _Sarr0 = ::mjx::make_smart_array<int>(5);
            _Sarr0[0]               = 10;
            smart_array<int> _Sarr1 = nullptr;
            _Sarr1                  = ::std::move(_Sarr0);
            EXPECT_EQ(_Sarr0.get(), nullptr);
            EXPECT_EQ(_Sarr0.use_count(), 0);
            EXPECT_EQ(*_Sarr1, 10);
            EXPECT_EQ(_Sarr1.use_count(), 1);
        }

        TEST(smart_array, assign_unique) {
            unique_smart_array<int> _Uarr = ::mjx::make_unique_smart_array<int>(5);
            _Uarr[0]                      = 10;
            smart_array<int> _Sarr        = nullptr;
            _Sarr                         = ::std::move(_Uarr);
            EXPECT_EQ(_Uarr.get(), nullptr);
            EXPECT_EQ(*_Sarr, 10);
            EXPECT_EQ(_Sarr.use_count(), 1);
            EXPECT_TRUE(_Sarr.unique());
        }

        TEST(smart_array, reset) {
            smart_array<int> _Sarr0 = ::mjx::make_smart_array<int>(5);
            smart_array<int> _Sarr1 = _Sarr0;
            EXPECT_EQ(_Sarr0.use_count(), 2);
            EXPECT_FALSE(_Sarr0.unique());

            _Sarr1.reset();
            EXPECT_EQ(_Sarr0.use_count(), 1);
            EXPECT_TRUE(_Sarr0.unique());
        }

        TEST(smart_array, bounds_checking) {
            smart_array<int> _Sarr = ::mjx::make_smart_array<int>(5);
            bool _Reported         = false;
            try {
                _Sarr[5] = 0; // intentionally raise resource_overrun exception
            } catch (const resource_overrun&) {
                _Reported = true;
            }

            EXPECT_TRUE(_Reported);
        }
    } // namespace test
} // namespace mjx

#endif // _MJMEM_TEST_UNIT_SMART_ARRAY_HPP_