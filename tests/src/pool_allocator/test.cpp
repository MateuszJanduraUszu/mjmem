// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/exception.hpp>
#include <mjmem/pool_allocator.hpp>
#include <mjmem/pool_resource.hpp>

namespace mjx {
    TEST(pool_allocator, allocate) {
        pool_resource _Res(8);
        pool_allocator _Al(_Res, 4);
        EXPECT_NO_THROW(_Al.allocate(4));
        EXPECT_NO_THROW(_Al.allocate(2));
        EXPECT_NO_THROW(_Al.allocate(1));
        EXPECT_NO_THROW(_Al.allocate(1));
        EXPECT_THROW(_Al.allocate(1), allocation_failure); // pool exhausted
    }

    TEST(pool_allocator, bad_allocation) {
        pool_resource _Res(128);
        pool_allocator _Al(_Res, 64);
        EXPECT_THROW(_Al.allocate(65), allocation_failure); // allocation limit exceeded
        void* const _Ptr0 = _Al.allocate(64);
        void* const _Ptr1 = _Al.allocate(32);
        EXPECT_THROW(_Al.allocate(64), allocation_failure); // pool exhausted
        _Al.deallocate(_Ptr0, 64);
        _Al.deallocate(_Ptr1, 32);
    }

    TEST(pool_allocator, max_size) {
        pool_resource _Res(128);
        pool_allocator _Al(_Res, _Res.size());
        EXPECT_EQ(_Al.max_size(), _Res.size());
    }

    TEST(pool_allocator, allocators_equality) {
        pool_resource _Res(128);
        pool_allocator _Al0(_Res);
        pool_allocator _Al1(_Res);
        EXPECT_EQ(_Al0, _Al1);
    }

    TEST(pool_allocator, allocators_inequality) {
        pool_resource _Res0(128);
        pool_resource _Res1(128);
        pool_allocator _Al0(_Res0);
        pool_allocator _Al1(_Res1);
        EXPECT_NE(_Al0, _Al1);
    }
} // namespace mjx