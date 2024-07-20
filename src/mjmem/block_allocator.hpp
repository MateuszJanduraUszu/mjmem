// block_allocator.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_BLOCK_ALLOCATOR_HPP_
#define _MJMEM_BLOCK_ALLOCATOR_HPP_
#include <mjmem/allocator.hpp>
#include <mjmem/api.hpp>
#include <mjmem/pool_resource.hpp>

namespace mjx {
    class _MJMEM_API block_allocator : public allocator { // fixed-size block allocator
    public:
        using value_type      = allocator::value_type;
        using size_type       = allocator::size_type;
        using difference_type = allocator::difference_type;
        using pointer         = allocator::pointer;

        block_allocator(pool_resource& _Resource, const size_type _Block_size);
        ~block_allocator() noexcept override;

        block_allocator()                                  = delete;
        block_allocator(const block_allocator&)            = delete;
        block_allocator& operator=(const block_allocator&) = delete;

        // allocates uninitialized storage
        pointer allocate(const size_type _Count) override;

        // allocates uninitialized storage with the specifed alignment
        pointer allocate_aligned(const size_type _Count, const size_type _Align) override;

        // deallocates storage
        void deallocate(pointer _Ptr, const size_type _Count) noexcept override;

        // returns the largest supported allocation size
        size_type max_size() const noexcept override;

        // compares for equality with another allocator
        bool is_equal(const allocator& _Other) const noexcept override;

        // returns the allocation block size
        size_type block_size() const noexcept;

        // returns the associated resource
        const pool_resource& resource() const noexcept;

    private:
        // initializes the bitmap
        void _Init_bitmap();

        // returns the least number of blocks that can hold _Bytes bytes
        size_type _Least_block_count(const size_type _Bytes) const noexcept;

        // returns the total number of blocks
        size_type _Total_block_count() const noexcept;

        // allocates the requested number of blocks
        pointer _Allocate_blocks(const size_type _Count) noexcept;

        struct _Bitmap { // stores an array of words
            using _Word_type = unsigned char; // 1-byte element, can store the state of 8 blocks
            
            // the maximum size for a small buffer, equal to a pointer to maintain
            // union size and alignment same as a pointer
            static constexpr size_type _Small_buffer_size = sizeof(void*);
            
            _Bitmap() noexcept;
            ~_Bitmap() noexcept;

            // returns the stored words
            _Word_type* _Get_words() noexcept;
            const _Word_type* _Get_words() const noexcept;

            union {
                _Word_type _Buf[_Small_buffer_size]; // buffer for small bitmaps
                _Word_type* _Ptr; // pointer to heap-allocated buffer for larger bitmaps
            };

            size_type _Size; // number of words
            size_type _Free; // number of zero bits (free blocks)
        };

        pool_resource& _Myres;
        size_type _Myblock;
#pragma warning(suppress : 4251) // C4251: _Bitmap needs to have dll-interface
        _Bitmap _Mymap;
    };
} // namespace mjx

#endif // _MJMEM_BLOCK_ALLOCATOR_HPP_