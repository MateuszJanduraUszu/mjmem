# `unique_smart_ptr`

## Description

Defines a smart pointer with unique object ownership semantics.

## Syntax

```cpp
template <class _Ty>
class unique_smart_ptr {
public:
    using element_type = _Ty;
    using pointer      = _Ty*;

    unique_smart_ptr() noexcept;
    unique_smart_ptr(unique_smart_ptr&& _Other) noexcept;
    ~unique_smart_ptr() noexcept;

    unique_smart_ptr(nullptr_t) noexcept;
    explicit unique_smart_ptr(pointer _Ptr) noexcept;

    unique_smart_ptr& operator=(unique_smart_ptr&& _Other) noexcept;
    unique_smart_ptr& operator=(nullptr_t) noexcept;

    unique_smart_ptr(const unique_smart_ptr&)            = delete;
    unique_smart_ptr& operator=(const unique_smart_ptr&) = delete;

    element_type& operator*() const noexcept(<expr>);
    pointer operator->() const noexcept;
    explicit operator bool() const noexcept;
    pointer get() const noexcept;
    pointer release() noexcept;
    void reset(pointer _New_ptr = nullptr) noexcept;
    void swap(unique_smart_ptr& _Other) noexcept;
};
```

## Member types

| Type         | Definition |
|--------------|------------|
| element_type | _Ty        |
| pointer      | _Ty*       |

## Member functions

- [(constructor)](unique_smart_ptr-ctor.md)
- [(destructor)](unique_smart_ptr-dtor.md)
- [operator=](unique_smart_ptr-operator-assign.md)
- [operator*](unique_smart_ptr-operator-deref.md)
- [operator->](unique_smart_ptr-operator-arrow.md)
- [operator bool](unique_smart_ptr-operator-bool.md)
- [get](unique_smart_ptr-get.md)
- [release](unique_smart_ptr-release.md)
- [reset](unique_smart_ptr-reset.md)
- [swap](unique_smart_ptr-swap.md)

## Member constants

(none)

## Non-member functions

- [operator==](unique_smart_ptr-operator-cmp.md)
- [make_unique_smart_ptr](make_unique_smart_ptr.md)

## Remarks

The class is a wraper around a pointer that ensures the pointer is destroyed when the class is destructed, unless it was released before. 
It does not share ownership of the pointer with other instances, ensuring unique ownership.

## Requirements

| Requirement             | Value                 |
|-------------------------|-----------------------|
| Include header          | `<smart_pointer.hpp>` |
| Minimum library version | `1.0.1`               |
| Maximum library version | `N/A`                 |

## See also

- [unique_smart_array](unique_smart_array.md)
- [smart_array](smart_array.md)
- [smart_ptr](smart_ptr.md)