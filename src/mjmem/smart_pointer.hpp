// smart_pointer.hpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _MJMEM_SMART_POINTER_HPP_
#define _MJMEM_SMART_POINTER_HPP_
#include <mjmem/exception.hpp>
#include <mjmem/object_allocator.hpp>
#include <type_traits>
#include <utility>

namespace mjx {
    template <class _Ty1, class _Ty2, bool = ::std::is_empty_v<_Ty2> && !::std::is_final_v<_Ty2>>
    class optimized_pair : public _Ty2 { // store T1 and derive from T2, optimization active
    public:
        using first_type  = _Ty1;
        using second_type = _Ty2;

        optimized_pair() noexcept(::std::is_nothrow_default_constructible_v<_Ty1>
            && ::std::is_nothrow_default_constructible_v<_Ty2>) : _Myval(), _Ty2() {}

        optimized_pair(const _Ty1& _Val1, const _Ty2& _Val2) noexcept(
            ::std::is_nothrow_copy_constructible_v<_Ty1> && ::std::is_nothrow_copy_constructible_v<_Ty2>)
            : _Myval(_Val1), _Ty2(_Val2) {}

        optimized_pair(_Ty1&& _Val1, _Ty2&& _Val2) noexcept(::std::is_nothrow_move_constructible_v<_Ty1>
            && ::std::is_nothrow_move_constructible_v<_Ty2>)
            : _Myval(::std::move(_Val1)), _Ty2(::std::move(_Val2)) {}

        optimized_pair(const optimized_pair&) = default;
        optimized_pair(optimized_pair&&)      = default;

        optimized_pair& operator=(const optimized_pair& _Other) noexcept(
            ::std::is_nothrow_copy_assignable_v<_Ty1> && ::std::is_nothrow_copy_assignable_v<_Ty2>) {
            if (this != ::std::addressof(_Other)) {
                _Myval                    = _Other._Myval;
                static_cast<_Ty2&>(*this) = static_cast<const _Ty2&>(_Other);
            }

            return *this;
        }

        optimized_pair& operator=(optimized_pair&& _Other) noexcept(
            ::std::is_nothrow_move_assignable_v<_Ty1> && ::std::is_nothrow_move_assignable_v<_Ty2>) {
            if (this != ::std::addressof(_Other)) {
                _Myval                    = ::std::move(_Other);
                static_cast<_Ty2&>(*this) = static_cast<_Ty2&&>(_Other);
            }

            return *this;
        }

        first_type& first() noexcept {
            return _Myval;
        }

        const first_type& first() const noexcept {
            return _Myval;
        }

        second_type& second() noexcept {
            return *this;
        }

        const second_type& second() const noexcept {
            return *this;
        }

        void swap(optimized_pair& _Other) noexcept(
            ::std::is_nothrow_swappable_v<_Ty1> && ::std::is_nothrow_swappable_v<_Ty2>) {
            ::std::swap(_Myval, _Other._Myval);
            ::std::swap(static_cast<_Ty2&>(*this), static_cast<_Ty2&>(_Other));
        }

    private:
        _Ty1 _Myval;
    };

    template <class _Ty1, class _Ty2>
    class optimized_pair<_Ty1, _Ty2, false> { // store both T1 and T2, optimization inactive
    public:
        using first_type  = _Ty1;
        using second_type = _Ty2;
    
        optimized_pair() noexcept(::std::is_nothrow_default_constructible_v<_Ty1>
            && ::std::is_nothrow_default_constructible_v<_Ty2>) : _Myval1(), _Myval2() {}

        optimized_pair(const _Ty1& _Val1, const _Ty2& _Val2) noexcept(
            ::std::is_nothrow_copy_constructible_v<_Ty1> && ::std::is_nothrow_copy_constructible_v<_Ty2>)
            : _Myval1(_Val1), _Myval2(_Val2) {}

        optimized_pair(_Ty1&& _Val1, _Ty2&& _Val2) noexcept(::std::is_nothrow_move_constructible_v<_Ty1>
            && ::std::is_nothrow_move_constructible_v<_Ty2>)
            : _Myval1(::std::move(_Val1)), _Myval2(::std::move(_Val2)) {}

        ~optimized_pair() noexcept {}

