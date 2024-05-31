// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    TEST(smart_ptr, copy_construct) {
        smart_ptr<int> _Ptr0 = ::mjx::make_smart_ptr<int>(1024);
        smart_ptr<int> _Ptr1 = _Ptr0;
        EXPECT_EQ(_Ptr0, _Ptr1);
        EXPECT_EQ(_Ptr0.use_count(), 2);
        EXPECT_FALSE(_Ptr0.unique());
    }

    TEST(smart_ptr, move_construct) {
        smart_ptr<int> _Ptr0 = ::mjx::make_smart_ptr<int>(1024);
        smart_ptr<int> _Ptr1 = ::std::move(_Ptr0);
        EXPECT_EQ(_Ptr0.get(), nullptr);
        EXPECT_EQ(_Ptr0.use_count(), 0);
        EXPECT_NE(_Ptr1.get(), nullptr);
        EXPECT_EQ(_Ptr1.use_count(), 1);
        EXPECT_TRUE(_Ptr1.unique());
    }

    TEST(smart_ptr, construct_from_unique) {
        unique_smart_ptr<int> _Uptr = ::mjx::make_unique_smart_ptr<int>(1024);
        smart_ptr<int> _Sptr        = ::std::move(_Uptr);
        EXPECT_EQ(_Uptr.get(), nullptr);
        EXPECT_NE(_Sptr.get(), nullptr);
        EXPECT_EQ(_Sptr.use_count(), 1);
        EXPECT_TRUE(_Sptr.unique());
    }

    TEST(smart_ptr, copy_assign) {
        smart_ptr<int> _Ptr0 = ::mjx::make_smart_ptr<int>(1024);
        smart_ptr<int> _Ptr1 = nullptr;
        _Ptr1                = _Ptr0;
        EXPECT_EQ(_Ptr0, _Ptr1);
        EXPECT_EQ(_Ptr0.use_count(), 2);
        EXPECT_FALSE(_Ptr0.unique());
    }

    TEST(smart_ptr, move_assign) {
        smart_ptr<int> _Ptr0 = ::mjx::make_smart_ptr<int>(1024);
        smart_ptr<int> _Ptr1 = nullptr;
        _Ptr1                = ::std::move(_Ptr0);
        EXPECT_EQ(_Ptr0.get(), nullptr);
        EXPECT_EQ(_Ptr0.use_count(), 0);
        EXPECT_NE(_Ptr1.get(), nullptr);
        EXPECT_EQ(_Ptr1.use_count(), 1);
        EXPECT_TRUE(_Ptr1.unique());
    }

    TEST(smart_ptr, assign_unique) {
        unique_smart_ptr<int> _Uptr = ::mjx::make_unique_smart_ptr<int>(1024);
        smart_ptr<int> _Sptr        = nullptr;
        _Sptr                       = ::std::move(_Uptr);
        EXPECT_EQ(_Uptr.get(), nullptr);
        EXPECT_NE(_Sptr.get(), nullptr);
        EXPECT_EQ(_Sptr.use_count(), 1);
        EXPECT_TRUE(_Sptr.unique());
    }

    TEST(smart_ptr, reset) {
        smart_ptr<int> _Ptr0 = ::mjx::make_smart_ptr<int>(1024);
        EXPECT_EQ(_Ptr0.use_count(), 1);
        EXPECT_TRUE(_Ptr0.unique());
        
        smart_ptr<int> _Ptr1 = _Ptr0;
        EXPECT_EQ(_Ptr0.use_count(), 2);
        EXPECT_FALSE(_Ptr0.unique());

        _Ptr1.reset();
        EXPECT_EQ(_Ptr0.use_count(), 1);
        EXPECT_TRUE(_Ptr0.unique());
    }

    TEST(smart_ptr, swap) {
        smart_ptr<int> _Ptr0 = ::mjx::make_smart_ptr<int>(1024);
        smart_ptr<int> _Ptr1 = ::mjx::make_smart_ptr<int>(2048);
        _Ptr0.swap(_Ptr1);
        EXPECT_EQ(*_Ptr0, 2048);
        EXPECT_EQ(*_Ptr1, 1024);
    }
} // namespace mjx