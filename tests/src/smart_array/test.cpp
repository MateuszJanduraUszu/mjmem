// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    TEST(smart_array, copy_construct) {
        smart_array<int> _Arr0 = ::mjx::make_smart_array<int>(16);
        smart_array<int> _Arr1 = _Arr0;
        EXPECT_EQ(_Arr0, _Arr1);
        EXPECT_EQ(_Arr0.use_count(), 2);
        EXPECT_FALSE(_Arr0.unique());
    }

    TEST(smart_array, move_construct) {
        smart_array<int> _Arr0 = ::mjx::make_smart_array<int>(16);
        smart_array<int> _Arr1 = ::std::move(_Arr0);
        EXPECT_EQ(_Arr0.get(), nullptr);
        EXPECT_EQ(_Arr0.use_count(), 0);
        EXPECT_NE(_Arr1.get(), nullptr);
        EXPECT_EQ(_Arr1.use_count(), 1);
        EXPECT_TRUE(_Arr1.unique());
    }

    TEST(smart_array, construct_from_unique) {
        unique_smart_array<int> _Uarr = ::mjx::make_unique_smart_array<int>(16);
        smart_array<int> _Sarr        = ::std::move(_Uarr);
        EXPECT_EQ(_Uarr.get(), nullptr);
        EXPECT_NE(_Sarr.get(), nullptr);
        EXPECT_EQ(_Sarr.use_count(), 1);
        EXPECT_TRUE(_Sarr.unique());
    }

    TEST(smart_array, copy_assign) {
        smart_array<int> _Arr0 = ::mjx::make_smart_array<int>(16);
        smart_array<int> _Arr1 = nullptr;
        _Arr1                  = _Arr0;
        EXPECT_EQ(_Arr0, _Arr1);
        EXPECT_EQ(_Arr0.use_count(), 2);
        EXPECT_FALSE(_Arr0.unique());
    }

    TEST(smart_array, move_assign) {
        smart_array<int> _Arr0 = ::mjx::make_smart_array<int>(16);
        smart_array<int> _Arr1 = nullptr;
        _Arr1                  = ::std::move(_Arr0);
        EXPECT_EQ(_Arr0.get(), nullptr);
        EXPECT_EQ(_Arr0.use_count(), 0);
        EXPECT_NE(_Arr1.get(), nullptr);
        EXPECT_EQ(_Arr1.use_count(), 1);
        EXPECT_TRUE(_Arr1.unique());
    }

    TEST(smart_array, assign_unique) {
        unique_smart_array<int> _Uarr = ::mjx::make_unique_smart_array<int>(16);
        smart_array<int> _Sarr        = nullptr;
        _Sarr                         = ::std::move(_Uarr);
        EXPECT_EQ(_Uarr.get(), nullptr);
        EXPECT_NE(_Sarr.get(), nullptr);
        EXPECT_EQ(_Sarr.use_count(), 1);
        EXPECT_TRUE(_Sarr.unique());
    }

    TEST(smart_array, size) {
        constexpr size_t _Size = 16;
        smart_array<int> _Arr  = ::mjx::make_smart_array<int>(_Size);
        EXPECT_EQ(_Arr.size(), _Size);
    }

    TEST(smart_array, reset) {
        smart_array<int> _Arr0 = ::mjx::make_smart_array<int>(16);
        EXPECT_EQ(_Arr0.use_count(), 1);
        EXPECT_TRUE(_Arr0.unique());

        smart_array<int> _Arr1 = _Arr0;
        EXPECT_EQ(_Arr0.use_count(), 2);
        EXPECT_FALSE(_Arr0.unique());

        _Arr1.reset();
        EXPECT_EQ(_Arr0.use_count(), 1);
        EXPECT_TRUE(_Arr0.unique());
    }

    TEST(smart_array, bounds_checking) {
        smart_array<int> _Arr = ::mjx::make_smart_array<int>(16);
        bool _Caught          = false;
        try {
            _Arr[16] = 0; // intentionally raise resource_overrun exception
        } catch (const resource_overrun&) {
            _Caught = true;
        }

        EXPECT_TRUE(_Caught);
    }

    TEST(smart_array, swap) {
        smart_array<char> _Arr0 = ::mjx::make_smart_array<char>(16);
        smart_array<char> _Arr1 = ::mjx::make_smart_array<char>(16);
        ::strcpy(_Arr0.get(), "_Arr0");
        ::strcpy(_Arr1.get(), "_Arr1");
        _Arr0.swap(_Arr1);
        EXPECT_STREQ(_Arr0.get(), "_Arr1");
        EXPECT_STREQ(_Arr1.get(), "_Arr0");
    }
} // namespace mjx