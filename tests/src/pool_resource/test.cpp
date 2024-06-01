// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/pool_resource.hpp>

namespace mjx {
    TEST(pool_resource, default_construct) {
        pool_resource _Res;
        EXPECT_EQ(_Res.data(), nullptr);
        EXPECT_EQ(_Res.size(), 0);
    }

    TEST(pool_resource, copy_construct) {
        pool_resource _Res0(128);
        pool_resource _Res1(_Res0);
        EXPECT_EQ(::memcmp(_Res0.data(), _Res1.data(), 128), 0);
        EXPECT_EQ(_Res0.size(), _Res1.size());
    }

    TEST(pool_resource, move_construct) {
        pool_resource _Res0(128);
        pool_resource _Res1(::std::move(_Res0));
        EXPECT_EQ(_Res0.data(), nullptr);
        EXPECT_EQ(_Res0.size(), 0);
        EXPECT_NE(_Res1.data(), nullptr);
        EXPECT_EQ(_Res1.size(), 128);
    }

    TEST(pool_resource, copy_assign) {
        pool_resource _Res0(128);
        pool_resource _Res1;
        _Res1 = _Res0;
        EXPECT_EQ(::memcmp(_Res0.data(), _Res1.data(), 128), 0);
        EXPECT_EQ(_Res0.size(), _Res1.size());
    }

    TEST(pool_resource, move_assign) {
        pool_resource _Res0(128);
        pool_resource _Res1;
        _Res1 = ::std::move(_Res0);
        EXPECT_EQ(_Res0.data(), nullptr);
        EXPECT_EQ(_Res0.size(), 0);
        EXPECT_NE(_Res1.data(), nullptr);
        EXPECT_EQ(_Res1.size(), 128);
    }

    TEST(pool_resource, contains) {
        pool_resource _Res(128);
        unsigned char* const _Base_address = static_cast<unsigned char*>(_Res.data());
        EXPECT_FALSE(_Res.contains(nullptr, 0));
        EXPECT_FALSE(_Res.contains(_Base_address, 0));
        EXPECT_FALSE(_Res.contains(nullptr, 16));
        EXPECT_FALSE(_Res.contains(_Base_address - 1, 16));
        EXPECT_FALSE(_Res.contains(_Base_address, 129));
        EXPECT_FALSE(_Res.contains(_Base_address + 1, 128));
        EXPECT_TRUE(_Res.contains(_Base_address, 128));
        EXPECT_TRUE(_Res.contains(_Base_address + 64, 64));
    }

    TEST(pool_resource, release) {
        pool_resource _Res(128);
        pool_resource::pointer _Res_data = _Res.release();
        EXPECT_EQ(_Res.data(), nullptr);
        EXPECT_EQ(_Res.size(), 0);
        EXPECT_NE(_Res_data, nullptr);

        dynamic_allocator _Al;
        _Al.deallocate(_Res_data, 128); // avoid memory leak
    }

    TEST(pool_resource, destroy) {
        pool_resource _Res(128);
        EXPECT_NE(_Res.data(), nullptr);
        EXPECT_EQ(_Res.size(), 128);

        _Res.destroy();
        EXPECT_EQ(_Res.data(), nullptr);
        EXPECT_EQ(_Res.size(), 0);
    }
} // namespace mjx