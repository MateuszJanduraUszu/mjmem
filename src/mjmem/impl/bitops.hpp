// bitops.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_IMPL_BITOPS_HPP_
#define _MJMEM_IMPL_BITOPS_HPP_
#include <algorithm>
#include <bit>
#include <climits>
#include <cstdint>
#include <mjmem/endian.hpp>

// Note: This implementation relies on constructing wider integers from 8-bit integers.
//       To ensure correctness, we must enforce little-endian byte order. This guarantees
//       that bytes are stored in memory in the same order as they appear in the array of words.
#ifdef _MJX_LITTLE_ENDIAN
#define _LOAD_LE(_Value) _Value
#else // ^^^ _MJX_LITTLE_ENDIAN ^^^ / vvv _MJX_BIG_ENDIAN vvv
#define _LOAD_LE(_Value) ::mjx::swap_endian(_Value)
#endif // _MJX_LITTLE_ENDIAN

namespace mjx {
    namespace mjmem_impl {
        template <class _Ty>
        constexpr const _Ty& _Min(const _Ty& _Val0, const _Ty& _Val1, const _Ty& _Val2) noexcept {
            // return the smallest number among the three elements
            return (::std::min)(_Val0, (::std::min)(_Val1, _Val2));
        }

        template <class _Word_type>
        struct _Word_traits { // general word-dependent traits
            static constexpr size_t _Bits_per_word     = sizeof(_Word_type) * CHAR_BIT;
            static constexpr size_t _Not_found         = static_cast<size_t>(-1);
            static constexpr _Word_type _All_bits_set  = ~_Word_type{0};
            static constexpr _Word_type _None_bits_set = _Word_type{0};
        };

        using _Base_word_type   = uint8_t;
        using _Base_word_traits = _Word_traits<_Base_word_type>;

        template <class _Word_type>
        constexpr size_t _Find_zero_bit(const _Word_type _Word) noexcept {
            // search for the first zero bit in a word, -1 if not found
            using _Traits     = _Word_traits<_Word_type>;
            const size_t _Off = static_cast<size_t>(::std::countr_one(_Word));
            return _Off < _Traits::_Bits_per_word ? _Off : _Traits::_Not_found;
        }

        template <class _Word_type>
        constexpr size_t _Count_trailing_zeros(const _Word_type _Word) noexcept {
            // count the number of trailing zeros in a word
            return static_cast<size_t>(::std::countr_zero(_Word));
        }

        template <class _Word_type>
        constexpr size_t _Find_contiguous_zero_bits_in_word(const _Word_type _Word, const size_t _Count) noexcept {
            // search for a contiguous sequence of zero bits of length _Count in the given _Word 
            using _Traits = _Word_traits<_Word_type>;
            switch (_Count) {
            case 0: // searching for zero bits always succeeds
                return 0;
            case 1: // search for exactly one zero bit
                return _Find_zero_bit(_Word);
            case _Traits::_Bits_per_word: // search for all bits in the word
                return _Word == _Traits::_None_bits_set ? 0 : _Traits::_Not_found;
            default:
                if (_Count > _Traits::_Bits_per_word) { // more bits requested than available in the word, break
                    return _Traits::_Not_found;
                }

                break;
            }

            size_t _Shift = 0; // shift used to discard already checked bits
            size_t _Off; // offset of the sequence occurrence
            size_t _Found; // number of zero bits found in the current sequence
            size_t _Remaining = _Traits::_Bits_per_word; // number of bits available in the word
            for (; _Shift < _Traits::_Bits_per_word; _Shift = _Off + 1) {
                // Note: Since we already checked if _Count is equal to 1, we can break
                //       if the zero bit was found in the last bit, as it means there is only
                //       one zero bit in the sequence.
                _Off = _Find_zero_bit(static_cast<_Word_type>(_Word >> _Shift));
                if (_Off == _Traits::_Not_found || _Off == _Traits::_Bits_per_word - 1) {
                    // no more zero bits or only one zero bit left
                    break;
                }

                _Off      += _Shift; // add shift to make offset absolute
                _Found     = _Count_trailing_zeros(static_cast<_Word_type>(_Word >> (_Off + 1))) + 1;
                _Remaining = _Traits::_Bits_per_word - _Off;

                // Note: Due to shifting, there are always bits that don't belong to _Word,
                //       thus we need to check if the found number of bits is within the word.
                if (_Found >= _Count && _Remaining >= _Count) { // the given number of bits found, break
                    return _Off;
                }
            }

            return _Traits::_Not_found;
        }

