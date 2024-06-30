// exception.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <mjmem/exception.hpp>

namespace mjx {
    allocation_failure::allocation_failure() noexcept {}

    allocation_failure::~allocation_failure() noexcept {}

    void allocation_failure::raise() {
        throw allocation_failure();
    }

    allocation_limit_exceeded::allocation_limit_exceeded() noexcept {}

    allocation_limit_exceeded::~allocation_limit_exceeded() noexcept {}

    void allocation_limit_exceeded::raise() {
        throw allocation_limit_exceeded();
    }

#if !_MJMEM_VERSION_SUPPORTED(1, 0, 1)
    pool_exhausted::pool_exhausted() noexcept {}

    pool_exhausted::~pool_exhausted() noexcept {}

    void pool_exhausted::raise() {
        throw pool_exhausted();
    }
#endif // !_MJMEM_VERSION_SUPPORTED(1, 0, 1)

    resource_overrun::resource_overrun() noexcept {}

    resource_overrun::~resource_overrun() noexcept {}

    void resource_overrun::raise() {
        throw resource_overrun();
    }
} // namespace mjx