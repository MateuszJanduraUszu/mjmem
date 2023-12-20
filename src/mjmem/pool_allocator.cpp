// pool_allocator.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/exception.hpp>
#include <mjmem/impl/utils.hpp>
#include <mjmem/pool_allocator.hpp>
#include <utility>

namespace mjx {
    pool_allocator::pool_allocator(pool_resource& _Resource, const size_type _Max_block_size)
        : _Myres(_Resource), _Mymax((::std::min)(_Max_block_size, _Resource.size())), _Mylist() {
#ifdef _DEBUG
        if (_Mymax != unbounded_block_size) { // maximum block size specified, validate it
            _INTERNAL_ASSERT(
                _Myres.size() >= _Mymax, "maximum block size cannot exceed the total pool resource size")
        }
#endif // _DEBUG

        _Mylist._Release_block(0, _Myres.size());
    }

    pool_allocator::~pool_allocator() noexcept {}

    pool_allocator::_List::_List() noexcept : _Myhead(nullptr), _Mytail(nullptr), _Mysize(0) {}

    pool_allocator::_List::~_List() noexcept {
        if (_Myhead) { // deallocate all nodes
            dynamic_allocator _Al;
            for (_List_node* _Node = _Myhead, *_Next; _Node != nullptr; _Node = _Next) {
                _Next = _Node->_Next;
                _Node->~_List_node();
                _Al.deallocate(_Node, sizeof(_List));
            }

            _Myhead = nullptr;
            _Mytail = nullptr;
            _Mysize = 0;
        }
    }

    pool_allocator::_List_node* pool_allocator::_List::_Create_node() {
        dynamic_allocator _Al;
        return ::new (_Al.allocate(sizeof(_List_node))) _List_node;
    }
    
    void pool_allocator::_List::_Deallocate_node(_List_node* const _Node) noexcept {
        dynamic_allocator _Al;
        _Node->~_List_node();
        _Al.deallocate(_Node, sizeof(_List_node));
    }

    void pool_allocator::_List::_Unlink_node(_List_node* const _Node) noexcept {
        if (_Node->_Prev) { // break connection with the previous node
            _Node->_Prev->_Next = _Node->_Next;
        } else { // set a new head
            _Myhead = _Node->_Next;
        }

        if (_Node->_Next) { // break connection with the next node
            _Node->_Next->_Prev = _Node->_Prev;
        } else { // set a new tail
            _Mytail = _Node->_Prev;
        }
    }

    void pool_allocator::_List::_Delete_node(_List_node* const _Node) noexcept {
        _Unlink_node(_Node);
        _Deallocate_node(_Node);
        --_Mysize;
    }

    void pool_allocator::_List::_Insert_node(_List_node* const _New_node) noexcept {
        _List_node* _Node = _Myhead;
        while (_Node && _Node->_Size > _New_node->_Size) { // search for smaller block to insert before it
            _Node = _Node->_Next;
        }

        if (_Node) { // insert before the tail
            _New_node->_Next = _Node;
            _New_node->_Prev = _Node->_Prev;
            if (_Node->_Prev) { // insert after the head
                _Node->_Prev->_Next = _New_node;
            } else { // insert before the head
                _Myhead = _New_node;
            }

            _Node->_Prev = _New_node;
        } else { // insert after the tail
            _New_node->_Prev = _Mytail;
            _Mytail->_Next   = _New_node;
            _Mytail          = _New_node;
        }
    }

    void pool_allocator::_List::_Reinsert_node(_List_node* const _Node) noexcept {
        _Unlink_node(_Node);
        _Insert_node(_Node);
    }

    bool pool_allocator::_List::_Merge_block(const size_type _Off, const size_type _Size) noexcept {
        for (_List_node* _Node = _Myhead; _Node != nullptr; _Node = _Node->_Next) {
            if (_Node->_Off + _Node->_Size == _Off) { // found appropriate block, merge with it
                _Node->_Size += _Size;
                if (_Node->_Prev && _Node->_Prev->_Size < _Node->_Size) { // re-insert node to keep list sorted
                    _Reinsert_node(_Node);
                }

                return true;
            }
        }

        return false;
    }

    pool_allocator::size_type pool_allocator::_List::_Size() const noexcept {
        return _Mysize;
    }

    pool_allocator::size_type pool_allocator::_List::_Reserve_block(const size_type _Size) noexcept {
        for (_List_node* _Node = _Mytail; _Node != nullptr; _Node = _Node->_Prev) {
            if (_Node->_Size >= _Size) { // found block of at least requested size, use it
                const size_type _Off = _Node->_Off;
                if (_Node->_Size == _Size) { // use the whole block
                    _Delete_node(_Node);
                } else { // use some part of the block
                    _Node->_Off  += _Size;
                    _Node->_Size -= _Size;
                }

                return _Off;
            }
        }

        return static_cast<size_type>(-1); // not found
    }

    void pool_allocator::_List::_Release_block(const size_type _Off, const size_type _Size) {
        if (_Merge_block(_Off, _Size)) { // block merged, break
            return;
        }

        _List_node* const _New_node = _Create_node();
        _New_node->_Off             = _Off;
        _New_node->_Size            = _Size;
        if (_Mytail) { // allocate the next node
            _Insert_node(_New_node);
        } else { // allocate the first node
            _Myhead = _New_node;
            _Mytail = _New_node;
        }

        ++_Mysize;
    }

    pool_allocator::pointer pool_allocator::_Allocate(const size_type _Count) {
        if (_Count > _Mymax) { // requested too much memory, break
            return nullptr;
        }

        const size_type _Off = _Mylist._Reserve_block(_Count);
        return _Off != static_cast<size_type>(-1)
            ? static_cast<pointer>(static_cast<unsigned char*>(_Myres.data()) + _Off) : nullptr;
    }

    pool_allocator::pointer pool_allocator::allocate(const size_type _Count) {
        pointer _Ptr = _Allocate(_Count);
        if (!_Ptr) { // not enough memory, raise an exception
            pool_exhausted::raise();
        }

        return _Ptr;
    }

    pool_allocator::pointer pool_allocator::allocate_aligned(const size_type _Count, const size_type _Align) {
#ifdef _DEBUG
        _INTERNAL_ASSERT(mjmem_impl::_Is_pow_of_2(_Align), "alignment must be a power of 2");
#endif // _DEBUG
        return allocate(mjmem_impl::_Align_value(_Count, _Align));
    }

    void pool_allocator::deallocate(pointer _Ptr, const size_type _Count) noexcept {
        if (_Myres.contains(_Ptr, _Count)) { // _Ptr allocated from the associated resource
            _Mylist._Release_block(
                static_cast<unsigned char*>(_Ptr) - static_cast<unsigned char*>(_Myres.data()), _Count);
        }
    }

    pool_allocator::size_type pool_allocator::max_size() const noexcept {
        return _Mymax;
    }

    bool pool_allocator::is_equal(const allocator& _Al) const noexcept {
        return _Myres == static_cast<const pool_allocator&>(_Al)._Myres;
    }

    pool_allocator::size_type pool_allocator::free_blocks() const noexcept {
        return _Mylist._Size();
    }
} // namespace mjx