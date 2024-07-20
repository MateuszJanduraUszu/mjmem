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
#include <random>
#include <vector>

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

    TEST(pool_allocator, resource) {
        pool_resource _Res0(128);
        pool_resource _Res1(256);
        pool_allocator _Al0(_Res0);
        pool_allocator _Al1(_Res1);
        EXPECT_EQ(_Al0.resource(), _Res0);
        EXPECT_EQ(_Al1.resource(), _Res1);
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
        pool_allocator _Al2(_Res1, 64);
        EXPECT_NE(_Al0, _Al1);
        EXPECT_NE(_Al0, _Al2);
        EXPECT_NE(_Al1, _Al2);
    }

    TEST(pool_allocator, predefined_allocators_inequality) {
        pool_resource _Res(128);
        block_allocator _Block_al(_Res, 16);
        dynamic_allocator _Dynamic_al;
        pool_allocator _Pool_al(_Res);
        synchronized_allocator _Sync_al(_Dynamic_al);
        EXPECT_NE(_Pool_al, _Block_al);
        EXPECT_NE(_Pool_al, _Dynamic_al);
        EXPECT_NE(_Pool_al, _Sync_al);
    }

    struct memory_block {
        void* _Ptr;
        size_t _Size;
    };

    inline memory_block allocate_block(pool_allocator& _Al, const size_t _Size) {
        return {_Al.allocate(_Size), _Size};
    }

    inline void deallocate_block(pool_allocator& _Al, memory_block& _Block) noexcept {
        _Al.deallocate(_Block._Ptr, _Block._Size);
    }

    inline size_t random_from_range(const size_t _Min, const size_t _Max) noexcept {
        static ::std::random_device _Device;
#ifdef _M_X64
        static ::std::mt19937_64 _Engine(_Device());
#else // ^^^ _M_X64 ^^^ / vvv _M_IX86 vvv
        static ::std::mt19937 _Engine(_Device());
#endif // _M_X64
        return ::std::uniform_int_distribution<size_t>{_Min, _Max}(_Engine);
    }

    TEST(pool_allocator, block_merging) {
        pool_resource _Res(128);
        pool_allocator _Al(_Res);
        
        // Note: This test is designed to evaluate the pool_allocator's block merging
        //       mechanism for anti-fragmentation. The test allocates an array of blocks
        //       with predefined sizes in random order and subsequently deallocates them,
        //       also in random order. The expected outcome is that the allocator will
        //       consolidate all blocks into a single large memory block.
        ::std::vector<size_t> _Sizes = {64, 32, 16, 8, 8};
        ::std::vector<memory_block> _Blocks;
        _Blocks.reserve(_Sizes.size());
        while (!_Sizes.empty()) { // allocate blocks in random order
            const size_t _Idx = random_from_range(0, _Sizes.size() - 1);
            _Blocks.push_back(allocate_block(_Al, _Sizes[_Idx]));
            _Sizes.erase(_Sizes.begin() + _Idx);
        }

        while (!_Blocks.empty()) { // deallocate blocks in random order
            const size_t _Idx = random_from_range(0, _Blocks.size() - 1);
            deallocate_block(_Al, _Blocks[_Idx]);
            _Blocks.erase(_Blocks.begin() + _Idx);
        }

        // verify that all blocks have been consolidated into a single large block,
        // allowing allocation of the entire block
        void* _Ptr = _Al.allocate(128);
        EXPECT_NE(_Ptr, nullptr);
        _Al.deallocate(_Ptr, 128);
    }
} // namespace mjx