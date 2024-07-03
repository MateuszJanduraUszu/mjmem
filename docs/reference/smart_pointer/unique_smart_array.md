# `unique_smart_array`

## Description

Defines a smart pointer with unique ownership semantics for arrays.

## Syntax

```cpp
template <class _Ty>
class unique_smart_array {
public:
    using element_type = _Ty;
    using pointer      = _Ty*;

    struct array {
        pointer ptr;
        size_t size;
    };

    unique_smart_array() noexcept;
    unique_smart_array(unique_smart_array&& _Other) noexcept;
    ~unique_smart_array() noexcept;

    unique_smart_array(nullptr_t) noexcept;
    unique_smart_array(pointer _Ptr, const size_t _Size) noexcept;

    unique_smart_array& operator=(unique_smart_array&& _Other) noexcept;
    unique_smart_array& operator=(nullptr_t) noexcept;

    unique_smart_array(const unique_smart_array&)            = delete;
    unique_smart_array& operator=(const unique_smart_array&) = delete;

#if !_MJMEM_VERSION_SUPPORTED(2, 0, 0)
    element_type& operator*() const noexcept;
    pointer operator->() const noexcept;
#endif // !_MJMEM_VERSION_SUPPORTED(2, 0, 0)

    element_type& operator[](const size_t _Idx) const;
    explicit operator bool() const noexcept;
    pointer get() const noexcept;
    size_t size() const noexcept;
    array release() noexcept;
    void reset(pointer _New_ptr, const size_t _New_size) noexcept;
    void reset(nullptr_t = nullptr) noexcept;
    void swap(unique_smart_array& _Other) noexcept;
};
```

## Member types

| Type         | Definition                                                                     |
|--------------|--------------------------------------------------------------------------------|
| element_type | _Ty                                                                            |
| pointer      | _Ty*                                                                           |
| array        | struct array {<br>&emsp;pointer ptr = nullptr;<br>&emsp;size_t size = 0;<br>}; |

## Member functions

- [(constructor)](unique_smart_array-ctor.md)
- [(destructor)](unique_smart_array-dtor.md)
- [operator=](unique_smart_array-operator-assign.md)
- [operator*](unique_smart_array-operator-deref.md)
- [operator->](unique_smart_array-operator-arrow.md)
- [operator[]](unique_smart_array-operator-subscript.md)
- [operator bool](unique_smart_array-operator-bool.md)
- [get](unique_smart_array-get.md)
- [size](unique_smart_array-size.md)
- [release](unique_smart_array-release.md)
- [reset](unique_smart_array-reset.md)
- [swap](unique_smart_array-swap.md)

## Member constants

(none)

## Non-member functions

- [operator==](unique_smart_array-operator-cmp.md)
- [make_unique_smart_array](make_unique_smart_array.md)

## Remarks

The class is a wrapper around an array that ensures the array is destroyed when the class is destructed, unless it was released before. 
It does not share ownership of the array with other instances, ensuring unique ownership.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_ptr](unique_smart_ptr.md)
- [smart_array](smart_array.md)
- [smart_ptr](smart_ptr.md)