        struct _Word_array { // stores an array of 1-byte words
            using _Word_type = _Base_word_type;

            constexpr _Word_array(_Word_type* const _Words, const size_t _Size, const size_t _Bits = 0) noexcept
                : _Words(_Words), _Size(_Size),
                _Bits(_Bits != 0 ? _Bits : _Size * _Base_word_traits::_Bits_per_word) {}

            _Word_type* _Words;
            size_t _Size; // the number of words
            size_t _Bits; // total number of bits (used in _Find_contiguous_zero_bits-related functions)
        };

        struct _Contiguous_zero_bits_search_state {
            size_t _Off   = _Base_word_traits::_Not_found; // offset of a sequence of zero bits
            size_t _Found = 0; // total number of zero bits found
            size_t _Idx   = 0; // index of the current word
        };

        template <class _Word_type>
        constexpr size_t _Calculate_bits_per_last_word(const size_t _Bits) noexcept {
            // return the number of bits in the last word, which may be incomplete
            using _Traits           = _Word_traits<_Word_type>;
            const size_t _Remainder = _Bits % _Base_word_traits::_Bits_per_word;
            if (_Remainder == 0) { // word is complete, return all bits
                return _Traits::_Bits_per_word;
            }

            // the last word has incomplete bits, calculate how many bits are present
            constexpr size_t _Full_words = sizeof(_Word_type) - 1;
            return (_Full_words * _Base_word_traits::_Bits_per_word) + _Remainder;
        }

        template <class _Word_type>
        constexpr bool _Find_contiguous_zero_bits_step(
            const _Word_array& _Array, const size_t _Count, _Contiguous_zero_bits_search_state& _State) noexcept {
            // search for a contiguous sequence of zero bits in the _Array
            using _Traits                  = _Word_traits<_Word_type>;
            const size_t _Bits_per_word    = _State._Idx + sizeof(_Word_type) == _Array._Size
                ? _Calculate_bits_per_last_word<_Word_type>(_Array._Bits) : _Traits::_Bits_per_word;
            const _Word_type _Word         = _LOAD_LE( // _Word must be stored in little-endian order
                *reinterpret_cast<const _Word_type*>(_Array._Words + _State._Idx));
            const _Word_type _All_bits_set = _Traits::_All_bits_set >> (_Traits::_Bits_per_word - _Bits_per_word);
            size_t _Off;
            size_t _Search;
            if (_Word == _Traits::_None_bits_set) { // all bits set to zero, count them and break
                if (_State._Off == _Traits::_Not_found) { // capture the start of the occurrence
                    _State._Off = _State._Idx * _Base_word_traits::_Bits_per_word;
                }

                _State._Found += _Bits_per_word;
                return _State._Found >= _Count;
            } else if (_Word == _All_bits_set) { // no zero bits found in this word, reset the counter
                _State._Off   = _Traits::_Not_found;
                _State._Found = 0;
                return false;
            }

            if (_State._Off != _Traits::_Not_found) { // continue searching from the previous word
                _Search = (::std::min)(_Count - _State._Found, _Bits_per_word);
                _Off    = _Find_contiguous_zero_bits_in_word(_Word, _Search);
                if (_Off != 0) { // sequence not contiguous, reset the counter
                    _State._Off   = _Traits::_Not_found;
                    _State._Found = 0;
                } else { // sequence contiguous, update the counter
                    _State._Found += _Search;
                    return _State._Found >= _Count;
                }
            }

            size_t _Shift     = 0; // shift used to discard already checked bits
            size_t _Remaining = _Bits_per_word; // number of bits available in the word
            size_t _Found; // number of zero bits found in the current sequence
            for (; _Shift < _Bits_per_word; _Shift = _Off + 1) {
                _Off = _Find_zero_bit(static_cast<_Word_type>(_Word >> _Shift));
                if (_Off == _Traits::_Not_found || _Off >= _Bits_per_word) { // no more zero bits in the word, break
                    break;
                }

                _Off      += _Shift; // add shift to make offset absolute
                _Search    = _Min(_Bits_per_word - _Off, _Bits_per_word, _Count);
                _Found     = _Count_trailing_zeros(static_cast<_Word_type>(_Word >> (_Off + 1))) + 1;
                _Remaining = _Bits_per_word - _Off;
                if (_Found >= _Search && _Remaining >= _Search) { // the given amount of zero bits found, break
                    _State._Off   = (_State._Idx * _Base_word_traits::_Bits_per_word) + _Off;
                    _State._Found = (::std::min)(_Found, _Remaining);
                    return _State._Found >= _Count;
                }
            }

            return false;
        }

