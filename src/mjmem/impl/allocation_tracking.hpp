// allocation_tracking.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_IMPL_ALLOCATION_TRACKING_HPP_
#define _MJMEM_IMPL_ALLOCATION_TRACKING_HPP_
#include <cstdlib>
#include <mjmem/dynamic_allocator.hpp>
#include <mjmem/impl/global_allocator.hpp>
#include <mjmem/impl/utils.hpp>
#include <mjmem/object_allocator.hpp>

namespace mjx {
    namespace mjmem_impl {
        struct _Memory_block {
            void* _Ptr   = nullptr;
            size_t _Size = 0;
        };

        constexpr bool operator==(const _Memory_block& _Left, const _Memory_block& _Right) noexcept {
            return _Left._Ptr == _Right._Ptr && _Left._Size == _Right._Size;
        }

        class _Allocated_block_list { // singly-linked list of allocated blocks
        public:
            _Allocated_block_list() noexcept : _Myhead(nullptr), _Mytail(nullptr), _Mysize(0) {}

            ~_Allocated_block_list() noexcept {
                if (_Myhead) { // deallocate all nodes
                    dynamic_allocator& _Al = _Get_internal_allocator();
                    for (_List_node* _Node = _Myhead, *_Next; _Node != nullptr; _Node = _Next) {
                        _Next = _Node->_Next;
                        ::mjx::delete_object_using_allocator(_Node, _Al);
                    }

                    _Myhead = nullptr;
                    _Mytail = nullptr;
                    _Mysize = 0;
                }
            }

            _Allocated_block_list(const _Allocated_block_list&)            = delete;
            _Allocated_block_list& operator=(const _Allocated_block_list&) = delete;

            static _Allocated_block_list* _Create() {
                // create a new list using a stateless allocator to avoid internal errors
                return ::mjx::create_object_using_allocator<_Allocated_block_list>(_Get_internal_allocator());
            }

            static void _Delete(_Allocated_block_list* const _List) noexcept {
                // delete an existing list using a stateless allocator to avoid internal errors
                ::mjx::delete_object_using_allocator(_List, _Get_internal_allocator());
            }

            bool _Is_block_registered(const _Memory_block& _Block) const noexcept {
                // check whether the list has a node that holds the given memory block
                if (_Mysize == 0) { // empty list, definitely not registered
                    return false;
                }

                for (_List_node* _Node = _Myhead; _Node != nullptr; _Node = _Node->_Next) {
                    if (_Node->_Block == _Block) { // searched block found, break
                        return true;
                    }
                }

                return false; // not found
            }

            void _Register_block(const _Memory_block& _Block) noexcept {
                // insert a new node that will hold the given memory block
                try {
                    _List_node* const _New_node = _List_node::_Create();
                    _New_node->_Block           = _Block;
                    if (_Mytail) { // insert a next node
                        _Mytail->_Next = _New_node;
                    } else { // set a new head
                        _Myhead = _New_node;
                    }

                    _Mytail = _New_node; // set a new tail
                    ++_Mysize;
                } catch (...) {
                    // Note: This function must not throw exceptions to maintain allocator::deallocate() noexcept.
                    //       Ignoring exceptions is not advisable, so the function will abort, optionally
                    //       reporting an error in debug mode.
#ifdef _DEBUG
                    _REPORT_ERROR("allocation failure during block registration");
#else // ^^^ _DEBUG ^^^ / vvv NDEBUG vvv
                    ::abort();
#endif // _DEBUG
                }
            }

            void _Unregister_block(const _Memory_block& _Block) noexcept {
                // remove a node that holds the given memory block, do nothing if such a node not exists
                for (_List_node* _Node = _Myhead, *_Prev = nullptr;
                    _Node != nullptr; _Prev = _Node, _Node = _Node->_Next) {
                    if (_Node->_Block == _Block) { // searched block found, remove the node that holds it
                        _Unlink_node(_Prev, _Node);
                        _List_node::_Delete(_Node);
                        --_Mysize;
                        break;
                    }
                }
            }

        private:
            struct _List_node {
                _List_node* _Next = nullptr; // pointer to the next node
                _Memory_block _Block; // the stored block

                static _List_node* _Create() {
                    // create a new node using a stateless allocator to avoid internal errors
                    return ::mjx::create_object_using_allocator<_List_node>(_Get_internal_allocator());
                }

                static void _Delete(_List_node* const _Node) noexcept {
                    // delete an existing node using a stateless allocator to avoid internal errors
                    return ::mjx::delete_object_using_allocator(_Node, _Get_internal_allocator());
                }
            };

            void _Unlink_node(_List_node* const _Prev, _List_node* const _Node) noexcept {
                // unlink _Node using _Prev as the previous node, since _Node has no _Prev pointer
                if (_Prev) { // break connection with the previous node
                    _Prev->_Next = _Node->_Next;
                    if (!_Node->_Next) { // set a new tail
                        _Mytail = _Prev;
                    }
                } else { // set a new head
                    _Myhead = _Node->_Next;
                    if (!_Node->_Next) { // mark the list as empty
                        _Mytail = nullptr;
                    }
                }
            }

            _List_node* _Myhead; // pointer to the first node
            _List_node* _Mytail; // pointer to the last node (for O(1) insertion)
            size_t _Mysize; // total number of nodes
        };
    } // namespace mjmem_impl
} // namespace mjx

#endif // _MJMEM_IMPL_ALLOCATION_TRACKING_HPP_