// unique_ptr.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_TEST_UNIT_UNIQUE_PTR_HPP_
#define _MJMEM_TEST_UNIT_UNIQUE_PTR_HPP_
#include <gtest/gtest.h>
#include <mjmem/smart_pointer.hpp>

namespace mjx {
    namespace test {
        TEST(unique_ptr, null_construct) {
            const auto _Return_null = []() noexcept -> int* { return nullptr; };
            unique_ptr<int> _Unique(_Return_null());
            EXPECT_EQ(_Unique.get(), nullptr);
        }

        TEST(unique_ptr, move_construct) {
            unique_ptr<int> _Unique0 = ::mjx::make_unique_ptr<int>(25);
            unique_ptr<int> _Unique1 = ::std::move(_Unique0);
            EXPECT_EQ(_Unique0.get(), nullptr);
            EXPECT_EQ(*_Unique1, 25);
        }

        TEST(unique_ptr, move_assign) {
            unique_ptr<int> _Unique0 = ::mjx::make_unique_ptr<int>(100);
            unique_ptr<int> _Unique1 = nullptr;
            _Unique1                 = ::std::move(_Unique0);
            EXPECT_EQ(_Unique0.get(), nullptr);
            EXPECT_EQ(*_Unique1, 100);
        }

        TEST(unique_ptr, assign_null) {
            unique_ptr<int> _Unique = ::mjx::make_unique_ptr<int>(150);
            _Unique                 = nullptr;
            EXPECT_EQ(_Unique.get(), nullptr);
        }

        template <class _Ty>
        struct _Custom_pointer_deleter {
            _Custom_pointer_deleter() noexcept = default;

            void operator()(_Ty* const _Ptr) noexcept {
                ::mjx::delete_object(_Ptr);
                _Called = true;
            }

            bool _Called = false;
        };

        TEST(unique_ptr, custom_deleter) {
            unique_ptr<int, _Custom_pointer_deleter<int>> _Unique(::mjx::create_object<int>(250));
            _Unique.reset();
            EXPECT_EQ(_Unique.get_deleter()._Called, true);
        }

        TEST(unique_ptr, release) {
            unique_ptr<int> _Unique = ::mjx::make_unique_ptr<int>(300);
            int* _Ptr               = _Unique.release();
            EXPECT_EQ(_Unique.get(), nullptr);
            EXPECT_EQ(*_Ptr, 300);
            _Unique.get_deleter()(_Ptr);
        }
    } // namespace test
} // namespace mjx

#endif // _MJMEM_TEST_UNIT_UNIQUE_PTR_HPP_