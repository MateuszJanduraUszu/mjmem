// pool_allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <cstdlib>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/exception.hpp>
#include <mjmem/impl/allocation_tracking.hpp>
#include <mjmem/impl/utils.hpp>
#include <mjmem/object_allocator.hpp>
#include <mjmem/pool_allocator.hpp>
#include <utility>

namespace mjx {
    pool_allocator::pool_allocator(pool_resource& _Resource, const size_type _Max_block_size)
#ifdef _DEBUG
        : _Myres(_Resource), _Mymax((::std::min)(_Max_block_size, _Resource.size())), _Myfbl(),
        _Myabl(mjmem_impl::_Allocated_block_list::_Create()) {
        if (_Mymax != unbounded_block_size) { // maximum block size specified, validate it
            _INTERNAL_ASSERT(
                _Myres.size() >= _Mymax, "maximum block size cannot exceed the total pool resource size");
        }
#else // ^^^ _DEBUG ^^^ / vvv NDEBUG vvv
        : _Myres(_Resource), _Mymax((::std::min)(_Max_block_size, _Resource.size())), _Myfbl() {
#endif // _DEBUG
        _Myfbl._Release_block(0, _Myres.size());
    }

    pool_allocator::~pool_allocator() noexcept {
#ifdef _DEBUG
        mjmem_impl::_Allocated_block_list::_Delete(_Myabl);
#endif // _DEBUG
    }

    pool_allocator::_Free_block_list::_Free_block_list() noexcept : _Myhead(nullptr), _Mysize(0) {}

    pool_allocator::_Free_block_list::~_Free_block_list() noexcept {
        if (_Myhead) { // deallocate all nodes
            dynamic_allocator _Al;
            for (_List_node* _Node = _Myhead, *_Next; _Node != nullptr; _Node = _Next) {
                _Next = _Node->_Next;
                ::mjx::delete_object_using_allocator(_Node, _Al);
            }

            _Myhead = nullptr;
            _Mysize = 0;
        }
    }

    pool_allocator::_Free_block_list::_List_node* pool_allocator::_Free_block_list::_List_node::_Create() {
        dynamic_allocator _Al;
        return ::mjx::create_object_using_allocator<_List_node>(_Al);
    }
    
    void pool_allocator::_Free_block_list::_List_node::_Delete(_List_node* const _Node) noexcept {
        dynamic_allocator _Al;
        ::mjx::delete_object_using_allocator(_Node, _Al);
    }

    void pool_allocator::_Free_block_list::_Unlink_node_directly(
        _List_node* const _Prev, _List_node* const _Node) noexcept {
        if (_Prev) { // break connection with the previous node
            _Prev->_Next = _Node->_Next;
        } else { // set a new head
            _Myhead = _Node->_Next;
        }
    }

    void pool_allocator::_Free_block_list::_Unlink_node_indirectly(_List_node* const _Node) noexcept {
        if (_Node == _Myhead) { // set a new head
            _Myhead = _Myhead->_Next;
            return;
        }

        _List_node* _Prev    = nullptr;
        _List_node* _Current = _Myhead;
        while (_Current && _Current != _Node) { // search for _Node's parent
            _Prev    = _Current;
            _Current = _Current->_Next;
        }

        if (_Current == _Node) { // _Node's parent found, unlink _Node
            _Unlink_node_directly(_Prev, _Node);
        }
    }

    void pool_allocator::_Free_block_list::_Delete_node_directly(
        _List_node* const _Prev, _List_node* const _Node) noexcept {
        _Unlink_node_directly(_Prev, _Node);
        _List_node::_Delete(_Node);
        --_Mysize;
    }

    void pool_allocator::_Free_block_list::_Delete_node_indirectly(_List_node* const _Node) noexcept {
        _Unlink_node_indirectly(_Node);
        _List_node::_Delete(_Node);
        --_Mysize;
    }

    void pool_allocator::_Free_block_list::_Insert_node(_List_node* const _New_node) noexcept {
        if (!_Myhead || _Myhead->_Off > _New_node->_Off) { // insert before the head
            _New_node->_Next = _Myhead;
            _Myhead          = _New_node;
            return;
        }

        _List_node* _Node = _Myhead;
        while (_Node->_Next && _Node->_Next->_Off < _New_node->_Off) {
            // search for the next block to insert before it
            _Node = _Node->_Next;
        }

        _New_node->_Next = _Node->_Next;
        _Node->_Next     = _New_node;
    }

    bool pool_allocator::_Free_block_list::_Merge_contiguous_block_before(
        _List_node* const _Prev, _List_node* const _Node, const size_type _Off, const size_type _Size) noexcept {
        if (_Off + _Size == _Node->_Off) { // merge the block with _Node
            _Node->_Off  -= _Size;
            _Node->_Size += _Size;
            if (_Prev && _Prev->_Off + _Prev->_Size == _Node->_Off) { // merge _Prev with _Node
                _Node->_Off  -= _Prev->_Size;
                _Node->_Size += _Prev->_Size;
                _Delete_node_indirectly(_Prev);
            }

            return true;
        }

        return false;
    }

    bool pool_allocator::_Free_block_list::_Merge_contiguous_block_after(
        _List_node* const _Node, const size_type _Off, const size_type _Size) noexcept {
        if (_Node->_Off + _Node->_Size == _Off) { // merge block with _Node
            _Node->_Size += _Size;
            if (_Node->_Next && _Node->_Off + _Node->_Size == _Node->_Next->_Off) { // merge _Node with _Node->_Next
                _Node->_Size += _Node->_Next->_Size;
                _Delete_node_directly(_Node, _Node->_Next);
            }

            return true;
        }

        return false;
    }

    bool pool_allocator::_Free_block_list::_Merge_block(const size_type _Off, const size_type _Size) noexcept {
        for (_List_node* _Node = _Myhead, *_Prev = nullptr; _Node != nullptr; _Prev = _Node, _Node = _Node->_Next) {
            if (_Merge_contiguous_block_before(_Prev, _Node, _Off, _Size)
                || _Merge_contiguous_block_after(_Node, _Off, _Size)) { // block merged, break
                return true;
            }
        }

        return false;
    }

    void pool_allocator::_Free_block_list::_Release_block_zero(const size_type _Size) {
        if (_Myhead && _Myhead->_Off == _Size) { // merge block to the head
            _Myhead->_Off   = 0;
            _Myhead->_Size += _Size;
            return;
        }

        _List_node* const _New_node = _List_node::_Create();
        _New_node->_Off             = 0;
        _New_node->_Size            = _Size;
        if (_Myhead) { // insert before the head
            _New_node->_Next = _Myhead;
            _Myhead          = _New_node;
        } else { // set a new head
            _Myhead = _New_node;
        }

        ++_Mysize;
    }

    pool_allocator::size_type pool_allocator::_Free_block_list::_Reserve_block(const size_type _Size) noexcept {
        _List_node* _Selected = nullptr;
        _List_node* _Prev     = nullptr;
        for (_List_node* _Node = _Myhead; _Node != nullptr; _Prev = _Node, _Node = _Node->_Next) {
            if (_Node->_Size == _Size) { // exact match, use the whole block
                const size_type _Off = _Node->_Off;
                _Delete_node_directly(_Prev, _Node);
                return _Off;
            }

            if (_Node->_Size > _Size && (!_Selected || _Node->_Size < _Selected->_Size)) {
                // either no node is selected or a better candidate is found
                _Selected = _Node;
            }
        }

        if (!_Selected) { // no suitable block found
            return static_cast<size_type>(-1);
        }

        // use part of the selected block
        const size_type _Off = _Selected->_Off;
        _Selected->_Off     += _Size;
        _Selected->_Size    -= _Size;
        return _Off;
    }

    void pool_allocator::_Free_block_list::_Release_block(const size_type _Off, const size_type _Size) {
        if (_Off == 0) { // release a block whose offset is zero (always the first block)
            _Release_block_zero(_Size);
            return;
        }

        if (_Merge_block(_Off, _Size)) { // block merged, break
            return;
        }

        _List_node* const _New_node = _List_node::_Create();
        _New_node->_Off             = _Off;
        _New_node->_Size            = _Size;
        if (_Myhead) { // insert a new node
            _Insert_node(_New_node);
        } else { // set a new head
            _Myhead = _New_node;
        }

        ++_Mysize;
    }

    pool_allocator::pointer pool_allocator::_Allocate(const size_type _Count) noexcept {
        if (_Count > _Mymax) { // requested too much memory, break
            return nullptr;
        }

        const size_type _Off = _Myfbl._Reserve_block(_Count);
        return _Off != static_cast<size_type>(-1)
            ? mjmem_impl::_Adjust_address_by_offset(_Myres.data(), _Off) : nullptr;
    }

    pool_allocator::pointer pool_allocator::allocate(const size_type _Count) {
        if (_Count == 0) { // no allocation, do nothing
            return nullptr;
        }

        pointer _Ptr = _Allocate(_Count);
        if (!_Ptr) { // not enough memory, raise an exception
            allocation_failure::raise();
        }

#ifdef _DEBUG
        _Myabl->_Register_block(mjmem_impl::_Memory_block{_Ptr, _Count});
#endif // _DEBUG
        return _Ptr;
    }

    pool_allocator::pointer pool_allocator::allocate_aligned(const size_type _Count, const size_type _Align) {
#ifdef _DEBUG
        _INTERNAL_ASSERT(mjmem_impl::_Is_pow_of_2(_Align), "alignment must be a power of 2");
#endif // _DEBUG
        return allocate(mjmem_impl::_Align_value(_Count, _Align));
    }

    void pool_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        if (!_Myres.contains(_Ptr, _Count)) { // _Ptr doesn't originate from the associated resource
            return;
        }

#ifdef _DEBUG
        const mjmem_impl::_Memory_block _Block = {_Ptr, _Count};
        if (!_Myabl->_Is_block_registered(_Block)) { // block not registered, break
            return;
        }
#endif // _DEBUG

        try {
            _Myfbl._Release_block(mjmem_impl::_Calculate_offset_from_address(_Myres.data(), _Ptr), _Count);
#ifdef _DEBUG
            _Myabl->_Unregister_block(_Block);
#endif // _DEBUG
        } catch (...) {
            // Note: Since deallocate() must be 'noexcept', it cannot throw any exceptions internally.
            //       In debug mode, _INTERNAL_ASSERT provides helpful feedback by reporting the failure.
            //       However, in release mode, _INTERNAL_ASSERT doesn't report any messages. Therefore,
            //       abort() is called in release mode to terminate the program immediately, as such
            //       failure can lead to various unexpected and unpredictable behaviors.
#ifdef _DEBUG
            _REPORT_ERROR("allocation failure during block release");
#else // ^^^ _DEBUG ^^^ / vvv NDEBUG vvv
            ::abort();
#endif // _DEBUG
        }
    }

    pool_allocator::size_type pool_allocator::max_size() const noexcept {
        return _Mymax;
    }

    bool pool_allocator::is_equal(const allocator& _Other) const noexcept {
        // cast to a pointer to avoid a bad_cast exception
        const pool_allocator* const _Other_ptr = dynamic_cast<const pool_allocator*>(::std::addressof(_Other));
        return _Other_ptr ? _Myres == _Other_ptr->_Myres && _Mymax == _Other_ptr->_Mymax : false;
    }

    const pool_resource& pool_allocator::resource() const noexcept {
        return _Myres;
    }
} // namespace mjx