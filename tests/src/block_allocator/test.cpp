// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/block_allocator.hpp>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/exception.hpp>
#include <mjmem/pool_allocator.hpp>
#include <mjmem/pool_resource.hpp>
#include <mjmem/synchronized_allocator.hpp>

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

    TEST(block_allocator, block_size) {
        pool_resource _Res(128);
        constexpr size_t _Block_size0 = 16;
        constexpr size_t _Block_size1 = 32;
        block_allocator _Al0(_Res, _Block_size0);
        block_allocator _Al1(_Res, _Block_size1);
        EXPECT_EQ(_Al0.block_size(), _Block_size0);
        EXPECT_EQ(_Al1.block_size(), _Block_size1);
    }

    TEST(block_allocator, resource) {
        pool_resource _Res0(128);
        pool_resource _Res1(256);
        block_allocator _Al0(_Res0, 16);
        block_allocator _Al1(_Res1, 32);
        EXPECT_EQ(_Al0.resource(), _Res0);
        EXPECT_EQ(_Al1.resource(), _Res1);
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
        block_allocator _Al2(_Res1, 32);
        EXPECT_NE(_Al0, _Al1);
        EXPECT_NE(_Al0, _Al2);
        EXPECT_NE(_Al1, _Al2);
    }

    TEST(block_allocator, predefined_allocators_inequality) {
        pool_resource _Res(128);
        block_allocator _Block_al(_Res, 16);
        dynamic_allocator _Dynamic_al;
        pool_allocator _Pool_al(_Res);
        synchronized_allocator _Sync_al(_Dynamic_al);
        EXPECT_NE(_Block_al, _Dynamic_al);
        EXPECT_NE(_Block_al, _Pool_al);
        EXPECT_NE(_Block_al, _Sync_al);
    }
} // namespace mjx