        using _Contiguous_zero_bits_search_step_callback = bool(*)(
            const _Word_array&, const size_t, _Contiguous_zero_bits_search_state&) noexcept;

        struct _Contiguous_zero_bits_search_step {
            _Contiguous_zero_bits_search_step_callback _Callback;
            size_t _Count; // the number of words processed by _Callback

            static constexpr _Contiguous_zero_bits_search_step _Choose(const size_t _Remaining) noexcept {
                // choose the appropriate callback and step size based on the number of remaining words
                if (_Remaining >= 8) {
                    return {&_Find_contiguous_zero_bits_step<uint64_t>, 8};
                } else if (_Remaining >= 4) {
                    return {&_Find_contiguous_zero_bits_step<uint32_t>, 4};
                } else if (_Remaining >= 2) {
                    return {&_Find_contiguous_zero_bits_step<uint16_t>, 2};
                } else {
                    return {&_Find_contiguous_zero_bits_step<uint8_t>, 1};
                }
            }
        };

        constexpr size_t _Find_contiguous_zero_bits(const _Word_array& _Array, const size_t _Count) noexcept {
            // search for a contiguous sequence of zero bits of length _Count in the given _Array
            _Contiguous_zero_bits_search_state _State;
            _Contiguous_zero_bits_search_step _Step;
            for (; _State._Idx < _Array._Size; _State._Idx += _Step._Count) {
                _Step = _Contiguous_zero_bits_search_step::_Choose(_Array._Size - _State._Idx);
                if (_Step._Callback(_Array, _Count, _State)) { // the given number of bits found, break
                    return _State._Off;
                }
            }

            return _Base_word_traits::_Not_found;
        }

        struct _Bit_range_modification_state {
            size_t _Off       = _Base_word_traits::_Not_found; // offset of the range
            size_t _Idx       = _Base_word_traits::_Not_found; // index of the current word
            size_t _Remaining = 0; // the number of bits remaining to be modified
            bool _Set         = false; // true if setting bits to 1, false if setting bits to 0
        };

