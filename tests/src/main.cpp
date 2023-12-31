// main.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <unit/smart_array.hpp>
#include <unit/smart_ptr.hpp>
#include <unit/unique_smart_array.hpp>
#include <unit/unique_smart_ptr.hpp>

int main() {
    ::testing::InitGoogleTest();
    return ::RUN_ALL_TESTS();
}