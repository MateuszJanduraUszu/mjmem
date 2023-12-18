// exception.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_EXCEPTION_HPP_
#define _MJMEM_EXCEPTION_HPP_
#include <mjmem/api.hpp>

namespace mjx {
    class _MJMEM_API allocation_failure {
    public:
        allocation_failure() noexcept;
        ~allocation_failure() noexcept;

        // raises allocation failure exception
        __declspec(noreturn) static void raise();
    };

    class _MJMEM_API pool_exhausted {
    public:
        pool_exhausted() noexcept;
        ~pool_exhausted() noexcept;

        // raises pool exhausted exception
        __declspec(noreturn) static void raise();
    };
} // namespace mjx

#endif // _MJMEM_EXCEPTION_HPP_