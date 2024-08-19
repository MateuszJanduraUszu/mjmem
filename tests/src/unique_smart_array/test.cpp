// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    TEST(unique_smart_array, null_construct) {
        unique_smart_array<int> _Arr(nullptr, 0);
        EXPECT_EQ(_Arr.get(), nullptr);
        EXPECT_EQ(_Arr.size(), 0);
    }

    TEST(unique_smart_array, move_construct) {
        unique_smart_array<int> _Arr0 = ::mjx::make_unique_smart_array<int>(16);
        unique_smart_array<int> _Arr1 = ::std::move(_Arr0);
        EXPECT_EQ(_Arr0.get(), nullptr);
        EXPECT_EQ(_Arr0.size(), 0);
        EXPECT_NE(_Arr1.get(), nullptr);
        EXPECT_EQ(_Arr1.size(), 16);
    }

    TEST(unique_smart_array, null_assign) {
        unique_smart_array<int> _Arr = ::mjx::make_unique_smart_array<int>(16);
        _Arr                         = nullptr;
        EXPECT_EQ(_Arr.get(), nullptr);
        EXPECT_EQ(_Arr.size(), 0);
    }

    TEST(unique_smart_array, move_assign) {
        unique_smart_array<int> _Arr0 = ::mjx::make_unique_smart_array<int>(16);
        unique_smart_array<int> _Arr1 = nullptr;
        _Arr1                         = ::std::move(_Arr0);
        EXPECT_EQ(_Arr0.get(), nullptr);
        EXPECT_EQ(_Arr0.size(), 0);
        EXPECT_NE(_Arr1.get(), nullptr);
        EXPECT_EQ(_Arr1.size(), 16);
    }

    TEST(unique_smart_array, release) {
        unique_smart_array<int> _Arr = ::mjx::make_unique_smart_array<int>(16);
        const auto& _Arr_data        = _Arr.release();
        EXPECT_EQ(_Arr.get(), nullptr);
        EXPECT_EQ(_Arr.size(), 0);
        EXPECT_NE(_Arr_data.ptr, nullptr);
        EXPECT_EQ(_Arr_data.size, 16);
        ::mjx::delete_object_array(_Arr_data.ptr, _Arr_data.size); // avoid memory leak
    }

    TEST(unique_smart_array, bounds_checking) {
        unique_smart_array<int> _Arr = ::mjx::make_unique_smart_array<int>(16);
        bool _Caught                 = false;
        try {
            _Arr[16] = 0; // intentionally raise resource_overrun exception
        } catch (const resource_overrun&) {
            _Caught = true;
        }

        EXPECT_TRUE(_Caught);
    }

    TEST(unique_smart_array, swap) {
        unique_smart_array<char> _Arr0 = ::mjx::make_unique_smart_array<char>(16);
        unique_smart_array<char> _Arr1 = ::mjx::make_unique_smart_array<char>(16);
#if defined(_MJX_MSVC) || (defined(_MJX_CLANG) && defined(_MJX_WINDOWS))
        ::strcpy_s(_Arr0.get(), _Arr0.size(), "_Arr0");
        ::strcpy_s(_Arr1.get(), _Arr1.size(), "_Arr1");
#else // ^^^ MSVC or Clang with MSVC toolchain ^^^ / vvv GCC vvv
        ::strcpy(_Arr0.get(), "_Arr0");
        ::strcpy(_Arr1.get(), "_Arr1");
#endif // defined(_MJX_MSVC) || (defined(_MJX_CLANG) && defined(_MJX_WINDOWS))
        _Arr0.swap(_Arr1);
        EXPECT_STREQ(_Arr0.get(), "_Arr1");
        EXPECT_STREQ(_Arr1.get(), "_Arr0");
    }
} // namespace mjx