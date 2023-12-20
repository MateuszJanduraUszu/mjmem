// pool_resource.cpp

// Copyright (c) Mateusz Jandura. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

#include <cstring>
#include <mjmem/pool_resource.hpp>
#include <utility>

namespace mjx {
    pool_resource::pool_resource() noexcept : _Mydata(nullptr), _Mysize(0) {}

    pool_resource::pool_resource(const pool_resource& _Other) : _Mydata(nullptr), _Mysize(0) {
        _Copy_resource(_Other._Mydata, _Other._Mysize);
    }

    pool_resource::pool_resource(pool_resource&& _Other) noexcept : _Mydata(nullptr), _Mysize(0) {
        _Steal_resource(_Other._Mydata, _Other._Mysize);
    }

    pool_resource::pool_resource(const size_type _Size) : _Mydata(nullptr), _Mysize(0) {
        dynamic_allocator _Al;
        _Mydata = _Al.allocate(_Size);
        _Mysize = _Size;
    }

    pool_resource::~pool_resource() noexcept {
        destroy();
    }

    pool_resource& pool_resource::operator=(const pool_resource& _Other) {
        if (this != ::std::addressof(_Other)) {
            destroy();
            _Copy_resource(_Other._Mydata, _Other._Mysize);
        }

        return *this;
    }

    pool_resource& pool_resource::operator=(pool_resource&& _Other) noexcept {
        if (this != ::std::addressof(_Other)) {
            destroy();
            _Steal_resource(_Other._Mydata, _Other._Mysize);
        }

        return *this;
    }

    void pool_resource::_Copy_resource(const_pointer _Data, const size_type _Size) {
        dynamic_allocator _Al;
        _Mydata = _Al.allocate(_Size);
        _Mysize = _Size;
        ::memcpy(_Mydata, _Data, _Size);
    }

    void pool_resource::_Steal_resource(pointer& _Data, size_type& _Size) noexcept {
        _Mydata = _Data;
        _Mysize = _Size;
        _Data   = nullptr;
        _Size   = 0;
    }

    bool pool_resource::empty() const noexcept {
        return !_Mydata && _Mysize == 0;
    }

    pool_resource::pointer pool_resource::data() noexcept {
        return _Mydata;
    }

    pool_resource::const_pointer pool_resource::data() const noexcept {
        return _Mydata;
    }

    pool_resource::size_type pool_resource::size() const noexcept {
        return _Mysize;
    }

    bool pool_resource::contains(const_pointer _Block, const size_type _Size) const noexcept {
        if (empty() || !_Block || _Size == 0) {
            return false;
        }

        const unsigned char* const _Block_end      = static_cast<const unsigned char*>(_Block) + _Size;
        const unsigned char* const _Root_block_end = static_cast<const unsigned char*>(_Mydata) + _Mysize;
        return _Block >= _Mydata && _Block_end <= _Root_block_end;
    }

    void pool_resource::swap(pool_resource& _Other) noexcept {
        ::std::swap(_Mydata, _Other._Mydata);
        ::std::swap(_Mysize, _Other._Mysize);
    }

    pool_resource::pointer pool_resource::release() noexcept {
        pointer _Old_data = _Mydata;
        _Mydata           = nullptr;
        _Mysize           = 0;
        return _Old_data;
    }

    void pool_resource::destroy() noexcept {
        if (_Mydata && _Mysize > 0) {
            dynamic_allocator _Al;
            _Al.deallocate(_Mydata, _Mysize);
            _Mydata = nullptr;
            _Mysize = 0;
        }
    }

    bool operator==(const pool_resource& _Left, const pool_resource& _Right) {
        return _Left.data() == _Right.data() && _Left.size() == _Right.size();
    }

    bool operator!=(const pool_resource& _Left, const pool_resource& _Right) {
        return !(_Left == _Right);
    }
} // namespace mjx