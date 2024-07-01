// block_allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <cstring>
#include <mjmem/block_allocator.hpp>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/exception.hpp>
#include <mjmem/impl/utils.hpp>
#include <utility>

namespace mjx {
    block_allocator::block_allocator(pool_resource& _Resource, const size_type _Block_size)
        : _Myres(_Resource), _Myblock(_Block_size), _Mymap() {
#ifdef _DEBUG
        // Note: The _Block_size must always be less than or equal to '_Resource.size()'.
        //       Although not explicitly checked, the assertion below will catch any issues.
        //       In the expression 'x % y', where 'x < y', the result is always 'y - x',
        //       which will fail the assertion, expecting the remainder to be 0.
        _INTERNAL_ASSERT(_Resource.size() % _Block_size == 0, "resource size must be a multiple of block size");
#endif // _DEBUG
        _Setup_bitmap();
    }

    block_allocator::~block_allocator() noexcept {}

    block_allocator::_Bitmap::_Bitmap() noexcept : _Buf{0}, _Size(0), _Free(0) {
        // starts lifetime of small buffer by default
    }

    block_allocator::_Bitmap::~_Bitmap() noexcept {
        if (_Size > _Small_buffer_size) { // deallocate larger buffer
            dynamic_allocator _Al;
            _Al.deallocate(_Ptr, _Size * sizeof(_Word_type));
        }
    }

    block_allocator::_Bitmap::_Word_type* block_allocator::_Bitmap::_Get_words() noexcept {
        return _Size <= _Small_buffer_size ? _Buf : _Ptr;
    }

    const block_allocator::_Bitmap::_Word_type* block_allocator::_Bitmap::_Get_words() const noexcept {
        return _Size <= _Small_buffer_size ? _Buf : _Ptr;
    }

    block_allocator::size_type block_allocator::_Bitmap::_Bits_per_last_word(const size_type _Max) const noexcept {
        return _Bits_per_word - ((_Size * _Bits_per_word) % _Max);
    }

    block_allocator::size_type block_allocator::_Bitmap::_Find_zero_bits(
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

    void block_allocator::_Bitmap::_Set_bits(size_type _Off, size_type _Count) noexcept {
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

    void block_allocator::_Bitmap::_Zero_bits(size_type _Off, size_type _Count) noexcept {
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

    void block_allocator::_Setup_bitmap() {
        using _Word_type       = _Bitmap::_Word_type;
        const size_type _Bits  = _Max_blocks(); // required number of bits
        const size_type _Words = (_Bits + _Bitmap::_Bits_per_word - 1) / _Bitmap::_Bits_per_word;
        if (_Words > _Bitmap::_Small_buffer_size) { // use larger buffer
            dynamic_allocator _Al;
            _Mymap._Ptr = static_cast<_Word_type*>(_Al.allocate(_Words * sizeof(_Word_type)));
            ::memset(_Mymap._Ptr, 0, _Words * sizeof(_Word_type)); // make sure each bit stores 0
        }
        
        _Mymap._Size = _Words;
        _Mymap._Free = _Bits;
    }

    block_allocator::size_type block_allocator::_Required_block_count(const size_type _Bytes) const noexcept {
        return mjmem_impl::_Align_value(_Bytes, _Myblock) / _Myblock;
    }

    block_allocator::size_type block_allocator::_Max_blocks() const noexcept {
        return _Myres.size() / _Myblock;
    }

    block_allocator::pointer block_allocator::_Allocate_block() noexcept {
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
                _Bits = _Mymap._Bits_per_last_word(_Max_blocks());
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

    block_allocator::pointer block_allocator::_Allocate_n_blocks(const size_type _Count) noexcept {
        if (_Mymap._Free < _Count) { // not enough free blocks
            return nullptr;
        }
        
        const size_type _Off = _Mymap._Find_zero_bits(_Count, _Max_blocks());
        if (_Off == static_cast<size_type>(-1)) { // not enough space, break
            return nullptr;
        }

        _Mymap._Set_bits(_Off, _Count);
        return static_cast<pointer>(static_cast<unsigned char*>(_Myres.data()) + (_Off * _Myblock));
    }

    block_allocator::pointer block_allocator::allocate(const size_type _Count) {
        const size_type _Blocks = _Required_block_count(_Count);
        pointer _Ptr            = _Blocks == 1 ? _Allocate_block() : _Allocate_n_blocks(_Blocks);
        if (!_Ptr) { // not enough memory, raise an exception
#if _MJMEM_VERSION_SUPPORTED(1, 0, 1)
            allocation_failure::raise();
#else // ^^^ _MJMEM_VERSION_SUPPORTED(1, 0, 1) ^^^ / vvv !_MJMEM_VERSION_SUPPORTED(1, 0, 1) vvv
            pool_exhausted::raise();
#endif // _MJMEM_VERSION_SUPPORTED(1, 0, 1)
        }

        _Mymap._Free -= _Blocks;
        return _Ptr;
    }

    block_allocator::pointer block_allocator::allocate_aligned(const size_type _Count, const size_type _Align) {
#ifdef _DEBUG
        _INTERNAL_ASSERT(mjmem_impl::_Is_pow_of_2(_Align), "alignment must be a power of 2");
#endif // _DEBUG
        return allocate(mjmem_impl::_Align_value(_Count, _Align));
    }

    void block_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        const size_type _Blocks = _Required_block_count(_Count);
        if (_Myres.contains(_Ptr, _Blocks * _Myblock)) { // _Ptr allocated from the associated resource
            _Mymap._Zero_bits((static_cast<unsigned char*>(_Ptr)
                - static_cast<unsigned char*>(_Myres.data())) / _Myblock, _Blocks);
            _Mymap._Free += _Blocks;
        }
    }

    block_allocator::size_type block_allocator::max_size() const noexcept {
        return _Myres.size();
    }

    bool block_allocator::is_equal(const allocator& _Other) const noexcept {
        // cast to a pointer to avoid a bad_cast exception
        const block_allocator* const _Other_ptr = dynamic_cast<const block_allocator*>(::std::addressof(_Other));
        return _Other_ptr ? _Myres == _Other_ptr->_Myres && _Myblock == _Other_ptr->_Myblock : false;
    }

    block_allocator::size_type block_allocator::block_size() const noexcept {
        return _Myblock;
    }

    const pool_resource& block_allocator::resource() const noexcept {
        return _Myres;
    }
} // namespace mjx