// smart_ptr.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_TEST_UNIT_SMART_PTR_HPP_
#define _MJMEM_TEST_UNIT_SMART_PTR_HPP_
#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    namespace test {
        TEST(smart_ptr, copy_construct) {
            smart_ptr<int> _Sptr0 = ::mjx::make_smart_ptr<int>(10);
            smart_ptr<int> _Sptr1 = _Sptr0;
            EXPECT_EQ(_Sptr0.use_count(), 2);
            EXPECT_FALSE(_Sptr0.unique());
        }

        TEST(smart_ptr, move_construct) {
            smart_ptr<int> _Sptr0 = ::mjx::make_smart_ptr<int>(10);
            smart_ptr<int> _Sptr1 = ::std::move(_Sptr0);
            EXPECT_EQ(_Sptr0.get(), nullptr);
            EXPECT_EQ(_Sptr0.use_count(), 0);
            EXPECT_EQ(*_Sptr1, 10);
            EXPECT_EQ(_Sptr1.use_count(), 1);
        }

        TEST(smart_ptr, copy_assign) {
            smart_ptr<int> _Sptr0 = ::mjx::make_smart_ptr<int>(10);
            smart_ptr<int> _Sptr1 = nullptr;
            _Sptr1                = _Sptr0;
            EXPECT_EQ(_Sptr0.use_count(), 2);
            EXPECT_FALSE(_Sptr0.unique());
        }

        TEST(smart_ptr, move_assign) {
            smart_ptr<int> _Sptr0 = ::mjx::make_smart_ptr<int>(10);
            smart_ptr<int> _Sptr1 = nullptr;
            _Sptr1                = ::std::move(_Sptr0);
            EXPECT_EQ(_Sptr0.get(), nullptr);
            EXPECT_EQ(_Sptr0.use_count(), 0);
            EXPECT_EQ(*_Sptr1, 10);
            EXPECT_EQ(_Sptr1.use_count(), 1);
        }

        TEST(smart_ptr, reset) {
            smart_ptr<int> _Sptr0 = ::mjx::make_smart_ptr<int>(10);
            smart_ptr<int> _Sptr1 = _Sptr0;
            EXPECT_EQ(_Sptr0.use_count(), 2);
            EXPECT_FALSE(_Sptr0.unique());

            _Sptr1.reset();
            EXPECT_EQ(_Sptr0.use_count(), 1);
            EXPECT_TRUE(_Sptr0.unique());
        }
    } // namespace test
} // namespace mjx

#endif // _MJMEM_TEST_UNIT_SMART_PTR_HPP_