        optimized_pair(const optimized_pair&) = default;
        optimized_pair(optimized_pair&&)      = default;

        optimized_pair& operator=(const optimized_pair& _Other) noexcept(
            ::std::is_nothrow_copy_assignable_v<_Ty1> && ::std::is_nothrow_copy_assignable_v<_Ty2>) {
            if (this != ::std::addressof(_Other)) {
                _Myval1 = _Other._Myval1;
                _Myval2 = _Other._Myval2;
            }

            return *this;
        }

        optimized_pair& operator=(optimized_pair&& _Other) noexcept(
            ::std::is_nothrow_move_assignable_v<_Ty1> && ::std::is_nothrow_move_assignable_v<_Ty2>) {
            if (this != ::std::addressof(_Other)) {
                _Myval1 = ::std::move(_Other._Myval1);
                _Myval2 = ::std::move(_Other._Myval2);
            }

            return *this;
        }

        first_type& first() noexcept {
            return _Myval1;
        }

        const first_type& first() const noexcept {
            return _Myval1;
        }

        second_type& second() noexcept {
            return _Myval2;
        }

        const second_type& second() const noexcept {
            return _Myval2;
        }

        void swap(optimized_pair& _Other) noexcept(
            ::std::is_nothrow_swappable_v<_Ty1> && ::std::is_nothrow_swappable_v<_Ty2>) {
            ::std::swap(_Myval1, _Other._Myval1);
            ::std::swap(_Myval2, _Other._Myval2);
        }

    private:
        _Ty1 _Myval1;
        _Ty2 _Myval2;
    };

    template <class _Ty1, class _Ty2>
    inline bool operator==(
        const optimized_pair<_Ty1, _Ty2>& _Left, const optimized_pair<_Ty1, _Ty2>& _Right) {
        return _Left.first() == _Right.first() && _Left.second() == _Right.second();
    }

    template <class _Ty1, class _Ty2>
    inline bool operator!=(
        const optimized_pair<_Ty1, _Ty2>& _Left, const optimized_pair<_Ty1, _Ty2>& _Right) {
        return !(_Left == _Right);
    }

    template <class _Ty1, class _Ty2>
    inline optimized_pair<_Ty1, _Ty2> make_optimized_pair(_Ty1&& _Val1, _Ty2&& _Val2) noexcept(
        ::std::is_nothrow_move_constructible_v<_Ty1> && ::std::is_nothrow_move_constructible_v<_Ty2>) {
        return optimized_pair<_Ty1, _Ty2>(::std::move(_Val1), ::std::move(_Val2));
    }

    template <class _Ty>
    struct default_pointer_deleter { // default deleter for any smart pointer
        default_pointer_deleter() noexcept = default;

        void operator()(_Ty* const _Ptr) const noexcept {
            ::mjx::delete_object(_Ptr);
        }
    };

    template <class _Ty>
    struct default_array_deleter { // default deleter for array types in smart pointers
        default_array_deleter() noexcept = default;

        void operator()(_Ty* const _Ptr, const size_t _Size) const noexcept {
            ::mjx::delete_objects(_Ptr, _Size);
        }
    };

    template <class _Ty, class _Deleter = default_pointer_deleter<_Ty>>
    class unique_ptr { // smart pointer with unique object ownership semantics
    public:
        using element_type = _Ty;
        using pointer      = _Ty*;
        using deleter_type = _Deleter;

        unique_ptr() noexcept : _Mypair() {}

        unique_ptr(nullptr_t) noexcept : _Mypair() {}

        explicit unique_ptr(pointer _Ptr) noexcept : _Mypair(_Ptr, _Deleter{}) {}

        unique_ptr(pointer _Ptr, const _Deleter& _Del) noexcept : _Mypair(_Ptr, _Del) {}

        unique_ptr(pointer _Ptr, _Deleter&& _Del) noexcept : _Mypair(_Ptr, ::std::move(_Del)) {}

        unique_ptr(unique_ptr&& _Other) noexcept
            : _Mypair(_Other.release(), ::std::move(_Other._Mypair.second())) {}

        ~unique_ptr() noexcept {
            pointer& _Ptr = _Mypair.first();
            if (_Ptr) {
                _Mypair.second()(_Ptr);
                _Ptr = nullptr;
            }
        }