        template <class _Word_type>
        constexpr void _Modify_bit_range_step(_Word_array& _Array, _Bit_range_modification_state& _State) noexcept {
            // modify a range of bits in the _Array based on the current state
            using _Traits = _Word_traits<_Word_type>;
            size_t _Off;
            size_t _Count;
            if (_State._Idx == _Traits::_Not_found) { // first word
                _State._Idx = _State._Off / _Base_word_traits::_Bits_per_word;
                _Off        = _State._Off % _Base_word_traits::_Bits_per_word == 0
                    ? 0 : _State._Off % _Base_word_traits::_Bits_per_word;
                _Count      = (::std::min)(_State._Remaining, _Traits::_Bits_per_word - _Off);
            } else { // subsequent words
                _Off   = 0; // start from the beginning of the word
                _Count = (::std::min)(_State._Remaining, _Traits::_Bits_per_word);
            }

#ifdef _MJX_LITTLE_ENDIAN
            _Word_type& _Word = *reinterpret_cast<_Word_type*>(_Array._Words + _State._Idx);
#else // ^^^ _MJX_LITTLE_ENDIAN ^^^ / vvv _MJX_BIG_ENDIAN vvv
            auto& _Words      = _Array._Words + _State._Idx;
            _Word_type _Word  = ::mjx::swap_endian(*reinterpret_cast<const _Word_type*>(_Words));
#endif // _MJX_LITTLE_ENDIAN
            _Word_type _Mask  = 0;
            if (_Count == _Traits::_Bits_per_word) { // modify all bits in the word
                _Mask = _Traits::_All_bits_set;
            } else { // modify only a portion of the bits
                _Mask = static_cast<_Word_type>(((1 << _Count) - 1) << _Off);
            }

            if (_State._Set) { // set bits to 1
                _Word |= _Mask;
            } else { // set bits to 0
                _Word &= ~_Mask;
            }

#ifdef _MJX_BIG_ENDIAN
            // on big-endian platforms, swap back to store the processed word correctly
            *reinterpret_cast<_Word_type*>(_Words) = ::mjx::swap_endian(_Word);
#endif // _MJX_BIG_ENDIAN
            _State._Remaining                     -= _Count; // update the number of remaining bits to modify
        }

        using _Bit_range_modification_step_callback = void(*)(
            _Word_array&, _Bit_range_modification_state&) noexcept;

        struct _Bit_range_modification_step {
            _Bit_range_modification_step_callback _Callback;
            size_t _Count; // the number of words processed by _Callback
        
            static constexpr _Bit_range_modification_step _Choose(const size_t _Remaining) noexcept {
                // choose the appropriate callback and step size based on the number of remaining words
                if (_Remaining >= 64) {
                    return {&_Modify_bit_range_step<uint64_t>, 8};
                } else if (_Remaining >= 32) {
                    return {&_Modify_bit_range_step<uint32_t>, 4};
                } else if (_Remaining >= 16) {
                    return {&_Modify_bit_range_step<uint16_t>, 2};
                } else {
                    return {&_Modify_bit_range_step<uint8_t>, 1};
                }
            }
        };

        constexpr void _Modify_bit_range(
            _Word_array& _Array, const size_t _Off, const size_t _Count, const bool _Set) noexcept {
            // modify bits in the range [_Off, _Off + _Count) to either 0 or 1 based on the _Set flag
            _Bit_range_modification_state _State;
            _State._Off       = _Off;
            _State._Remaining = _Count;
            _State._Set       = _Set;
            _Bit_range_modification_step _Step;
            for (; _State._Remaining > 0; _State._Idx += _Step._Count) {
                _Step = _Bit_range_modification_step::_Choose(_State._Remaining);
                _Step._Callback(_Array, _State);
            }
        }

        constexpr void _Set_bit_range(_Word_array& _Array, const size_t _Off, const size_t _Count) noexcept {
            // set all bits to 1 in the range [_Off, _Off + _Count)
            _Modify_bit_range(_Array, _Off, _Count, true);
        }

        constexpr void _Clear_bit_range(_Word_array& _Array, const size_t _Off, const size_t _Count) noexcept {
            // set all bits to 0 in the range [_Off, _Off + _Count)
            _Modify_bit_range(_Array, _Off, _Count, false);
        }
    } // namespace mjmem_impl
} // namespace mjx

#endif // _MJMEM_IMPL_BITOPS_HPP_