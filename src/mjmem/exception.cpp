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

    pool_exhausted::pool_exhausted() noexcept {}

    pool_exhausted::~pool_exhausted() noexcept {}

    void pool_exhausted::raise() {
        throw pool_exhausted();
    }
} // namespace mjx