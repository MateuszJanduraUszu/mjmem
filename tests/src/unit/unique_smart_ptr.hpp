// unique_smart_ptr.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_TEST_UNIT_UNIQUE_SMART_PTR_HPP_
#define _MJMEM_TEST_UNIT_UNIQUE_SMART_PTR_HPP_
#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    namespace test {
        TEST(unique_smart_ptr, null_construct) {
            const auto _Return_null = []() noexcept -> int* { return nullptr; };
            unique_smart_ptr<int> _Sptr(_Return_null());
            EXPECT_EQ(_Sptr.get(), nullptr);
        }

        TEST(unique_smart_ptr, move_construct) {
            unique_smart_ptr<int> _Sptr0 = ::mjx::make_unique_smart_ptr<int>(25);
            unique_smart_ptr<int> _Sptr1 = ::std::move(_Sptr0);
            EXPECT_EQ(_Sptr0.get(), nullptr);
            EXPECT_EQ(*_Sptr1, 25);
        }

        TEST(unique_smart_ptr, move_assign) {
            unique_smart_ptr<int> _Sptr0 = ::mjx::make_unique_smart_ptr<int>(100);
            unique_smart_ptr<int> _Sptr1 = nullptr;
            _Sptr1                       = ::std::move(_Sptr0);
            EXPECT_EQ(_Sptr0.get(), nullptr);
            EXPECT_EQ(*_Sptr1, 100);
        }

        TEST(unique_smart_ptr, assign_null) {
            unique_smart_ptr<int> _Sptr = ::mjx::make_unique_smart_ptr<int>(150);
            _Sptr                       = nullptr;
            EXPECT_EQ(_Sptr.get(), nullptr);
        }

        TEST(unique_smart_ptr, release) {
            unique_smart_ptr<int> _Sptr = ::mjx::make_unique_smart_ptr<int>(300);
            int* _Ptr                   = _Sptr.release();
            EXPECT_EQ(_Sptr.get(), nullptr);
            EXPECT_EQ(*_Ptr, 300);
            ::mjx::delete_object(_Ptr);
        }
    } // namespace test
} // namespace mjx

#endif // _MJMEM_TEST_UNIT_UNIQUE_SMART_PTR_HPP_