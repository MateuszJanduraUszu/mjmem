// bitmap_allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <cstring>
#include <mjmem/bitmap_allocator.hpp>
#include <mjmem/exception.hpp>
#include <mjmem/impl/utils.hpp>
#include <utility>

namespace mjx {
    bitmap_allocator::bitmap_allocator(pool_resource& _Resource, const size_type _Block_size)
        : _Myres(_Resource), _Myblock(_Block_size), _Mymap() {
#ifdef _DEBUG
        _INTERNAL_ASSERT(
            _Resource.size() % _Block_size == 0, "resource size must be a multiple of block size");
#endif // _DEBUG
        _Setup_bitmap();
    }

    bitmap_allocator::~bitmap_allocator() noexcept {}

    bitmap_allocator::_Bitmap::_Bitmap() noexcept : _Buf{0}, _Size(0), _Free(0) {
        // starts lifetime of small buffer by default
    }

    bitmap_allocator::_Bitmap::~_Bitmap() noexcept {
        if (_Size > _Small_buffer_size) { // deallocate larger buffer
            heap_allocator _Al;
            _Al.deallocate(_Ptr, _Size * sizeof(_Word_type));
        }
    }

    bitmap_allocator::_Bitmap::_Word_type* bitmap_allocator::_Bitmap::_Get_words() noexcept {
        return _Size <= _Small_buffer_size ? _Buf : _Ptr;
    }

    const bitmap_allocator::_Bitmap::_Word_type* bitmap_allocator::_Bitmap::_Get_words() const noexcept {
        return _Size <= _Small_buffer_size ? _Buf : _Ptr;
    }

    bitmap_allocator::size_type
        bitmap_allocator::_Bitmap::_Bits_per_last_word(const size_type _Max) const noexcept {
        return _Bits_per_word - ((_Size * _Bits_per_word) % _Max);
    }

    bitmap_allocator::size_type bitmap_allocator::_Bitmap::_Find_zero_bits(
        const size_type _Count, const size_type _Max) const noexcept {
        const _Word_type* const _Words = _Get_words();
        size_type _Bits                = _Bits_per_word;
        size_type _Zeros               = 0; // number of zero bits
        size_type _Off; // number of bit
        for (size_type _Word = 0; _Word < _Size; ++_Word) {
            if (_Words[_Word] == _All_bits_set) { // all bits set, skip this word
                continue;
            }

            if (_Word == _Size - 1) { // last word may use less bits
                _Bits = _Bits_per_last_word(_Max);
            }

            for (size_type _Bit = 0; _Bit < _Bits; ++_Bit) {
                if ((_Words[_Word] & (1 << _Bit)) == 0) { // found zero bit
                    if (_Zeros++ == 0) { // set start of this occurence
                        _Off = (_Word * _Bits_per_word) + _Bit;
                    }

                    if (_Zeros == _Count) { // found requested number of zero bits, break
                        return _Off;
                    }
                } else {
                    _Zeros = 0; // reset counter
                }
            }
        }

        return static_cast<size_type>(-1); // not found
    }

    void bitmap_allocator::_Bitmap::_Set_bits(size_type _Off, size_type _Count) noexcept {
        _Word_type* const _Words       = _Get_words();
        size_type _Word                = _Off / _Bits_per_word;
        size_type _Word_remaining_bits = (::std::min)(_Count, _Bits_per_word - (_Off % _Bits_per_word));
        size_type _Shift               = _Off % _Bits_per_word;
        _Word_type _Mask;
        for (;;) {
            if (_Word_remaining_bits == _Bits_per_word) { // set all bits
                _Mask = _All_bits_set;
            } else { // set n bits
                _Mask = static_cast<_Word_type>(((1 << _Word_remaining_bits) - 1) << _Shift);
            }

            _Words[_Word] |= _Mask;
            _Count        -= _Word_remaining_bits;
            if (_Count == 0) { // no more bits to set
                break;
            }

            ++_Word; // advance to the next word
            _Shift               = 0; // start from the first bit, no shifting
            _Word_remaining_bits = (::std::min)(_Bits_per_word, _Count);
        }
    }