        unique_ptr& operator=(unique_ptr&& _Other) noexcept {
            reset(_Other.release());
            _Mypair.second() = ::std::forward<_Deleter>(_Other._Mypair.second());
            return *this;
        }

        unique_ptr& operator=(nullptr_t) noexcept {
            reset();
            return *this;
        }

        unique_ptr(const unique_ptr&)            = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

        explicit operator bool() const noexcept {
            return _Mypair.first() != nullptr;
        }

        ::std::add_lvalue_reference_t<_Ty> operator*() const noexcept(noexcept(*::std::declval<pointer>())) {
            return *_Mypair.first();
        }

        pointer operator->() const noexcept {
            return _Mypair.first();
        }

        pointer get() const noexcept {
            return _Mypair.first();
        }

        deleter_type& get_deleter() noexcept {
            return _Mypair.second();
        }

        const deleter_type& get_deleter() const noexcept {
            return _Mypair.second();
        }

        pointer release() noexcept {
            pointer& _Ptr    = _Mypair.first();
            pointer _Old_ptr = _Ptr;
            _Ptr             = nullptr;
            return _Old_ptr;
        }

        void reset(pointer _New_ptr = nullptr) noexcept {
            pointer& _Ptr = _Mypair.first();
            if (_Ptr) {
                _Mypair.second()(_Ptr);
            }

            _Ptr = _New_ptr;
        }

        void swap(unique_ptr& _Other) noexcept {
            _Mypair.swap(_Other._Mypair);
        }

    private:
        optimized_pair<pointer, _Deleter> _Mypair;
    };

    template <class _Ty, class _Deleter>
    inline bool operator==(const unique_ptr<_Ty, _Deleter>& _Left, const unique_ptr<_Ty, _Deleter>& _Right) {
        return _Left.get() == _Right.get();
    }

    template <class _Ty, class _Deleter>
    inline bool operator==(const unique_ptr<_Ty, _Deleter>& _Unique, nullptr_t) {
        return !_Unique;
    }

    template <class _Ty, class _Deleter>
    inline bool operator==(nullptr_t, const unique_ptr<_Ty, _Deleter>& _Unique) {
        return !_Unique;
    }

    template <class _Ty, class _Deleter>
    inline bool operator!=(const unique_ptr<_Ty, _Deleter>& _Left, const unique_ptr<_Ty, _Deleter>& _Right) {
        return _Left.get() != _Right.get();
    }

    template <class _Ty, class _Deleter>
    inline bool operator!=(const unique_ptr<_Ty, _Deleter>& _Unique, nullptr_t) {
        return static_cast<bool>(_Unique);
    }

    template <class _Ty, class _Deleter>
    inline bool operator!=(nullptr_t, const unique_ptr<_Ty, _Deleter>& _Unique) {
        return static_cast<bool>(_Unique);
    }

    template <class _Ty, class _Deleter = default_array_deleter<_Ty>>
    class unique_array { // exclusive ownership smart pointer for arrays
    public:
        using element_type = _Ty;
        using pointer      = _Ty*;
        using deleter_type = _Deleter;

        struct array {
            pointer ptr = nullptr;
            size_t size = 0;
        };

        unique_array() noexcept : _Mypair() {}

        unique_array(nullptr_t) noexcept : _Mypair() {}

        unique_array(pointer _Ptr, const size_t _Size) noexcept : _Mypair(array{_Ptr, _Size}, _Deleter{}) {}

        unique_array(pointer _Ptr, const size_t _Size, const _Deleter& _Del) noexcept
            : _Mypair(array{_Ptr, _Size}, _Del) {}

        unique_array(pointer _Ptr, const size_t _Size, _Deleter&& _Del) noexcept
            : _Mypair(array{_Ptr, _Size}, ::std::move(_Del)) {}

        unique_array(unique_array&& _Other) noexcept
            : _Mypair(_Other.release(), ::std::move(_Other._Mypair.second())) {}

        ~unique_array() noexcept {
            array& _Array = _Mypair.first();
            if (_Array.ptr) {
                _Mypair.second()(_Array.ptr, _Array.size);
                _Array.ptr  = nullptr;
                _Array.size = 0;
            }
        }

