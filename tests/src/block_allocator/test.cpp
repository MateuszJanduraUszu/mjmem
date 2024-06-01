// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/block_allocator.hpp>
#include <mjmem/exception.hpp>

namespace mjx {
    TEST(block_allocator, allocate) {
        pool_resource _Res(8);
        block_allocator _Al(_Res, 2);
        EXPECT_NO_THROW(_Al.allocate(2));
        EXPECT_NO_THROW(_Al.allocate(2));
        EXPECT_NO_THROW(_Al.allocate(2));
        EXPECT_NO_THROW(_Al.allocate(2));
        EXPECT_THROW(_Al.allocate(1), allocation_failure); // all blocks already allocated
    }

    TEST(block_allocator, pool_exhausted) {
        pool_resource _Res(128);
        block_allocator _Al(_Res, 16);
        EXPECT_THROW(_Al.allocate(129), allocation_failure);
        void* const _Ptr = _Al.allocate(64); // allocate 4 blocks (each 16 bytes)
        EXPECT_THROW(_Al.allocate(100), allocation_failure); // 4 blocks available, while 7 required
        _Al.deallocate(_Ptr, 64);
    }
    
    TEST(block_allocator, max_size) {
        pool_resource _Res(128);
        block_allocator _Al(_Res, 16);
        EXPECT_EQ(_Al.max_size(), _Res.size());
    }

    TEST(block_allocator, allocators_equality) {
        pool_resource _Res(128);
        block_allocator _Al0(_Res, 16);
        block_allocator _Al1(_Res, 16);
        EXPECT_EQ(_Al0, _Al1);
    }

    TEST(block_allocator, allocators_inequality) {
        pool_resource _Res0(128);
        pool_resource _Res1(128);
        block_allocator _Al0(_Res0, 16);
        block_allocator _Al1(_Res1, 16);
        EXPECT_NE(_Al0, _Al1);
    }
} // namespace mjx