    void bitmap_allocator::_Bitmap::_Zero_bits(size_type _Off, size_type _Count) noexcept {
        _Word_type* const _Words       = _Get_words();
        size_type _Word                = _Off / _Bits_per_word;
        size_type _Word_remaining_bits = (::std::min)(_Count, _Bits_per_word - (_Off % _Bits_per_word));
        size_type _Shift               = _Off % _Bits_per_word;
        _Word_type _Mask;
        for (;;) {
            if (_Word_remaining_bits == _Bits_per_word) { // zero all bits
                _Mask = _All_bits_set;
            } else { // zero n bits
                _Mask = static_cast<_Word_type>(((1 << _Word_remaining_bits) - 1) << _Shift);
            }

            _Words[_Word] &= ~_Mask;
            _Count        -= _Word_remaining_bits;
            if (_Count == 0) { // no more bits to set
                break;
            }

            ++_Word; // advance to the next word
            _Shift               = 0; // start from the first bit, no shifting
            _Word_remaining_bits = (::std::min)(_Bits_per_word, _Count);
        }
    }

    void bitmap_allocator::_Setup_bitmap() {
        using _Word_type       = _Bitmap::_Word_type;
        const size_type _Max   = max_size(); // required number of bits
        const size_type _Words = (_Max + _Bitmap::_Bits_per_word - 1) / _Bitmap::_Bits_per_word;
        if (_Words > _Bitmap::_Small_buffer_size) { // use larger buffer
            heap_allocator _Al;
            _Mymap._Ptr = static_cast<_Word_type*>(_Al.allocate(_Words * sizeof(_Word_type)));
            ::memset(_Mymap._Ptr, 0, _Words * sizeof(_Word_type)); // make sure each bit stores 0
        }
        
        _Mymap._Size = _Words;
        _Mymap._Free = _Max;
    }

    bitmap_allocator::pointer bitmap_allocator::_Allocate_block() noexcept {
        if (_Mymap._Free == 0) { // no free blocks
            return nullptr;
        }

        using _Word_type         = _Bitmap::_Word_type;
        _Word_type* const _Words = _Mymap._Get_words();
        size_type _Bits          = _Bitmap::_Bits_per_word;
        for (size_type _Word = 0; _Word < _Mymap._Size; ++_Word) {
            if (_Words[_Word] == _Bitmap::_All_bits_set) { // definitely no free block
                continue;
            }

            if (_Word == _Mymap._Size - 1) { // last word may use less bits
                _Bits = _Mymap._Bits_per_last_word(max_size());
            }

            for (size_type _Bit = 0; _Bit < _Bitmap::_Bits_per_word; ++_Bit) {
                if ((_Words[_Word] & (1 << _Bit)) == 0) { // found free block, use it
                    _Words[_Word] |= 1 << _Bit; // mark as used
                    return static_cast<pointer>(static_cast<unsigned char*>(_Myres.data())
                        + (((_Word * _Bitmap::_Bits_per_word) + _Bit) * _Myblock));
                }
            }
        }

        return nullptr;
    }

    bitmap_allocator::pointer bitmap_allocator::_Allocate_n_blocks(const size_type _Count) noexcept {
        if (_Mymap._Free < _Count) { // not enough free blocks
            return nullptr;
        }
        
        const size_type _Off = _Mymap._Find_zero_bits(_Count, max_size());
        if (_Off == static_cast<size_type>(-1)) { // not enough space, break
            return nullptr;
        }

        _Mymap._Set_bits(_Off, _Count);
        return static_cast<pointer>(static_cast<unsigned char*>(_Myres.data()) + (_Off * _Myblock));
    }

    bitmap_allocator::pointer bitmap_allocator::allocate(const size_type _Count) {
        pointer _Ptr = _Count == 1 ? _Allocate_block() : _Allocate_n_blocks(_Count);
        if (!_Ptr) { // not enough memory, raise an exception
            pool_exhausted::raise();
        }

        _Mymap._Free -= _Count;
        return _Ptr;
    }

    bitmap_allocator::pointer bitmap_allocator::allocate_aligned(const size_type _Count, const size_type) {
        // alignment has no meaning in bitmap allocator (allocates fixed-size blocks)
        return allocate(_Count);
    }

    void bitmap_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        if (_Myres.contains(_Ptr, _Count * _Myblock)) { // _Ptr allocated from the associated resource
            _Mymap._Zero_bits((static_cast<unsigned char*>(_Ptr)
                - static_cast<unsigned char*>(_Myres.data())) / _Myblock, _Count);
            _Mymap._Free += _Count;
        }
    }

    bitmap_allocator::size_type bitmap_allocator::max_size() const noexcept {
        return _Myres.size() / _Myblock;
    }

    bool bitmap_allocator::is_equal(const allocator& _Al) const noexcept {
        return _Myres == static_cast<const bitmap_allocator&>(_Al)._Myres;
    }

    bitmap_allocator::size_type bitmap_allocator::block_size() const noexcept {
        return _Myblock;
    }

    bitmap_allocator::size_type bitmap_allocator::free_blocks() const noexcept {
        return _Mymap._Free;
    }
} // namespace mjx