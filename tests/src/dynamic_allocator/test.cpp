// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/block_allocator.hpp>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/pool_allocator.hpp>
#include <mjmem/pool_resource.hpp>
#include <mjmem/synchronized_allocator.hpp>

namespace mjx {
    TEST(dynamic_allocator, max_size) {
        dynamic_allocator _Al;
        EXPECT_EQ(_Al.max_size(), static_cast<dynamic_allocator::size_type>(-1));
    }

    TEST(dynamic_allocator, allocators_equality) {
        dynamic_allocator _Al0;
        dynamic_allocator _Al1;
        EXPECT_EQ(_Al0, _Al1);
    }

    TEST(dynamic_allocator, predefined_allocators_inequality) {
        pool_resource _Res(128);
        block_allocator _Block_al(_Res, 16);
        dynamic_allocator _Dynamic_al;
        pool_allocator _Pool_al(_Res);
        synchronized_allocator _Sync_al(_Block_al);
        EXPECT_NE(_Dynamic_al, _Block_al);
        EXPECT_NE(_Dynamic_al, _Pool_al);
        EXPECT_NE(_Dynamic_al, _Sync_al);
    }
} // namespace mjx