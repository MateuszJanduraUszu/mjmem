// test.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <array>
#include <gtest/gtest.h>
#include <mjmem/impl/bitops.hpp>

namespace mjx {
    using namespace mjmem_impl;
    
    constexpr size_t _Not_found = _Base_word_traits::_Not_found;

    TEST(bitops, count_trailing_zeros) {
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b11111111), 0);
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b00000010), 1);
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b10111100), 2);
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b00001000), 3);
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b00110000), 4);
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b10100000), 5);
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b11000000), 6);
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b10000000), 7);
        EXPECT_EQ(_Count_trailing_zeros<uint8_t>(0b00000000), 8);
    }

    TEST(bitops, find_zero_bit) {
        EXPECT_EQ(_Find_zero_bit<uint8_t>(0b11111111), _Not_found);
        EXPECT_EQ(_Find_zero_bit<uint8_t>(0b11111110), 0);
        EXPECT_EQ(_Find_zero_bit<uint8_t>(0b01111111), 7);
        EXPECT_EQ(_Find_zero_bit<uint8_t>(0b11110111), 3);
        EXPECT_EQ(_Find_zero_bit<uint8_t>(0b01010101), 1);
        EXPECT_EQ(_Find_zero_bit<uint8_t>(0b10101010), 0);
        EXPECT_EQ(_Find_zero_bit<uint8_t>(0b11110000), 0);
        EXPECT_EQ(_Find_zero_bit<uint8_t>(0b01111110), 0);
    }

    TEST(bitops, find_contiguous_zero_bits_in_word) {
        EXPECT_EQ(_Find_contiguous_zero_bits_in_word<uint8_t>(0b11111111, 1), _Not_found);
        EXPECT_EQ(_Find_contiguous_zero_bits_in_word<uint8_t>(0b00000000, 8), 0);
        EXPECT_EQ(_Find_contiguous_zero_bits_in_word<uint8_t>(0b00111111, 2), 6);
        EXPECT_EQ(_Find_contiguous_zero_bits_in_word<uint8_t>(0b11110000, 4), 0);
        EXPECT_EQ(_Find_contiguous_zero_bits_in_word<uint8_t>(0b11100111, 2), 3);
        EXPECT_EQ(_Find_contiguous_zero_bits_in_word<uint8_t>(0b01010101, 1), 1);
        EXPECT_EQ(_Find_contiguous_zero_bits_in_word<uint8_t>(0b10101010, 2), _Not_found);
        EXPECT_EQ(_Find_contiguous_zero_bits_in_word<uint8_t>(0b11100011, 3), 2);
    }

    inline void test_find_contiguous_zero_bits(
        ::std::array<uint8_t, 4> _Words, const size_t _Bits, const size_t _Count, const size_t _Expected) noexcept {
        const _Word_array _Array(_Words.data(), _Words.size(), _Bits);
        EXPECT_EQ(_Find_contiguous_zero_bits(_Array, _Count), _Expected);
    }

    TEST(bitops, find_contiguous_zero_bits) {
        test_find_contiguous_zero_bits({0b11111111, 0b11111111, 0b11111111, 0b11111111}, 32, 1, _Not_found);
        test_find_contiguous_zero_bits({0b00000000, 0b00000000, 0b00000000, 0b00000000}, 32, 32, 0);
        test_find_contiguous_zero_bits({0b01111111, 0b11111110, 0b11111111, 0b11111111}, 32, 2, 7);
        test_find_contiguous_zero_bits({0b11111111, 0b00111111, 0b11111100, 0b11111111}, 32, 4, 14);
        test_find_contiguous_zero_bits({0b11100111, 0b00001111, 0b00000000, 0b11110000}, 32, 16, 12);
        test_find_contiguous_zero_bits({0b01010101, 0b11101101, 0b01011011, 0b11111110}, 32, 2, 23);
        test_find_contiguous_zero_bits({0b10101010, 0b11111111, 0b00000000, 0b11111100}, 32, 10, 16);
        test_find_contiguous_zero_bits({0b11111111, 0b11111111, 0b11111111, 0b00011111}, 29, 3, _Not_found);
    }
} // namespace mjx