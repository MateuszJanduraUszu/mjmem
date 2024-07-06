# `smart_array`

## Description

Defines a smart pointer with shared ownership semantics for arrays.

## Syntax

```cpp
template <class _Ty>
class smart_array {
public:
    using element_type = _Ty;
    using pointer      = _Ty*;

    smart_array() noexcept;
    smart_array(const smart_array& _Other) noexcept;
    smart_array(smart_array&& _Other) noexcept;
    ~smart_array() noexcept;

    smart_array(nullptr_t) noexcept;
    smart_array(pointer _Ptr, const size_t _Size);
    smart_array(unique_smart_array<_Ty>&& _Sarr);

    smart_array& operator=(const smart_array& _Other) noexcept;
    smart_array& operator=(smart_array&& _Other) noexcept;
    smart_array& operator=(unique_smart_array<_Ty>&& _Sarr);

#if !_MJMEM_VERSION_SUPPORTED(2, 0, 0)
    explicit operator bool() const noexcept;
    element_type& operator*() const noexcept;
#endif // !_MJMEM_VERSION_SUPPORTED(2, 0, 0)

    pointer operator->() const noexcept;
    element_type& operator[](const size_t _Idx) const;
    pointer get() const noexcept;

#if _MJMEM_VERSION_SUPPORTED(2, 0, 0)
    size_t size() const noexcept;
#endif // _MJMEM_VERSION_SUPPORTED(2, 0, 0)
    
    long use_count() const noexcept;
    bool unique() const noexcept;
    void reset() noexcept;
    void reset(pointer _New_ptr, const size_t _New_size);
    void swap(smart_array& _Other) noexcept;
};
```

## Member types

| Type         | Definition |
|--------------|------------|
| element_type | _Ty        |
| pointer      | _Ty*       |

## Member functions

- [(constructor)](smart_array-ctor.md)
- [(destructor)](smart_array-dtor.md)
- [operator=](smart_array-operator-assign.md)
- [operator bool](smart_array-operator-bool.md)
- [operator*](smart_array-operator-deref.md)
- [operator->](smart_array-operator-arrow.md)
- [operator[]](smart_array-operator-subscript.md)
- [get](smart_array-get.md)
- [size](smart_array-size.md)
- [use_count](smart_array-use_count.md)
- [unique](smart_array-unique.md)
- [reset](smart_array-reset.md)
- [swap](smart_array-swap.md)

## Member constants

(none)

## Non-member functions

- [operator==](smart_array-operator-cmp.md)
- [make_smart_array](make_smart_array.md)

## Remarks

The class is a wrapper around an array that ensures the array is destroyed when the class is destructed and the array is unique. 
It shares ownership of the array with other instances via reference-counting.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [smart_ptr](smart_ptr.md)
- [unique_smart_array](unique_smart_array.md)
- [unique_smart_ptr](unique_smart_ptr.md)