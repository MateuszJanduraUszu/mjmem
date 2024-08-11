// synchronized_allocator.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_SYNCHRONIZED_ALLOCATOR_HPP_
#define _MJMEM_SYNCHRONIZED_ALLOCATOR_HPP_
#include <mjmem/allocator.hpp>
#include <mjmem/api.hpp>

namespace mjx {
    class _MJMEM_API synchronized_allocator : public allocator { // thread-safe memory allocator
    public:
        using value_type      = allocator::value_type;
        using size_type       = allocator::size_type;
        using difference_type = allocator::difference_type;
        using pointer         = allocator::pointer;

        explicit synchronized_allocator(allocator& _Al) noexcept;
        ~synchronized_allocator() noexcept override;

        synchronized_allocator()                                         = delete;
        synchronized_allocator(const synchronized_allocator&)            = delete;
        synchronized_allocator& operator=(const synchronized_allocator&) = delete;

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

    private:
        // Note: To encapsulate the internal lock type, we store the lock as raw bytes in an
        //       appropriately-sized buffer. On Windows, SRW Lock is a simple structure with size
        //       and alignment equivalent to void*. On Linux, pthread_rwlock_t is more complex,
        //       requiring a larger buffer. Thus, we need to adjust the storage size and alignment
        //       accordingly for each platform. To minimize memory usage, _Lock_size and _Lock_align
        //       are defined specifically for each platform based on its requirements.
#ifdef _MJX_WINDOWS
        static constexpr size_type _Lock_size  = sizeof(void*);
        static constexpr size_type _Lock_align = alignof(void*);
#else // ^^^ _MJX_WINDOWS ^^^ / vvv _MJX_LINUX vvv
        static constexpr size_type _Lock_size  = 56;
        static constexpr size_type _Lock_align = 8;
#endif // _MJX_WINDOWS

        allocator& _Mywrapped; // wrapped allocator
        mutable alignas(_Lock_align) unsigned char _Mylock[_Lock_size];
    };
} // namespace mjx

#endif // _MJMEM_SYNCHRONIZED_ALLOCATOR_HPP_