        unique_array& operator=(unique_array&& _Other) noexcept {
            const array& _Array = _Other.release();
            reset(_Array.ptr, _Array.size);
            _Mypair.second() = ::std::forward<_Deleter>(_Other._Mypair.second());
            return *this;
        }

        unique_array& operator=(nullptr_t) noexcept {
            reset();
            return *this;
        }

        unique_array(const unique_array&)            = delete;
        unique_array& operator=(const unique_array&) = delete;

        explicit operator bool() const noexcept {
            return _Mypair.first().ptr != nullptr;
        }

        ::std::add_lvalue_reference_t<_Ty> operator*() const noexcept(noexcept(*::std::declval<pointer>())) {
            return *_Mypair.first().ptr;
        }

        pointer operator->() const noexcept {
            return _Mypair.first().ptr;
        }

        _Ty& operator[](const size_t _Idx) const {
            const array& _Array = _Mypair.first();
            if (_Idx >= _Array.size) {
                resource_overrun::raise();
            }

            return _Array.ptr[_Idx];
        }

        pointer get() const noexcept {
            return _Mypair.first().ptr;
        }

        size_t size() const noexcept {
            return _Mypair.first().size;
        }

        deleter_type& get_deleter() noexcept {
            return _Mypair.second();
        }

        const deleter_type& get_deleter() const noexcept {
            return _Mypair.second();
        }

        array release() noexcept {
            array& _Array    = _Mypair.first();
            array _Old_array = {_Array.ptr, _Array.size};
            _Array.ptr       = nullptr;
            _Array.size      = 0;
            return _Old_array;
        }

        void reset(pointer _New_ptr, const size_t _New_size) noexcept {
            array& _Array = _Mypair.first();
            if (_Array.ptr) {
                _Mypair.second()(_Array.ptr, _Array.size);
            }

            _Array.ptr  = _New_ptr;
            _Array.size = _New_size;
        }

        void reset(nullptr_t = nullptr) noexcept {
            array& _Array = _Mypair.first();
            if (_Array.ptr) {
                _Mypair.second()(_Array.ptr, _Array.size);
                _Array.ptr  = nullptr;
                _Array.size = 0;
            }
        }

        void swap(unique_array& _Other) noexcept {
            _Mypair.swap(_Other._Mypair);
        }

    private:
        optimized_pair<array, _Deleter> _Mypair;
    };

    template <class _Ty, class _Deleter>
    inline bool operator==(
        const unique_array<_Ty, _Deleter>& _Left, const unique_array<_Ty, _Deleter>& _Right) {
        return _Left.get() == _Right.get();
    }

    template <class _Ty, class _Deleter>
    inline bool operator==(const unique_array<_Ty, _Deleter>& _Unique, nullptr_t) {
        return !_Unique;
    }

    template <class _Ty, class _Deleter>
    inline bool operator==(nullptr_t, const unique_array<_Ty, _Deleter>& _Unique) {
        return !_Unique;
    }

    template <class _Ty, class _Deleter>
    inline bool operator!=(
        const unique_array<_Ty, _Deleter>& _Left, const unique_array<_Ty, _Deleter>& _Right) {
        return _Left.get() != _Right.get();
    }

    template <class _Ty, class _Deleter>
    inline bool operator!=(const unique_array<_Ty, _Deleter>& _Unique, nullptr_t) {
        return static_cast<bool>(_Unique);
    }

    template <class _Ty, class _Deleter>
    inline bool operator!=(nullptr_t, const unique_array<_Ty, _Deleter>& _Unique) {
        return static_cast<bool>(_Unique);
    }

    template <class _Ty, class... _Types>
    inline unique_ptr<_Ty> make_unique_ptr(_Types&&... _Args) {
        return unique_ptr<_Ty>(::mjx::create_object<_Ty>(::std::forward<_Types>(_Args)...));
    }

    template <class _Ty>
    inline unique_array<_Ty> make_unique_array(const size_t _Size) {
        return unique_array<_Ty>(::mjx::allocate_objects<_Ty>(_Size), _Size);
    }
} // namespace mjx

#endif // _MJMEM_SMART_POINTER_HPP_