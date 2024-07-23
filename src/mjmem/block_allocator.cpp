// block_allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <cstring>
#include <mjmem/block_allocator.hpp>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/exception.hpp>
#include <mjmem/impl/allocation_tracking.hpp>
#include <mjmem/impl/bitops.hpp>
#include <mjmem/impl/utils.hpp>
#include <mjmem/object_allocator.hpp>

namespace mjx {
    block_allocator::block_allocator(pool_resource& _Resource, const size_type _Block_size)
#ifdef _DEBUG
        : _Myres(_Resource), _Myblock(_Block_size), _Mymap(),
        _Myabl(mjmem_impl::_Allocated_block_list::_Create()) {
        // Note: The _Block_size must always be less than or equal to '_Resource.size()'.
        //       Although not explicitly checked, the assertion below will catch any issues.
        //       In the expression 'x % y', where 'x < y', the result is always 'y - x',
        //       which will fail the assertion, expecting the remainder to be 0.
        _INTERNAL_ASSERT(_Resource.size() % _Block_size == 0, "resource size must be a multiple of block size");
#else // ^^^ _DEBUG ^^^ / vvv NDEBUG vvv
        : _Myres(_Resource), _Myblock(_Block_size), _Mymap() {
#endif // _DEBUG
        _Init_bitmap();
    }

    block_allocator::~block_allocator() noexcept {
#ifdef _DEBUG
        mjmem_impl::_Allocated_block_list::_Delete(_Myabl);
#endif // _DEBUG
    }

    block_allocator::_Bitmap::_Bitmap() noexcept : _Buf{0}, _Size(0), _Free(0) {
        // starts lifetime of small buffer by default
    }

    block_allocator::_Bitmap::~_Bitmap() noexcept {
        if (_Size > _Small_buffer_size) { // deallocate larger buffer
            dynamic_allocator _Al;
            ::mjx::delete_object_array_using_allocator(_Ptr, _Size, _Al);
        }
    }

    block_allocator::_Bitmap::_Word_type* block_allocator::_Bitmap::_Get_words() noexcept {
        return _Size <= _Small_buffer_size ? _Buf : _Ptr;
    }

    const block_allocator::_Bitmap::_Word_type* block_allocator::_Bitmap::_Get_words() const noexcept {
        return _Size <= _Small_buffer_size ? _Buf : _Ptr;
    }

    void block_allocator::_Init_bitmap() {
        using _Word_type       = _Bitmap::_Word_type;
        using _Traits          = mjmem_impl::_Word_traits<_Word_type>;
        const size_type _Bits  = _Total_block_count(); // required number of bits
        const size_type _Words = (_Bits + _Traits::_Bits_per_word - 1) / _Traits::_Bits_per_word;
        if (_Words > _Bitmap::_Small_buffer_size) { // use larger buffer
            dynamic_allocator _Al;
            const size_type _Bytes = _Words * sizeof(_Word_type); // number of bytes to allocate
            _Mymap._Ptr            = static_cast<_Word_type*>(_Al.allocate(_Bytes));
            ::memset(_Mymap._Ptr, 0, _Bytes); // make sure each bit is set to 0
        }
        
        _Mymap._Size = _Words;
        _Mymap._Free = _Bits;
    }

    block_allocator::size_type block_allocator::_Least_block_count(const size_type _Bytes) const noexcept {
        // calculate the least number of blocks that will fit the given number of bytes
        return (_Bytes + _Myblock - 1) / _Myblock;
    }

    block_allocator::size_type block_allocator::_Total_block_count() const noexcept {
        // calculate the total number of fixed-size blocks
        return _Myres.size() / _Myblock;
    }

    block_allocator::pointer block_allocator::_Allocate_blocks(const size_type _Count) noexcept {
        if (_Mymap._Free < _Count) { // not enough free blocks
            return nullptr;
        }
        
        mjmem_impl::_Word_array _Array(_Mymap._Get_words(), _Mymap._Size, _Total_block_count());
        const size_type _Off = mjmem_impl::_Find_contiguous_zero_bits(_Array, _Count);
        if (_Off == static_cast<size_type>(-1)) { // not enough free space, break
            return nullptr;
        }

        mjmem_impl::_Set_bit_range(_Array, _Off, _Count); // mark the allocated blocks as used
        return mjmem_impl::_Adjust_address_by_offset(_Myres.data(), _Off * _Myblock);
    }

    block_allocator::pointer block_allocator::allocate(const size_type _Count) {
        if (_Count == 0) { // no allocation, do nothing
            return nullptr;
        }

        const size_type _Blocks = _Least_block_count(_Count);
        pointer _Ptr            = _Allocate_blocks(_Blocks);
        if (!_Ptr) { // not enough free space, raise an exception
            allocation_failure::raise();
        }

#ifdef _DEBUG
        _Myabl->_Register_block(mjmem_impl::_Memory_block{_Ptr, _Blocks * _Myblock});
#endif // _DEBUG
        _Mymap._Free -= _Blocks; // update the number of free blocks
        return _Ptr;
    }

    block_allocator::pointer block_allocator::allocate_aligned(const size_type _Count, const size_type _Align) {
#ifdef _DEBUG
        _INTERNAL_ASSERT(mjmem_impl::_Is_pow_of_2(_Align), "alignment must be a power of 2");
#endif // _DEBUG
        return allocate(mjmem_impl::_Align_value(_Count, _Align));
    }

    void block_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        const size_type _Blocks = _Least_block_count(_Count);
        const size_type _Bytes  = _Blocks * _Myblock;
        if (!_Myres.contains(_Ptr, _Bytes)) { // _Ptr doesn't originate from the associated resource
            return;
        }

#ifdef _DEBUG
        const mjmem_impl::_Memory_block _Block = {_Ptr, _Bytes};
        if (!_Myabl->_Is_block_registered(_Block)) { // block not registered, report an error
            _REPORT_ERROR("attempt to deallocate a non-allocated block");
        }
#endif // _DEBUG

        mjmem_impl::_Word_array _Array(_Mymap._Get_words(), _Mymap._Size);
        mjmem_impl::_Clear_bit_range(
            _Array, mjmem_impl::_Calculate_offset_from_address(_Myres.data(), _Ptr) / _Myblock, _Blocks);
        _Mymap._Free += _Blocks; // update the number of free blocks
#ifdef _DEBUG
        _Myabl->_Unregister_block(_Block);
#endif // _DEBUG
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