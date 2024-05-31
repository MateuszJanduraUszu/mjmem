// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    TEST(unique_smart_ptr, null_construct) {
        unique_smart_ptr<int> _Ptr(nullptr);
        EXPECT_EQ(_Ptr.get(), nullptr);
    }

    TEST(unique_smart_ptr, move_construct) {
        unique_smart_ptr<int> _Ptr0 = ::mjx::make_unique_smart_ptr<int>(1024);
        unique_smart_ptr<int> _Ptr1 = ::std::move(_Ptr0);
        EXPECT_EQ(_Ptr0.get(), nullptr);
        EXPECT_NE(_Ptr1.get(), nullptr);
    }

    TEST(unique_smart_ptr, null_assign) {
        unique_smart_ptr<int> _Ptr = ::mjx::make_unique_smart_ptr<int>(1024);
        _Ptr                       = nullptr;
        EXPECT_EQ(_Ptr.get(), nullptr);
    }

    TEST(unique_smart_ptr, move_assign) {
        unique_smart_ptr<int> _Ptr0 = ::mjx::make_unique_smart_ptr<int>(1024);
        unique_smart_ptr<int> _Ptr1 = nullptr;
        _Ptr1                       = ::std::move(_Ptr0);
        EXPECT_EQ(_Ptr0.get(), nullptr);
        EXPECT_NE(_Ptr1.get(), nullptr);
    }

    TEST(unique_smart_ptr, release) {
        unique_smart_ptr<int> _Ptr = ::mjx::make_unique_smart_ptr<int>(1024);
        int* const _Raw_ptr        = _Ptr.release();
        EXPECT_EQ(_Ptr.get(), nullptr);
        EXPECT_NE(_Raw_ptr, nullptr);
        ::mjx::delete_object(_Raw_ptr); // avoid memory leak
    }

    TEST(unique_smart_ptr, swap) {
        unique_smart_ptr<int> _Ptr0 = ::mjx::make_unique_smart_ptr<int>(1024);
        unique_smart_ptr<int> _Ptr1 = ::mjx::make_unique_smart_ptr<int>(2048);
        _Ptr0.swap(_Ptr1);
        EXPECT_EQ(*_Ptr0, 2048);
        EXPECT_EQ(*_Ptr1, 1024);
    }
} // namespace mjx